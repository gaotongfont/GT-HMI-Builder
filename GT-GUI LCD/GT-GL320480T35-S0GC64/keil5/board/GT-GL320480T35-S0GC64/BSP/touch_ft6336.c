/**
 * @file touch_ft6336.c
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-26 14:51:38
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "touch_ft6336.h"
#include "stdbool.h"
#include "bsp_lcd_xmc.h"


/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/
#define FT6336_DEV_ADDR        0x38    // 设备地址 7bit
#define FT6336_STAT_ADDR       0x02
#define FT6336_XH_1            0x03
#define FT6336_XH_2            0x09
#define FT6336_XH_3            0x0F
#define FT6336_XH_4            0x15

#define TT_MODE_BUFFER_INVALID  0x08
#define TD_STAT_NUMBER_TOUCH    0x07

/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/
static tp_dev_t* tp_dev_ft6336 = NULL;



/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/
static bool ft6336_read_point(void)
{
    uint8_t temp[4][4];
    uint16_t x = 0xFFFF, y = 0xFFFF ;

    if(NULL == tp_dev_ft6336 || NULL == tp_dev_ft6336->read_reg){
        return false;
    }

    // make sure data in buffer is valid
    uint8_t lvalue , count = 0 , point_numb = 0 , i = 0;
    do{
        tp_dev_ft6336->read_reg(FT6336_DEV_ADDR , FT6336_STAT_ADDR , &lvalue , 1);
        if(0x30 == count++){
            return false;
        }

    }while (lvalue & TT_MODE_BUFFER_INVALID);

    tp_dev_ft6336->read_reg(FT6336_DEV_ADDR , FT6336_STAT_ADDR , &lvalue , 1);

    point_numb = (uint8_t)(lvalue & TD_STAT_NUMBER_TOUCH);

    if(0 == point_numb){
        tp_dev_ft6336->point.status = TP_STATE_RELEASED;
        return false;
    }

    if((point_numb >= 5)){
        point_numb = 1;
    }

    const u8 x_base[] = {FT6336_XH_1, FT6336_XH_2, FT6336_XH_3, FT6336_XH_4};

    for(i = 0 ; i < point_numb ; ++i){
        tp_dev_ft6336->read_reg(FT6336_DEV_ADDR , x_base[i] , &temp[i] , 4);
    }

    x = ((uint16_t)(temp[0][0] & 0x0F) << 8) | temp[0][1];
    y = ((uint16_t)(temp[0][2] & 0x0F) << 8) | temp[0][3];
    lvalue = (temp[0][0] >> 6) & 0x03;


    tp_dev_ft6336->point.x = x;
    tp_dev_ft6336->point.y = y;
    tp_dev_ft6336->point.status = lvalue;

#if TOUCH_LOGD_EN
    printf("touch: x = %d y = %d status = %d\r\n" , tp_dev_ft6336->point.x , tp_dev_ft6336->point.y , tp_dev_ft6336->point.status);
#endif 

#if TOUCH_DRAW_POINT_EN 
    bsp_lcd_draw_point( tp_dev_ft6336->point.x , tp_dev_ft6336->point.y , 0xF800);
#endif

    return true;
}


/* global functions / API interface -------------------------------------*/
void ft6336_init(tp_dev_t *dev)
{
    if(NULL == dev){
        return ;
    }

    tp_dev_ft6336 = dev;
    dev->read_point = ft6336_read_point;//函数指针指向read point函数
}


/* end of file ----------------------------------------------------------*/


