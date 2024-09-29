/**
 * @file bsp_led.h
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-02 15:21:31
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */
#ifndef _BSP_LED_H_
#define _BSP_LED_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include "SWM341.h"


/* define ---------------------------------------------------------------*/
#define LED_GPIO    GPIOM
#define LED_PIN     PIN15

/* typedef --------------------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void bsp_led_init(void);
void bsp_led_on(void);
void bsp_led_off(void);
void bsp_led_toggle(void);


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_BSP_LED_H_

/* end of file ----------------------------------------------------------*/


