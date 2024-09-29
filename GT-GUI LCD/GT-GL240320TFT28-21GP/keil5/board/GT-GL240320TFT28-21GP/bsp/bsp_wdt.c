/**
 * @file bsp_wdt.c
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-06 16:39:25
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "bsp_wdt.h"


/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/



/* global functions / API interface -------------------------------------*/


/* set reload value

timeout = reload_value * (divider / lick_freq )    (s)

lick_freq     = 40000 Hz
divider      = 4
reload_value = 3000

timeout = 3000 * (4 / 40000 ) = 0.3s = 300ms
*/



/**
 * @brief wdt init
 * 
 * @param reload_value 
 *      timeout = reload_value * (divider / lick_freq )    (s)
 *      lick_freq     = 40000 Hz
 *      divider      = 4
 *      reload_value = 3000
 *      timeout = 3000 * (4 / 40000 ) = 0.3s = 300ms
 */
void bsp_wdt_init(uint16_t reload_value)
{
    wdt_register_write_enable(TRUE);
    wdt_divider_set(WDT_CLK_DIV_4);
    wdt_reload_value_set((reload_value * 10) - 1);
    wdt_counter_reload();
    wdt_enable();
}

void bsp_wdt_reload(void)
{
    wdt_counter_reload();
}

/* end of file ----------------------------------------------------------*/


