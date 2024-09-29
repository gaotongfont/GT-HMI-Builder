#include "dev_uart.h"
#include "SWM341.h"

void SerialInit(void)
{
	UART_InitStructure UART_initStruct;
	
	PORT_Init(PORTB, PIN4, PORTB_PIN4_UART3_RX, 1);		
 	PORT_Init(PORTB, PIN3, PORTB_PIN3_UART3_TX, 0);		
 	
 	UART_initStruct.Baudrate = 115200;
	UART_initStruct.DataBits = UART_DATA_8BIT;
	UART_initStruct.Parity = UART_PARITY_NONE;
	UART_initStruct.StopBits = UART_STOP_1BIT;
	UART_initStruct.RXThresholdIEn = 0;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutIEn = 0;
 	UART_Init(UART3, &UART_initStruct);
	UART_Open(UART3);
}


int fputc(int ch, FILE *f)
{
	UART_WriteByte(UART3, ch);
	
	while(UART_IsTXBusy(UART3));
 	
	return ch;
}




