/**
 * @file bsp_lcd_rgb.c
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-15 10:02:35
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "bsp_lcd_rgb.h"


 _lcd_dev lcddev;	//管理LCD重要参数
 u32  POINT_COLOR;//默认红色    
 u32  BACK_COLOR; //背景颜色.默认为白色
/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/
LCD_BUF_UT *_LCD_Buffer = (LCD_BUF_UT *)SDRAMM_BASE;


/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/
static void _bsp_lcd_gpio_config(void)
{
    uint32_t i;
	
	GPIO_Init(LCD_BKL_PORT, LCD_BKL_PIN, 1, 0, 0, 0);		//背光
	GPIO_SetBit(LCD_BKL_PORT, LCD_BKL_PIN);
	GPIO_Init(LCD_RST_PORT, LCD_RST_PIN, 1, 0, 0, 0);         //复位
	GPIO_ClrBit(LCD_RST_PORT, LCD_RST_PIN);
	for(i = 0; i < 1000000; i++) __NOP();
	GPIO_SetBit(LCD_RST_PORT, LCD_RST_PIN);
	for(i = 0; i < 1000000; i++) __NOP();
	
	PORT_Init(LCD_B0_PORT, LCD_B0_PIN, LCD_B0_SEL, 0);
	PORT_Init(LCD_B1_PORT, LCD_B1_PIN, LCD_B1_SEL, 0);
	PORT_Init(LCD_B2_PORT, LCD_B2_PIN, LCD_B2_SEL, 0);
	PORT_Init(LCD_B3_PORT, LCD_B3_PIN, LCD_B3_SEL, 0);
	PORT_Init(LCD_B4_PORT, LCD_B4_PIN, LCD_B4_SEL, 0);
	PORT_Init(LCD_B5_PORT, LCD_B5_PIN, LCD_B5_SEL, 0);
	PORT_Init(LCD_B6_PORT, LCD_B6_PIN, LCD_B6_SEL, 0);
	PORT_Init(LCD_B7_PORT, LCD_B7_PIN, LCD_B7_SEL, 0);
	PORT_Init(LCD_G0_PORT, LCD_G0_PIN, LCD_G0_SEL, 0);
	PORT_Init(LCD_G1_PORT, LCD_G1_PIN, LCD_G1_SEL, 0);
	PORT_Init(LCD_G2_PORT, LCD_G2_PIN, LCD_G2_SEL, 0);
	PORT_Init(LCD_G3_PORT, LCD_G3_PIN, LCD_G3_SEL, 0);
	PORT_Init(LCD_G4_PORT, LCD_G4_PIN, LCD_G4_SEL, 0);
	PORT_Init(LCD_G5_PORT, LCD_G5_PIN, LCD_G5_SEL, 0);
	PORT_Init(LCD_G6_PORT, LCD_G6_PIN, LCD_G6_SEL, 0);
	PORT_Init(LCD_G7_PORT, LCD_G7_PIN, LCD_G7_SEL, 0);
	PORT_Init(LCD_R0_PORT, LCD_R0_PIN, LCD_R0_SEL, 0);
	PORT_Init(LCD_R1_PORT, LCD_R1_PIN, LCD_R1_SEL, 0);
	PORT_Init(LCD_R2_PORT, LCD_R2_PIN, LCD_R2_SEL, 0);
	PORT_Init(LCD_R3_PORT, LCD_R3_PIN, LCD_R3_SEL, 0);
	PORT_Init(LCD_R4_PORT, LCD_R4_PIN, LCD_R4_SEL, 0);
	PORT_Init(LCD_R5_PORT, LCD_R5_PIN, LCD_R5_SEL, 0);
	PORT_Init(LCD_R6_PORT, LCD_R6_PIN, LCD_R6_SEL, 0);
	PORT_Init(LCD_R7_PORT, LCD_R7_PIN, LCD_R7_SEL, 0);

	PORT_Init(LCD_VSYNC_PORT, LCD_VSYNC_PIN, LCD_VSYNC_SEL, 0);
	PORT_Init(LCD_HSYNC_PORT, LCD_HSYNC_PIN, LCD_HSYNC_SEL, 0);
	PORT_Init(LCD_DEN_PORT  , LCD_DEN_PIN  , LCD_DEN_SEL  , 0);
	PORT_Init(LCD_DCLK_PORT , LCD_DCLK_PIN , LCD_DCLK_SEL , 0);
}


void _lcd_init_sturct()
{
	LCD_InitStructure LCD_initStruct;

	LCD_initStruct.ClkDiv = LCD_ClkDiv;
	LCD_initStruct.Format = LCD_Format;
	LCD_initStruct.HnPixel = LCD_WIDTH;
	LCD_initStruct.VnPixel = LCD_HEIGTH;
	LCD_initStruct.Hfp = LCD_Hfp;
	LCD_initStruct.Hbp = LCD_Hbp;
	LCD_initStruct.Vfp = LCD_Vfp;
	LCD_initStruct.Vbp = LCD_Vbp;
	LCD_initStruct.HsyncWidth = LCD_HsyncWidth;
	LCD_initStruct.VsyncWidth = LCD_VsyncWidth;
	LCD_initStruct.DataSource = (uint32_t)_LCD_Buffer;
	LCD_initStruct.Background = 0xFFFF;
	LCD_initStruct.SampleEdge = LCD_SAMPLE_RISE;	// ATK-4342 RGBLCD 下降沿采样
	LCD_initStruct.IntEOTEn = 1;
	LCD_Init(LCD, &LCD_initStruct);

}

static void _MemoryInit(void)
{
	SDRAM_InitStructure SDRAM_InitStruct;
	
	PORT_Init(PORTM, PIN13, PORTM_PIN13_SDR_CLK, 0);
	PORT_Init(PORTM, PIN14, PORTM_PIN14_SDR_CKE, 0);
	PORT_Init(PORTB, PIN7,  PORTB_PIN7_SDR_WE,   0);
	PORT_Init(PORTB, PIN8,  PORTB_PIN8_SDR_CAS,  0);
	PORT_Init(PORTB, PIN9,  PORTB_PIN9_SDR_RAS,  0);
	PORT_Init(PORTB, PIN10, PORTB_PIN10_SDR_CS,  0);
	PORT_Init(PORTE, PIN15, PORTE_PIN15_SDR_BA0, 0);
	PORT_Init(PORTE, PIN14, PORTE_PIN14_SDR_BA1, 0);
	PORT_Init(PORTN, PIN14, PORTN_PIN14_SDR_A0,  0);
	PORT_Init(PORTN, PIN13, PORTN_PIN13_SDR_A1,  0);
	PORT_Init(PORTN, PIN12, PORTN_PIN12_SDR_A2,  0);
	PORT_Init(PORTN, PIN11, PORTN_PIN11_SDR_A3,  0);
	PORT_Init(PORTN, PIN10, PORTN_PIN10_SDR_A4,  0);
	PORT_Init(PORTN, PIN9,  PORTN_PIN9_SDR_A5,   0);
	PORT_Init(PORTN, PIN8,  PORTN_PIN8_SDR_A6,   0);
	PORT_Init(PORTN, PIN7,  PORTN_PIN7_SDR_A7,   0);
	PORT_Init(PORTN, PIN6,  PORTN_PIN6_SDR_A8,   0);
	PORT_Init(PORTN, PIN3,  PORTN_PIN3_SDR_A9,   0);
	PORT_Init(PORTN, PIN15, PORTN_PIN15_SDR_A10, 0);
	PORT_Init(PORTN, PIN2,  PORTN_PIN2_SDR_A11,  0);
	PORT_Init(PORTM, PIN15, PORTM_PIN15_SDR_A12, 0);
	PORT_Init(PORTE, PIN7,  PORTE_PIN7_SDR_D0,   1);
	PORT_Init(PORTE, PIN6,  PORTE_PIN6_SDR_D1,   1);
	PORT_Init(PORTE, PIN5,  PORTE_PIN5_SDR_D2,   1);
	PORT_Init(PORTE, PIN4,  PORTE_PIN4_SDR_D3,   1);
	PORT_Init(PORTE, PIN3,  PORTE_PIN3_SDR_D4,   1);
	PORT_Init(PORTE, PIN2,  PORTE_PIN2_SDR_D5,   1);
	PORT_Init(PORTE, PIN1,  PORTE_PIN1_SDR_D6,   1);
	PORT_Init(PORTE, PIN0,  PORTE_PIN0_SDR_D7,   1);
	PORT_Init(PORTE, PIN8,  PORTE_PIN8_SDR_D8,   1);
	PORT_Init(PORTE, PIN9,  PORTE_PIN9_SDR_D9,   1);
	PORT_Init(PORTE, PIN10, PORTE_PIN10_SDR_D10, 1);
	PORT_Init(PORTE, PIN11, PORTE_PIN11_SDR_D11, 1);
	PORT_Init(PORTE, PIN12, PORTE_PIN12_SDR_D12, 1);
	PORT_Init(PORTE, PIN13, PORTE_PIN13_SDR_D13, 1);
	PORT_Init(PORTC, PIN14, PORTC_PIN14_SDR_D14, 1);
	PORT_Init(PORTC, PIN15, PORTC_PIN15_SDR_D15, 1);
	PORT_Init(PORTB, PIN6,  PORTB_PIN6_SDR_LDQM, 0);
	PORT_Init(PORTM, PIN12, PORTM_PIN12_SDR_UDQM,0);
	
	SDRAM_InitStruct.Size = SDRAM_SIZE_8MB;
	SDRAM_InitStruct.ClkDiv = SDRAM_CLKDIV_1;
	SDRAM_InitStruct.CASLatency = SDRAM_CASLATENCY_2;
	SDRAM_InitStruct.TimeTRP  = SDRAM_TRP_3;
	SDRAM_InitStruct.TimeTRCD = SDRAM_TRCD_3;
	SDRAM_InitStruct.TimeTRFC  = SDRAM_TRFC_16;
	SDRAM_Init(&SDRAM_InitStruct);
}

void LCD_Handler(void)
{
	LCD_INTClr(LCD);
	
	LCD_Start(LCD);
}

/* global functions / API interface -------------------------------------*/
void bsp_lcd_rgb_init(void)
{	
	_MemoryInit();
	_bsp_lcd_gpio_config();
	_lcd_init_sturct();
	LCD_Start(LCD);
}

void lcd_draw_point(uint16_t x, uint16_t y, uint32_t c)
{	
#if LCD_DIR
	_LCD_Buffer[y * LCD_WIDTH + x] = c;
#else
	_LCD_Buffer[(LCD_HEIGTH - x) * LCD_WIDTH + y] = c;
#endif
}

/* end of file ----------------------------------------------------------*/
void LCD_DrawPoint(u16 x,u16 y)
{

	lcd_draw_point(x,y,POINT_COLOR);
	
}



