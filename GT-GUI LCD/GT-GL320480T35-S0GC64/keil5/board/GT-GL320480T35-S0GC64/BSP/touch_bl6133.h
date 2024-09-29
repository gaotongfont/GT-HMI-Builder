/**
 * @file touch_bl6133.h
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-14 15:37:49
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */
#ifndef _TOUCH_BL6133_H_
#define _TOUCH_BL6133_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include "bsp_iic_io.h"
#include "touch.h"


/* define ---------------------------------------------------------------*/
#define BL6133_UPDATE_EN    0


/* typedef --------------------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void bl6133_init(tp_dev_t *dev);



#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_TOUCH_BL6133_H_

/* end of file ----------------------------------------------------------*/


