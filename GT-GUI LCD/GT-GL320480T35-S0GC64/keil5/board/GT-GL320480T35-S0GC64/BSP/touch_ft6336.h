/**
 * @file touch_ft6336.h
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-26 14:51:55
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */
#ifndef _TOUCH_FT6336_H_
#define _TOUCH_FT6336_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include "bsp_iic_io.h"
#include "touch.h"


/* define ---------------------------------------------------------------*/



/* typedef --------------------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void ft6336_init(tp_dev_t *dev);



#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_TOUCH_FT6336_H_

/* end of file ----------------------------------------------------------*/


