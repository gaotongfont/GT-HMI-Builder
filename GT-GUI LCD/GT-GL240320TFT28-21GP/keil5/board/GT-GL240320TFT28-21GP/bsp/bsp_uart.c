/**
 * @file bsp_uart.c
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-05 09:49:06
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "bsp_uart.h"
#include "bsp_wdt.h"

/* private define -------------------------------------------------------*/
#define _UART1_RX_BUFFER_SIZE     (32)
static unsigned char _uart1_rx_buf[_UART1_RX_BUFFER_SIZE];
static unsigned char _uart1_count = 0;


/* private typedef ------------------------------------------------------*/



/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/
static const bsp_uart_st _uart_info[UART_ALL] = {
    {
        .uart = USART1 , .baudrate = 115200 ,
        .gpio_tx.port = GPIOA , .gpio_tx.pin = GPIO_PINS_9 , .gpio_tx.crm_clk = CRM_GPIOA_PERIPH_CLOCK , 
        .gpio_rx.port = GPIOA , .gpio_rx.pin = GPIO_PINS_10 , .gpio_rx.crm_clk = CRM_GPIOA_PERIPH_CLOCK ,
        .mux_tx.gpio_mux = GPIO_MUX_7 , .mux_tx.pin_source = GPIO_PINS_SOURCE9 ,
        .mux_rx.gpio_mux = GPIO_MUX_7 , .mux_rx.pin_source = GPIO_PINS_SOURCE10,
        .crm_clk = CRM_USART1_PERIPH_CLOCK ,
        .rx_en = true , .rx_int_en = true , .tx_en = true , .tx_int_en = false ,
        .irqn = USART1_IRQn ,
    },
};


/* macros ---------------------------------------------------------------*/
#if defined ( __GNUC__ ) && !defined (__clang__)
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

/**
  * @brief  retargets the c library printf function to the usart.
  * @param  none
  * @retval none
  */
// PUTCHAR_PROTOTYPE
int fputc(int ch, FILE *f)
{
    while(usart_flag_get(PRINTF_UART, USART_TDBE_FLAG) == RESET);

    usart_data_transmit(PRINTF_UART, ch);
    return ch;
}


/* static functions -----------------------------------------------------*/
/**
 * @brief Set interrupts other than TDBE and RDBF
 * 
 */
static void _uart_other_interrupt(void)
{
    usart_interrupt_enable(_uart_info[UART_1].uart, USART_IDLE_INT , TRUE);
}


/* global functions / API interface -------------------------------------*/
void bsp_uart_init(UART_Type uart_e)
{
    uint8_t i = uart_e >= UART_ALL ? 0 : uart_e;
    uint8_t count = uart_e >= UART_ALL ? UART_ALL-1 : uart_e ;
    gpio_init_type gpio_init_struct;

    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;

    for( ; i <= count; ++i){
        // tx
        if(_uart_info[i].tx_en){
            gpio_init_struct.gpio_pins = _uart_info[i].gpio_tx.pin;
            crm_periph_clock_enable(_uart_info[i].gpio_tx.crm_clk, TRUE);
            gpio_init(_uart_info[i].gpio_tx.port, &gpio_init_struct);
            gpio_pin_mux_config(_uart_info[i].gpio_tx.port , _uart_info[i].mux_tx.pin_source, _uart_info[i].mux_tx.gpio_mux);
        }
        
        // rx 
        if(_uart_info[i].rx_en){
            gpio_init_struct.gpio_pins = _uart_info[i].gpio_rx.pin;
            crm_periph_clock_enable(_uart_info[i].gpio_rx.crm_clk, TRUE);
            gpio_init(_uart_info[i].gpio_rx.port, &gpio_init_struct);
            gpio_pin_mux_config(_uart_info[i].gpio_rx.port , _uart_info[i].mux_rx.pin_source, _uart_info[i].mux_rx.gpio_mux);
        }
        // uart
        crm_periph_clock_enable(_uart_info[i].crm_clk, TRUE);
        usart_init(_uart_info[i].uart, _uart_info[i].baudrate, USART_DATA_8BITS, USART_STOP_1_BIT);
        
        if(_uart_info[i].tx_en){
            usart_transmitter_enable(_uart_info[i].uart, TRUE);
        }

        if(_uart_info[i].rx_en){
            usart_receiver_enable(_uart_info[i].uart, TRUE);
        }
        usart_enable(_uart_info[i].uart, TRUE);
        
        // interrupt
        if(_uart_info[i].tx_int_en || _uart_info[i].rx_int_en){
            nvic_irq_enable(_uart_info[i].irqn, 0, 0);

            if(_uart_info[i].tx_int_en){
                usart_interrupt_enable(_uart_info[i].uart, USART_TDBE_INT , TRUE);
            }

            if(_uart_info[i].rx_int_en){
                usart_interrupt_enable(_uart_info[i].uart, USART_RDBF_INT , TRUE);
            }
        }

    }

    _uart_other_interrupt();
}


void USART1_IRQHandler(void)
{
    uint8_t chr;
    if(usart_flag_get(USART1, USART_RDBF_FLAG)){

        chr = usart_data_receive(USART1);
        if(_uart1_count < _UART1_RX_BUFFER_SIZE)
        {
            _uart1_rx_buf[_uart1_count++] = chr;
        }
        usart_flag_clear(USART1, USART_RDBF_FLAG);
    }
    else if(usart_flag_get(USART1, USART_IDLEF_FLAG))
    {
        if(1 == _uart1_count && 0x05 == _uart1_rx_buf[0])
        {
            __disable_irq();
            bsp_wdt_init(5);
            while(1) __NOP();
        }
        _uart1_count = 0;
        usart_flag_clear(USART1, USART_IDLEF_FLAG);

    }

}

/* end of file ----------------------------------------------------------*/


