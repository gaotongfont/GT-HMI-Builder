#ifndef _LCD_SHOW_H_
#define _LCD_SHOW_H_
#include "SWM341.h"
#include "bsp_lcd_rgb.h"
void lcd_draw_point(uint16_t x, uint16_t y, uint32_t c);
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,uint32_t color);
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r);
void LCD_Draw_color_Circle(u16 x0,u16 y0,u8 r,uint32_t c);
#endif // !_LCD_SHOW_H_

