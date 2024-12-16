/**
 * @file zk_hw_conf.h
 * @author D.
 * @brief Ӳ�� ����
 * @version 0.1
 * @date 2024-04-30 14:54:32
 * @copyright Copyright (c) 2014-present, Company Genitop. Co., Ltd.
 */
#ifndef _ZK_HW_CONF_H_
#define _ZK_HW_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include "stdio.h"
#include "string.h"
#include "stdlib.h"


/* define ---------------------------------------------------------------*/


/*----------------- hw_flash -- start -----------------*/


/*----------------- hw_flash -- start -----------------*/


/* typedef --------------------------------------------------------------*/



/* macros ---------------------------------------------------------------*/

/* ������ ------------------------------------------------------------------*/
/**
 * ZK_RW_DATA_SIZE �ķֲ�:
 *  |-
 *  |   ZK_LOCATE_DATA_SIZE //�������ݴ洢
 *  |-
 *  |   ZK_WORD_BOOK_SIZE   //���ʱ�
 *  |-
 */

//�������ݴ洢����
#define ZK_LOCATE_DATA_SIZE             0x100


//�������ݴ洢��ַ
#define     ADDRESS_LOCATE_DATA_START   (0x1000000 - ZK_LOCATE_DATA_SIZE) //@ref GT_VF_FLASH_SIZE

/* class ----------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/



#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_ZK_HW_CONF_H_
