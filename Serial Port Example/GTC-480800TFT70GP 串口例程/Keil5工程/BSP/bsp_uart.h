/**
 * @file bsp_uart.h
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-15 16:46:14
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */
#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include "SWM341.h"


/* define ---------------------------------------------------------------*/
// uart0
#define UART0_RX_PORT       PORTM
#define UART0_RX_PIN        PIN0
#define UART0_RX_SEL        PORTM_PIN0_UART0_RX
#define UART0_TX_PORT       PORTM
#define UART0_TX_PIN        PIN1
#define UART0_TX_SEL        PORTM_PIN1_UART0_TX
#define UART0_Baudrate      (115200)
// uart3
#define UART3_RX_PORT       PORTB
#define UART3_RX_PIN        PIN4
#define UART3_RX_SEL        PORTB_PIN4_UART3_RX
#define UART3_TX_PORT       PORTB
#define UART3_TX_PIN        PIN3
#define UART3_TX_SEL        PORTB_PIN3_UART3_TX
#define UART3_Baudrate      (115200)
// fputc uart
#define PRINTF_FPUTC_UART        UART3
extern unsigned char uart_status;
extern unsigned char UART_BUF[20];

/* typedef --------------------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void bsp_uart3_init(void);
void bsp_uart0_init(void);

void uart_send_pack(unsigned char *buf);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_BSP_UART_H_

/* end of file ----------------------------------------------------------*/


