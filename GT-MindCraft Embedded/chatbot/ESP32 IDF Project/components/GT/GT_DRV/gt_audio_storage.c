/**
 * @file gt_recording.c
 * @author Yang (your@email.com)
 * @brief
 * @version 0.1
 * @date 2024-08-27 09:59:36
 * @copyright Copyright (c) 2014-2024, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
// #include "gt_recording.h"
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "board.h"
#include "esp_log.h"
// #include "fatfs_stream.h"
#include "i2s_stream.h"
// #include "wav_encoder.h"
#include "audio_mem.h"
#include "gt_audio_storage.h"

/* private define -------------------------------------------------------*/
#define GT_RING_BUFFER_SIZE (4*1024)//(2048)

/* private typedef ------------------------------------------------------*/



/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/
#define AUDIO_MEMORY_SIZE (1024)
static char audio_memory_buffer[AUDIO_MEMORY_SIZE] = {0};
int buffer_index = 0;

static const char *TAG = "GT_AUDIO_STORAGE";
//
static bool gt_lock_recording = false;
static audio_element_handle_t gt_i2s_stream_reader = NULL;
static audio_element_handle_t gt_memory_stream_writer  = NULL;
ringbuf_handle_t gt_ringbuf01 = NULL;
/* macros ---------------------------------------------------------------*/


void gt_audio_storage_init(void)
{
    if(gt_lock_recording) {
        ESP_LOGW(TAG, "recording is locked!");
        return;
    }
    // 为PCM数据分配内存
    // pcm_buffer = malloc(PCM_BUFFER_SIZE);
    // if (pcm_buffer == NULL) {
    //     ESP_LOGE(TAG, "Failed to allocate PCM buffer!");
    //     return;
    // }
    // pcm_buffer_offset = 0;
    ESP_LOGI(TAG, "[1.0] Create i2s stream to read audio data from codec chip");
    int bits_per_sample = 16;  // 假设每个样本为16位
    i2s_stream_cfg_t i2s_cfg = I2S_STREAM_CFG_DEFAULT_WITH_PARA(I2S_NUM_0, GT_AUDIO_MEMORY_I2C_RATE, bits_per_sample, AUDIO_STREAM_READER);
    // i2s_cfg.std_cfg.clk_cfg.clk_src = I2S_CLK_SRC_DEFAULT;
    i2s_cfg.std_cfg.clk_cfg.sample_rate_hz = 16000;
    // i2s_cfg.std_cfg.clk_cfg.mclk_multiple = I2S_MCLK_MULTIPLE_256;
    i2s_cfg.std_cfg.slot_cfg.slot_mode = I2S_SLOT_MODE_MONO; 
    i2s_cfg.std_cfg.slot_cfg.slot_mask = I2S_STD_SLOT_LEFT;
    // i2s_cfg.stack_in_ext = true;
    i2s_cfg.use_alc = true;
    i2s_cfg.uninstall_drv = false;
    gt_i2s_stream_reader = i2s_stream_init(&i2s_cfg);
    ESP_LOGI(TAG, "[1.1] Create a ringbuffer and insert it between i2s_stream_reader and the PCM buffer");
    gt_ringbuf01 = rb_create(GT_RING_BUFFER_SIZE, 14);
    if (!gt_ringbuf01) {
        ESP_LOGE(TAG, "Failed to create ring buffer");
        return;
    }
    audio_element_set_output_ringbuf(gt_i2s_stream_reader, gt_ringbuf01);
    
    gt_lock_recording = true;
}

void gt_audio_storage_deinit(void)
{
    if(!gt_lock_recording) return ;

    ESP_LOGI(TAG, "[4.0] Stop elements and release resources");
    /* Release all resources */
    audio_element_deinit(gt_i2s_stream_reader);

    gt_i2s_stream_reader = NULL;

    rb_destroy(gt_ringbuf01);
    gt_ringbuf01 = NULL;

    gt_lock_recording = false;
}

void gt_audio_storage_start(void)
{
    if(!gt_i2s_stream_reader) {
        ESP_LOGW(TAG, "recording not initialized!");
        return ;
    }
    ESP_LOGI(TAG, "[2.0] Start recording!");
    audio_element_run(gt_i2s_stream_reader);
    audio_element_resume(gt_i2s_stream_reader, 0, 0);
    ESP_LOGI(TAG, "i2s_stream_reader state: %d", audio_element_get_state(gt_i2s_stream_reader));

}

void gt_audio_storage_stop(void)
{
    if(!gt_i2s_stream_reader) {
        ESP_LOGW(TAG, " not initialized!");
        return ;
    }

    ESP_LOGI(TAG, "[3.0] Stop recording!");
    audio_element_stop(gt_i2s_stream_reader);
}


void get_pcm_data(void)
{
    size_t bytes_read = 0;
    short* temp_buffer = (short*)audio_malloc(4*1024);  // 临时缓存区
    memset(temp_buffer, 0, 4*1024);
    // ESP_LOGI(TAG, "get_pcm_data prepare!!!!!!!!!!");
    // while(audio_element_get_state(gt_i2s_stream_reader) == AEL_STATE_RUNNING)
    // {
    //     if (rb_read(gt_ringbuf01, (char*)temp_buffer, 4*1024, portMAX_DELAY) > 0) {
    //         // 将读取的数据存储到pcm_buffer
    //         ESP_LOGI(TAG, "get_pcm_data bytes_read %d %d %d", temp_buffer[0], temp_buffer[50], temp_buffer[100]);
    //         gt_websocket_send_data((char*)temp_buffer);
    //     }
    //     vTaskDelay(10);
    // }
    while(1)
    {
        if (rb_read(gt_ringbuf01, (char*)temp_buffer, 4*1024, portMAX_DELAY) > 0) {
            // 将读取的数据存储到pcm_buffer
            ESP_LOGI(TAG, "get_pcm_data bytes_read %d %d %d", temp_buffer[0], temp_buffer[50], temp_buffer[100]);
            gt_websocket_send_data((char*)temp_buffer);
        }
        if(audio_element_get_state(gt_i2s_stream_reader) != AEL_STATE_RUNNING)
        {break;}
        vTaskDelay(10);
    }
    audio_free(temp_buffer);
    temp_buffer = NULL;
    ESP_LOGI(TAG, "get_pcm_data bytes_read finish!!!!!!!!!!!");
    vTaskDelete(NULL);
}

// char* get_audio_memory_buffer()
// {
//     return audio_memory_buffer;
// }

// /* static functions -----------------------------------------------------*/
// audio_element_err_t memory_stream_write(audio_element_handle_t self, char *buffer, int len, TickType_t ticks_to_wait,void *context)
// {
//     // memcpy(audio_memory_buffer, buffer, len);
//     ESP_LOGI(TAG, "memory_stream_write data len = %d", len);
//     // gt_websocket_send_data(buffer);
//     ESP_LOGI(TAG, "gt_websocket_send_data finish");
//     return ESP_OK;
// }



// /* global functions / API interface -------------------------------------*/
// void gt_audio_storage_init(void)
// {
//     if(gt_lock_recording) {
//         ESP_LOGW(TAG, "recording is locked!");
//         return;
//     }
//     //
//     ESP_LOGI(TAG, "[1.0] Create i2s stream to read audio data from codec chip");
//     int bits_per_sample = 0;
// #if (CONFIG_ESP32_S3_GT_KORVO2_V3_BOARD == 1) && (CONFIG_AFE_MIC_NUM == 1)
//     bits_per_sample = 16;
// #else
//     bits_per_sample = CODEC_ADC_BITS_PER_SAMPLE;
// #endif
    
//     audio_element_cfg_t cfg = DEFAULT_AUDIO_ELEMENT_CONFIG();
//     cfg.read = memory_stream_write;  // 设置自定义的写入回调
//     cfg.multi_in_rb_num = 1;
//     cfg.multi_out_rb_num = 1;
//     cfg.task_stack = 8*1024;
//     cfg.stack_in_ext = true;
//     cfg.buffer_len = 1*1024;
//     gt_memory_stream_writer = audio_element_init(&cfg);
//     if(gt_memory_stream_writer == NULL)
//     {
//         ESP_LOGE(TAG, "gt_memory_stream_writer init error");
//     }

//     i2s_stream_cfg_t i2s_cfg = I2S_STREAM_CFG_DEFAULT_WITH_PARA(CODEC_ADC_I2S_PORT, GT_AUDIO_MEMORY_I2C_RATE, bits_per_sample, AUDIO_STREAM_READER);
//     i2s_cfg.stack_in_ext = true;
//     gt_i2s_stream_reader = i2s_stream_init(&i2s_cfg);

//     audio_element_info_t info = AUDIO_ELEMENT_INFO_DEFAULT();
//     // info.sample_rates = 16000;
//     audio_element_getinfo(gt_i2s_stream_reader, &info);
//     audio_element_setinfo(gt_memory_stream_writer , &info);

//     ESP_LOGI(TAG, "[1.3] Create a ringbuffer and insert it between i2s_stream_reader and wav_encoder");
//     gt_ringbuf01 = rb_create(GT_RING_BUFFER_SIZE, 1);
//     if(gt_ringbuf01 == NULL)
//     {
//         ESP_LOGE(TAG, "gt_ringbuf01 init error");
//     }
//     audio_element_set_output_ringbuf(gt_i2s_stream_reader, gt_ringbuf01);
//     audio_element_set_input_ringbuf(gt_memory_stream_writer , gt_ringbuf01);

//     gt_lock_recording = true;
// }

// void gt_audio_storage_deinit(void)
// {
//     if(!gt_lock_recording) return ;

//     ESP_LOGI(TAG, "[4.0] Stop elements and release resources");
//     /* Release all resources */
//     audio_element_deinit(gt_i2s_stream_reader);
//     audio_element_deinit(gt_i2s_stream_reader);

//     gt_i2s_stream_reader = NULL;
//     gt_memory_stream_writer = NULL;

//     rb_destroy(gt_ringbuf01);
//     gt_ringbuf01 = NULL;

//     gt_lock_recording = false;
// }

// void gt_audio_storage_start(void)
// {
//     if(!gt_i2s_stream_reader || !gt_memory_stream_writer) {
//         ESP_LOGW(TAG, "recording not initialized!");
//         return ;
//     }
//     ESP_LOGI(TAG, "[2.0] Start recording!");
//     audio_element_run(gt_i2s_stream_reader);
//     audio_element_run(gt_memory_stream_writer);

//     ESP_LOGI(TAG, "i2s_stream_reader state: %d", audio_element_get_state(gt_i2s_stream_reader));
//     ESP_LOGI(TAG, "gt_memory_stream_writer state: %d", audio_element_get_state(gt_memory_stream_writer)); 

//     audio_element_resume(gt_i2s_stream_reader, 0, 0);
//     audio_element_resume(gt_memory_stream_writer, 0, 0);

// }

// void gt_audio_storage_stop(void)
// {
//     if(!gt_i2s_stream_reader || !gt_memory_stream_writer) {
//         ESP_LOGW(TAG, " not initialized!");
//         return ;
//     }

//     ESP_LOGI(TAG, "[3.0] Stop recording!");
//     audio_element_stop(gt_i2s_stream_reader);
//     audio_element_stop(gt_memory_stream_writer);
// }

// char gt_audio_storage_state_get(void)
// {
//     return audio_element_get_state(gt_memory_stream_writer);
// }



/* end of file ----------------------------------------------------------*/


