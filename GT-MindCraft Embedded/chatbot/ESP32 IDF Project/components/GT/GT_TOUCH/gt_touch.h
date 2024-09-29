/**
 * @file gt_touch.h
 * @author Yang (your@email.com)
 * @brief
 * @version 0.1
 * @date 2023-06-21 17:22:12
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */
#ifndef _TOUCH_H_
#define _TOUCH_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "esp_bit_defs.h"

/* define ---------------------------------------------------------------*/

// The touch interface was enabled to interrupt reading packets
// 0: disable  1: enable
#define TOUCH_INT_READ_POINT_EN       0
// log
#define TOUCH_LOGD_EN                 0
#define TOUCH_DRAW_POINT_EN           0

#if (TOUCH_LOGD_EN)
    #define TP_LOGD(fmt , arg...)  do{ printf("[TP--D] <%s> <%d>" fmt "\n" , __func__ , __LINE__ , ##arg ); }while(0)
    #define TP_LOGE(fmt , arg...)  do{ printf("[TP--E] <%s> <%d>" fmt "\n" , __func__ , __LINE__ , ##arg ); }while(0)
#else
    #define TP_LOGD(fmt , arg...) ((void)0)
    #define TP_LOGE(fmt , arg...) ((void)0)
#endif

// touc iic port
#define TOUCH_IIC_PORT I2C_NUM_0

// rest pin
#define TOUCH_RST_PIN  (BIT2)

// INT pin
#define TOUCH_INT_PIN  (BIT4)
/* typedef --------------------------------------------------------------*/
/** 触摸状态 */
enum
{
    TP_STATE_PRESSED = 0,
    TP_STATE_RELEASED,
    TP_STATE_HOLDE,
};

/** 触摸信息结构体 */
typedef struct
{
    uint16_t x;     /*!< 当前x坐标 */
    uint16_t y;     /*!< 当前y坐标 */
    uint8_t status; /*!< 触摸状态 */
} tp_point;

typedef struct
{
    uint16_t chipID;
    tp_point point;
    bool (*write_reg)(uint8_t ic_add , uint8_t reg, uint8_t *buf , uint32_t len);
    bool (*read_reg)(uint8_t ic_add , uint8_t reg, uint8_t *buf , uint32_t len);
    bool (*read_point)(void);
    bool (*update)(void);
} tp_dev_t;

/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
//
tp_dev_t* gt_touch_init(void);



#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_TOUCH_H_

/* end of file ----------------------------------------------------------*/


