#include "bsp_iic_io.h"
#include "bsp_delay.h"

#define DELAY_TIME 	(4)	//us

void IIC_SDA_IN(void)
{
	gpio_init_type gpio_init_struct;
	/* configure the led gpio */
	gpio_init_struct.gpio_pins = IIC_SDA_PIN ; 
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(IIC_SDA_GPIO, &gpio_init_struct);
}

void IIC_SDA_OUT(void)
{
	gpio_init_type gpio_init_struct;
	/* configure the led gpio */
	gpio_init_struct.gpio_pins = IIC_SDA_PIN ; 
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(IIC_SDA_GPIO, &gpio_init_struct);
}

//初始化IIC
void IIC_Init(void)
{
	gpio_init_type gpio_init_struct;

	/* enable the led clock */
	crm_periph_clock_enable(IIC_SCL_GPIO_CRM_CLK, TRUE);
	crm_periph_clock_enable(IIC_SDA_GPIO_CRM_CLK, TRUE);

	gpio_default_para_init(&gpio_init_struct);
	
	/* configure the led gpio */
	gpio_init_struct.gpio_pins = IIC_SCL_PIN ; 
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;

	gpio_init(IIC_SCL_GPIO, &gpio_init_struct);

	IIC_SCL_SET(1);
	IIC_SDA_SET(1);
}



//产生IIC起始信号
void IIC_Start(void)
{
	IIC_SDA_OUT();     //sda线输出
	IIC_SDA_SET(1);	  	  
	IIC_SCL_SET(1);
	delay_us(DELAY_TIME);
	IIC_SDA_SET(0);//START:when CLK is high,DATA change form high to low 
	delay_us(DELAY_TIME);
	IIC_SCL_SET(0);//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	IIC_SDA_OUT();//sda线输出
	IIC_SCL_SET(0);
	IIC_SDA_SET(0);//STOP:when CLK is high DATA change form low to high
	delay_us(DELAY_TIME);
	IIC_SCL_SET(1); 
	IIC_SDA_SET(1);//发送I2C总线结束信号
	delay_us(DELAY_TIME);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	IIC_SDA_IN();      //SDA设置为输入  
	IIC_SDA_SET(1);
	delay_us(DELAY_TIME);	   
	IIC_SCL_SET(1);
	delay_us(DELAY_TIME);	 
	while(IIC_SDA_READ())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_SET(0);//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL_SET(0);
	IIC_SDA_OUT();
	IIC_SDA_SET(0);
	delay_us(DELAY_TIME);
	IIC_SCL_SET(1);
	delay_us(DELAY_TIME);
	IIC_SCL_SET(0);
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL_SET(0);
	IIC_SDA_OUT();
	IIC_SDA_SET(1);
	delay_us(DELAY_TIME);
	IIC_SCL_SET(1);
	delay_us(DELAY_TIME);
	IIC_SCL_SET(0);
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	IIC_SDA_OUT();
    IIC_SCL_SET(0);//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
		IIC_SDA_SET((txd&0x80)>>7);
        txd<<=1; 	  
		delay_us(DELAY_TIME);   //对TEA5767这三个延时都是必须的
		IIC_SCL_SET(1);
		delay_us(DELAY_TIME); 
		IIC_SCL_SET(0);	
		delay_us(DELAY_TIME);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	IIC_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL_SET(0); 
        delay_us(DELAY_TIME);
		IIC_SCL_SET(1);
        receive<<=1;
        if(IIC_SDA_READ())receive++;   
		delay_us(DELAY_TIME); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}



























