/**
 * @file bsp_uart.c
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-15 16:46:18
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "bsp_uart.h"

/* private define -------------------------------------------------------*/
#define _UART3_Threshold_Size      (3)
#define _UART3_RX_BUFFER_SIZE     (20)
static unsigned char _uart3_rx_buf[_UART3_RX_BUFFER_SIZE];
static unsigned char _uart3_count = 0;
typedef unsigned char uint8_t;
/* private typedef ------------------------------------------------------*/



/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
int fputc(int ch , FILE *f)
{
    UART_WriteByte(PRINTF_FPUTC_UART, ch);
	
	while(UART_IsTXBusy(PRINTF_FPUTC_UART));
    
	return ch;
}

void bsp_uart0_init(void)
{
    UART_InitStructure UART_initStruct;

    PORT_Init(UART0_RX_PORT, UART0_RX_PIN, UART0_RX_SEL, 1);	//GPIOM.0配置为UART0输入引脚
    PORT_Init(UART0_TX_PORT, UART0_TX_PIN, UART0_TX_SEL, 0);	//GPIOM.1配置为UART0输出引脚

    UART_initStruct.Baudrate = UART0_Baudrate;
    UART_initStruct.DataBits = UART_DATA_8BIT;
    UART_initStruct.Parity = UART_PARITY_NONE;
    UART_initStruct.StopBits = UART_STOP_1BIT;
    UART_initStruct.RXThresholdIEn = 0;
    UART_initStruct.TXThresholdIEn = 0;
    UART_initStruct.TimeoutIEn = 0;
    UART_Init(UART0, &UART_initStruct);
    UART_Open(UART0);
}

void bsp_uart3_init(void)
{
    UART_InitStructure UART_initStruct;

    PORT_Init(UART3_RX_PORT, UART3_RX_PIN, UART3_RX_SEL, 1);	//GPIOM.0配置为UART0输入引脚
    PORT_Init(UART3_TX_PORT, UART3_TX_PIN, UART3_TX_SEL, 0);	//GPIOM.1配置为UART0输出引脚

    UART_initStruct.Baudrate = UART3_Baudrate;
    UART_initStruct.DataBits = UART_DATA_8BIT;
    UART_initStruct.Parity = UART_PARITY_NONE;
    UART_initStruct.StopBits = UART_STOP_1BIT;
    UART_initStruct.RXThreshold = _UART3_Threshold_Size;
	UART_initStruct.RXThresholdIEn = 1;
	UART_initStruct.TXThreshold = _UART3_Threshold_Size;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutTime = 10;		//10个字符时间内未接收到新的数据则触发超时中断
	UART_initStruct.TimeoutIEn = 1;
    UART_Init(UART3, &UART_initStruct);

    UART3->TOCR &= ~(1 << UART_TOCR_MODE_Pos);  
    UART_Open(UART3);
}


void UART3_Handler(void)
{
    uint8_t data[20];
    char count = _UART3_Threshold_Size;
    uint32_t chr ;
    if(UART_INTStat(UART3, UART_IT_RX_THR))
    {
        UART_INTClr(UART3, UART_IT_RX_THR);
        while (count--)
        {
			if(UART_ReadByte(UART3, &chr) == 0)
            { 
                if(_uart3_count < _UART3_RX_BUFFER_SIZE)
                {
                    _uart3_rx_buf[_uart3_count++] = chr;
                }
            }
        }
    }
    if(UART_INTStat(UART3, UART_IT_RX_TOUT))
    {
		while(UART_IsRXFIFOEmpty(UART3) == 0)
        {
            if(UART_ReadByte(UART3, &chr) == 0)
            { 
                if(_uart3_count < _UART3_RX_BUFFER_SIZE)
                {
                    _uart3_rx_buf[_uart3_count++] = chr;
                }
            }
        }
        if(1 == _uart3_count && 0x05 == _uart3_rx_buf[0])
        {
            __disable_irq();
            WDT_Init(WDT, 0, 5);			// 通过触发WDT复位跳转到UserBoot
			WDT_Start(WDT);
			while(1) __NOP();
        }

        //主界面协议 数据头0xAA+数据长度0x03+功能选择(0x01-0x04)

        _uart3_count = 0;
        UART_INTClr(UART3, UART_IT_RX_TOUT);
    }

}


void gt_put_char(unsigned char c)
{
    UART_WriteByte( UART3 , c);
}


/* end of file ----------------------------------------------------------*/


