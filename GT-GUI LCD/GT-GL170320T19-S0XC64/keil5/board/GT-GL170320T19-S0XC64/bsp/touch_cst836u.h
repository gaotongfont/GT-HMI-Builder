/**
 * @file touch_cst836u.h
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-21 15:30:13
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */
#ifndef _TOUCH_CST836U_H_
#define _TOUCH_CST836U_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include "bsp_iic_io.h"
#include "touch.h"


/* define ---------------------------------------------------------------*/


// ----------------------------------------------------------------


/* typedef --------------------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void cst836u_init(tp_dev_t *dev);


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_TOUCH_CST836U_H_

/* end of file ----------------------------------------------------------*/


