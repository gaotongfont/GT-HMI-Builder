#ifndef __GT911_H
#define __GT911_H

#include "dev_systick.h"

typedef struct {
	uint8_t (*init)(void);
	uint8_t (*scan)(uint8_t);
	void (*adjust)(void);
	uint16_t x[5];
	uint16_t y[5];
	uint8_t  status;
	float xfac;
	float yfac;
	short xoff;
	short yoff;
	uint8_t touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;

#define GT911_RST_1() 	GPIO_SetBit(TP_GPIO_RST, TP_PIN_RST)
#define GT911_RST_0()  GPIO_ClrBit(TP_GPIO_RST, TP_PIN_RST)

#define GT911_INT_1()  	GPIO_SetBit(TP_GPIO_INT, TP_PIN_INT)
#define GT911_INT_0()  	GPIO_ClrBit(TP_GPIO_INT, TP_PIN_INT)

#define GT9x_ADDR 		0x5D

#define GT_CMD_WR 		0X28
#define GT_CMD_RD 		0X29

#define GT_CTRL_REG 	0X8040
#define GT_CFGS_REG 	0X8047
#define GT_CHECK_REG 	0X80FF
#define GT_PID_REG 		0X8140

#define GT_GSTID_REG 	0X814E
#define GT_TP1_REG 		0X8150
#define GT_TP2_REG 		0X8158
#define GT_TP3_REG 		0X8160
#define GT_TP4_REG 		0X8168
#define GT_TP5_REG 		0X8170

#define GT911_READ_XY_REG 			0x814E
#define GT911_CLEARBUF_REG 			0x814E
#define GT911_CONFIG_REG 			0x8047
#define GT911_COMMAND_REG 			0x8040
#define GT911_PRODUCT_ID_REG 		0x8140
#define GT911_VENDOR_ID_REG 		0x814A
#define GT911_CONFIG_VERSION_REG 	0x8047
#define GT911_CONFIG_CHECKSUM_REG 	0x80FF
#define GT911_FIRMWARE_VERSION_REG	0x8144


uint8_t GT911_Send_Cfg(uint8_t mode);
uint8_t GT911_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
uint8_t GT911_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
uint8_t GT911_Init(void);
uint8_t GT911_Scan(uint8_t mode);

void GT911_Reset_Sequence(uint8_t ucAddr);
void GT911_Soft_Reset(void);

#endif
