#ifndef _BSP_IIC_IO_H_
#define _BSP_IIC_IO_H_

#include "bsp.h"


// SCL
#define IIC_SCL_PIN                         GPIO_PINS_15
#define IIC_SCL_GPIO                        GPIOB
#define IIC_SCL_GPIO_CRM_CLK                CRM_GPIOB_PERIPH_CLOCK
// SDA
#define IIC_SDA_PIN                         GPIO_PINS_14
#define IIC_SDA_GPIO                        GPIOB
#define IIC_SDA_GPIO_CRM_CLK                CRM_GPIOB_PERIPH_CLOCK

//IO操作函数
#define IIC_SCL_SET(value)                  gpio_bits_write(IIC_SCL_GPIO , IIC_SCL_PIN , (value == 0 ? FALSE : TRUE))
#define IIC_SDA_SET(value)                  gpio_bits_write(IIC_SDA_GPIO , IIC_SDA_PIN , (value == 0 ? FALSE : TRUE))
#define IIC_SDA_READ()                      gpio_input_data_bit_read(IIC_SDA_GPIO , IIC_SDA_PIN)


//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	  
#endif
















