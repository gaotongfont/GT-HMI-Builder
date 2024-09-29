#include "gt911.h"
#include "dev_touch.h"
#include "dev_systick.h"
#include "string.h"
#include "bsp_lcd_rgb.h"
#include "dev_touch.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
/*原子 STM32F429 HAL 实验30
 GT911驱动
步骤记录：

// 接线 芯片GT911
//T_PEN----PH7
//T_SCK----PH6
//T_MISO---PG3	不使用
//T_MOSI---PI3
//T_CS-----PI8

QQ:516583078
*/
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////


/*
GT911 的从设备地址有两组可选，两组地址分别为：0xBA/0xBB和0x28/0x29
*/
#define GT911_I2C_ADDR	0xBA   //不使用


//GT911配置参数表
//第一个字节为版本号(0X60),必须保证新的版本号大于等于GT911内部
//flash原有版本号,才会更新配置.
const uint8_t GT911_CFG_TBL[] =   //数组内容修改了
{
  0x68,0x20,0x03,0xE0,0x01,0x05,0x3D,0x00,0x01,0x48, //0x68是自己定义的版本号
  0x28,0x0D,0x50,0x32,0x03,0x05,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x18,0x1A,0x1E,0x14,0x8A,0x2A,0x0C,
  0x30,0x38,0x31,0x0D,0x00,0x00,0x02,0xB9,0x03,0x2D,
  0x00,0x00,0x00,0x00,0x00,0x03,0x64,0x32,0x00,0x00,
  0x00,0x1D,0x41,0x94,0xC5,0x02,0x07,0x00,0x00,0x04,
  0xA5,0x1F,0x00,0x94,0x25,0x00,0x88,0x2B,0x00,0x7D,
  0x33,0x00,0x74,0x3C,0x00,0x74,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x18,0x16,0x14,0x12,0x10,0x0E,0x0C,0x0A,
  0x08,0x06,0x04,0x02,0xFF,0xFF,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x24,0x22,0x21,0x20,0x1F,0x1E,0x1D,0x1C,
  0x18,0x16,0x13,0x12,0x10,0x0F,0x0A,0x08,0x06,0x04,
  0x02,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,

};
//发送GT9147配置参数
//mode:0,参数不保存到flash
//     1,参数保存到flash
uint8_t GT911_Send_Cfg(uint8_t mode)//修改
{
	//	uint8_t buf[2],temp[4];
	//	uint8_t i=0;
	//	buf[0]=0;
	//	buf[1]=mode;	//是否写入到GT911 FLASH?  即是否掉电保存
	//	for(i=0;i<sizeof(GT911_CFG_TBL);i++)buf[0]+=GT911_CFG_TBL[i];//计算校验和
	//    buf[0]=(~buf[0])+1;
	//	GT911_WR_Reg(GT_CFGS_REG,(uint8_t*)GT911_CFG_TBL,sizeof(GT911_CFG_TBL));//发送寄存器配置
	//	GT911_WR_Reg(GT_CHECK_REG,buf,2);//写入校验和,和配置更新标记
	//	GT911_WR_Reg(GT_CTRL_REG, temp, 1); // 软复位
	//	GT911_RD_Reg(GT_PID_REG,temp,4);//读取产品ID
	//	printf("temp:%s\r\n",temp);
	return 0;
}
//向GT9147写入一次数据
//reg:起始寄存器地址
//buf:数据缓缓存区
//len:写数据长度
//返回值:0,成功;1,失败.
uint8_t GT911_WR_Reg(uint16_t reg, uint8_t * buf, uint8_t len)
{

	uint32_t i;
	uint8_t ack;

	ack = I2C_Start(I2C0, (GT9x_ADDR << 1) | 0, 1);
	if (ack == 0)
		goto wr_fail;

	ack = I2C_Write(I2C0, reg >> 8, 1);
	if (ack == 0)
		goto wr_fail;

	ack = I2C_Write(I2C0, reg & 0XFF, 1);
	if (ack == 0)
		goto wr_fail;

	for (i = 0; i < len; i++) {
		ack = I2C_Write(I2C0, buf[i], 1);
		if (ack == 0)
			goto wr_fail;
	}

	I2C_Stop(I2C0, 1);
	//    swm_delay_ms(10);

	return 0;

wr_fail:
	I2C_Stop(I2C0, 1);
	//    swm_delay_ms(10);
	return 1;
}
//从GT9147读出一次数据
//reg:起始寄存器地址
//buf:数据缓缓存区
//len:读数据长度
uint8_t GT911_RD_Reg(uint16_t reg, uint8_t * buf, uint8_t len)
{
	uint8_t i;
	uint8_t ack;

	ack = I2C_Start(I2C0, (GT9x_ADDR << 1) | 0, 1);
	if (ack == 0) {
		goto rd_fail;
	}
	ack = I2C_Write(I2C0, reg >> 8, 1);
	if (ack == 0) {
		goto rd_fail;
	}
	ack = I2C_Write(I2C0, reg & 0XFF, 1);
	if (ack == 0) {
		goto rd_fail;
	}
	swm_delay_ms(5);//此处必须延时等待一会再启动

	ack = I2C_Start(I2C0, (GT9x_ADDR << 1) | 1, 1); //ReStart
	if (ack == 0) {
		goto rd_fail;
	}
	for (i = 0; i < len - 1; i++) {
		buf[i] = I2C_Read(I2C0, 1, 1);
	}
	buf[i] = I2C_Read(I2C0, 0, 1);

	I2C_Stop(I2C0, 1);
	//    swm_delay_ms(10);
	return 0;

rd_fail:
	I2C_Stop(I2C0, 1);
	//    swm_delay_ms(10);
	return 1;
}

const uint16_t GT911_TPX_TBL[5] = { GT_TP1_REG,GT_TP2_REG,GT_TP3_REG,GT_TP4_REG,GT_TP5_REG };

//扫描触摸屏(采用查询方式)
//mode:0,正常扫描.
//返回值:当前触屏状态.
//0,触屏无触摸;1,触屏有触摸
uint8_t GT911_Init(void)
{
	uint8_t temp[4]; uint16_t i = 0;
#if 01
	//	GPIO_InitTypeDef  GPIO_InitStructure;

	//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOB,C时钟

	//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;//PB1设置为上拉输入
	//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//输入模式
	//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	//  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化

	//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//PC13设置为推挽输出
	//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出模式
	//	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化

	//	CT_IIC_Init();      	//初始化电容屏的I2C总线
	//	GT_RST=0;				//复位
	//	delay_ms(10);
	// 	GT_RST=1;				//释放复位
	//	delay_ms(10);

	//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//PB1设置为浮空输入
	//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出模式
	//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化

	I2C_InitStructure I2C_initStruct;

	PORT_Init(TP_PORT_SCL, TP_PIN_SCL, TP_PIN_SCL_FUN, 1); //配置为 I2C1 SCL 引脚
	TP_PORT_SCL->PULLU |= (1 << TP_PIN_SCL);               //必须使能上拉
	TP_PORT_SCL->OPEND |= (1 << TP_PIN_SCL);	           //开漏
	PORT_Init(TP_PORT_SDA, TP_PIN_SDA, TP_PIN_SDA_FUN, 1); //配置为 I2C1 SDA 引脚
	TP_PORT_SDA->PULLU |= (1 << TP_PIN_SDA);
	TP_PORT_SDA->OPEND |= (1 << TP_PIN_SDA);

	I2C_initStruct.Master = 1;
	I2C_initStruct.Addr10b = 0;
	I2C_initStruct.MstClk = 100000;
	I2C_initStruct.TXEmptyIEn = 0;	 //发送寄存器空中断使能
	I2C_initStruct.RXNotEmptyIEn = 0;//接收寄存器非空中断使能
	//	I2C_initStruct.SlvAddr = 0;
	//	I2C_initStruct.SlvAddrMsk = 0;
	//	I2C_initStruct.SlvSTADetIEn = 0;//从机检测到起始中断使能
	//	I2C_initStruct.SlvSTODetIEn = 0;//从机检测到终止中断使能
	I2C_Init(I2C0, &I2C_initStruct);
	I2C_Open(I2C0);

	GPIO_Init(TP_GPIO_INT, TP_PIN_INT, 0, 0, 1, 0); // 输入，开启下拉。复位时INT为低，选择0xBA作为地址

	GPIO_Init(TP_GPIO_RST, TP_PIN_RST, 1, 1, 0, 0); //复位
	GPIO_ClrBit(TP_GPIO_RST, TP_PIN_RST);
	swm_delay_ms(10);
	GPIO_SetBit(TP_GPIO_RST, TP_PIN_RST); // 释放复位
	swm_delay_ms(10);

	temp[0] = 0x02;
	GT911_WR_Reg(GT_CTRL_REG, temp, 1); // 软复位
	swm_delay_ms(100);
#else
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOH_CLK_ENABLE();			//开启GPIOH时钟
	__HAL_RCC_GPIOI_CLK_ENABLE();			//开启GPIOI时钟

	//PH7
	GPIO_Initure.Pin = GPIO_PIN_7;            //PH7
	GPIO_Initure.Mode = GPIO_MODE_INPUT;      //输入
	GPIO_Initure.Pull = GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;     //高速
	HAL_GPIO_Init(GPIOH, &GPIO_Initure);     //初始化

	//PI8
	GPIO_Initure.Pin = GPIO_PIN_8;            //PI8
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;  //推挽输出
	HAL_GPIO_Init(GPIOI, &GPIO_Initure);     //初始化
	CT_IIC_Init();      	//初始化电容屏的I2C总线
	GT_RST = 0;				//复位
	delay_ms(10);
	GT_RST = 1;				//释放复位
	delay_ms(10);
	GPIO_Initure.Pin = GPIO_PIN_7;            //PH7
	GPIO_Initure.Mode = GPIO_MODE_INPUT;      //输入
	GPIO_Initure.Pull = GPIO_NOPULL;          //不带上下拉，浮空输入
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;     //高速
	HAL_GPIO_Init(GPIOH, &GPIO_Initure);     //初始化
#endif
	swm_delay_ms(100);

	GT911_Reset_Sequence(0xBA);
	GT911_RD_Reg(GT_PID_REG, temp, 4);//读取产品ID
	//temp[4]=0;
	// printf("%s\r\n",temp);	//打印ID
	// printf("TouchPad_ID:%d,%d,%d\r\n",temp[0],temp[1],temp[2]);


	if (strcmp((char *)temp, "911") == 0)//ID==9147
	{
		temp[0] = 0X02;
		GT911_WR_Reg(GT_CTRL_REG, temp, 1);//软复位GT9147
		GT911_RD_Reg(GT_CFGS_REG, temp, 1);//读取GT_CFGS_REG寄存器
		// printf("读出版本:%x\r\n",temp[0]);
		if (temp[0] < 0X68)//默认版本比较低,需要更新flash配置
		{
			printf("Default Ver:%x\r\n", temp[0]);
			//		  GT911_Send_Cfg(1);//更新并保存配置  //先屏蔽//

						//测试内部的XY触摸范围

			//			GT911_RD_Reg(0X8049,temp,1);
			//			printf("读出X高八位:%x\r\n",temp[0]);
			//			GT911_RD_Reg(0X804A,temp,1);
			//			printf("读出Y低八位:%x\r\n",temp[0]);
			//			GT911_RD_Reg(0X804B,temp,1);
			//			printf("读出Y高八位:%x\r\n",temp[0]);
		}
		//读出配置表
//			for(i=0;i<184;i++)
//			{
//				GT9147_RD_Reg(0X8047+i,temp,1);
//				printf("TEMP[%x]:%x\r\n",(0X8047+i),temp[0]);
//			}

		swm_delay_ms(10);
		temp[0] = 0X00;
		GT911_WR_Reg(GT_CTRL_REG, temp, 1);//结束复位
		return 0;
	}
	return 1;
}





//添加硬复位  复位后将911地址设置为0xBA/0xBB
//调用下面函数前IO要初始化
/*
*********************************************************************************************************
*	函 数 名: GT911_Reset_Sequence
*	功能说明: G911硬复位操作,RST为低电平时，INT持续为低电平，1ms后RST置为高电平，10ms后INT设置为输入，
*	使GT911地址设定为0xBA/0xBB。
*	形 参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void GT911_Reset_Sequence(uint8_t ucAddr) //未使用
{
	//GT911_RST_INT_GPIO_Init();
	switch (ucAddr) {
	case 0xBA:
		GT911_RST_0(); //RST引脚低电平
		GT911_INT_0(); //INT引脚低电平
		swm_delay_ms(30); //延时30ms，最短1
		GT911_RST_1(); //RST引脚高电平
		GT911_INT_0(); //INT引脚低电平
		swm_delay_ms(30); //延时30ms，最短20
		GT911_INT_0();
		swm_delay_ms(30); //延时30ms，最短20
		GT911_INT_1();
		break;
	case 0x28:
		GT911_RST_0(); //RST引脚低电平
		GT911_INT_1(); //INT引脚高电平
		swm_delay_ms(30); //延时30ms，最短1
		GT911_RST_1(); //RST引脚高电平
		GT911_INT_1(); //INT引脚高电平
		swm_delay_ms(30); //延时30ms，最短20
		GT911_INT_0();
		swm_delay_ms(30); //延时30ms，最短20
		GT911_INT_1();
		break;
	default: //缺省为0xBA
		GT911_RST_0(); //RST引脚低电平
		GT911_INT_0(); //INT引脚低电平
		swm_delay_ms(30); //延时30ms，最短1
		GT911_RST_1(); //RST引脚高电平
		GT911_INT_0(); //INT引脚低电平
		swm_delay_ms(30); //延时30ms，最短20
		GT911_INT_0();
		swm_delay_ms(30); //延时30ms，最短20
		GT911_INT_1();
		break;

	}
}


uint8_t GT911_Scan(uint8_t mode)
{
	uint8_t buf[4];
	uint8_t i = 0, res = 0;
	uint8_t temp, temp_sta;
	uint8_t cnt = 0;
	uint8_t status = 0;
	uint8_t ret_reset = 0;

	//读取触摸点的状态
	if (GT911_RD_Reg(GT_GSTID_REG, &status, 1)) {
		ret_reset = 1;
		goto reset_lb;
	}
	if (TP_Dev.status & TP_PRES_DOWN) {
		switch (status) {
		case 0x00: {
			res = 1;
			goto ret_lb;
		}
		case 0xff: {
			res = 0;
			TP_Dev.status = 0x00;
			goto ret_lb;
		}
		default:
			break;
		}
	}
	cnt = status & 0X0f;

	if (status & 0X80 && cnt < 6) {
		temp = 0;
		//清标志
		if (GT911_WR_Reg(GT_GSTID_REG, &temp, 1)) {
			ret_reset = 1;
			goto reset_lb;
		}
	}
	if (!cnt) {
		goto ret_lb;
	}
	temp = 0XFF << cnt;		//将点的个数转换为1的位数,匹配TP_Dev.sta定义
	temp_sta = TP_Dev.status;			//保存当前的TP_Dev.sta值
	TP_Dev.status = (~temp) | TP_PRES_DOWN | TP_CATH_PRES;

	TP_Dev.x[4] = TP_Dev.x[0];	//保存触点0的数据
	TP_Dev.y[4] = TP_Dev.y[0];
	for (i = 0; i < 5; i++) {
		if (TP_Dev.status & (1 << i)) {
			//读取XY坐标值
			if (GT911_RD_Reg(GT911_TPX_TBL[i], buf, 4)) {
				ret_reset = 1;
				goto reset_lb;
			}
			TP_Dev.x[i] = ((uint16_t)(buf[1] & 0X0F) << 8) + buf[0];
			TP_Dev.y[i] = ((uint16_t)(buf[3] & 0X0F) << 8) + buf[2];
		}
	}
	res = 1;
	if (TP_Dev.x[0] < LCD_HDOT && TP_Dev.y[0] < LCD_VDOT) {
		goto ret_lb;
	}
	/** 非法范围的值 */
	if (cnt > 1) {
		TP_Dev.x[0] = TP_Dev.x[1];
		TP_Dev.y[0] = TP_Dev.y[1];
	} else {
		TP_Dev.x[0] = TP_Dev.x[4];
		TP_Dev.y[0] = TP_Dev.y[4];
		status = 0X80;
		TP_Dev.status = temp_sta;	//恢复TP_Dev.sta
	}
ret_lb:
	if ((status & 0X8F) == 0X80)//无触摸点按下
	{
		if (TP_Dev.status & TP_PRES_DOWN)	//之前是被按下的
		{
			TP_Dev.status &= ~(1 << 7);	//标记按键松开
		} else {
			TP_Dev.x[0] = 0xffff;
			TP_Dev.y[0] = 0xffff;
			TP_Dev.status &= 0XE0;	//清除点有效标记
		}
	}
	return res;

reset_lb:
	if (ret_reset) {
		GT911_Soft_Reset();
		// GT911_Init();
	}
	return res;
}

/*
*********************************************************************************************************
*	函 数 名: GT911_Soft_Reset
*	功能说明: G911软复位操作。
*	形 参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void GT911_Soft_Reset(void)
{
	uint8_t buf[1];
	buf[0] = 0x01;
	GT911_WR_Reg(GT911_COMMAND_REG, (uint8_t *)buf, 1);
}


























