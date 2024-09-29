/**
 * @file bsp_delay.h
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-05 15:38:30
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */
#ifndef _BSP_DELAY_H_
#define _BSP_DELAY_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include "bsp.h"


/* define ---------------------------------------------------------------*/



/* typedef --------------------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void delay_init(void);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);
void delay_sec(uint16_t sec);


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_BSP_DELAY_H_

/* end of file ----------------------------------------------------------*/


