/**
 * @file touch_bl6133.c
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-14 15:37:33
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */
/********触摸用贝特莱得IC*************/
/* include --------------------------------------------------------------*/
#include "touch_bl6133.h"
#include "stdbool.h"
#include "bsp_lcd_xmc.h"

#if BL6133_UPDATE_EN
    #include "touch_bl6133_fwbin.h"
#endif

/* private define -------------------------------------------------------*/
#define BL6133_ADDR            0x2C    // 设备地址 7bit
#define BL6133_Chip_ID         0xE7    // chip ID
#define BL6133_Gesture         0x01    // Gesture Code
#define BL6133_Point_Numb      0x02    // Point Number
#define BL6133_Pos_XH          0x03    // X 高4bit
#define BL6133_Pos_XL          0x04    // X 低8bit
#define BL6133_Pos_YH          0x05    // Y 高4bit
#define BL6133_Pos_YL          0x06    // Y 低8bit
//
#define BL6133_X_OFFSET    (0)
#define BL6133_Y_OFFSET    (0)

// ctp type
#define SELF_CTP                    0x00
#define COMPATIBLE_CTP              0x01
#define SELF_INTERACTIVE_CTP        0x02
#define CTP_TYPE                SELF_CTP

#define BTL_ARGUMENT_BASE_OFFSET	0x200

/* private typedef ------------------------------------------------------*/
enum firmware_file_type{
	
	HEADER_FILE_UPDATE		= 0x00,
	BIN_FILE_UPDATE		= 0x01,
};

enum update_type{
	
	NONE_UPDATE		= 0x00,
	FW_ARG_UPDATE   = 0x01,
};

/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/
static tp_dev_t* tp_dev_bl6133 = NULL;


/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/
static bool bl6133_read_point(void)
{
    uint8_t temp[6];
    uint16_t x = 0xFFFF, y = 0xFFFF ;

    if(NULL == tp_dev_bl6133 || NULL == tp_dev_bl6133->read_reg){
        return false;
    }

    tp_dev_bl6133->read_reg( BL6133_ADDR , BL6133_Gesture, &temp[0] , 6);//读寄存器

    x=(uint16_t)((temp[2]&0x0F)<<8)|temp[3];
	y=(uint16_t)((temp[4]&0x0F)<<8)|temp[5];

    tp_dev_bl6133->point.status = temp[2] >> 6 ;
    
    tp_dev_bl6133->point.x = x + BL6133_X_OFFSET;
    tp_dev_bl6133->point.y = y + BL6133_Y_OFFSET;

#if TOUCH_LOGD_EN
    printf("touch: x = %d y = %d status = %d\r\n" , tp_dev_bl6133->point.x , tp_dev_bl6133->point.y , tp_dev_bl6133->point.status);
#endif 

#if TOUCH_DRAW_POINT_EN 
    bsp_lcd_draw_point( tp_dev_bl6133->point.x , tp_dev_bl6133->point.y , 0xF800);
#endif

    return true;
}
/*********读ID**********/
static bool bl6133_read_chipID(void)
{

    return false;
}

//

static int bl6133_auto_update(void)
{
    int ret = 0;

    return ret;
}

/* global functions / API interface -------------------------------------*/

void bl6133_init(tp_dev_t *dev)
{
    if(NULL == dev){
        return ;
    }

    dev->read_point = bl6133_read_point;//函数指针指向read point函数
    tp_dev_bl6133 = dev;

    bl6133_read_chipID();//读ID

    bl6133_auto_update();//更新固件，没有写

}

/* end of file ----------------------------------------------------------*/


