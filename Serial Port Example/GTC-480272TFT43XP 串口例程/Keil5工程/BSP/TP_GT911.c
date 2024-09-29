//----------------------------头文件依赖----------------------------//
#include "TP_GT911.h"
#include "SWM341.h"
#include "dev_systick.h"
#include "string.h"
/* Tips : 本驱动例程为触摸 IC : GT911 */

//----------------------------本地宏定义----------------------------//
#define GT9x_ADDR 		0x5D

#define GT9x_CTRL 		0x8040  //gt9x控制寄存器
#define GT9x_CFGS 		0x8047  //gt9x配置寄存器
#define GT9x_CHECK 		0x80FF 	//gt9x校验和寄存器
#define GT9x_PID 		0x8140  //gt9x产品ID寄存器

#define GT9x_GSTID 		0x814E	//当前检测到的触摸情况
#define GT9x_TP1 		0x8150	//第一个触摸点数据地址
#define GT9x_TP2 		0x8158	//第二个触摸点数据地址
#define GT9x_TP3 		0x8160	//第三个触摸点数据地址
#define GT9x_TP4 		0x8168	//第四个触摸点数据地址
#define GT9x_TP5 		0x8170	//第五个触摸点数据地址

//----------------------------本地全局变量----------------------------//
static const uint16_t GT9x_TP_Tab[5] = {GT9x_TP1, GT9x_TP2, GT9x_TP3, GT9x_TP4, GT9x_TP5};

/*********************************************************************************
 * 如果需要更新触摸配置请定义宏 UPDATE_CFG, 否则默认无须更新, 请在更新前咨询 TP 厂家
**********************************************************************************/
//#define UPDATE_CFG
#ifdef UPDATE_CFG 
//配置文件的版本号(新下发的配置版本号大于原版本，或等于原版本号但配置内容有变化时保存，
//版本号版本正常范围：'A'~'Z',发送 0x00 则将版本号初始化为'A')
static uint8_t GT9x_CFG_Tab[] = {
    0x00,       //config_version
    0xE0, 0x01, //x output max
    0x10, 0x01, //y output max
    0x05,       //touch number
    0x3D, 0x00, //module switch
    0x02, 0x08, 0x1E, 0x08, 0x50, 0x3C, 0x0F, 0x05,
    0x00, 0x00, 0xFF, 0x67, 0x50, 0x00, 0x00, 0x18,
    0x1A, 0x1E, 0x14, 0x89, 0x28, 0x0A, 0x30, 0x2E,
    0xBB, 0x0A, 0x03, 0x00, 0x00, 0x02, 0x33, 0x1D,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32,
    0x00, 0x00, 0x2A, 0x1C, 0x5A, 0x94, 0xC5, 0x02,
    0x07, 0x00, 0x00, 0x00, 0xB5, 0x1F, 0x00, 0x90,
    0x28, 0x00, 0x77, 0x32, 0x00, 0x62, 0x3F, 0x00,
    0x52, 0x50, 0x00, 0x52, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0F, 0x0F, 0x03, 0x06, 0x10,
    0x42, 0xF8, 0x0F, 0x14, 0x00, 0x00, 0x00, 0x00,
    0x1A, 0x18, 0x16, 0x14, 0x12, 0x10, 0x0E, 0x0C,
    0x0A, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x28,
    0x24, 0x22, 0x20, 0x1F, 0x1E, 0x1D, 0x0E, 0x0C,
    0x0A, 0x08, 0x06, 0x05, 0x04, 0x02, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
#endif

//----------------------------本地函数定义----------------------------//
#ifdef UPDATE_CFG 
//更新触摸芯片配置函数
static bool gt9x_update_cfg(void)
{
    uint8_t buf[2];
    uint8_t i = 0;

    /* set x range */
    GT9x_CFG_Tab[2] = (uint8_t)(LCD_HOR >> 8);
    GT9x_CFG_Tab[1] = (uint8_t)(LCD_HOR & 0xff);

    /* set y range */
    GT9x_CFG_Tab[4] = (uint8_t)(LCD_VER >> 8);
    GT9x_CFG_Tab[3] = (uint8_t)(LCD_VER & 0xff);

    /* change x y */
    // GT9x_CFG_Tab[6] ^= (1 << 3);

    /* change int trig type */
    /* FLAG_INT_FALL_RX */
    GT9x_CFG_Tab[6] &= 0xFC;
    GT9x_CFG_Tab[6] |= 0x01;
    /* FLAG_RDONLY */
    // GT9x_CFG_Tab[6] &= 0xFC;
    // GT9x_CFG_Tab[6] |= 0x03;

    if (touch_write_regs(GT9x_CFGS, GT9x_CFG_Tab, sizeof(GT9x_CFG_Tab)) != 0) /* send config */
    {
        DEBUG("send config failed\n");
        return false;
    }

    buf[0] = 0;
    for (i = 0; i < sizeof(GT9x_CFG_Tab); i++)
        buf[0] += GT9x_CFG_Tab[i];
    buf[0] = (~buf[0]) + 1;
    buf[1] = 1;
    touch_write_regs(GT9x_CHECK, buf, 2);
    swm_delay_ms(10);

	return true;
}
#endif

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

// TP_IC 写入寄存器
static uint32_t touch_write_regs(uint16_t reg, uint8_t *buf, uint8_t len)
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
    delay();
    return 0;

wr_fail:
    I2C_Stop(I2C0, 1);
    delay();
    return 1;
}

// TP_IC 读取寄存器
static uint32_t touch_read_regs(uint16_t reg, uint8_t *buf, uint8_t len)
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

	delay();//此处必须延时等待一会再启动
	
    ack = I2C_Start(I2C0, (GT9x_ADDR << 1) | 1, 1); //ReStart
    if (ack == 0)
        goto rd_fail;

    for (i = 0; i < len - 1; i++)
    {
        buf[i] = I2C_Read(I2C0, 1, 1);
    }
    buf[i] = I2C_Read(I2C0, 0, 1);

    I2C_Stop(I2C0, 1);
    delay();
    return 0;

rd_fail:
    I2C_Stop(I2C0, 1);
    delay();
    return 1;
}

//------------------------------对外接口------------------------------//
/**
  \brief		TP_IC 读取触摸点
  \param [in]	tp_dev_t 
  \return       0 : success    非0: error
  \note    		\
 */
uint8_t gt9x_read_points(tp_dev_t *tp_dev)
{
    uint8_t temp_status = 0, touch_num = 0, temp = 0;
    uint8_t buf[5] = {0};

    touch_read_regs(GT9x_GSTID, &temp_status, 1);
    touch_num = temp_status & 0x0F;
	
    if ((temp_status & 0x80) && (touch_num < 6))
    {
        touch_write_regs(GT9x_GSTID, &temp, 1); // 清除READY标志
    }
    if ((0 != touch_num) && (touch_num < 6))
    {
        touch_read_regs(GT9x_TP_Tab[0], buf, 4); //读取XY坐标值

        tp_dev->x[0] = /*LV_HOR_RES_MAX -*/ (((uint16_t)buf[1] << 8) + buf[0]); // x 坐标偏移
        
		#if (4 == __RESOLUTION_TARGET__ && 1 == LCD_TYPE) // 1024*600 H743(玫瑰科技)
		tp_dev->y[0] = /*LV_VER_RES_MAX -*/ (((uint16_t)buf[3] << 8) + buf[2]);	// y 坐标偏移
		#else //晶力泰
		tp_dev->y[0] = LV_VER_RES_MAX - (((uint16_t)buf[3] << 8) + buf[2]);		// y 坐标偏移
		#endif
        tp_dev->status = TP_PRES_DOWN;//标记按键按下
    }
    if ((temp_status & 0x8F) == 0x80) //无触摸点按下
    {
        tp_dev->x[0] = 0xFFFF;
        tp_dev->y[0] = 0xFFFF;
        tp_dev->status &= ~TP_PRES_DOWN; //标记按键松开
    }
    return 0;
}

/**
  \brief		TP_IC 初始化
  \param [in]	\
  \return       0 : success    非0: error
  \note    		\
 */
uint8_t gt9x_init(void)
{
    uint8_t temp[5] = {0};
    I2C_InitStructure I2C_initStruct;

    PORT_Init(TP_PORT_SCL, TP_PIN_SCL, TP_PIN_SCL_FUN, 1); //配置为 I2C0 SCL 引脚
    TP_PORT_SCL->PULLU |= (1 << TP_PIN_SCL);               //必须使能上拉
    TP_PORT_SCL->OPEND |= (1 << TP_PIN_SCL);	           //开漏
    PORT_Init(TP_PORT_SDA, TP_PIN_SDA, TP_PIN_SDA_FUN, 1); //配置为 I2C0 SDA 引脚
    TP_PORT_SDA->PULLU |= (1 << TP_PIN_SDA);
    TP_PORT_SDA->OPEND |= (1 << TP_PIN_SDA);
	
    I2C_initStruct.Master = 1;
    I2C_initStruct.Addr10b = 0;
    I2C_initStruct.MstClk = 400000;
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
    GPIO_ClrBit(TP_GPIO_INT, TP_PIN_INT);
    swm_delay_ms(10);
    GPIO_SetBit(TP_GPIO_RST, TP_PIN_RST); // 释放复位
    swm_delay_ms(10);

    GPIO_Init(TP_GPIO_INT, TP_PIN_INT, 0, 0, 1, 0);
    temp[0] = 0x02;
    touch_write_regs(GT9x_CTRL, temp, 1); // 软复位
    swm_delay_ms(100);

#ifdef UPDATE_CFG //更新触摸芯片配置
    gt9x_update_cfg();
#endif

    touch_read_regs(GT9x_PID, temp, 4);
    printf("Touch IC id:%s\r\n", temp);
    if (NULL == strstr((const char *)temp, "911")) // ID 验证
    {
        return 1;
    }
    return 0;
}
