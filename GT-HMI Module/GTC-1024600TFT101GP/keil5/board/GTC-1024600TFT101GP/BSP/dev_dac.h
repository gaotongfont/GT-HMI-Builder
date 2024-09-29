/**************************************************************************/ /**
 * @file     dev_dac.h
 * @brief    dac相关配置函数
 * @version  V1.0
 * @date     2021.11.11
 ******************************************************************************/
#ifndef __DEV_DAC_H__
#define __DEV_DAC_H__

void dac_init(void);
void dac_dma_init(uint32_t addr, uint32_t count);
void dac_deinit(void);

#endif //__DEV_DAC_H__
