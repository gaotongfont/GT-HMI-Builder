#ifndef __GT911_H
#define __GT911_H
#include "dev_systick.h"//////////////////////////////////////////////////////////////////////////////////



//IO操作函数
//#define GT_RST    		PCout(13)	//GT9147复位引脚
//#define GT_INT    		PBin(1)		//GT9147中断引脚

//#define GT911_RST_1()  PBout(11)=1	/* RST = 1 */
//#define GT911_RST_0()  PBout(11)=0	/* RST = 0 */

//#define GT911_INT_1()  	PDin(0)=1/* INT = 1 */
//#define GT911_INT_0()  	PDin(0)=0/* INT = 0 */

//----------------------------宏定义----------------------------//
//端口配置


#define GT911_RST_1() 	GPIO_SetBit(TP_GPIO_RST, TP_PIN_RST)
#define GT911_RST_0()  GPIO_ClrBit(TP_GPIO_RST, TP_PIN_RST)

#define GT911_INT_1()  	GPIO_SetBit(TP_GPIO_INT, TP_PIN_INT)
#define GT911_INT_0()  	GPIO_ClrBit(TP_GPIO_INT, TP_PIN_INT)


#define GT9x_ADDR 		0x5D

//I2C读写命令
#define GT_CMD_WR 		0X28     	//写命令
#define GT_CMD_RD 		0X29		//读命令

//GT9147 部分寄存器定义
#define GT_CTRL_REG 	0X8040   	//GT9147控制寄存器
#define GT_CFGS_REG 	0X8047   	//GT9147配置起始地址寄存器
#define GT_CHECK_REG 	0X80FF   	//GT9147校验和寄存器
#define GT_PID_REG 		0X8140   	//GT9147产品ID寄存器

#define GT_GSTID_REG 	0X814E   	//GT9147当前检测到的触摸情况
#define GT_TP1_REG 		0X8150  	//第一个触摸点数据地址
#define GT_TP2_REG 		0X8158		//第二个触摸点数据地址
#define GT_TP3_REG 		0X8160		//第三个触摸点数据地址
#define GT_TP4_REG 		0X8168		//第四个触摸点数据地址
#define GT_TP5_REG 		0X8170		//第五个触摸点数据地址


 //一下未使用
#define GT911_READ_XY_REG 					0x814E	/* 坐标寄存器 */
#define GT911_CLEARBUF_REG 					0x814E	/* 清除坐标寄存器 */
#define GT911_CONFIG_REG 						0x8047	/* 配置参数寄存器 */
#define GT911_COMMAND_REG 					0x8040 	/* 实时命令 */
#define GT911_PRODUCT_ID_REG 				0x8140 	/*productid*/
#define GT911_VENDOR_ID_REG 				0x814A 	/* 当前模组选项信息 */
#define GT911_CONFIG_VERSION_REG 		0x8047 	/* 配置文件版本号 */
#define GT911_CONFIG_CHECKSUM_REG 	0x80FF 	/* 配置文件校验码 */
#define GT911_FIRMWARE_VERSION_REG	0x8144 	/* 固件版本号 */



uint8_t GT911_Send_Cfg(uint8_t mode);
uint8_t GT911_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
uint8_t GT911_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
uint8_t GT911_Init(void);
uint8_t GT911_Scan(uint8_t mode);


void GT911_Reset_Sequence(uint8_t ucAddr);//使用
void GT911_Soft_Reset(void);//未使用
#endif













