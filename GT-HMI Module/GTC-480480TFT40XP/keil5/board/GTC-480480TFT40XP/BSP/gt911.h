#ifndef __GT911_H
#define __GT911_H
#include "dev_systick.h"//////////////////////////////////////////////////////////////////////////////////



//IO��������
//#define GT_RST    		PCout(13)	//GT9147��λ����
//#define GT_INT    		PBin(1)		//GT9147�ж�����

//#define GT911_RST_1()  PBout(11)=1	/* RST = 1 */
//#define GT911_RST_0()  PBout(11)=0	/* RST = 0 */

//#define GT911_INT_1()  	PDin(0)=1/* INT = 1 */
//#define GT911_INT_0()  	PDin(0)=0/* INT = 0 */

//----------------------------�궨��----------------------------//
//�˿�����


#define GT911_RST_1() 	GPIO_SetBit(TP_GPIO_RST, TP_PIN_RST)
#define GT911_RST_0()  GPIO_ClrBit(TP_GPIO_RST, TP_PIN_RST)

#define GT911_INT_1()  	GPIO_SetBit(TP_GPIO_INT, TP_PIN_INT)
#define GT911_INT_0()  	GPIO_ClrBit(TP_GPIO_INT, TP_PIN_INT)


#define GT9x_ADDR 		0x5D

//I2C��д����
#define GT_CMD_WR 		0X28     	//д����
#define GT_CMD_RD 		0X29		//������

//GT9147 ���ּĴ�������
#define GT_CTRL_REG 	0X8040   	//GT9147���ƼĴ���
#define GT_CFGS_REG 	0X8047   	//GT9147������ʼ��ַ�Ĵ���
#define GT_CHECK_REG 	0X80FF   	//GT9147У��ͼĴ���
#define GT_PID_REG 		0X8140   	//GT9147��ƷID�Ĵ���

#define GT_GSTID_REG 	0X814E   	//GT9147��ǰ��⵽�Ĵ������
#define GT_TP1_REG 		0X8150  	//��һ�����������ݵ�ַ
#define GT_TP2_REG 		0X8158		//�ڶ������������ݵ�ַ
#define GT_TP3_REG 		0X8160		//���������������ݵ�ַ
#define GT_TP4_REG 		0X8168		//���ĸ����������ݵ�ַ
#define GT_TP5_REG 		0X8170		//��������������ݵ�ַ


 //һ��δʹ��
#define GT911_READ_XY_REG 					0x814E	/* ����Ĵ��� */
#define GT911_CLEARBUF_REG 					0x814E	/* �������Ĵ��� */
#define GT911_CONFIG_REG 						0x8047	/* ���ò����Ĵ��� */
#define GT911_COMMAND_REG 					0x8040 	/* ʵʱ���� */
#define GT911_PRODUCT_ID_REG 				0x8140 	/*productid*/
#define GT911_VENDOR_ID_REG 				0x814A 	/* ��ǰģ��ѡ����Ϣ */
#define GT911_CONFIG_VERSION_REG 		0x8047 	/* �����ļ��汾�� */
#define GT911_CONFIG_CHECKSUM_REG 	0x80FF 	/* �����ļ�У���� */
#define GT911_FIRMWARE_VERSION_REG	0x8144 	/* �̼��汾�� */



uint8_t GT911_Send_Cfg(uint8_t mode);
uint8_t GT911_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
uint8_t GT911_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
uint8_t GT911_Init(void);
uint8_t GT911_Scan(uint8_t mode);


void GT911_Reset_Sequence(uint8_t ucAddr);//ʹ��
void GT911_Soft_Reset(void);//δʹ��
#endif













