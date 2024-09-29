/**
 * @file bsp_led.h
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-04 15:46:45
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */
#ifndef _BSP_LED_H_
#define _BSP_LED_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include "bsp.h"


/* define ---------------------------------------------------------------*/



/* typedef --------------------------------------------------------------*/
typedef enum {
    LED_1 = 0,
    LED_2,

    //end
    LED_ALL
}LED_Type;


/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void bsp_led_init(LED_Type led);
void bsp_led_open(LED_Type led);
void bsp_led_close(LED_Type led);
void bsp_led_toggle(LED_Type led_e);



#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_BSP_LED_H_

/* end of file ----------------------------------------------------------*/


