/**
 * @file bsp_sfc.c
 * @author Yang (your@email.com)
 * @brief
 * @version 0.1
 * @date 2023-02-15 16:16:08
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "bsp_sfc.h"
#include <string.h>

/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void bsp_sfc_config(uint8_t width)
{
    SFC_InitStructure SFC_initStruct;

	/* SFC使用专用的FSPI（Flash SPI）接口连接SPI Flash */
	PORT_Init(PORTD, PIN5, PORTD_PIN5_FSPI_SCLK,  0);
	PORT_Init(PORTD, PIN6, PORTD_PIN6_FSPI_SSEL,  0);
	PORT_Init(PORTD, PIN8, PORTD_PIN8_FSPI_MOSI,  1);
	PORT_Init(PORTD, PIN7, PORTD_PIN7_FSPI_MISO,  1);
	PORT_Init(PORTD, PIN3, PORTD_PIN3_FSPI_DATA2, 1);
	PORT_Init(PORTD, PIN4, PORTD_PIN4_FSPI_DATA3, 1);

	switch(width)
	{
	case 1:
	default:
		SFC_initStruct.ClkDiv = SFC_CLKDIV_4;
		SFC_initStruct.Cmd_Read = 0x03;
		SFC_initStruct.Width_Read = SFC_RDWIDTH_1;
		SFC_initStruct.Cmd_PageProgram = 0x02;
		SFC_initStruct.Width_PageProgram = SFC_PPWIDTH_1;
		break;

	case 2:
		SFC_initStruct.ClkDiv = SFC_CLKDIV_4;
		SFC_initStruct.Cmd_Read = 0xBB;
		SFC_initStruct.Width_Read = SFC_RDWIDTH_2;
		SFC_initStruct.Cmd_PageProgram = 0x02;
		SFC_initStruct.Width_PageProgram = SFC_PPWIDTH_1;
		break;

	case 4:
		SFC_initStruct.ClkDiv = SFC_CLKDIV_4;
		SFC_initStruct.Cmd_Read = 0xEB;
		SFC_initStruct.Width_Read = SFC_RDWIDTH_4;
		SFC_initStruct.Cmd_PageProgram = 0x32;
		SFC_initStruct.Width_PageProgram = SFC_PPWIDTH_4;
		break;
	}

	SFC_Init(&SFC_initStruct);

}
/* ------------------------------------------------------------------------ */
#define Rom_csH		GPIO_SetBit(GPIOD , PIN6)
#define Rom_csL 	GPIO_ClrBit(GPIOD , PIN6)
#define MOSIH 		GPIO_SetBit(GPIOD , PIN8)
#define MOSIL 		GPIO_ClrBit(GPIOD , PIN8)
#define Rom_sckH 	GPIO_SetBit(GPIOD , PIN5)
#define Rom_sckL	GPIO_ClrBit(GPIOD , PIN5)

#define MISO		GPIO_GetBit(GPIOD , PIN7)

void bsp_spi_io_config()
{
	// gpio pins dir pull_up pull_down open_drain
	// sclk
	GPIO_Init(GPIOD, PIN5 , 1 , 1 , 0 , 0);
	// cs
	GPIO_Init(GPIOD, PIN6 , 1 , 1 , 0 , 0);
	// mosi
	GPIO_Init(GPIOD, PIN8 , 1 , 1 , 0 , 0);
	// miso
	GPIO_Init(GPIOD, PIN7 , 0 , 1 , 0 , 0);

	GPIO_Init(GPIOD, PIN3 , 1 , 1 , 0 , 0);
	GPIO_Init(GPIOD, PIN4 , 1 , 1 , 0 , 0);
	GPIO_SetBit(GPIOD , PIN3);
	GPIO_SetBit(GPIOD , PIN4);

	Rom_csH;
	MOSIH;
	Rom_sckH;
}

/*******************************************************************************/
// Send data sub-pro (STM8,STM32等双向口)   SPI发送地址的时序算法               /
/*******************************************************************************/

void Send_Byte(unsigned char out)
{	
	unsigned char i=0;

	for(i=0;i<8;i++)
	{
	  Rom_sckL;  //字库芯片时钟置低
	if(((out<<i)&0x80)==0)
		MOSIL;   
	else
		MOSIH;
	Rom_sckH;
	}
}

/*******************************************************************************/
// Get data sub-pro (STM8,STM32等双向口)    SPI接收点阵数据的算法               /
/*******************************************************************************/
unsigned char Get_Byte(void)         
{
	unsigned char i;
	unsigned char read_dat;

	Rom_sckH;
	for(i=0;i<8;i++)
	{
		Rom_sckL;
		read_dat=read_dat<<1;
		if(MISO)				
			read_dat|=0x01;
		else
			read_dat&=0xfe;
		Rom_sckH;
	}
	return(read_dat);
}

unsigned char gt_read_data(unsigned char* sendbuf , unsigned char sendlen , unsigned char* receivebuf, unsigned int receivelen)
{
    unsigned int i;

	bsp_spi_io_config();

    Rom_csL;
    for(i = 0; i < sendlen;i++)
    {
        Send_Byte(sendbuf[i]);
    }
    for(i = 0; i < receivelen;i++)
    {
        receivebuf[i] = Get_Byte();
    }
    Rom_csH;

	bsp_sfc_config(1);
    return 1;
}

/* ------------------------------------------------------------------------ */
unsigned long r_dat_bat(unsigned long address, unsigned long DataLen, unsigned char* pBuff)
{
	unsigned long addr = 0;
	unsigned long cnt = address%4;
	if(cnt == 0){
			addr = address;
	}else{
			addr = address - cnt;
	}

	unsigned len = DataLen + cnt;
	if(len % 4 != 0){
			len = len + 4 - (len%4);
	}

	memcpy((volatile unsigned int *)0x80258000,(volatile unsigned int *)(0x70000000+addr),len);
	memcpy(pBuff,(volatile unsigned int *)(0x80258000+cnt),DataLen);

	return 1;
}
/* -------------------------------------------------------------------------------- */

void SFC_FLASH_PageWrite(const uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{

	if(NumByteToWrite > SFC_FLASH_PAGE_SIZE)
	{
		NumByteToWrite = SFC_FLASH_PAGE_SIZE;
		printf("SFC_FLASH_PageWrite too large!\r\n");
	}
	SFC_Write(WriteAddr , (uint32_t*)pBuffer , NumByteToWrite / 4);
}

void SFC_FLASH_BufferWrite(const uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

	/*mod运算求余，若writeAddr是SFC_FLASH_PAGE_SIZE整数倍，运算结果Addr值为0*/
	Addr = WriteAddr % SFC_FLASH_PAGE_SIZE;

	/*差count个数据值，刚好可以对齐到页地址*/
	count = SFC_FLASH_PAGE_SIZE - Addr;
	/*计算出要写多少整数页*/
	NumOfPage =  NumByteToWrite / SFC_FLASH_PAGE_SIZE;
	/*mod运算求余，计算出剩余不满一页的字节数*/
	NumOfSingle = NumByteToWrite % SFC_FLASH_PAGE_SIZE;

	/* Addr=0,则WriteAddr 刚好按页对齐 aligned  */
	if (Addr == 0)
	{
		/* NumByteToWrite < SFC_FLASH_PAGE_SIZE */
	if (NumOfPage == 0)
	{
		SFC_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
	}
	else /* NumByteToWrite > SFC_FLASH_PAGE_SIZE */
	{
			/*先把整数页都写了*/
		while (NumOfPage--)
		{
		SFC_FLASH_PageWrite(pBuffer, WriteAddr, SFC_FLASH_PAGE_SIZE);
		WriteAddr +=  SFC_FLASH_PAGE_SIZE;
		pBuffer += SFC_FLASH_PAGE_SIZE;
		}
			/*若有多余的不满一页的数据，把它写完*/
		SFC_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
	}
	}
	/* 若地址与 SFC_FLASH_PAGE_SIZE 不对齐  */
	else
	{
		/* NumByteToWrite < SFC_FLASH_PAGE_SIZE */
	if (NumOfPage == 0)
	{
			/*当前页剩余的count个位置比NumOfSingle小，一页写不完*/
		if (NumOfSingle > count)
		{
		temp = NumOfSingle - count;
				/*先写满当前页*/
		SFC_FLASH_PageWrite(pBuffer, WriteAddr, count);

		WriteAddr +=  count;
		pBuffer += count;
				/*再写剩余的数据*/
		SFC_FLASH_PageWrite(pBuffer, WriteAddr, temp);
		}
		else /*当前页剩余的count个位置能写完NumOfSingle个数据*/
		{
		SFC_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
		}
	}
	else /* NumByteToWrite > SFC_FLASH_PAGE_SIZE */
	{
			/*地址不对齐多出的count分开处理，不加入这个运算*/
		NumByteToWrite -= count;
		NumOfPage =  NumByteToWrite / SFC_FLASH_PAGE_SIZE;
		NumOfSingle = NumByteToWrite % SFC_FLASH_PAGE_SIZE;

			/* 先写完count个数据，为的是让下一次要写的地址对齐 */
		SFC_FLASH_PageWrite(pBuffer, WriteAddr, count);

			/* 接下来就重复地址对齐的情况 */
		WriteAddr +=  count;
		pBuffer += count;
			/*把整数页都写了*/
		while (NumOfPage--)
		{
		SFC_FLASH_PageWrite(pBuffer, WriteAddr, SFC_FLASH_PAGE_SIZE);
		WriteAddr +=  SFC_FLASH_PAGE_SIZE;
		pBuffer += SFC_FLASH_PAGE_SIZE;
		}
			/*若有多余的不满一页的数据，把它写完*/
		if (NumOfSingle != 0)
		{
		SFC_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
		}
	}
	}
}

/* end of file ----------------------------------------------------------*/


