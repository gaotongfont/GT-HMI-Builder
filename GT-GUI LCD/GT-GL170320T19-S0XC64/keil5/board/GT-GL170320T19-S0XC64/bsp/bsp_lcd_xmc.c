/**
 * @file bsp_lcd_xmc.c
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-07 15:41:38
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "bsp_lcd_xmc.h"
#include "bsp_delay.h"


/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/
static void _xmc_init(void)
{
    gpio_init_type  gpio_init_struct = {0}; 
    xmc_norsram_init_type  xmc_norsram_init_struct; 
    xmc_norsram_timing_init_type rw_timing_struct, w_timing_struct; 
    /* enable the gpio clock */
    // crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);
    // crm_periph_clock_enable(CRM_GPIOF_PERIPH_CLOCK, TRUE);

    /* enable the xmc clock */
    crm_periph_clock_enable(CRM_XMC_PERIPH_CLOCK, TRUE); 

    /*-- gpio configuration ------------------------------------------------------*/
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE7, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE13, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE4, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE5, GPIO_MUX_12);

    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE0, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE1, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE14, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOD, GPIO_PINS_SOURCE15, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE7, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE8, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE9, GPIO_MUX_12);
    gpio_pin_mux_config(GPIOE, GPIO_PINS_SOURCE10, GPIO_MUX_12);

    /* ne1/nwe/noe/a0 lines configuration */
    gpio_init_struct.gpio_pins = GPIO_PINS_7 | GPIO_PINS_13 |  GPIO_PINS_4 | GPIO_PINS_5;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOD, &gpio_init_struct);

    /* data lines configuration */
    gpio_init_struct.gpio_pins = GPIO_PINS_0 | GPIO_PINS_1 | GPIO_PINS_14 | GPIO_PINS_15;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOD, &gpio_init_struct);

    gpio_init_struct.gpio_pins = GPIO_PINS_7 | GPIO_PINS_8 | GPIO_PINS_9 | GPIO_PINS_10;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOE, &gpio_init_struct);

    /* lcd reset lines configuration */
    gpio_init_struct.gpio_pins = GPIO_PINS_7;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOC, &gpio_init_struct);

    /* lcd BL lines configuration */
    gpio_init_struct.gpio_pins = GPIO_PINS_6;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOA, &gpio_init_struct);
    /*-- xmc configuration ------------------------------------------------------*/
    xmc_norsram_default_para_init(&xmc_norsram_init_struct); 
    xmc_norsram_init_struct.subbank = XMC_BANK1_NOR_SRAM1; 
    xmc_norsram_init_struct.data_addr_multiplex = XMC_DATA_ADDR_MUX_DISABLE; 
    xmc_norsram_init_struct.device = XMC_DEVICE_SRAM; 
    xmc_norsram_init_struct.bus_type = XMC_BUSTYPE_8_BITS; 
    xmc_norsram_init_struct.burst_mode_enable = XMC_BURST_MODE_DISABLE; 
    xmc_norsram_init_struct.asynwait_enable = XMC_ASYN_WAIT_DISABLE; 
    xmc_norsram_init_struct.wait_signal_lv = XMC_WAIT_SIGNAL_LEVEL_LOW; 
    xmc_norsram_init_struct.wrapped_mode_enable = XMC_WRAPPED_MODE_DISABLE; 
    xmc_norsram_init_struct.wait_signal_config = XMC_WAIT_SIGNAL_SYN_BEFORE; 
    xmc_norsram_init_struct.write_enable = XMC_WRITE_OPERATION_ENABLE; 
    xmc_norsram_init_struct.wait_signal_enable = XMC_WAIT_SIGNAL_DISABLE; 
    xmc_norsram_init_struct.write_timing_enable = XMC_WRITE_TIMING_ENABLE; 
    xmc_norsram_init_struct.write_burst_syn = XMC_WRITE_BURST_SYN_DISABLE; 
    xmc_nor_sram_init(&xmc_norsram_init_struct); 

    /* timing configuration */
    xmc_norsram_timing_default_para_init(&rw_timing_struct, &w_timing_struct); 
    rw_timing_struct.subbank = XMC_BANK1_NOR_SRAM1; 
    rw_timing_struct.write_timing_enable = XMC_WRITE_TIMING_ENABLE; 
    rw_timing_struct.addr_setup_time = 0x2; 
    rw_timing_struct.addr_hold_time = 0x0; 
    rw_timing_struct.data_setup_time = 0x2; 
    rw_timing_struct.bus_latency_time = 0x0; 
    rw_timing_struct.clk_psc = 0x0; 
    rw_timing_struct.data_latency_time = 0x0; 
    rw_timing_struct.mode = XMC_ACCESS_MODE_A; 
    w_timing_struct.subbank = XMC_BANK1_NOR_SRAM1; 
    w_timing_struct.write_timing_enable = XMC_WRITE_TIMING_ENABLE; 
    w_timing_struct.addr_setup_time = 0x2; 
    w_timing_struct.addr_hold_time = 0x0; 
    w_timing_struct.data_setup_time = 0x2; 
    w_timing_struct.bus_latency_time = 0x0; 
    w_timing_struct.clk_psc = 0x0; 
    w_timing_struct.data_latency_time = 0x0; 
    w_timing_struct.mode = XMC_ACCESS_MODE_A;  
    xmc_nor_sram_timing_config(&rw_timing_struct, &w_timing_struct); 

    /* enable xmc_bank1_nor_sram4 */
    xmc_nor_sram_enable(XMC_BANK1_NOR_SRAM1, TRUE);

    

}

static void _lcd_write_cmd(uint8_t cmd)
{
    *(__IO uint8_t *) LCD_XMC_COMMAND = cmd; 
}

static void _lcd_write_data(uint8_t dat)
{
    *(__IO uint8_t *) LCD_XMC_DATA = dat; 
}

static void _lcd_init(void)
{
    /* reset lcd */
    LCD_RESET_HIGH; 
    delay_ms(200); 
    LCD_RESET_LOW; 
    delay_ms(200); 
    LCD_RESET_HIGH; 
    delay_ms(800); 

    _lcd_write_cmd( 0x11);
    delay_ms(120);

    _lcd_write_cmd( 0x36);
    _lcd_write_data(0x60);

    _lcd_write_cmd(0x3A);
    _lcd_write_data( 0x55);

    _lcd_write_cmd( 0xB2);
    _lcd_write_data(0x1F);
    _lcd_write_data(0x1F);
    _lcd_write_data(0x00);
    _lcd_write_data( 0x33);
    _lcd_write_data( 0x33);

    _lcd_write_cmd( 0xB7);
    _lcd_write_data(0x73);   

    _lcd_write_cmd( 0xBB);
    _lcd_write_data( 0x1E);   

    _lcd_write_cmd(0xC0);
    _lcd_write_data( 0x2C);

    _lcd_write_cmd(0xC2);
    _lcd_write_data( 0x01);

    _lcd_write_cmd(0xC3);
    _lcd_write_data(0x13);

    _lcd_write_cmd(0xC4);
    _lcd_write_data(0x20);

    _lcd_write_cmd( 0xC6);
    _lcd_write_data( 0x0F);

    _lcd_write_cmd(0xD0);
    _lcd_write_data(0xA7);
    _lcd_write_data(0xA1);

    _lcd_write_cmd( 0xD0);
    _lcd_write_data( 0xA4);
    _lcd_write_data(0xA1);

    _lcd_write_cmd(0xD6);
    _lcd_write_data( 0xA1);

    _lcd_write_cmd(0xE0);
    _lcd_write_data(0xF0);
    _lcd_write_data(0x0C);
    _lcd_write_data(0x15);
    _lcd_write_data(0x09);
    _lcd_write_data(0x09);
    _lcd_write_data(0x07);
    _lcd_write_data(0x3B);
    _lcd_write_data(0x44);
    _lcd_write_data(0x50);
    _lcd_write_data(0x36);
    _lcd_write_data(0x11);
    _lcd_write_data(0x10);
    _lcd_write_data(0x2F);
    _lcd_write_data(0x35);

    _lcd_write_cmd(0xE1);
    _lcd_write_data(0xF0);
    _lcd_write_data(0x17);
    _lcd_write_data(0x1A);
    _lcd_write_data(0x0C);
    _lcd_write_data(0x0B);
    _lcd_write_data(0x25);
    _lcd_write_data(0x3A);
    _lcd_write_data(0x43);
    _lcd_write_data(0x4F);
    _lcd_write_data(0x19);
    _lcd_write_data(0x15);
    _lcd_write_data(0x16);
    _lcd_write_data(0x30);
    _lcd_write_data(0x37);

    _lcd_write_cmd( 0xe9);
    _lcd_write_data(0x07);
    _lcd_write_data(0x07);
    _lcd_write_data(0x03);	
    _lcd_write_cmd(0xE7);       //Set Gamma 
    _lcd_write_data(0x10);	
    _lcd_write_cmd(0x21);    //inversion

    _lcd_write_cmd(0x29);    //Display on 
    
}

/* global functions / API interface -------------------------------------*/
void bsp_lcd_xmc_init(void)
{
    _xmc_init();
    LCD_BL_HIGH;
    _lcd_init();
    bsp_lcd_clear(0xFFFF);
    LCD_BL_LOW;
}

void bsp_lcd_write_2_data(uint16_t dat)
{
    _lcd_write_data(dat >> 8); 
    _lcd_write_data(dat); 
}

void bsp_lcd_set_block(uint16_t xstart, uint16_t ystart, uint16_t xend, uint16_t yend)
{
    /* set row coordinates */
    _lcd_write_cmd(0x2a); 
    _lcd_write_data(xstart >> 8); 
    _lcd_write_data(xstart); 
    _lcd_write_data(xend >> 8); 
    _lcd_write_data(xend); 

    /* set column coordinates */
    _lcd_write_cmd(0x2b); 
    _lcd_write_data(ystart >> 8); 
    _lcd_write_data(ystart); 
    _lcd_write_data(yend >> 8); 
    _lcd_write_data(yend); 
    /* enable write menory */
    _lcd_write_cmd(0x2c); 
}

void bsp_lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    bsp_lcd_set_block(LCD_XMC_OFFSET_X + x, LCD_XMC_OFFSET_Y + y, LCD_XMC_OFFSET_X + x, LCD_XMC_OFFSET_Y + y); 
    bsp_lcd_write_2_data(color);
}

void bsp_lcd_clear(uint16_t color)
{   
    uint32_t i , len = LCD_XMC_WIDTH * LCD_XMC_HEIGHT; 

    bsp_lcd_set_block(LCD_XMC_OFFSET_X, LCD_XMC_OFFSET_Y, LCD_XMC_OFFSET_X+LCD_XMC_WIDTH-1, LCD_XMC_OFFSET_Y+LCD_XMC_HEIGHT-1); 
    for(i = 0; i < len; i++)
    {
        bsp_lcd_write_2_data(color);
    }
}

void bsp_lcd_frame_fill(uint16_t x, uint16_t y, uint16_t w , uint16_t h , uint16_t color)
{
    uint32_t i , len = w * h; 

    bsp_lcd_set_block(LCD_XMC_OFFSET_X + x, LCD_XMC_OFFSET_Y + y, LCD_XMC_OFFSET_X + x + w - 1, LCD_XMC_OFFSET_Y + y + h - 1); 

    for(i = 0; i < len ; i++)
    {
        bsp_lcd_write_2_data(color);
    }
}



/* end of file ----------------------------------------------------------*/

