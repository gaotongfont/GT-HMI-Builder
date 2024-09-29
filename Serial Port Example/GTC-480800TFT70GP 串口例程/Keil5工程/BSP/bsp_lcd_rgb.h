/**
 * @file bsp_lcd.h
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-15 09:37:49
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */
#ifndef _BSP_LCD_H_
#define _BSP_LCD_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;



//LCD重要参数集
typedef struct  
{		 	 
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;				//LCD ID
	u8  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	u16	wramcmd;		//开始写gram指令
	u16 setxcmd;		//设置x坐标指令
	u16 setycmd;		//设置y坐标指令 
}_lcd_dev; 	  

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数
extern u32  POINT_COLOR;//默认红色    
extern u32  BACK_COLOR; //背景颜色.默认为白色
/* include --------------------------------------------------------------*/
#include "SWM341.h"

/* define ---------------------------------------------------------------*/
// lcd backlight
#define LCD_BKL_PORT        GPIOD
#define LCD_BKL_PIN         PIN9
// lcd rst
#define LCD_RST_PORT        GPIOD
#define LCD_RST_PIN         PIN1
// lcd b0
#define LCD_B0_PORT         PORTB
#define LCD_B0_PIN          PIN1
#define LCD_B0_SEL          PORTB_PIN1_LCD_B0
// lcd b1
#define LCD_B1_PORT         PORTB
#define LCD_B1_PIN          PIN11
#define LCD_B1_SEL          PORTB_PIN11_LCD_B1
// lcd b2
#define LCD_B2_PORT         PORTB
#define LCD_B2_PIN          PIN13
#define LCD_B2_SEL          PORTB_PIN13_LCD_B2
// lcd b3
#define LCD_B3_PORT         PORTB
#define LCD_B3_PIN          PIN15
#define LCD_B3_SEL          PORTB_PIN15_LCD_B3
// lcd b4
#define LCD_B4_PORT         PORTA
#define LCD_B4_PIN          PIN2
#define LCD_B4_SEL          PORTA_PIN2_LCD_B4
// lcd b5
#define LCD_B5_PORT         PORTA
#define LCD_B5_PIN          PIN9
#define LCD_B5_SEL          PORTA_PIN9_LCD_B5
// lcd b6
#define LCD_B6_PORT         PORTA
#define LCD_B6_PIN          PIN10
#define LCD_B6_SEL          PORTA_PIN10_LCD_B6
// lcd b7
#define LCD_B7_PORT         PORTA
#define LCD_B7_PIN          PIN11
#define LCD_B7_SEL          PORTA_PIN11_LCD_B7
// lcd g0
#define LCD_G0_PORT         PORTA
#define LCD_G0_PIN          PIN12
#define LCD_G0_SEL          PORTA_PIN12_LCD_G0
// lcd g1
#define LCD_G1_PORT         PORTA
#define LCD_G1_PIN          PIN13
#define LCD_G1_SEL          PORTA_PIN13_LCD_G1
// lcd g2
#define LCD_G2_PORT         PORTA
#define LCD_G2_PIN          PIN14
#define LCD_G2_SEL          PORTA_PIN14_LCD_G2
// lcd g3
#define LCD_G3_PORT         PORTA
#define LCD_G3_PIN          PIN15
#define LCD_G3_SEL          PORTA_PIN15_LCD_G3
// lcd g4
#define LCD_G4_PORT         PORTC
#define LCD_G4_PIN          PIN0
#define LCD_G4_SEL          PORTC_PIN0_LCD_G4
// lcd g5
#define LCD_G5_PORT         PORTC
#define LCD_G5_PIN          PIN1
#define LCD_G5_SEL          PORTC_PIN1_LCD_G5
// lcd g6
#define LCD_G6_PORT         PORTC
#define LCD_G6_PIN          PIN2
#define LCD_G6_SEL          PORTC_PIN2_LCD_G6
// lcd g7
#define LCD_G7_PORT         PORTC
#define LCD_G7_PIN          PIN3
#define LCD_G7_SEL          PORTC_PIN3_LCD_G7
// lcd R0
#define LCD_R0_PORT         PORTC
#define LCD_R0_PIN          PIN4
#define LCD_R0_SEL          PORTC_PIN4_LCD_R0
// lcd R1
#define LCD_R1_PORT         PORTC
#define LCD_R1_PIN          PIN5
#define LCD_R1_SEL          PORTC_PIN5_LCD_R1
// lcd R2
#define LCD_R2_PORT         PORTC
#define LCD_R2_PIN          PIN8
#define LCD_R2_SEL          PORTC_PIN8_LCD_R2
// lcd R3
#define LCD_R3_PORT         PORTC
#define LCD_R3_PIN          PIN9
#define LCD_R3_SEL          PORTC_PIN9_LCD_R3
// lcd R4
#define LCD_R4_PORT         PORTC
#define LCD_R4_PIN          PIN10
#define LCD_R4_SEL          PORTC_PIN10_LCD_R4
// lcd R5
#define LCD_R5_PORT         PORTC
#define LCD_R5_PIN          PIN11
#define LCD_R5_SEL          PORTC_PIN11_LCD_R5
// lcd R6
#define LCD_R6_PORT         PORTC
#define LCD_R6_PIN          PIN12
#define LCD_R6_SEL          PORTC_PIN12_LCD_R6
// lcd R7
#define LCD_R7_PORT         PORTC
#define LCD_R7_PIN          PIN13
#define LCD_R7_SEL          PORTC_PIN13_LCD_R7
// lcd vsync / cs
#define LCD_VSYNC_PORT      PORTB
#define LCD_VSYNC_PIN       PIN2
#define LCD_VSYNC_SEL       PORTB_PIN2_LCD_VSYNC
// lcd hsync / wr
#define LCD_HSYNC_PORT      PORTM
#define LCD_HSYNC_PIN       PIN8
#define LCD_HSYNC_SEL       PORTM_PIN8_LCD_HSYNC
// lcd den / rs
#define LCD_DEN_PORT        PORTM
#define LCD_DEN_PIN         PIN11
#define LCD_DEN_SEL         PORTM_PIN11_LCD_DEN
//lcd dclk / rd
#define LCD_DCLK_PORT       PORTB
#define LCD_DCLK_PIN        PIN5
#define LCD_DCLK_SEL        PORTB_PIN5_LCD_DCLK


  
#define LCD_BUF_UT      uint16_t
#define LCD_WIDTH       (800)
#define LCD_HEIGTH      (480)
#define LCD_DIR         (1)     // 1 / 0
//
#define LCD_ClkDiv      (4)
#define LCD_Format      (LCD_FMT_RGB565)
#define LCD_Hfp         (40)
#define LCD_Hbp         (40)
#define LCD_Vfp         (13)
#define LCD_Vbp         (29)
#define LCD_HsyncWidth  (48)
#define LCD_VsyncWidth  (48)




/* typedef --------------------------------------------------------------*/\



/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void bsp_lcd_rgb_init(void);
void LCD_DrawPoint(u16 x,u16 y);
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_BSP_LCD_H_

/* end of file ----------------------------------------------------------*/


