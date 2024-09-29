/**
 * @file dev_sdio.c
 * @author lik
 * @brief sdio相关配置函数
 * @version 0.1
 * @date 2022-01-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "SWM341.h"

/**
 * @brief sdio初始化
 * 
 * @return uint32_t 错误代码
 */
uint32_t sdcard_init(void)
{
    PORT_Init(PORTM, PIN2, PORTM_PIN2_SD_CLK, 0);
    PORT_Init(PORTM, PIN4, PORTM_PIN4_SD_CMD, 1);
    PORT_Init(PORTM, PIN5, PORTM_PIN5_SD_D0,  1);
    PORT_Init(PORTM, PIN6, PORTM_PIN6_SD_D1,  1);
    PORT_Init(PORTN, PIN0, PORTN_PIN0_SD_D2,  1);
    PORT_Init(PORTN, PIN1, PORTN_PIN1_SD_D3,  1);
    return SDIO_Init(37500000);
}
