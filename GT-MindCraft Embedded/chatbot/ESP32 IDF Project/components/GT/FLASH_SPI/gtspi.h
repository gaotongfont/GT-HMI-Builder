#ifndef _GTSPI_H_
#define _GTSPI_H_


#include "driver/spi_master.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include <string.h>

#include "esp_log.h"
#include <stdio.h>
#include "esp_rom_sys.h"

void spi_init();
//esp_err_t gt_read_otp_data(uint8_t cmd, uint32_t addr, uint8_t *data, size_t len);
//unsigned char gt_read_data(uint8_t cmd, uint32_t addr, uint8_t *data, size_t len);
//extern unsigned char gt_read_data(unsigned char* sendbuf, unsigned char sendlen, unsigned char* receivebuf, unsigned int receivelen);
unsigned char gt_read_data(unsigned char* sendbuf, unsigned char sendlen, unsigned char* receivebuf, unsigned int receivelen) ;


#endif 