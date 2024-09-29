#ifndef __GT911_H
#define __GT911_H
#include "dev_systick.h"//////////////////////////////////////////////////////////////////////////////////
//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ö»ï¿½ï¿½Ñ§Ï°Ê¹ï¿½Ã£ï¿½Î´ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½É£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Îºï¿½ï¿½ï¿½Í¾
//ALIENTEK STM32ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
//4.3ï¿½ï¿½ï¿½ï¿½Ý´ï¿½ï¿½ï¿½ï¿½ï¿?-GT9147 ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
//ï¿½ï¿½ï¿½ï¿½Ô­ï¿½ï¿½@ALIENTEK
//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì³:www.openedv.com
//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½:2015/12/28
//ï¿½æ±¾ï¿½ï¿½V1.0
//ï¿½ï¿½È¨ï¿½ï¿½ï¿½Ð£ï¿½ï¿½ï¿½ï¿½ï¿½Ø¾ï¿½ï¿½ï¿?
//Copyright(C) ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ó¿Æ¼ï¿½ï¿½ï¿½ï¿½Þ¹ï¿½Ë¾ 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////


//IOï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
//#define GT_RST    		PCout(13)	//GT9147ï¿½ï¿½Î»ï¿½ï¿½ï¿½ï¿½
//#define GT_INT    		PBin(1)		//GT9147ï¿½Ð¶ï¿½ï¿½ï¿½ï¿½ï¿½

//#define GT911_RST_1()  PBout(11)=1	/* RST = 1 */
//#define GT911_RST_0()  PBout(11)=0	/* RST = 0 */

//#define GT911_INT_1()  	PDin(0)=1/* INT = 1 */
//#define GT911_INT_0()  	PDin(0)=0/* INT = 0 */
//´¥ÃþÆÁ¿ØÖÆÆ÷
typedef struct
{
	uint8_t (*init)(void);			//³õÊ¼»¯´¥ÃþÆÁ¿ØÖÆÆ÷
	uint8_t (*scan)(uint8_t);				//É¨Ãè´¥ÃþÆÁ.0,ÆÁÄ»É¨Ãè;1,ÎïÀí×ø±ê;	 
	void (*adjust)(void);		//´¥ÃþÆÁÐ£×¼ 
	uint16_t x[5]; 		//µ±Ç°×ø±ê
	uint16_t y[5];		//µçÈÝÆÁÓÐ×î¶à5×é×ø±ê,µç×èÆÁÔòÓÃx[0],y[0]´ú±í:´Ë´ÎÉ¨ÃèÊ±,´¥ÆÁµÄ×ø±ê,ÓÃ
								//x[4],y[4]´æ´¢µÚÒ»´Î°´ÏÂÊ±µÄ×ø±ê. 
	uint8_t  status;					//±ÊµÄ×´Ì¬ 
								//b7:°´ÏÂ1/ËÉ¿ª0; 
	                            //b6:0,Ã»ÓÐ°´¼ü°´ÏÂ;1,ÓÐ°´¼ü°´ÏÂ. 
								//b5:±£Áô
								//b4~b0:µçÈÝ´¥ÃþÆÁ°´ÏÂµÄµãÊý(0,±íÊ¾Î´°´ÏÂ,1±íÊ¾°´ÏÂ)
/////////////////////´¥ÃþÆÁÐ£×¼²ÎÊý(µçÈÝÆÁ²»ÐèÒªÐ£×¼)//////////////////////								
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
//ÐÂÔöµÄ²ÎÊý,µ±´¥ÃþÆÁµÄ×óÓÒÉÏÏÂÍêÈ«µßµ¹Ê±ÐèÒªÓÃµ½.
//b0:0,ÊúÆÁ(ÊÊºÏ×óÓÒÎªX×ø±ê,ÉÏÏÂÎªY×ø±êµÄTP)
//   1,ºáÆÁ(ÊÊºÏ×óÓÒÎªY×ø±ê,ÉÏÏÂÎªX×ø±êµÄTP) 
//b1~6:±£Áô.
//b7:0,µç×èÆÁ
//   1,µçÈÝÆÁ 
	uint8_t touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//´¥ÆÁ¿ØÖÆÆ÷ÔÚtouch.cÀïÃæ¶¨Òå

#define GT911_RST_1() 	GPIO_SetBit(TP_GPIO_RST, TP_PIN_RST)
#define GT911_RST_0()  GPIO_ClrBit(TP_GPIO_RST, TP_PIN_RST)

#define GT911_INT_1()  	GPIO_SetBit(TP_GPIO_INT, TP_PIN_INT)
#define GT911_INT_0()  	GPIO_ClrBit(TP_GPIO_INT, TP_PIN_INT)


#define GT9x_ADDR 		0x5D

//I2Cï¿½ï¿½Ð´ï¿½ï¿½ï¿½ï¿½
#define GT_CMD_WR 		0X28     	//Ð´ï¿½ï¿½ï¿½ï¿½
#define GT_CMD_RD 		0X29		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½

//GT9147 ï¿½ï¿½ï¿½Ö¼Ä´ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
#define GT_CTRL_REG 	0X8040   	//GT9147ï¿½ï¿½ï¿½Æ¼Ä´ï¿½ï¿½ï¿½
#define GT_CFGS_REG 	0X8047   	//GT9147ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¼ï¿½ï¿½Ö·ï¿½Ä´ï¿½ï¿½ï¿½
#define GT_CHECK_REG 	0X80FF   	//GT9147Ð£ï¿½ï¿½Í¼Ä´ï¿½ï¿½ï¿?
#define GT_PID_REG 		0X8140   	//GT9147ï¿½ï¿½Æ·IDï¿½Ä´ï¿½ï¿½ï¿½

#define GT_GSTID_REG 	0X814E   	//GT9147ï¿½ï¿½Ç°ï¿½ï¿½âµ½ï¿½Ä´ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
#define GT_TP1_REG 		0X8150  	//ï¿½ï¿½Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ýµï¿½Ö·
#define GT_TP2_REG 		0X8158		//ï¿½Ú¶ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ýµï¿½Ö·
#define GT_TP3_REG 		0X8160		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ýµï¿½Ö·
#define GT_TP4_REG 		0X8168		//ï¿½ï¿½ï¿½Ä¸ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ýµï¿½Ö·
#define GT_TP5_REG 		0X8170		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ýµï¿½Ö?


 //Ò»ï¿½ï¿½Î´Ê¹ï¿½ï¿½
#define GT911_READ_XY_REG 					0x814E	/* ï¿½ï¿½ï¿½ï¿½Ä´ï¿½ï¿½ï¿? */
#define GT911_CLEARBUF_REG 					0x814E	/* ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä´ï¿½ï¿½ï¿½ */
#define GT911_CONFIG_REG 						0x8047	/* ï¿½ï¿½ï¿½Ã²ï¿½ï¿½ï¿½ï¿½Ä´ï¿½ï¿½ï¿½ */
#define GT911_COMMAND_REG 					0x8040 	/* ÊµÊ±ï¿½ï¿½ï¿½ï¿½ */
#define GT911_PRODUCT_ID_REG 				0x8140 	/*productid*/
#define GT911_VENDOR_ID_REG 				0x814A 	/* ï¿½ï¿½Ç°Ä£ï¿½ï¿½Ñ¡ï¿½ï¿½ï¿½ï¿½Ï¢ */
#define GT911_CONFIG_VERSION_REG 		0x8047 	/* ï¿½ï¿½ï¿½ï¿½ï¿½Ä¼ï¿½ï¿½æ±¾ï¿½ï¿½ */
#define GT911_CONFIG_CHECKSUM_REG 	0x80FF 	/* ï¿½ï¿½ï¿½ï¿½ï¿½Ä¼ï¿½Ð£ï¿½ï¿½ï¿½ï¿½ */
#define GT911_FIRMWARE_VERSION_REG	0x8144 	/* ï¿½Ì¼ï¿½ï¿½æ±¾ï¿½ï¿½ */



uint8_t GT911_Send_Cfg(uint8_t mode);
uint8_t GT911_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
uint8_t GT911_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
uint8_t GT911_Init(void);
uint8_t GT911_Scan(uint8_t mode);


void GT911_Reset_Sequence(uint8_t ucAddr);//Î´Ê¹ï¿½ï¿½
void GT911_Soft_Reset(void);//Î´Ê¹ï¿½ï¿½
#endif













