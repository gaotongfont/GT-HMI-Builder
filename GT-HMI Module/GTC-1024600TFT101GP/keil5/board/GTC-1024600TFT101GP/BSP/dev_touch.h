#ifndef __DEV_TOUCH_H__
#define __DEV_TOUCH_H__
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef char BOOL;
#define TRUE 1
#define FALSE 0

#include "../GT-HMI-Engine/src/gt_conf.h"

#define LCD_HDOT	GT_SCREEN_WIDTH
#define LCD_VDOT	GT_SCREEN_HEIGHT
#define LCD_DIRH	1

// #define LCD_TYPE    1


//----------------------------头文件依赖----------------------------//

//----------------------------宏定义----------------------------//
//端口配置
#define TP_GPIO_RST 		GPIOA
#define TP_PIN_RST 			PIN5

#define TP_GPIO_INT 		GPIOD
#define TP_PIN_INT 			PIN0

#define TP_PORT_SCL 		PORTA
#define TP_PIN_SCL 			PIN1
#define TP_PIN_SCL_FUN 		PORTA_PIN1_I2C0_SCL

#define TP_PORT_SDA 		PORTA
#define TP_PIN_SDA 			PIN0
#define TP_PIN_SDA_FUN 		PORTA_PIN0_I2C0_SDA


#define TP_PRES_DOWN 		(0x80) //触屏被按下
#define TP_CATH_PRES 		(0x40) //有按键按下
#define TP_MAX_TOUCH 		(5)    //电容屏支持的点数,固定为5点

//----------------------------类型声明----------------------------//
//触摸屏控制器
typedef struct
{
    uint16_t x[TP_MAX_TOUCH]; //当前坐标
    uint16_t y[TP_MAX_TOUCH]; //电容屏有最多5组坐标
    uint8_t status;           //笔的状态
                              //b7:按下1/松开0;
                              //b6~b5:保留
                              //b4~b0:电容触摸屏按下的点数(0,表示未按下,1表示按下)
	uint8_t touchtype;//电阻屏或者电容屏类型
} tp_dev_t;

//----------------------------外部变量----------------------------//
extern tp_dev_t TP_Dev;
extern volatile BOOL Boot_Video_Flag;

//----------------------------函数定义----------------------------//
void touch_ic_init(void);
void touch_read_points(void);

#endif //__DEV_TOUCH_H__
