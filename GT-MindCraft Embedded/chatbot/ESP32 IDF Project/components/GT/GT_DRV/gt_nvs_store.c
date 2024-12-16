#include "gt_nvs_store.h"

static const char *TAG = "NVS_STORE";

/**
 * @brief 将数据存储到 NVS（非易失性存储）中
 *
 * @param key 存储数据时使用的键
 * @param buff 要存储的数据
 */
void store_data_in_nvs(const char *key, const char *buff) {
    esp_err_t err;
    nvs_handle_t my_handle;
    err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(err));
        return;
    }
    err = nvs_set_str(my_handle, key, buff);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error storing data: %s", esp_err_to_name(err));
    } else {
        ESP_LOGI(TAG, "data stored successfully");
    }
    err = nvs_commit(my_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error committing changes: %s", esp_err_to_name(err));
    }
    nvs_close(my_handle);
}

/**
 * @brief 从 NVS 中读取数据
 *
 * @param key 要读取的键
 * @param out_buff 输出缓冲区，用于存储读取到的数据
 * @param max_len 输出缓冲区的最大长度
 */
void read_data_from_nvs(const char *key, const char *out_buff, size_t max_len) {
    esp_err_t err;
    nvs_handle_t my_handle;
    err = nvs_open("storage", NVS_READONLY, &my_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(err));
        return;
    }
    size_t required_size = 0;
    err = nvs_get_str(my_handle, key, NULL, &required_size);
    ESP_LOGI(TAG, "required_size: %d", required_size);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error getting data size: %s", esp_err_to_name(err));
        nvs_close(my_handle);
        return;
    }
    if (required_size > max_len) {
        ESP_LOGE(TAG, "Buffer size is too small for data");
        nvs_close(my_handle);
        return;
    }
    err = nvs_get_str(my_handle, key, out_buff, &required_size);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error reading data: %s", esp_err_to_name(err));
    } else {
        ESP_LOGI(TAG, "data read successfully: %s", out_buff);
    }
    nvs_close(my_handle);
}

/**
 * @brief 从 NVS 中删除指定键的数据
 *
 * @param key 要删除的数据的键
 */
void erase_data_from_nvs(const char *key) {
    esp_err_t err;
    nvs_handle_t my_handle;
    err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(err));
        return;
    }
    err = nvs_erase_key(my_handle, key);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error erasing data: %s", esp_err_to_name(err));
    } else {
        ESP_LOGI(TAG, "data erased successfully");
    }
    err = nvs_commit(my_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error committing changes: %s", esp_err_to_name(err));
    }
    nvs_close(my_handle);
}