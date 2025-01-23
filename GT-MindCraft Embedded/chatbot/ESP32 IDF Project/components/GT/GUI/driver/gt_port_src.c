/**
 * @file gt_port_src.c
 * @author Feyoung
 * @brief
 * @version 0.1
 * @date 2022-08-31 10:38:37
 * @copyright Copyright (c) 2014-present, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "gt_port_src.h"
#include "../src/others/gt_types.h"
#include "stddef.h"


/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static variables -----------------------------------------------------*/
#if GT_USE_MODE_SRC

static const gt_src_st _src_icon_sys[] = {
    {NULL, 0, 0, NULL, 0, 0},
};
#endif  /** GT_USE_MODE_SRC */


/* macros ---------------------------------------------------------------*/



/* class ----------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/



/* global functions / API interface -------------------------------------*/

/**
 * @brief Initializes the array mode file management system
 */
void gt_port_src_init(void)
{
#if GT_USE_MODE_SRC
    gt_src_init(_src_icon_sys, sizeof(_src_icon_sys));
#endif
}


/* end ------------------------------------------------------------------*/
