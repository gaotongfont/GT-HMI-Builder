/**************************************************************************/ /**
 * @file     dev_dac.c
 * @brief    dac相关配置函数
 * @version  V1.0
 * @date     2021.11.11
 ******************************************************************************/
#include "SWM341.h"

/**
  \brief   dac初始化
  \param [in]   无
  \return       无
  \note
 */
void dac_init(void)
{
    PORT_Init(PORTD, PIN2, PORTD_PIN2_DAC_OUT, 0);
    DAC_Init(DAC, DAC_FORMAT_MSB12B); //DHR高12位传输给DOR
    /* 测试设置 */
    SYS->DACCR &= ~(0x0F << 2);
    SYS->DACCR |= ~(0x14 << 2);

    DAC_Open(DAC);
}

/**
  \brief   dac dma初始化
  \param [in]   addr    dac dma传输数据源地址
  \param [in]   count   传输 Unit 个数
  \return       无
  \note
 */
void dac_dma_init(uint32_t addr, uint32_t count)
{
    DMA_InitStructure DMA_initStruct;

    DMA_initStruct.Mode = DMA_MODE_SINGLE;
    DMA_initStruct.Unit = DMA_UNIT_HALFWORD;
    DMA_initStruct.Count = count;
    DMA_initStruct.SrcAddr = addr;
    DMA_initStruct.SrcAddrInc = 1;
    DMA_initStruct.DstAddr = (uint32_t)&DAC->DHR;
    DMA_initStruct.DstAddrInc = 0;
    DMA_initStruct.Priority = DMA_PRI_LOW;
//    DMA_initStruct.INTEn = 1;
    DMA_initStruct.Handshake = DMA_EXHS_TIMR0;

    DMA_CH_Init(DMA_CH0, &DMA_initStruct);
    DMA_CH_Open(DMA_CH0);
}

/**
  \brief   dac反初始化
  \param [in]   无
  \return       无
  \note
 */
void dac_deinit(void)
{
    DMA_CH_Close(DMA_CH0);
    DAC_Close(DAC);
    TIMR_Stop(TIMR0);
}
