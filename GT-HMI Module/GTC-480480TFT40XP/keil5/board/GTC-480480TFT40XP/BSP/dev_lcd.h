#ifndef __DEV_LCD_H__
#define __DEV_LCD_H__

//----------------------------ͷ�ļ�����----------------------------//
#include "SWM341.h"

#define LCD_HDOT	480		// ??????
#define LCD_VDOT	480		// ???????
#define LCD_DIRH	1		// ???????

#define LCD_WIDTH LCD_HDOT
#define LCD_HEIGHT LCD_VDOT

#define LV_HOR_RES_MAX          480
#define LV_VER_RES_MAX          480
//----------------------------��������----------------------------//
void lcd_init(void);
void MemoryInit(void);
void _HW_DrawPoint(unsigned short x, unsigned short y, unsigned int c);

extern uint16_t *LCD_Buffer;

#endif //__DEV_LCD_H__
