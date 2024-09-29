/**
 * @file bsp_led.c
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-04 15:46:33
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "bsp_led.h"


/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/
static const bsp_gpio_st _led_info[LED_ALL] = {
    {.port = GPIOE , .pin = GPIO_PINS_1 , .state = FALSE, .crm_clk = CRM_GPIOE_PERIPH_CLOCK},
    {.port = GPIOE , .pin = GPIO_PINS_0 , .state = FALSE, .crm_clk = CRM_GPIOE_PERIPH_CLOCK},

};


/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/
/**
 * @brief 
 * 
 * @param led_e 
 * @param flag true : led open; false : led close
 */
void _set_led(LED_Type led_e , bool flag)
{
    uint8_t i = led_e >= LED_ALL ? 0 : led_e;
    uint8_t count = led_e >= LED_ALL ? LED_ALL-1 : led_e ;

    for( ; i <= count; ++i){
        gpio_bits_write(_led_info[i].port, _led_info[i].pin , (confirm_state)(flag ? _led_info[i].state : !_led_info[i].state));
    }
}


/* global functions / API interface -------------------------------------*/
void bsp_led_init(LED_Type led_e)
{
    uint8_t i = led_e >= LED_ALL ? 0 : led_e;
    uint8_t count = led_e >= LED_ALL ? LED_ALL-1 : led_e ;
    gpio_init_type gpio_init_struct;

    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;

    for( ; i <= count; ++i){
        crm_periph_clock_enable( _led_info[i].crm_clk , TRUE);
        gpio_init_struct.gpio_pins = _led_info[i].pin;
        gpio_init(_led_info[i].port, &gpio_init_struct);
    }

    bsp_led_close(led_e);
}

void bsp_led_open(LED_Type led_e)
{
    _set_led(led_e , true);
}

void bsp_led_close(LED_Type led_e)
{
    _set_led(led_e , false);
}

void bsp_led_toggle(LED_Type led_e)
{
    uint8_t i = led_e >= LED_ALL ? 0 : led_e;
    uint8_t count = led_e >= LED_ALL ? LED_ALL-1 : led_e ;

    for( ; i <= count; ++i){
        if(gpio_output_data_bit_read(_led_info[i].port , _led_info[i].pin)){
            gpio_bits_reset(_led_info[i].port , _led_info[i].pin);
        }
        else{
            gpio_bits_set(_led_info[i].port , _led_info[i].pin);
        }
    }
}
/* end of file ----------------------------------------------------------*/


