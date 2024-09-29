/**
 * @file touch.c
 * @author Yang (your@email.com)
 * @brief
 * @version 0.1
 * @date 2023-06-21 17:22:16
 * @copyright Copyright (c) 2014-2023, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "gt_touch.h"
//
#include "i2c_bus.h"
#include "board.h"
#include "esp_log.h"
#include "tca9554.h"

/* private define -------------------------------------------------------*/
/*
 * 0 : ft6336
 * 1 : cst836u
 * 2 : bl6133
*/
#define TOUCH_IC_SELECT     (1)
#if (1 == TOUCH_IC_SELECT)
    #include "touch_cst836u.h"
#elif (2 == TOUCH_IC_SELECT)
    #include "touch_bl6133.h"
#elif (3 == TOUCH_IC_SELECT)
    #include "bsp_xpt2046.h"
#else
    #include "touch_ft6336.h"
#endif


/* private typedef ------------------------------------------------------*/
static i2c_bus_handle_t _touch_i2c_handle = NULL;



/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/



/* macros ---------------------------------------------------------------*/
static tp_dev_t _tp_dev;
static const char *TAG = "GT_TOUCH";

/* static functions -----------------------------------------------------*/
static int i2c_init(void)
{
    int res = 0;
    i2c_config_t i2c_pin = { 0 };
    res = get_i2c_pins(TOUCH_IIC_PORT, &i2c_pin);
    if (res != 0) {
        ESP_LOGE(TAG, "get i2c pins error");
        return res;
    }
    i2c_config_t es_i2c_cfg = {
        .mode = I2C_MODE_MASTER,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,
        .sda_io_num = i2c_pin.sda_io_num,
        .scl_io_num = i2c_pin.scl_io_num,
    };
    _touch_i2c_handle = i2c_bus_create(TOUCH_IIC_PORT, &es_i2c_cfg);
    if (_touch_i2c_handle == NULL) {
        ESP_LOGE(TAG, "i2c_bus_create error");
        return -1;
    }
    return 0;
}

static bool _touch_write_reg(uint8_t ic_add , uint8_t reg, uint8_t *buf , uint32_t len)
{
    esp_err_t ret;
    ret = i2c_bus_write_bytes(_touch_i2c_handle, ic_add, &reg, 1 , buf, len);
    return (ret == ESP_OK);
}

static bool _touch_read_reg(uint8_t ic_add , uint8_t reg, uint8_t *buf , uint32_t len)
{
    esp_err_t ret;
    ret = i2c_bus_read_bytes(_touch_i2c_handle, ic_add, &reg, 1 , buf, len);
    return (ret == ESP_OK);
}

static void touch_rest_pin_state_set(bool val)
{
    tca9554_set_output_state(TOUCH_RST_PIN, val);
}

static void _touch_rest(void)
{
    tca9554_set_io_config(TOUCH_RST_PIN, TCA9554_IO_OUTPUT);
    touch_rest_pin_state_set(true);
    vTaskDelay(5);
    touch_rest_pin_state_set(false);
    vTaskDelay(5);
    touch_rest_pin_state_set(true);
    vTaskDelay(100);
}



/* global functions / API interface -------------------------------------*/
tp_dev_t* gt_touch_init(void)
{
    i2c_init();

    // rst
    // _touch_rest();

    //tp ic init
    _tp_dev.write_reg = _touch_write_reg;
    _tp_dev.read_reg = _touch_read_reg;

#if (1 == TOUCH_IC_SELECT)
    cst836u_init(&_tp_dev);
#elif (2 == TOUCH_IC_SELECT)
    bl6133_init(&_tp_dev);
#elif (3 == TOUCH_IC_SELECT)
    bsp_xpt2046_init(&_tp_dev);
#else
    ft6336_init(&_tp_dev);
#endif
    _tp_dev.point.status = TP_STATE_RELEASED;
    return &_tp_dev;
}


/* end of file ----------------------------------------------------------*/


