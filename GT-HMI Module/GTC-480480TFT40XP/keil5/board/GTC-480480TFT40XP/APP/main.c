#include <string.h>
#include "stdio.h"
#include "SWM341.h"
#include "dev_lcd.h"
#include "dev_touch.h"
#include "dev_systick.h"
#include "gt911.h"
#include "bsp_sfc.h"
#include "gt.h"
#include "gt_ui.h"


void _flush_cb(struct _gt_disp_drv_s * drv, gt_area_st * area, gt_color_t * color) {
    uint16_t x=0,y=0;
    uint16_t * p = &LCD_Buffer[( area->y) * LCD_WIDTH + ( area->x)];
    uint16_t step = LCD_WIDTH;
    if(area->w==LCD_WIDTH) {
        memcpy(p, color, area->w * area->h << 1);
    } else {
        for (y = 0; y < area->h; y++) {
            memcpy(p, color, area->w << 1);
            p+=step;
            color+=area->w;
        }
    }
}


void read_cb(struct _gt_indev_drv_s * indev_drv, gt_indev_data_st * data) {
    if (!TP_Dev.scan()) {
        data->state = GT_INDEV_STATE_RELEASED;
        return;
    }
    data->point.x = TP_Dev.x[0];
    data->point.y = TP_Dev.y[0];
    data->state = GT_INDEV_STATE_PRESSED;
}



uint32_t spi_wr(uint8_t * data_write, uint32_t len_write, uint8_t * data_read, uint32_t len_read)
{
    unsigned long ReadAddr;
    unsigned long addr,len;
    uint8_t cnt=0;
    uint32_t x,j=0;

    ReadAddr = *(data_write+1)<<16;
    ReadAddr +=  *(data_write+2)<<8;
    ReadAddr +=  *(data_write+3);

    cnt = ReadAddr%4;
    if(cnt == 0){
        addr = ReadAddr;
    }else{
        addr = ReadAddr - cnt;
    }

    len = len_read + cnt;
    if(len % 4 != 0){
        len = len + 4 - (len%4);
    }

    memcpy((volatile unsigned int *)0x80368000,(volatile unsigned int *)(0x70000000+addr),len);
    memcpy(data_read,(volatile unsigned int *)(0x80368000+cnt),len_read);

    return 1;
}

void read_cb_btn(struct _gt_indev_drv_s * indev_drv, gt_indev_data_st * data)
{

}



int main(void)
{
    unsigned short col = 0x7E0;
    int i,j;
    SystemInit();
    SerialInit();
    systick_init();
    bsp_sfc_config(4);
    GT911_Init();
    MemoryInit();
    lcd_init();
    LCD_Start(LCD);
    TIMR_Init(TIMR4, TIMR_MODE_TIMER, CyclesPerUs, 1000, 1);
    TIMR_Start(TIMR4);
    GT_Font_Init();
    gt_init();

    gt_ui_init();
    while(1)
    {
        gt_task_handler();
        swm_delay_ms(1);
    }
}


void TIMR4_Handler(void)
{
    TIMR_INTClr(TIMR4);
    gt_tick_inc(1);
}


