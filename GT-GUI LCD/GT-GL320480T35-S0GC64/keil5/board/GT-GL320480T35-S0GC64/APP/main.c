/**
  **************************************************************************
  * @file     main.c
  * @brief    main program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#include "at32f435_437_clock.h"
#include "bsp_led.h"
#include "bsp_uart.h"
#include "bsp_delay.h"
#include "bsp_qspi_flash.h"
#include "bsp_lcd_xmc.h"
#include "touch.h"

tp_dev_t *tp_dev;
/* --------------------------------------------------------------------------*/
#include "gt.h"
#include "gt_ui.h"

uint32_t spi_wr(uint8_t * data_write, uint32_t len_write, uint8_t * data_read, uint32_t len_read)
{
    uint32_t ReadAddr;
	ReadAddr = *(data_write + 1) << 16;					//高八位地址
	ReadAddr += *(data_write + 2) << 8;				//中八位地址
	ReadAddr += *(data_write + 3);						//低八位地址

    bsp_qspi_flash_read(ReadAddr , len_read , data_read);
    return 1;
}

void _flush_cb(struct _gt_disp_drv_s * drv, gt_area_st * area, gt_color_t * color)
{
    gt_size_t x=area->x,y=area->y;
	uint16_t w = area->w,h = area->h;
	uint32_t i = 0 , len = w*h;

    bsp_lcd_set_block(LCD_XMC_OFFSET_X + x, LCD_XMC_OFFSET_Y + y, LCD_XMC_OFFSET_X + x + w - 1, LCD_XMC_OFFSET_Y + y + h - 1);

    for(i = 0 ; i < len ; ++i)
    {
        bsp_lcd_write_2_data(color->full);
        color++;
    }

}

void read_cb(struct _gt_indev_drv_s * indev_drv, gt_indev_data_st * data)
{
	// GT_LOGD(GT_LOG_TAG_TP , "point in: x: %d , y: %d , state = %d\r\n", data->point.x , data->point.y , data->state);

    if(!tp_dev->read_point()){
		data->state = GT_INDEV_STATE_RELEASED;
        data->point.x = tp_dev->point.x;
        data->point.y = tp_dev->point.y;
		return;
	}
    data->point.x = tp_dev->point.x;
	data->point.y = tp_dev->point.y;
	data->state = tp_dev->point.status == TP_STATE_RELEASED ? GT_INDEV_STATE_RELEASED : GT_INDEV_STATE_PRESSED;

	// GT_LOGD(GT_LOG_TAG_TP , "point: x: %d , y: %d , state = %d\r\n", data->point.x , data->point.y , data->state);
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

void time_init(void)
{
	crm_clocks_freq_type crm_clocks_freq_struct = {0};
	/* enable tmr1 clock */
    crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);

    /* get system clock */
    crm_clocks_freq_get(&crm_clocks_freq_struct);
    /* tmr1 configuration */
    /* time base configuration */
    tmr_base_init(TMR1, (10-1), (crm_clocks_freq_struct.apb2_freq * 2 / 10000) - 1);
    tmr_cnt_dir_set(TMR1, TMR_COUNT_UP);

    /* overflow interrupt enable */
    tmr_interrupt_enable(TMR1, TMR_OVF_INT, TRUE);

    /* tmr1 hall interrupt nvic init */
    //  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
    nvic_irq_enable(TMR1_OVF_TMR10_IRQn, 1, 0);

    /* enable tmr1 */
    tmr_counter_enable(TMR1, TRUE);
}

void TMR1_OVF_TMR10_IRQHandler(void)
{
    if(tmr_flag_get(TMR1, TMR_OVF_FLAG) == SET)
    {
        gt_tick_inc(1);
        tmr_flag_clear(TMR1, TMR_OVF_FLAG);
    }
}
/* --------------------------------------------------------------------------*/

/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void)
{
	/* config vector table offset */
	nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x20000);

	system_clock_config();
	/* config nvic priority group */
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
	__enable_irq();
	delay_init();
	bsp_led_init(LED_ALL);
	bsp_uart_init(UART_1);
	bsp_qspi_flash_init();
    bsp_lcd_xmc_init();
    tp_dev = touch_init();

    //
    time_init();
    //
	GT_Font_Init();
	gt_init();
	gt_ui_init();

	while(1)
	{
		gt_task_handler();
		delay_ms(1);
	}
}

/**
  * @}
  */

/**
  * @}
  */
