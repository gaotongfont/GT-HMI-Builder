#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "SWM341.h"

#define TP_PRES_DOWN 0x80  //触屏被按下	  
#define TP_CATH_PRES 0x40  //有按键按下了 


//触摸屏控制器
typedef struct
{
	uint8_t (*init)(void);			//初始化触摸屏控制器
	uint8_t (*scan)(uint8_t);				//扫描触摸屏.0,屏幕扫描;1,物理坐标;	 
	void (*adjust)(void);		//触摸屏校准 
	uint16_t x[5]; 		//当前坐标
	uint16_t y[5];		//电容屏有最多5组坐标,电阻屏则用x[0],y[0]代表:此次扫描时,触屏的坐标,用
								//x[4],y[4]存储第一次按下时的坐标. 
	uint8_t  status;					//笔的状态 
								//b7:按下1/松开0; 
	                            //b6:0,没有按键按下;1,有按键按下. 
								//b5:保留
								//b4~b0:电容触摸屏按下的点数(0,表示未按下,1表示按下)
/////////////////////触摸屏校准参数(电容屏不需要校准)//////////////////////								
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
//新增的参数,当触摸屏的左右上下完全颠倒时需要用到.
//b0:0,竖屏(适合左右为X坐标,上下为Y坐标的TP)
//   1,横屏(适合左右为Y坐标,上下为X坐标的TP) 
//b1~6:保留.
//b7:0,电阻屏
//   1,电容屏 
	uint8_t touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//触屏控制器在touch.c里面定义

//电阻屏芯片连接引脚	   
//#define PEN  		PBin(7)  	//T_PEN

#define PORT_TSCL GPIOA
#define PIN_TSCL  PIN1

#define PORT_TSDO GPIOA
#define PIN_TSDO  PIN0

#define PORT_TPEN GPIOD
#define PIN_TPEN  PIN0

#define PORT_TCS GPIOA
#define PIN_TCS  PIN5

#define PORT_TSDI GPIOC
#define PIN_TSDI  PIN7

#define DOUT_Clr 		GPIO_AtomicClrBit(PORT_TSDI, PIN_TSDI);		//T_MISO
#define DOUT_Set 		GPIO_AtomicSetBit(PORT_TSDI, PIN_TSDI);

#define TDIN_Clr 		GPIO_AtomicClrBit(PORT_TSDO, PIN_TSDO);		//T_MOSI
#define TDIN_Set 		GPIO_AtomicSetBit(PORT_TSDO, PIN_TSDO);

#define TCLK_Clr 		GPIO_AtomicClrBit(PORT_TSCL, PIN_TSCL);		//T_SCK
#define TCLK_Set 		GPIO_AtomicSetBit(PORT_TSCL, PIN_TSCL);

#define TCS_Clr 		GPIO_AtomicClrBit(PORT_TCS, PIN_TCS);		//T_CS  
#define TCS_Set 		GPIO_AtomicSetBit(PORT_TCS, PIN_TCS);
	




//电阻屏函数
void TP_Write_Byte(uint8_t num);						//向控制芯片写入一个数据
uint16_t TP_Read_AD(uint8_t CMD);							//读取AD转换值
uint16_t TP_Read_XOY(uint8_t xy);							//带滤波的坐标读取(X/Y)
uint8_t TP_Read_XY(uint16_t *x,uint16_t *y);					//双方向读取(X+Y)
uint8_t TP_Read_XY2(uint16_t *x,uint16_t *y);					//带加强滤波的双方向坐标读取
uint8_t TP_Scan(uint8_t tp);								//扫描
uint8_t TP_Init(void);//初始化
void TP_Adjust(void);
void RTP_Read(void);
uint8_t TP_Get_Adjdata(void);
#endif

