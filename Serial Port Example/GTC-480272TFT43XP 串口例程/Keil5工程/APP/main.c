#include "SWM341.h"
#include "bsp_led.h"
#include "bsp_lcd_rgb.h"
#include "bsp_sfc.h"
#include "bsp_uart.h"
#include "ugui.h"
#include "dev_systick.h"
#include "dev_touch.h"
#include "touch.h"
#include "lcd_show.h"
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

	ReadAddr = *(data_write + 1) << 16;
	ReadAddr += *(data_write + 2) << 8;
	ReadAddr += *(data_write + 3);

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


extern uint16_t * _LCD_Buffer;
void _flush_cb(struct _gt_disp_drv_s * drv, gt_area_st * area, gt_color_t * color) {
	uint32_t x = 0, y, j = 0;
	uint32_t indx = 0;
	//	uint32_t _color;
	uint16_t * p = &_LCD_Buffer[(area->y) * LCD_WIDTH + (area->x)];
	uint32_t step = LCD_WIDTH - area->w;
	for (y = 0; y < area->h; y++) {
		for (x = 0; x < area->w; x++) {

			*p = color->full;
			color++;
			p++;
		}
		p += step;
	}
	return;
}

void read_cb(struct _gt_indev_drv_s * indev_drv, gt_indev_data_st * data) {
	if (!TP_Scan(0)) {
		data->state = GT_INDEV_STATE_RELEASED;
		return;
	}
	data->point.x = tp_dev.x[0];
	data->point.y = tp_dev.y[0];

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
	bsp_sfc_config(1);
	bsp_lcd_rgb_init();
	systick_init();
	TP_Init();

	TIMR_Init(TIMR4, TIMR_MODE_TIMER, CyclesPerUs, 1000, 1);
	TIMR_Start(TIMR4);
	GT_Font_Init();
	gt_init();

	gt_ui_init();

	while (1) {
		gt_task_handler();
		swm_delay_ms(1);
		// WDT_Feed(WDT);
		if(uart_status)//串口是否接收数据
		{
			uart_status=0;
			Refresh_New_Page(UART_BUF);	//更新页面
			for(int i=0;i<8;i++)
				printf("%#x ",UART_BUF[i]);
			printf("\r\n");
			memset(UART_BUF,0,8);//清空缓存区
		}
		if(update_sreen_status)//屏幕界面是否有变化
		{
			update_sreen_status=0;
			send_pack();//发送变化后的数值
		}
#if _RUNNING_PRINT
		if (_cnt >= 1000) {
			_cnt = 0;
			GT_LOGI(GT_LOG_TAG_TEST, "tick: %d s", gt_tick_get() / 1000);
		}
#endif
	}
}




