/**
 * @file bsp_wdt.h
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-06 16:39:37
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */
#ifndef _BSP_WDT_H_
#define _BSP_WDT_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include "bsp.h"


/* define ---------------------------------------------------------------*/



/* typedef --------------------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void bsp_wdt_init(uint16_t reload_value);
void bsp_wdt_reload(void);


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_BSP_WDT_H_

/* end of file ----------------------------------------------------------*/


