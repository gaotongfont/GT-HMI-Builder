/**
 * @file bsp_sfc.h
 * @author Yang (your@email.com)
 * @brief
 * @version 0.1
 * @date 2023-02-15 16:16:03
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */
#ifndef _BSP_SFC_H_
#define _BSP_SFC_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include "SWM341.h"


/* define ---------------------------------------------------------------*/
#define SFC_FLASH_PAGE_SIZE     (256)
#define SFC_FLASH_SECTOR_SIZE   (4096)


/* typedef --------------------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void bsp_sfc_config(uint8_t width);
int bsp_spc_flash_write(const uint8_t* data, uint32_t addr , uint32_t length);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_BSP_SFC_H_

/* end of file ----------------------------------------------------------*/


