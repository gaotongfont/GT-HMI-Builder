#include "gt911.h"
#include "dev_touch.h"
#include "dev_systick.h"
#include "string.h"
#include "dev_lcd.h"
//////////////////////////////////////////////////////////////////////////////////
/* GT911����
�����¼��

// ���� оƬGT911
//T_PEN----PH7
//T_SCK----PH6
//T_MISO---PG3	��ʹ��
//T_MOSI---PI3
//T_CS-----PI8


*/
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////


/*
GT911 �Ĵ��豸��ַ�������ѡ�������ַ�ֱ�Ϊ��0xBA/0xBB��0x28/0x29
*/
#define GT911_I2C_ADDR	0xBA    //��ʹ��


//GT911���ò�����
//��һ���ֽ�Ϊ�汾��(0X60),���뱣֤�µİ汾�Ŵ��ڵ���GT911�ڲ�
//flashԭ�а汾��,�Ż��������.
const uint8_t GT911_CFG_TBL[]=   //���������޸���
{

	0x69,0xE0,0x01,0xE0,0x01,0x05,0x35,0x10,0x01,0x08,
	0x23,0x05,0x50,0x37,0x03,0x05,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x18,0x1A,0x1E,0x14,0x87,0x27,0x0E,
	0x38,0x3A,0x0C,0x08,0x00,0x00,0x00,0x9A,0x02,0x1C,
	0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,
	0x00,0x19,0x58,0x94,0xC5,0x02,0x07,0x00,0x00,0x04,
	0xF8,0x1C,0x00,0xC3,0x24,0x00,0x97,0x2F,0x00,0x77,
	0x3C,0x00,0x5D,0x4E,0x00,0x5D,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1C,0x1A,0x18,0x16,0x14,0x12,0x10,0x0E,
	0x0C,0x0A,0x08,0x06,0x04,0x02,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0x00,0x02,0x04,0x06,0x08,0x0A,0x0C,0x24,
	0x22,0x21,0x20,0x1F,0x1E,0x1D,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0x73,0x01

};
static inline void delay(void)
{
	#if 0
	for(uint32_t i = 0; i < CyclesPerUs; i++) 
		__NOP();
	#else 
    for (uint32_t i = 0; i < 600; i++)
        __NOP();
	#endif
}


//����GT9147���ò���
//mode:0,���������浽flash
//     1,�������浽flash
uint8_t GT911_Send_Cfg(uint8_t mode)//�޸�
{
	// uint8_t buf[2];
	// uint8_t i=0;
	// buf[0]=0;
	// buf[1]=mode;	//�Ƿ�д�뵽GT911 FLASH?  ���Ƿ���籣��
	// for(i=0;i<sizeof(GT911_CFG_TBL);i++)buf[0]+=GT911_CFG_TBL[i];//����У���
    // buf[0]=(~buf[0])+1;
	// GT911_WR_Reg(GT_CFGS_REG,(uint8_t*)GT911_CFG_TBL,sizeof(GT911_CFG_TBL));//���ͼĴ�������
	// GT911_WR_Reg(GT_CHECK_REG,buf,2);//д��У���,�����ø��±��
	// return 0;
}
//��GT9147д��һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:д���ݳ���
//����ֵ:0,�ɹ�;1,ʧ��.
uint8_t GT911_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
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

    for (i = 0; i < len; i++)
    {
        ack = I2C_Write(I2C0, buf[i], 1);
        if (ack == 0)
            goto wr_fail;
    }

    I2C_Stop(I2C0, 1);
    // delay();
    return 0;

wr_fail:
    I2C_Stop(I2C0, 1);
    // delay();
    return 1;
}
//��GT9147����һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:�����ݳ���
uint8_t GT911_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t i;
    uint8_t ack;

    ack = I2C_Start(I2C0, (GT9x_ADDR << 1) | 0, 1);
    if (ack == 0)
        goto rd_fail;

    ack = I2C_Write(I2C0, reg >> 8, 1);
    if (ack == 0)
        goto rd_fail;

    ack = I2C_Write(I2C0, reg & 0XFF, 1);
    if (ack == 0)
        goto rd_fail;

		swm_delay_ms(5);//delay();//�˴�������ʱ�ȴ�һ��������
	
    ack = I2C_Start(I2C0, (GT9x_ADDR << 1) | 1, 1); //ReStart
    if (ack == 0)
        goto rd_fail;

    for (i = 0; i < len - 1; i++)
    {
        buf[i] = I2C_Read(I2C0, 1, 1);
    }
    buf[i] = I2C_Read(I2C0, 0, 1);

    I2C_Stop(I2C0, 1);
    // delay();
    return 0;

rd_fail:
    I2C_Stop(I2C0, 1);
    // delay();
    return 1;
}
//��ʼ��GT9147������
//����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ��
uint8_t GT911_Init(void)
{
	uint8_t temp[4]; uint16_t i=0;

	I2C_InitStructure I2C_initStruct;

    PORT_Init(TP_PORT_SCL, TP_PIN_SCL, TP_PIN_SCL_FUN, 1); //����Ϊ I2C0 SCL ����
    TP_PORT_SCL->PULLU |= (1 << TP_PIN_SCL);               //����ʹ������
    TP_PORT_SCL->OPEND |= (1 << TP_PIN_SCL);	           //��©
    PORT_Init(TP_PORT_SDA, TP_PIN_SDA, TP_PIN_SDA_FUN, 1); //����Ϊ I2C0 SDA ����
    TP_PORT_SDA->PULLU |= (1 << TP_PIN_SDA);
    TP_PORT_SDA->OPEND |= (1 << TP_PIN_SDA);
	
    I2C_initStruct.Master = 1;
    I2C_initStruct.Addr10b = 0;
    I2C_initStruct.MstClk = 100000;
	I2C_initStruct.TXEmptyIEn = 0;	 //���ͼĴ������ж�ʹ��
	I2C_initStruct.RXNotEmptyIEn = 0;//���ռĴ����ǿ��ж�ʹ��
//	I2C_initStruct.SlvAddr = 0;
//	I2C_initStruct.SlvAddrMsk = 0;
//	I2C_initStruct.SlvSTADetIEn = 0;//�ӻ���⵽��ʼ�ж�ʹ��
//	I2C_initStruct.SlvSTODetIEn = 0;//�ӻ���⵽��ֹ�ж�ʹ��
    I2C_Init(I2C0, &I2C_initStruct);
    I2C_Open(I2C0);

    GPIO_Init(TP_GPIO_INT, TP_PIN_INT, 0, 0, 1, 0); // ���룬������������λʱINTΪ�ͣ�ѡ��0xBA��Ϊ��ַ

    GPIO_Init(TP_GPIO_RST, TP_PIN_RST, 1, 1, 0, 0); //��λ
		
    GPIO_ClrBit(TP_GPIO_RST, TP_PIN_RST);
    swm_delay_ms(10);
    GPIO_SetBit(TP_GPIO_RST, TP_PIN_RST); // �ͷŸ�λ
    swm_delay_ms(10);

    temp[0] = 0x02;
    GT911_WR_Reg(GT_CTRL_REG, temp, 1); // ��λ
    swm_delay_ms(100);

	swm_delay_ms(100);

	GT911_Reset_Sequence(0xBA);
	GT911_RD_Reg(GT_PID_REG,temp,4);//��ȡ��ƷID



	if(strcmp((char*)temp,"911")==0)//ID==9147
	{
		temp[0]=0X02;
		GT911_WR_Reg(GT_CTRL_REG,temp,1);//��λGT9147
		GT911_RD_Reg(GT_CFGS_REG,temp,1);//��ȡGT_CFGS_REG�Ĵ���
		if(temp[0]<0X69)//Ĭ�ϰ汾�Ƚϵ�,��Ҫ����flash����
		{
			printf("Default Ver:%x\r\n",temp[0]);

		}


		swm_delay_ms(10);
		temp[0]=0X00;
		GT911_WR_Reg(GT_CTRL_REG,temp,1);//������λ
		return 0;
	}
	return 1;
}

const uint16_t GT911_TPX_TBL[5]={GT_TP1_REG,GT_TP2_REG,GT_TP3_REG,GT_TP4_REG,GT_TP5_REG};
//ɨ�败����(���ò�ѯ��ʽ)
//mode:0,����ɨ��.
//����ֵ:��ǰ����״̬.
//0,�����޴���;1,�����д���
uint8_t GT911_Scan(uint8_t mode)
{
	uint8_t buf[4];
	uint8_t i=0;
	uint8_t res=0;
	uint8_t temp;
	uint8_t tempsta;
 	static uint8_t t=0;//���Ʋ�ѯ���,�Ӷ�����CPUռ����
	t++;
	if(((t%10)==0) || (t<10))//����ʱ,ÿ����10��CTP_Scan�����ż��1��,�Ӷ���ʡCPUʹ����
	{
		GT911_RD_Reg(GT_GSTID_REG,&mode,1);	//��ȡ�������״̬
		if (TP_Dev.status & TP_PRES_DOWN) {
			switch (mode) {
				case 0x00: {
					swm_delay_ms(1);
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
		
 		if(mode&0X80&&((mode&0XF)<6))
		{
			temp=0;
			GT911_WR_Reg(GT_GSTID_REG,&temp,1);//���־
		}
		if((mode&0XF)&&((mode&0XF)<6))
		{
			temp=0XFF<<(mode&0XF);		//����ĸ���ת��Ϊ1��λ��,ƥ��TP_Dev.sta����
			tempsta=TP_Dev.status;			//���浱ǰ��TP_Dev.staֵ
			TP_Dev.status=(~temp)|TP_PRES_DOWN|TP_CATH_PRES;
			TP_Dev.x[4]=TP_Dev.x[0];	//���津��0������
			TP_Dev.y[4]=TP_Dev.y[0];
			for(i=0;i<5;i++) //for(i=0;i<5;i++)
			{
				if(TP_Dev.status&(1<<i))	//������Ч?
				{
					GT911_RD_Reg(GT911_TPX_TBL[i],buf,4);	//��ȡXY����ֵ


						if(TP_Dev.touchtype&0X01)// ���� ////����ʹ�ã���
						{
							TP_Dev.x[i]=(((uint16_t)(buf[1]&0X0F)<<8)+buf[0]);//lcddev.width-
							//if(TP_Dev.x[i]<420)TP_Dev.x[i]=415-TP_Dev.x[i];
							TP_Dev.y[i]=((uint16_t)(buf[3]&0X0F)<<8)+buf[2];
//							_HW_DrawPoint(TP_Dev.x[i],TP_Dev.y[i],C_GREEN);
						}else
						{
							TP_Dev.x[i]=((uint16_t)(buf[1]&0X0F)<<8)+buf[0];
							TP_Dev.y[i]=((uint16_t)(buf[3]&0X0F)<<8)+buf[2];
//							_HW_DrawPoint(TP_Dev.x[i],TP_Dev.y[i],C_GREEN);
						}

					// if((buf[0]&0XF0)!=0X80)TP_Dev.x[i]=TP_Dev.y[i]=0;//������contact�¼�������Ϊ��Ч    ���ʲô��˼

//					printf("x[%d]:%d,y[%d]:%d\r\n",i,TP_Dev.x[i],i,TP_Dev.y[i]);
				}
			}
			res=1;
			if(TP_Dev.x[0]>LCD_VDOT||TP_Dev.y[0]>LCD_HDOT)//�Ƿ�����(���곬����)
			{
				if((mode&0XF)>1)		//��������������,�򸴵ڶ�����������ݵ���һ������.
				{
					TP_Dev.x[0]=TP_Dev.x[1];
					TP_Dev.y[0]=TP_Dev.y[1];
					t=0;				//����һ��,��������������10��,�Ӷ����������
				}else					//�Ƿ�����,����Դ˴�����(��ԭԭ����)
				{
					TP_Dev.x[0]=TP_Dev.x[4];
					TP_Dev.y[0]=TP_Dev.y[4];
					mode=0X80;
					TP_Dev.status=tempsta;	//�ָ�TP_Dev.sta
				}
			}else t=0;					//����һ��,��������������10��,�Ӷ����������
		}
	}
ret_lb:
	if((mode&0X8F)==0X80)//�޴����㰴��
	{
		if(TP_Dev.status&TP_PRES_DOWN)	//֮ǰ�Ǳ����µ�
		{
			TP_Dev.status&=~(1<<7);	//��ǰ����ɿ�
//			printf("�����ɿ�");
		}else						//֮ǰ��û�б�����
		{
			TP_Dev.x[0]=0xffff;
			TP_Dev.y[0]=0xffff;
			TP_Dev.status&=0XE0;	//�������Ч���
//			printf("û�а�������");
		}
	}
	if(t>240)t=10;//���´�10��ʼ����
	// printf("���е�SCAN %d\n", res);
	return res;
}




//���Ӳ��λ  ��λ��911��ַ����Ϊ0xBA/0xBB
//�������溯��ǰIOҪ��ʼ��
/*
*********************************************************************************************************
*	�� �� ��: GT911_Reset_Sequence
*	����˵��: G911Ӳ��λ����,RSTΪ�͵�ƽʱ��INT����Ϊ�͵�ƽ��1ms��RST��Ϊ�ߵ�ƽ��10ms��INT����Ϊ���룬
*	ʹGT911��ַ�趨Ϊ0xBA/0xBB��
*	�� ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void GT911_Reset_Sequence(uint8_t ucAddr) //δʹ��
{
//GT911_RST_INT_GPIO_Init();
	switch(ucAddr)
	{
		case 0xBA:
							GT911_RST_0(); //RST���ŵ͵�ƽ
							GT911_INT_0(); //INT���ŵ͵�ƽ
							swm_delay_ms(30); //��ʱ30ms�����1
							GT911_RST_1(); //RST���Ÿߵ�ƽ
							GT911_INT_0(); //INT���ŵ͵�ƽ
							swm_delay_ms(30); //��ʱ30ms�����20
							GT911_INT_0();
							swm_delay_ms(30); //��ʱ30ms�����20
							GT911_INT_1();
							break;
		case 0x28:
							GT911_RST_0(); //RST���ŵ͵�ƽ
							GT911_INT_1(); //INT���Ÿߵ�ƽ
							swm_delay_ms(30); //��ʱ30ms�����1
							GT911_RST_1(); //RST���Ÿߵ�ƽ
							GT911_INT_1(); //INT���Ÿߵ�ƽ
							swm_delay_ms(30); //��ʱ30ms�����20
							GT911_INT_0();
							swm_delay_ms(30); //��ʱ30ms�����20
							GT911_INT_1();
							break;
		default: //ȱʡΪ0xBA
							GT911_RST_0(); //RST���ŵ͵�ƽ
							GT911_INT_0(); //INT���ŵ͵�ƽ
							swm_delay_ms(30); //��ʱ30ms�����1
							GT911_RST_1(); //RST���Ÿߵ�ƽ
							GT911_INT_0(); //INT���ŵ͵�ƽ
							swm_delay_ms(30); //��ʱ30ms�����20
							GT911_INT_0();
							swm_delay_ms(30); //��ʱ30ms�����20
							GT911_INT_1();
							break;

	}
}


/*
*********************************************************************************************************
*	�� �� ��: GT911_Soft_Reset
*	����˵��: G911��λ������
*	�� ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void GT911_Soft_Reset(void) //δʹ��
{
	uint8_t buf[1];
	buf[0] = 0x01;
	GT911_WR_Reg(GT911_COMMAND_REG, (uint8_t *)buf, 1);
}


























