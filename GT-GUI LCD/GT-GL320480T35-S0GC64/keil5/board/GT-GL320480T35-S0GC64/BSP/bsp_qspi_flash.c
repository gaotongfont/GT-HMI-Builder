/**
 * @file bsp_qspi_flash.c
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-07 16:05:28
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "bsp_qspi_flash.h"
#include "bsp_delay.h"

/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/
static qspi_cmd_type _qspi_flash_cmd_config;



/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/
static void _qspi_flash_cmd_read_config_eb(qspi_cmd_type *qspi_cmd_struct, uint32_t addr, uint32_t counter)
{
    qspi_cmd_struct->pe_mode_enable = FALSE;
    qspi_cmd_struct->pe_mode_operate_code = 0;
    qspi_cmd_struct->instruction_code = 0xEB;
    qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
    qspi_cmd_struct->address_code = addr;
    qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_3_BYTE;
    qspi_cmd_struct->data_counter = counter;
    qspi_cmd_struct->second_dummy_cycle_num = 6;
    qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_144;
    qspi_cmd_struct->read_status_config = QSPI_RSTSC_HW_AUTO;
    qspi_cmd_struct->read_status_enable = FALSE;
    qspi_cmd_struct->write_data_enable = FALSE;
}

static void _qspi_flash_cmd_write_config_32(qspi_cmd_type *qspi_cmd_struct, uint32_t addr, uint32_t counter)
{
    qspi_cmd_struct->pe_mode_enable = FALSE;
    qspi_cmd_struct->pe_mode_operate_code = 0;
    qspi_cmd_struct->instruction_code = 0x32;
    qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
    qspi_cmd_struct->address_code = addr;
    qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_3_BYTE;
    qspi_cmd_struct->data_counter = counter;
    qspi_cmd_struct->second_dummy_cycle_num = 0;
    qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_114;
    qspi_cmd_struct->read_status_config = QSPI_RSTSC_HW_AUTO;
    qspi_cmd_struct->read_status_enable = FALSE;
    qspi_cmd_struct->write_data_enable = TRUE;
}

static void _qspi_flash_cmd_sector_erase_config(qspi_cmd_type *qspi_cmd_struct, uint32_t addr)
{
    qspi_cmd_struct->pe_mode_enable = FALSE;
    qspi_cmd_struct->pe_mode_operate_code = 0;
    qspi_cmd_struct->instruction_code = 0x20;
    qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
    qspi_cmd_struct->address_code = addr;
    qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_3_BYTE;
    qspi_cmd_struct->data_counter = 0;
    qspi_cmd_struct->second_dummy_cycle_num = 0;
    qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_111;
    qspi_cmd_struct->read_status_config = QSPI_RSTSC_HW_AUTO;
    qspi_cmd_struct->read_status_enable = FALSE;
    qspi_cmd_struct->write_data_enable = TRUE;
}

static void _qspi_flash_cmd_read_id_config(qspi_cmd_type *qspi_cmd_struct)
{
    qspi_cmd_struct->pe_mode_enable = FALSE;
    qspi_cmd_struct->pe_mode_operate_code = 0;
    qspi_cmd_struct->instruction_code = 0x9F;
    qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
    qspi_cmd_struct->address_code = 0;
    qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_0_BYTE;
    qspi_cmd_struct->data_counter = 3;
    qspi_cmd_struct->second_dummy_cycle_num = 0;
    qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_111;
    qspi_cmd_struct->read_status_config = QSPI_RSTSC_HW_AUTO;
    qspi_cmd_struct->read_status_enable = FALSE;
    qspi_cmd_struct->write_data_enable = FALSE;
}

static void _qspi_flash_cmd_write_enable_config(qspi_cmd_type *qspi_cmd_struct)
{
    qspi_cmd_struct->pe_mode_enable = FALSE;
    qspi_cmd_struct->pe_mode_operate_code = 0;
    qspi_cmd_struct->instruction_code = 0x06;
    qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
    qspi_cmd_struct->address_code = 0;
    qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_0_BYTE;
    qspi_cmd_struct->data_counter = 0;
    qspi_cmd_struct->second_dummy_cycle_num = 0;
    qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_111;
    qspi_cmd_struct->read_status_config = QSPI_RSTSC_HW_AUTO;
    qspi_cmd_struct->read_status_enable = FALSE;
    qspi_cmd_struct->write_data_enable = TRUE;
}

static void _qspi_flash_cmd_read_status_reg_config(qspi_cmd_type *qspi_cmd_struct , uint8_t cmd)
{
    qspi_cmd_struct->pe_mode_enable = FALSE;
    qspi_cmd_struct->pe_mode_operate_code = 0;
    qspi_cmd_struct->instruction_code = cmd;
    qspi_cmd_struct->instruction_length = QSPI_CMD_INSLEN_1_BYTE;
    qspi_cmd_struct->address_code = 0;
    qspi_cmd_struct->address_length = QSPI_CMD_ADRLEN_0_BYTE;
    qspi_cmd_struct->data_counter = 1;
    qspi_cmd_struct->second_dummy_cycle_num = 0;
    qspi_cmd_struct->operation_mode = QSPI_OPERATE_MODE_111;
    qspi_cmd_struct->read_status_config = QSPI_RSTSC_HW_AUTO;
    qspi_cmd_struct->read_status_enable = FALSE;
    qspi_cmd_struct->write_data_enable = FALSE;
}

static void _qspi_flash_write_enable(void)
{
    _qspi_flash_cmd_write_enable_config(&_qspi_flash_cmd_config);
    qspi_cmd_operation_kick(QSPI_FLASH_QSPIx, &_qspi_flash_cmd_config);

    /* wait command completed */
    while(qspi_flag_get(QSPI_FLASH_QSPIx, QSPI_CMDSTS_FLAG) == RESET);
    qspi_flag_clear(QSPI_FLASH_QSPIx, QSPI_CMDSTS_FLAG);
}

uint8_t _qspi_flash_read_status_reg(uint8_t cmd)
{
    uint8_t reg = 0;
    _qspi_flash_cmd_read_status_reg_config(&_qspi_flash_cmd_config , cmd);
    qspi_cmd_operation_kick(QSPI_FLASH_QSPIx, &_qspi_flash_cmd_config);

    /* read data */
    while(qspi_flag_get(QSPI_FLASH_QSPIx, QSPI_RXFIFORDY_FLAG) == RESET);

    reg = qspi_byte_read(QSPI_FLASH_QSPIx);

    /* wait command completed */
    while(qspi_flag_get(QSPI_FLASH_QSPIx, QSPI_CMDSTS_FLAG) == RESET);
    qspi_flag_clear(QSPI_FLASH_QSPIx, QSPI_CMDSTS_FLAG);

    return reg;
}

/* global functions / API interface -------------------------------------*/
void bsp_qspi_flash_init(void)
{
    gpio_init_type gpio_init_struct;

    /* enable the qspi flash clock */
    crm_periph_clock_enable(QSPI_FLASH_QSPI_CLK, TRUE);

    /* enable the pin clock */
    crm_periph_clock_enable(QSPI_FLASH_CS_GPIO_CLK, TRUE);
    crm_periph_clock_enable(QSPI_FLASH_CLK_GPIO_CLK, TRUE);
    crm_periph_clock_enable(QSPI_FLASH_D0_GPIO_CLK, TRUE);
    crm_periph_clock_enable(QSPI_FLASH_D1_GPIO_CLK, TRUE);
    crm_periph_clock_enable(QSPI_FLASH_D2_GPIO_CLK, TRUE);
    crm_periph_clock_enable(QSPI_FLASH_D3_GPIO_CLK, TRUE);

    /* configure gpio */
    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;

    gpio_init_struct.gpio_pins = QSPI_FLASH_CS_GPIO_PIN;
    gpio_init(QSPI_FLASH_CS_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = QSPI_FLASH_CLK_GPIO_PIN;
    gpio_init(QSPI_FLASH_CLK_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = QSPI_FLASH_D0_GPIO_PIN;
    gpio_init(QSPI_FLASH_D0_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = QSPI_FLASH_D1_GPIO_PIN;
    gpio_init(QSPI_FLASH_D1_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = QSPI_FLASH_D2_GPIO_PIN;
    gpio_init(QSPI_FLASH_D2_GPIO_PORT, &gpio_init_struct);

    gpio_init_struct.gpio_pins = QSPI_FLASH_D3_GPIO_PIN;
    gpio_init(QSPI_FLASH_D3_GPIO_PORT, &gpio_init_struct);

    /* gpio mux config */
    gpio_pin_mux_config(QSPI_FLASH_CS_GPIO_PORT,  QSPI_FLASH_CS_GPIO_PINS_SOURCE,  QSPI_FLASH_CS_GPIO_MUX);
    gpio_pin_mux_config(QSPI_FLASH_CLK_GPIO_PORT, QSPI_FLASH_CLK_GPIO_PINS_SOURCE, QSPI_FLASH_CLK_GPIO_MUX);
    gpio_pin_mux_config(QSPI_FLASH_D0_GPIO_PORT,  QSPI_FLASH_D0_GPIO_PINS_SOURCE,  QSPI_FLASH_D0_GPIO_MUX);
    gpio_pin_mux_config(QSPI_FLASH_D1_GPIO_PORT,  QSPI_FLASH_D1_GPIO_PINS_SOURCE,  QSPI_FLASH_D1_GPIO_MUX);
    gpio_pin_mux_config(QSPI_FLASH_D2_GPIO_PORT,  QSPI_FLASH_D2_GPIO_PINS_SOURCE,  QSPI_FLASH_D2_GPIO_MUX);
    gpio_pin_mux_config(QSPI_FLASH_D3_GPIO_PORT,  QSPI_FLASH_D3_GPIO_PINS_SOURCE,  QSPI_FLASH_D3_GPIO_MUX);

    /* switch to cmd port */
    qspi_xip_enable(QSPI_FLASH_QSPIx, FALSE);

    /* set sclk */
    qspi_clk_division_set(QSPI_FLASH_QSPIx, QSPI_CLK_DIV_4);

    /* set sck idle mode 0 */
    qspi_sck_mode_set(QSPI_FLASH_QSPIx, QSPI_SCK_MODE_0);

    /* set wip in bit 0 */
    qspi_busy_config(QSPI_FLASH_QSPIx, QSPI_BUSY_OFFSET_0);
}

int bsp_qspi_flash_read(uint32_t addr , uint32_t length , uint8_t *buf)
{
    uint32_t i, len = length;

    if(NULL == buf || 0 == length){
        return 0;
    }

    _qspi_flash_cmd_read_config_eb(&_qspi_flash_cmd_config, addr, length);
    qspi_cmd_operation_kick(QSPI_FLASH_QSPIx, &_qspi_flash_cmd_config);

    /* read data */
    do
    {
        if(length >= QSPI_FLASH_FIFO_DEPTH)
        {
            len = QSPI_FLASH_FIFO_DEPTH;
        }
        else
        {
            len = length;
        }
        while(qspi_flag_get(QSPI_FLASH_QSPIx, QSPI_RXFIFORDY_FLAG) == RESET);
        for(i = 0; i < len; ++i)
        {
            *buf++ = qspi_byte_read(QSPI_FLASH_QSPIx);
        }
        length -= len;
    }while(length);

    /* wait command completed */
    while(qspi_flag_get(QSPI_FLASH_QSPIx, QSPI_CMDSTS_FLAG) == RESET);
    qspi_flag_clear(QSPI_FLASH_QSPIx, QSPI_CMDSTS_FLAG);

    return 1;
}

int bsp_qspi_flash_write(uint32_t addr , uint32_t length , const uint8_t *buf)
{
    uint32_t i, len;
    int32_t timeout = 500;
    
    if(NULL == buf || 0 == length){
        return 0;
    }
    
    do
    {
        _qspi_flash_write_enable();
        /* send up to 256 bytes at one time, and only one page */
        len = (addr / QSPI_FLASH_PAGE_SIZE + 1) * QSPI_FLASH_PAGE_SIZE - addr;
        if(length < len){
            len = length;
        }

        _qspi_flash_cmd_write_config_32(&_qspi_flash_cmd_config, addr, len);
        qspi_cmd_operation_kick(QSPI_FLASH_QSPIx, &_qspi_flash_cmd_config);

        for(i = 0; i < len; ++i)
        {
            while(qspi_flag_get(QSPI_FLASH_QSPIx, QSPI_TXFIFORDY_FLAG) == RESET);
            qspi_byte_write(QSPI_FLASH_QSPIx, *buf++);
        }
        length -= len;
        addr += len;

        /* wait command completed */
        while(qspi_flag_get(QSPI_FLASH_QSPIx, QSPI_CMDSTS_FLAG) == RESET);
        qspi_flag_clear(QSPI_FLASH_QSPIx, QSPI_CMDSTS_FLAG);

        while (bsp_qspi_flash_busy_check())
        {
            if(--timeout <= 0){
                return 0;
            }
            delay_ms(1);    
        }

    }while(length);

    return 1;
}

int bsp_qspi_flash_erase(uint32_t addr)
{
    int32_t timeout = 500;
    _qspi_flash_write_enable();

    _qspi_flash_cmd_sector_erase_config(&_qspi_flash_cmd_config, addr);
    qspi_cmd_operation_kick(QSPI_FLASH_QSPIx, &_qspi_flash_cmd_config);

    /* wait command completed */
    while(qspi_flag_get(QSPI_FLASH_QSPIx, QSPI_CMDSTS_FLAG) == RESET);
    qspi_flag_clear(QSPI_FLASH_QSPIx, QSPI_CMDSTS_FLAG);

    while (bsp_qspi_flash_busy_check()){
        if(--timeout <= 0){
            return 0;
        }
        delay_ms(1);
    }

    return 1;
}

uint32_t bsp_qspi_flash_read_id(void)
{
    uint8_t i , id_buf[3];
    _qspi_flash_cmd_read_id_config(&_qspi_flash_cmd_config);
    qspi_cmd_operation_kick(QSPI_FLASH_QSPIx, &_qspi_flash_cmd_config);

    /* read data */
    while(qspi_flag_get(QSPI_FLASH_QSPIx, QSPI_RXFIFORDY_FLAG) == RESET);
    for(i = 0; i < 3; ++i)
    {
        id_buf[i] = qspi_byte_read(QSPI_FLASH_QSPIx);
    }

    /* wait command completed */
    while(qspi_flag_get(QSPI_FLASH_QSPIx, QSPI_CMDSTS_FLAG) == RESET);
    qspi_flag_clear(QSPI_FLASH_QSPIx, QSPI_CMDSTS_FLAG);

    return (id_buf[0] << 16) | (id_buf[1] << 8) | id_buf[2];
    
}

uint8_t bsp_qspi_flash_read_status_reg1(void)
{
    return _qspi_flash_read_status_reg(0x05);
}

uint8_t bsp_qspi_flash_read_status_reg2(void)
{
    return _qspi_flash_read_status_reg(0x35);
}

bool bsp_qspi_flash_busy_check(void)
{
    return bsp_qspi_flash_read_status_reg1() & 0x01;
}

bool bsp_qspi_flash_read_qe(void)
{
    return bsp_qspi_flash_read_status_reg2() & (0x01 << 1);
}

/* ---------------------------------------------------------------------*/
unsigned long r_dat_bat(unsigned long address,unsigned long DataLen,unsigned char *pBuff)
{
    return bsp_qspi_flash_read(address , DataLen , pBuff);
}

unsigned char gt_read_data(unsigned char* sendbuf , unsigned char sendlen , unsigned char* receivebuf, unsigned int receivelen)
{

    uint8_t i;
    uint32_t combination = 0 ;
    if(sendlen>5){
        return 0;
    }

    for(i=0;i<sendlen - 1;i++)
    {
        combination |=sendbuf[sendlen-i-1]<<8*i;
    }

    qspi_cmd_type qspi_cmd_struct;
    qspi_cmd_struct.pe_mode_enable = FALSE;
    qspi_cmd_struct.pe_mode_operate_code = 0;
    qspi_cmd_struct.instruction_code = sendbuf[0];
    qspi_cmd_struct.instruction_length = QSPI_CMD_INSLEN_1_BYTE;
    qspi_cmd_struct.address_code = combination;
    qspi_cmd_struct.address_length = (qspi_cmd_adrlen_type)(sendlen - 1);
    qspi_cmd_struct.data_counter = receivelen;
    qspi_cmd_struct.second_dummy_cycle_num = 0;
    qspi_cmd_struct.operation_mode = QSPI_OPERATE_MODE_111;
    qspi_cmd_struct.read_status_config = QSPI_RSTSC_HW_AUTO;
    qspi_cmd_struct.read_status_enable = FALSE;
    qspi_cmd_struct.write_data_enable = FALSE;

    qspi_cmd_operation_kick(QSPI_FLASH_QSPIx, &qspi_cmd_struct);

    while(qspi_flag_get(QSPI_FLASH_QSPIx, QSPI_RXFIFORDY_FLAG) == RESET);

    for(i = 0; i < receivelen; ++i)
    {
        receivebuf[i] = qspi_byte_read(QSPI_FLASH_QSPIx);
    }

    while(qspi_flag_get(QSPI_FLASH_QSPIx, QSPI_CMDSTS_FLAG) == RESET);
    qspi_flag_clear(QSPI_FLASH_QSPIx, QSPI_CMDSTS_FLAG);

    return 1;
}


/* end of file ----------------------------------------------------------*/


