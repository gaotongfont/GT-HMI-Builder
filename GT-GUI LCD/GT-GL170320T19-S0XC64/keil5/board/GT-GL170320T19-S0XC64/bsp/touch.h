/**
 * @file touch.h
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
#include "bsp.h"
#include "stdbool.h"
#include "stdint.h"

/* define ---------------------------------------------------------------*/
// RST
#define TOUCH_RST_PIN                         GPIO_PINS_12
#define TOUCH_RST_GPIO                        GPIOB
#define TOUCH_RST_GPIO_CRM_CLK                CRM_GPIOB_PERIPH_CLOCK
#define TOUCH_RST_SET(value)                  gpio_bits_write(TOUCH_RST_GPIO , TOUCH_RST_PIN , (value == 0 ? FALSE : TRUE))

// IRQ
#define TOUCH_IRQ_PIN                         GPIO_PINS_11
#define TOUCH_IRQ_GPIO                        GPIOD
#define TOUCH_IRQ_SCFG_PIN                    SCFG_PINS_SOURCE11
#define TOUCH_IRQ_SCFG_GPIO                   SCFG_PORT_SOURCE_GPIOD
#define TOUCH_IRQ_GPIO_CRM_CLK                CRM_GPIOD_PERIPH_CLOCK
#define TOUCH_IRQ_EXINT_LINE                  EXINT_LINE_11
#define TOUCH_IRQ_EXINT_IRQn                  EXINT15_10_IRQn
#define TOUCH_IRQ_EXINT_IRQHandler            EXINT15_10_IRQHandler

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
extern tp_dev_t tp_dev;
// 
void touch_init(void);



#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_TOUCH_H_

/* end of file ----------------------------------------------------------*/


