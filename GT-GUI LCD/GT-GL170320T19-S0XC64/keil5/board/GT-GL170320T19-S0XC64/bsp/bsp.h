/**
 * @file bsp.h
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-04 15:50:34
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */
#ifndef _BSP_H_
#define _BSP_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include "at32f435_437.h"
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"

/* define ---------------------------------------------------------------*/



/* typedef --------------------------------------------------------------*/
typedef struct bsp_gpio {
    gpio_type *port;
    uint16_t pin;
    confirm_state state;
    crm_periph_clock_type crm_clk;
}bsp_gpio_st;

typedef struct _gpio_mux {
    gpio_pins_source_type pin_source;
    gpio_mux_sel_type gpio_mux;
}_gpio_mux;

typedef struct bsp_uart {
    usart_type *uart;
    uint32_t baudrate;
    bsp_gpio_st gpio_tx;
    bsp_gpio_st gpio_rx;
    _gpio_mux mux_tx;
    _gpio_mux mux_rx;
    crm_periph_clock_type crm_clk;
    IRQn_Type irqn; 


    //
    uint8_t tx_en : 1;
    uint8_t rx_en : 1;
    uint8_t tx_int_en : 1;
    uint8_t rx_int_en : 1;


}bsp_uart_st;

/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/



#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_BSP_H_

/* end of file ----------------------------------------------------------*/


