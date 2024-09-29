/**
 * @file gt_recording.c
 * @author Yang (your@email.com)
 * @brief
 * @version 0.1
 * @date 2024-08-27 09:59:36
 * @copyright Copyright (c) 2014-2024, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "gt_recording.h"
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "board.h"
#include "esp_log.h"
#include "fatfs_stream.h"
#include "i2s_stream.h"
#include "wav_encoder.h"
#include "audio_mem.h"
/* private define -------------------------------------------------------*/
#define RING_BUFFER_SIZE (2048)

/* private typedef ------------------------------------------------------*/



/* static prototypes ----------------------------------------------------*/



/* static variables -----------------------------------------------------*/
static const char *TAG = "GT_RECORDING";
static const char *fixed_recording_path = "/sdcard/recording.wav";
//
static bool lock_recording = false;
static audio_element_handle_t wav_fatfs_stream_writer = NULL, i2s_stream_reader = NULL, wav_encoder = NULL;
ringbuf_handle_t ringbuf01 = NULL, ringbuf02 = NULL;

/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/




/* global functions / API interface -------------------------------------*/
void gt_recording_init(void)
{
    if(lock_recording) {
        ESP_LOGW(TAG, "recording is locked!");
        return;
    }
    //
    ESP_LOGI(TAG, "[1.0] Create i2s stream to read audio data from codec chip");
    int bits_per_sample = 0;
#if (CONFIG_ESP32_S3_GT_KORVO2_V3_BOARD == 1) && (CONFIG_AFE_MIC_NUM == 1)
    bits_per_sample = 16;
#else
    bits_per_sample = CODEC_ADC_BITS_PER_SAMPLE;
#endif
    i2s_stream_cfg_t i2s_cfg = I2S_STREAM_CFG_DEFAULT_WITH_PARA(CODEC_ADC_I2S_PORT, GT_RECORING_I2C_RATE, bits_per_sample, AUDIO_STREAM_READER);
    i2s_cfg.stack_in_ext = true;
    i2s_stream_reader = i2s_stream_init(&i2s_cfg);

    ESP_LOGI(TAG, "[1.1] Create wav encoder to encode wav format");
    wav_encoder_cfg_t wav_cfg = DEFAULT_WAV_ENCODER_CONFIG();
    wav_cfg.stack_in_ext = true;
    wav_encoder = wav_encoder_init(&wav_cfg);

    ESP_LOGI(TAG, "[1.2] Create fatfs stream to write data to sdcard");
    fatfs_stream_cfg_t fatfs_cfg = FATFS_STREAM_CFG_DEFAULT();
    fatfs_cfg.type = AUDIO_STREAM_WRITER;
    fatfs_cfg.ext_stack = true;
    wav_fatfs_stream_writer = fatfs_stream_init(&fatfs_cfg);

    audio_element_info_t info = AUDIO_ELEMENT_INFO_DEFAULT();
    audio_element_getinfo(i2s_stream_reader, &info);
    audio_element_setinfo(wav_fatfs_stream_writer, &info);

    ESP_LOGI(TAG, "[1.3] Create a ringbuffer and insert it between i2s_stream_reader and wav_encoder");
    ringbuf01 = rb_create(RING_BUFFER_SIZE, 1);
    audio_element_set_output_ringbuf(i2s_stream_reader, ringbuf01);
    audio_element_set_input_ringbuf(wav_encoder, ringbuf01);

    ESP_LOGI(TAG, "[1.4] Create a ringbuffer and insert it between wav_encoder and wav_fatfs_stream_writer");
    ringbuf02 = rb_create(RING_BUFFER_SIZE, 1);
    audio_element_set_output_ringbuf(wav_encoder, ringbuf02);
    audio_element_set_input_ringbuf(wav_fatfs_stream_writer, ringbuf02);

    ESP_LOGI(TAG, "[1.5] Set up uri (file as fatfs_stream, wav as wav encoder)");
    audio_element_set_uri(wav_fatfs_stream_writer, fixed_recording_path);

    lock_recording = true;
}

void gt_recording_deinit(void)
{
    if(!lock_recording) return ;

    ESP_LOGI(TAG, "[4.0] Stop elements and release resources");
    /* Release all resources */
    audio_element_deinit(i2s_stream_reader);
    audio_element_deinit(wav_encoder);
    audio_element_deinit(wav_fatfs_stream_writer);
    i2s_stream_reader = NULL;
    wav_encoder = NULL;
    wav_fatfs_stream_writer = NULL;

    rb_destroy(ringbuf01);
    rb_destroy(ringbuf02);
    ringbuf01 = NULL;
    ringbuf02 = NULL;

    lock_recording = false;
}

void gt_recording_start(void)
{
    if(!i2s_stream_reader || !wav_encoder || !wav_fatfs_stream_writer) {
        ESP_LOGW(TAG, "recording not initialized!");
        return ;
    }
    ESP_LOGI(TAG, "[2.0] Start recording!");
    audio_element_run(i2s_stream_reader);
    audio_element_run(wav_encoder);
    audio_element_run(wav_fatfs_stream_writer);

    audio_element_resume(i2s_stream_reader, 0, 0);
    audio_element_resume(wav_encoder, 0, 0);
    audio_element_resume(wav_fatfs_stream_writer, 0, 0);
}

void gt_recording_stop(void)
{
    if(!i2s_stream_reader || !wav_encoder || !wav_fatfs_stream_writer) {
        ESP_LOGW(TAG, "recording not initialized!");
        return ;
    }

    ESP_LOGI(TAG, "[3.0] Stop recording!");
    audio_element_stop(i2s_stream_reader);
    audio_element_stop(wav_encoder);
    audio_element_stop(wav_fatfs_stream_writer);
}

char gt_recording_state_get(void)
{
    return audio_element_get_state(wav_fatfs_stream_writer);
}

void gt_recording_path_set(char* path)
{
    if(!wav_fatfs_stream_writer){
        ESP_LOGW(TAG, "recording not initialized!");
        return;
    }

    if(!path) {
        ESP_LOGW(TAG, "path is NULL!");
        return;
    }

    int len = strlen(path) + 1;
    // check
    if(len < strlen("/sdcard/x.wav")+1){
        ESP_LOGE(TAG, "path too short! example: /sdcard/x.wav");
        return;
    }

    if(memcmp("/sdcard/", path, 8) != 0){
        ESP_LOGE(TAG, "path must start with /sdcard/! path too short! example: /sdcard/x.wav");
        return;
    }

    if(memcmp(".wav", path + len - 5, 4) != 0){
        ESP_LOGE(TAG, "path must end with .wav! example: /sdcard/x.wav");
        return;
    }

    ESP_LOGI(TAG, "[ * ] Set recording path: %s", path);
    audio_element_set_uri(wav_fatfs_stream_writer, path);
}


char* gt_recording_path_get(void)
{
    if(!wav_fatfs_stream_writer){
        ESP_LOGW(TAG, "recording not initialized!");
        return NULL;
    }

    return audio_element_get_uri(wav_fatfs_stream_writer);
}



/* end of file ----------------------------------------------------------*/


