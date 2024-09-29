/**
 * @file touch_cst836u.c
 * @author Yang (your@email.com)
 * @brief
 * @version 0.1
 * @date 2023-06-21 15:30:18
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "touch_cst836u.h"
#include "stdbool.h"
// #include "xmc_lcd.h"

/* private define -------------------------------------------------------*/
#define CST836U_ADDR            0x15    // 设备地址 7bit
#define CST836U_Chip_ID         0xAA    // chip ID
#define CST836U_Pos_XH          0x03    // X 高4bit
#define CST836U_Pos_XL          0x04    // X 低8bit
#define CST836U_Pos_YH          0x05    // Y 高4bit
#define CST836U_Pos_YL          0x06    // Y 低8bit


//
#define CST836U_X_OFFSET    (0)
#define CST836U_Y_OFFSET    (0)
/* private typedef ------------------------------------------------------*/



/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/
static tp_dev_t* tp_dev_cst836u = NULL;

/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/
static bool cst836u_write_reg(uint16_t reg, uint8_t *buf , uint32_t len)
{
    uint32_t i ;

    // start
    IIC_Start();

    // send addr
    IIC_Send_Byte( CST836U_ADDR << 1 );
    if(IIC_Wait_Ack()){
        goto ret_fail;
    }

    // send reg
    IIC_Send_Byte( reg & 0xFF);
    if(IIC_Wait_Ack()){
        goto ret_fail;
    }

    // write data
    for(i = 0 ; i < len ; i++){
        IIC_Send_Byte( buf[i] );
        if(IIC_Wait_Ack()){
            goto ret_fail;
        }
    }

    // stop
    IIC_Stop();

    return true;

ret_fail:
    return false;
}

static bool cst836u_read_reg(uint16_t reg, uint8_t *buf , uint32_t len)
{
    uint32_t i = 0;

    // start
    IIC_Start();

    // send addr
    IIC_Send_Byte( CST836U_ADDR << 1 );
    if(IIC_Wait_Ack()){
        goto ret_fail;
    }
    // send reg
    IIC_Send_Byte( reg & 0xFF);
    if(IIC_Wait_Ack()){
        goto ret_fail;
    }
    IIC_Stop();
    //
    IIC_Start();
    // read
    IIC_Send_Byte((CST836U_ADDR << 1) | 0x01);
    if(IIC_Wait_Ack()){
        goto ret_fail;
    }
    // read data
    for(i = 0 ; i < len-1 ; i++){
        buf[i] = IIC_Read_Byte(1);
        // IIC_Wait_Ack();
    }
    buf[i] = IIC_Read_Byte(0);
    // IIC_Wait_Ack();
    // stop
    IIC_Stop();

    return true;

ret_fail:
    return false;
}

static bool cst836u_read_point(void)
{
    uint8_t temp[4];
    uint16_t x = 0xFFFF, y = 0xFFFF;

    if(NULL == tp_dev_cst836u){
        return false;
    }

    cst836u_read_reg( CST836U_Pos_XH, &temp[0] , 4);
    // cst836u_read_reg( CST836U_Pos_XL, &temp[1] , 1);
    // cst836u_read_reg( CST836U_Pos_YH, &temp[2] , 1);
    // cst836u_read_reg( CST836U_Pos_YL, &temp[3] , 1);

    x=(uint16_t)((temp[0]&0x0F)<<8)|temp[1];
	y=(uint16_t)((temp[2]&0x0F)<<8)|temp[3];

    tp_dev_cst836u->point.status = temp[0] >> 6;
#if GT_HMI_BOARD_CONFIG_VERTICAL
    tp_dev_cst836u->point.x = GT_SCREEN_WIDTH - y + CST836U_Y_OFFSET;
    tp_dev_cst836u->point.y = x + CST836U_X_OFFSET;
#else
    tp_dev_cst836u->point.x = x + CST836U_X_OFFSET;
    tp_dev_cst836u->point.y = y + CST836U_Y_OFFSET;
#endif

#if TOUCH_LOGD_EN
    printf("touch: x = %d y = %d status = %d\n" , tp_dev_cst836u->point.x , tp_dev_cst836u->point.y , tp_dev_cst836u->point.status);
#endif

#if TOUCH_DRAW_POINT_EN
    lcd_drawpoint( tp_dev_cst836u->point.x , tp_dev_cst836u->point.y , RED);
#endif

    return true;
}

static bool cst836u_read_chipID(void)
{
    uint8_t chip_id[2] = {0};

    if(NULL == tp_dev_cst836u){
        return false;
    }

    cst836u_read_reg( CST836U_Chip_ID, &chip_id[0] , 2);

    tp_dev_cst836u->chipID = chip_id[1] << 8 | chip_id[0];

#if TOUCH_LOGD_EN
    printf("touch id : 0x%X\n" , tp_dev_cst836u->chipID);
#endif

    return true;
}

/* global functions / API interface -------------------------------------*/
void cst836u_init(tp_dev_t *dev)
{
    if(NULL == dev){
        return ;
    }

    dev->read_point = cst836u_read_point;
    tp_dev_cst836u = dev;

    cst836u_read_chipID();
}


/* end of file ----------------------------------------------------------*/


