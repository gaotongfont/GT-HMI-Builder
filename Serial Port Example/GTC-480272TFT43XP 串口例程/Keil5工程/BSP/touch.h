#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "SWM341.h"

#define TP_PRES_DOWN 0x80  //����������	  
#define TP_CATH_PRES 0x40  //�а��������� 


//������������
typedef struct
{
	uint8_t (*init)(void);			//��ʼ��������������
	uint8_t (*scan)(uint8_t);				//ɨ�败����.0,��Ļɨ��;1,��������;	 
	void (*adjust)(void);		//������У׼ 
	uint16_t x[5]; 		//��ǰ����
	uint16_t y[5];		//�����������5������,����������x[0],y[0]����:�˴�ɨ��ʱ,����������,��
								//x[4],y[4]�洢��һ�ΰ���ʱ������. 
	uint8_t  status;					//�ʵ�״̬ 
								//b7:����1/�ɿ�0; 
	                            //b6:0,û�а�������;1,�а�������. 
								//b5:����
								//b4~b0:���ݴ��������µĵ���(0,��ʾδ����,1��ʾ����)
/////////////////////������У׼����(����������ҪУ׼)//////////////////////								
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
//�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
//b0:0,����(�ʺ�����ΪX����,����ΪY�����TP)
//   1,����(�ʺ�����ΪY����,����ΪX�����TP) 
//b1~6:����.
//b7:0,������
//   1,������ 
	uint8_t touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//������������touch.c���涨��

//������оƬ��������	   
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
	




//����������
void TP_Write_Byte(uint8_t num);						//�����оƬд��һ������
uint16_t TP_Read_AD(uint8_t CMD);							//��ȡADת��ֵ
uint16_t TP_Read_XOY(uint8_t xy);							//���˲��������ȡ(X/Y)
uint8_t TP_Read_XY(uint16_t *x,uint16_t *y);					//˫�����ȡ(X+Y)
uint8_t TP_Read_XY2(uint16_t *x,uint16_t *y);					//����ǿ�˲���˫���������ȡ
uint8_t TP_Scan(uint8_t tp);								//ɨ��
uint8_t TP_Init(void);//��ʼ��
void TP_Adjust(void);
void RTP_Read(void);
uint8_t TP_Get_Adjdata(void);
#endif

