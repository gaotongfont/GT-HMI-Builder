/**
 ****************************************************************************************************
 * @file        esptim.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-08-26
 * @brief       高分辨率定时器（ESP定时器）驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 ESP32-S3 开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "esptim.h"

/**
 * @brief       初始化高精度定时器（ESP_TIMER）
 * @param       tps: 定时器周期，以微妙为单位（μs），以一秒为定时器周期来执行一次定时器中断，
 *                   那此处tps = 1s = 1000000μs
 * @retval      无
 */

void esptim_int_init(uint64_t tps)
{
    esp_timer_handle_t esp_tim_handle;                      /* 定时器回调函数句柄 */

    /* 定义一个定时器结构体 */
    esp_timer_create_args_t tim_periodic_arg = {
        .callback = &esptim_callback,                       /* 设置回调函数 */
        .arg = NULL,                                        /* 不携带参数 */
    };

    esp_timer_create(&tim_periodic_arg, &esp_tim_handle);   /* 创建一个事件 */
    esp_timer_start_periodic(esp_tim_handle, tps);          /* 每周期内触发一次 */
}

/**
 * @brief       定时器回调函数
 * @param       arg: 不携带参数
 * @retval      无
 */
void esptim_callback(void *arg)
{
    gt_tick_inc(1);
}
