#include "SWM341.h"
#include "bsp_led.h"
#include "bsp_lcd_rgb.h"
#include "bsp_sfc.h"
#include "bsp_uart.h"
#include "dev_sdio.h"
#include "dev_systick.h"
#include "dev_touch.h"
#include "gt911.h"
#include "gt911.h"

#include "gt.h"
#include "gt_ui.h"

/** Print serial port information regularly */
#define _RUNNING_PRINT 		0

#if _RUNNING_PRINT
static size_t _cnt = 0;
#endif

void TIMR4_Handler(void)
{
	TIMR_INTClr(TIMR4);
	gt_tick_inc(1);
#if _RUNNING_PRINT
	++_cnt;
#endif
}

uint32_t spi_wr(uint8_t * data_write, uint32_t len_write, uint8_t * data_read, uint32_t len_read)
{
	unsigned long ReadAddr;
	unsigned long addr, len;
	uint8_t cnt = 0;
	uint32_t x, j = 0;

	ReadAddr = *(data_write + 1) << 16;					//高八位地址
	ReadAddr += *(data_write + 2) << 8;				//中八位地址
	ReadAddr += *(data_write + 3);						//低八位地址

	cnt = ReadAddr % 4;
	if (cnt == 0) {
		addr = ReadAddr;
	}
	else {
		addr = ReadAddr - cnt;
	}

	len = len_read + cnt;
	if (len % 4 != 0) {
		len = len + 4 - (len % 4);
	}

	memcpy((volatile unsigned int *)0x80368000, (volatile unsigned int *)(0x70000000 + addr), len);
	memcpy(data_read, (volatile unsigned int *)(0x80368000 + cnt), len_read);

	return 1;
}

extern LCD_BUF_UT * _LCD_Buffer;

//横屏刷新
void _flush_cb(struct _gt_disp_drv_s * drv, gt_area_st * area, gt_color_t * color) {
#if GT_HMI_BOARD_CONFIG_VERTICAL
	uint32_t x = 0, y = 0;

	for (y = 0; y < area->h; y++) {
		for (x = 0; x < area->w ; x++) {
			_LCD_Buffer[(LCD_HEIGTH - (x + area->x)-1) * LCD_WIDTH + (y + area->y)] = color->full;
			color++;
		}
	}
#else
	uint16_t * p = &_LCD_Buffer[(area->y) * LCD_WIDTH + (area->x)];
	uint16_t x = 0, y = 0;
	uint16_t width_full = LCD_WIDTH;

	if (area->w == LCD_WIDTH) {
		memcpy(p, color, area->w * area->h << 1);
	}
	else {
		for (y = 0; y < area->h; y++) {
			memcpy(p, color, area->w << 1);
			p += width_full;
			color += (area->w);
		}
	}
#endif
}

void read_cb(struct _gt_indev_drv_s * indev_drv, gt_indev_data_st * data) {
	if (!GT911_Scan(0)) {
		data->state = GT_INDEV_STATE_RELEASED;
		return;
	}

#if GT_HMI_BOARD_CONFIG_VERTICAL
	data->point.x = LCD_HEIGTH - TP_Dev.y[0];
	data->point.y = TP_Dev.x[0];
#else
	data->point.x = TP_Dev.x[0];
	data->point.y = TP_Dev.y[0];
#endif
	data->state = GT_INDEV_STATE_PRESSED;
}

void read_cb_btn(struct _gt_indev_drv_s * indev_drv, gt_indev_data_st * data)
{
	uint8_t status = 0;
	//status = KEY_Scan(1);
	if (status) {
		data->btn_id = status;
		data->state = GT_INDEV_STATE_PRESSED;
	}
	else {
		data->state = GT_INDEV_STATE_RELEASED;
	}
}


uint8_t HexToChar(uint8_t temp)
{
	uint8_t dst;
	if (temp < 10) {
		dst = temp + '0';
	}
	else {
		dst = temp - 10 + 'A';
	}
	return dst;
}


int main(void)
{

	SystemInit();
	__enable_irq();
	bsp_uart0_init();
	bsp_uart3_init();
	bsp_lcd_rgb_init();
	systick_init();

	SFC_QuadSwitch(1);
	bsp_sfc_config(4);
	SFC_ReadJEDEC();

	GT911_Init();

	TIMR_Init(TIMR4, TIMR_MODE_TIMER, CyclesPerUs, 1000, 1); //每1ms触发一次中断
	TIMR_Start(TIMR4);


	gt_init();

	memset((volatile unsigned int *)0x80000000, 0x00, LCD_WIDTH * LCD_HEIGTH * 4);	//刷黑屏
	GT_Font_Init();
	gt_ui_init();

	if(SYS->RSTSR & SYS_RSTSR_WDT_Msk)
	{
		SYS->RSTSR = (1 << SYS_RSTSR_WDT_Pos);
		printf("WDT Reset Happened\r\n");
	}
	WDT_Init(WDT, 0, 2 * 1024);
	WDT_Start(WDT);

	while (1) {
		gt_task_handler();
		swm_delay_ms(1);
		WDT_Feed(WDT);

#if _RUNNING_PRINT
		if (_cnt >= 1000) {
			_cnt = 0;
			GT_LOGI(GT_LOG_TAG_TEST, "tick: %d s", gt_tick_get() / 1000);
		}
#endif
	}
}




