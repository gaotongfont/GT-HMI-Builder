/**
 * @file bsp_uart.h
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-05 09:49:02
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */
#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include "bsp.h"


/* define ---------------------------------------------------------------*/
#define PRINTF_UART     USART1


/* typedef --------------------------------------------------------------*/
typedef enum {
    UART_1 ,

    // end
    UART_ALL
}UART_Type;


/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void bsp_uart_init(UART_Type uart_e);



#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_BSP_UART_H_

/* end of file ----------------------------------------------------------*/


