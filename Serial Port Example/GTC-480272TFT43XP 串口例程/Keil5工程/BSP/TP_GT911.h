#ifndef __TP_GT911_H__
#define __TP_GT911_H__

//----------------------------头文件依赖----------------------------//
#include "dev_touch.h"
#define LCD_HDOT		(800)		// 水平点数
#define LCD_VDOT		(480)		// 垂直点数

#define LV_HOR_RES_MAX          LCD_HDOT
#define LV_VER_RES_MAX          LCD_VDOT
//----------------------------函数定义----------------------------//
uint8_t gt9x_init(void);
uint8_t gt9x_read_points(tp_dev_t *tp_dev);

#endif //__TP_GT911_H__
