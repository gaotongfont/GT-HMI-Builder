/**
 * @file touch.c
 * @author Yang (your@email.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-21 17:22:16
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "touch.h"
#include "at32f435_437_scfg.h"
#include "at32f435_437_exint.h"
#include "at32f435_437_misc.h"
#include "bsp_delay.h"

#include "touch_cst836u.h"
#include "touch_bl6133.h"
/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/



/* macros ---------------------------------------------------------------*/
tp_dev_t tp_dev;


/* static functions -----------------------------------------------------*/
static bool _touch_write_reg(uint8_t ic_add , uint8_t reg, uint8_t *buf , uint32_t len)
{
    uint32_t i ;

    // start
    IIC_Start();

    // send addr
    IIC_Send_Byte( ic_add << 1 );
    if(IIC_Wait_Ack()){
        goto ret_fail;
    }

    // send reg
    IIC_Send_Byte( reg );
    if(IIC_Wait_Ack()){
        goto ret_fail;
    }

    // write data
    for(i = 0 ; i < len ; i++){
        IIC_Send_Byte( buf[i] );
        if(IIC_Wait_Ack()){
            goto ret_fail;
        }
    }

    // stop
    IIC_Stop();
    
    return true;

ret_fail:
    return false;
}

static bool _touch_read_reg(uint8_t ic_add , uint8_t reg, uint8_t *buf , uint32_t len)
{
    uint32_t i = 0;

    // start
    IIC_Start();

    // send addr
    IIC_Send_Byte( ic_add << 1 );
    if(IIC_Wait_Ack()){
        goto ret_fail;
    }
    // send reg
    IIC_Send_Byte( reg );
    if(IIC_Wait_Ack()){
        goto ret_fail;
    }
    IIC_Stop();

    //
    IIC_Start();
    // read
    IIC_Send_Byte((ic_add << 1) | 0x01);
    if(IIC_Wait_Ack()){
        goto ret_fail;
    }

    // read data
    for(i = 0 ; i < len-1 ; i++){
        buf[i] = IIC_Read_Byte(1);
    }
    buf[i] = IIC_Read_Byte(0);

    // stop
    IIC_Stop();

    return true;

ret_fail:
    return false;
}

/* global functions / API interface -------------------------------------*/
void touch_init(void)
{ 
    gpio_init_type gpio_init_struct;
    exint_init_type exint_init_struct;

	crm_periph_clock_enable(TOUCH_RST_GPIO_CRM_CLK, TRUE);
    // irq
    crm_periph_clock_enable(CRM_SCFG_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(TOUCH_IRQ_GPIO_CRM_CLK, TRUE);

    scfg_exint_line_config(TOUCH_IRQ_SCFG_GPIO, TOUCH_IRQ_SCFG_PIN);

    exint_default_para_init(&exint_init_struct);
    exint_init_struct.line_enable = TRUE;
    exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
    exint_init_struct.line_select = TOUCH_IRQ_EXINT_LINE;
    exint_init_struct.line_polarity = EXINT_TRIGGER_FALLING_EDGE;
    exint_init(&exint_init_struct);

    nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
    nvic_irq_enable(TOUCH_IRQ_EXINT_IRQn, 1, 0);

    /* configure the rst gpio */
	gpio_default_para_init(&gpio_init_struct);
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_pins = TOUCH_IRQ_PIN ; 
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init(TOUCH_IRQ_GPIO, &gpio_init_struct);

    gpio_init_struct.gpio_pins = TOUCH_RST_PIN ; 
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init(TOUCH_RST_GPIO, &gpio_init_struct);

    // iic io
	IIC_Init();
    // rst
    TOUCH_RST_SET(1);
    delay_ms(5);
    TOUCH_RST_SET(0);
    delay_ms(5);
    TOUCH_RST_SET(1);
    delay_ms(100);

    //tp ic init
    tp_dev.write_reg = _touch_write_reg;
    tp_dev.read_reg = _touch_read_reg;
    // cst836u_init(&tp_dev);
    bl6133_init(&tp_dev);

}


void TOUCH_IRQ_EXINT_IRQHandler(void)
{
    if(exint_flag_get(TOUCH_IRQ_EXINT_LINE) != RESET)
    {
        if(NULL != tp_dev.read_point){
            // tp_dev.read_point();
        }

        exint_flag_clear(TOUCH_IRQ_EXINT_LINE);
    }
}

/* end of file ----------------------------------------------------------*/


