/**
 * @file bsp_qspi_flash.h
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-07 16:05:38
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */
#ifndef _BSP_QSPI_FLASH_H_
#define _BSP_QSPI_FLASH_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include "bsp.h"


/* define ---------------------------------------------------------------*/
#define QSPI_FLASH_SECTOR_SIZE           4096
#define QSPI_FLASH_PAGE_SIZE             256
#define QSPI_FLASH_FIFO_DEPTH            (32*4)

#define QSPI_FLASH_QSPIx                 QSPI1
#define QSPI_FLASH_QSPI_CLK              CRM_QSPI1_PERIPH_CLOCK

#define QSPI_FLASH_CS_GPIO_CLK           CRM_GPIOB_PERIPH_CLOCK
#define QSPI_FLASH_CS_GPIO_PIN           GPIO_PINS_10
#define QSPI_FLASH_CS_GPIO_PINS_SOURCE   GPIO_PINS_SOURCE10
#define QSPI_FLASH_CS_GPIO_PORT          GPIOB
#define QSPI_FLASH_CS_GPIO_MUX           GPIO_MUX_9

#define QSPI_FLASH_CLK_GPIO_CLK          CRM_GPIOD_PERIPH_CLOCK
#define QSPI_FLASH_CLK_GPIO_PIN          GPIO_PINS_3
#define QSPI_FLASH_CLK_GPIO_PINS_SOURCE  GPIO_PINS_SOURCE3
#define QSPI_FLASH_CLK_GPIO_PORT         GPIOD
#define QSPI_FLASH_CLK_GPIO_MUX          GPIO_MUX_9

#define QSPI_FLASH_D0_GPIO_CLK           CRM_GPIOB_PERIPH_CLOCK
#define QSPI_FLASH_D0_GPIO_PIN           GPIO_PINS_0
#define QSPI_FLASH_D0_GPIO_PINS_SOURCE   GPIO_PINS_SOURCE0
#define QSPI_FLASH_D0_GPIO_PORT          GPIOB
#define QSPI_FLASH_D0_GPIO_MUX           GPIO_MUX_10

#define QSPI_FLASH_D1_GPIO_CLK           CRM_GPIOA_PERIPH_CLOCK
#define QSPI_FLASH_D1_GPIO_PIN           GPIO_PINS_7
#define QSPI_FLASH_D1_GPIO_PINS_SOURCE   GPIO_PINS_SOURCE7
#define QSPI_FLASH_D1_GPIO_PORT          GPIOA
#define QSPI_FLASH_D1_GPIO_MUX           GPIO_MUX_10

#define QSPI_FLASH_D2_GPIO_CLK           CRM_GPIOC_PERIPH_CLOCK
#define QSPI_FLASH_D2_GPIO_PIN           GPIO_PINS_4
#define QSPI_FLASH_D2_GPIO_PINS_SOURCE   GPIO_PINS_SOURCE4
#define QSPI_FLASH_D2_GPIO_PORT          GPIOC
#define QSPI_FLASH_D2_GPIO_MUX           GPIO_MUX_10

#define QSPI_FLASH_D3_GPIO_CLK           CRM_GPIOB_PERIPH_CLOCK
#define QSPI_FLASH_D3_GPIO_PIN           GPIO_PINS_3
#define QSPI_FLASH_D3_GPIO_PINS_SOURCE   GPIO_PINS_SOURCE3
#define QSPI_FLASH_D3_GPIO_PORT          GPIOB
#define QSPI_FLASH_D3_GPIO_MUX           GPIO_MUX_10


/* typedef --------------------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void bsp_qspi_flash_init(void);
uint32_t bsp_qspi_flash_read_id(void);
int bsp_qspi_flash_erase(uint32_t addr);
int bsp_qspi_flash_read(uint32_t addr , uint32_t length , uint8_t *buf);
int bsp_qspi_flash_write(uint32_t addr , uint32_t length , const uint8_t *buf);
uint8_t bsp_qspi_flash_read_status_reg2(void);
uint8_t bsp_qspi_flash_read_status_reg1(void);
bool bsp_qspi_flash_busy_check(void);
bool bsp_qspi_flash_read_qe(void);

//
unsigned long r_dat_bat(unsigned long address,unsigned long DataLen,unsigned char *pBuff);
unsigned char gt_read_data(unsigned char* sendbuf , unsigned char sendlen , unsigned char* receivebuf, unsigned int receivelen);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_BSP_QSPI_FLASH_H_

/* end of file ----------------------------------------------------------*/


