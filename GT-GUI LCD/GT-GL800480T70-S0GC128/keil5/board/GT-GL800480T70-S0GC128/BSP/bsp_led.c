/**
 * @file bsp_led.c
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-02 15:21:36
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "bsp_led.h"


/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void bsp_led_on(void)
{
    GPIO_SetBit(LED_GPIO , LED_PIN);
}

void bsp_led_off(void)
{
    GPIO_ClrBit(LED_GPIO , LED_PIN);
}

void bsp_led_toggle(void)
{
    GPIO_InvBit(LED_GPIO , LED_PIN);
}

void bsp_led_init(void)
{
    GPIO_Init(LED_GPIO, LED_PIN , 1 , 0 , 0 , 0);
    bsp_led_off();
}


/* end of file ----------------------------------------------------------*/


