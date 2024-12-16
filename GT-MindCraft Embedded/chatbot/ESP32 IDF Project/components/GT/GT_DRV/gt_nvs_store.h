#ifndef GT_NVS_STORE_H
#define GT_NVS_STORE_H

#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"

//general api
void store_data_in_nvs(const char *key, const char *value);
void read_data_from_nvs(const char *key, const char *out_value, size_t max_len);
void erase_data_from_nvs(const char *key);

#endif