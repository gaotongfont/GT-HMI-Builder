/**
 * @file zk_config.h
 * @author D.
 * @brief
 * @version 0.1
 * @date 2024-12-06 19:41:04
 * @copyright Copyright (c) 2014-present, Company Genitop. Co., Ltd.
 */
#ifndef _ZK_CONFIG_H_
#define _ZK_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include "stdio.h"
#include "string.h"
#include "stdlib.h"


/* define ---------------------------------------------------------------*/
//本地保存用户数据
//固件版本信息
    #define LIB_MAJOR_VER            1
    #define LIB_MINOR_VER            0
    #define LIB_PATCH_VER            1



//功能开关 @ref zk_app.h
#ifndef USE_FUNC_LOCATE_DATA
    #define USE_FUNC_LOCATE_DATA    01
#endif

//闹钟列表
#ifndef USE_FUNC_CLOCK_LIST
    #define USE_FUNC_CLOCK_LIST 0
#endif

//天气信息
#ifndef USE_FUNC_WEATHER
    #define USE_FUNC_WEATHER 0
#endif


/* typedef --------------------------------------------------------------*/
typedef enum {
    GT_OK = 0,
    ZK_BUSY,	/* device or resource busy */
    GT_ERR,
    GT_MALLOC_ERR,
    GT_TIMEOUT,	/* wait timeout */
    GT_INVALID,	/* invalid argument */
    GT_NONE,
    GT_FILE_ERR,
}GT_Status;


/* macros ---------------------------------------------------------------*/



/* class ----------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/



#ifdef __cplusplus
} /*extern "C"*/
#endif

/********************** 头文件 **********************/
#include "zk_hw_conf.h"
#endif //!_ZK_CONFIG_H_
