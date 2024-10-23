/**
 * @file gt_audio_play.c
 * @author Yang (your@email.com)
 * @brief
 * @version 0.1
 * @date 2024-08-28 17:51:12
 * @copyright Copyright (c) 2014-2024, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "gt_audio_play.h"
#include <string.h>
#include <ctype.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "audio_element.h"
#include "audio_mem.h"
#include "board.h"
#include "audio_common.h"
#include "fatfs_stream.h"
#include "raw_stream.h"
#include "i2s_stream.h"
#include "esp_audio.h"
#include "esp_peripherals.h"
#include "periph_sdcard.h"
#include "periph_wifi.h"
#include "periph_button.h"
#include "periph_console.h"
#include "esp_decoder.h"
#include "amr_decoder.h"
#include "flac_decoder.h"
#include "ogg_decoder.h"
#include "opus_decoder.h"
#include "mp3_decoder.h"
#include "wav_decoder.h"
#include "aac_decoder.h"
#include "http_stream.h"
#include "wav_encoder.h"
#include "http_send.h"

/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static prototypes ----------------------------------------------------*/
extern audio_board_handle_t gt_board_handle;



/* static variables -----------------------------------------------------*/
static const char *TAG = "GT_AUDIO_PLAY";
static esp_audio_handle_t _gt_player = NULL;


/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void gt_audio_player_init(void)
{
    if(_gt_player){
        ESP_LOGW(TAG, "audio player already created!");
        return ;
    }

    ESP_LOGI(TAG, "[1.0] esp_audio_create!");
    esp_audio_cfg_t cfg = DEFAULT_ESP_AUDIO_CONFIG();
    cfg.vol_handle = gt_board_handle->audio_hal;
    cfg.vol_set = (audio_volume_set)audio_hal_set_volume;
    cfg.vol_get = (audio_volume_get)audio_hal_get_volume;
    cfg.resample_rate = 48000;
    cfg.prefer_type = ESP_AUDIO_PREFER_MEM;

    _gt_player = esp_audio_create(&cfg);

    // Create readers and add to esp_audio
    ESP_LOGI(TAG, "[2.0] esp_audio_input_stream_add!");
    fatfs_stream_cfg_t fs_reader = FATFS_STREAM_CFG_DEFAULT();
    fs_reader.type = AUDIO_STREAM_READER;
    fs_reader.ext_stack = true;

    raw_stream_cfg_t raw_reader = RAW_STREAM_CFG_DEFAULT();
    raw_reader.type = AUDIO_STREAM_READER;

    http_stream_cfg_t http_cfg = HTTP_STREAM_CFG_DEFAULT();
    http_cfg.type = AUDIO_STREAM_READER;
    http_cfg.stack_in_ext = true;

    esp_audio_input_stream_add(_gt_player, fatfs_stream_init(&fs_reader));
    esp_audio_input_stream_add(_gt_player, raw_stream_init(&raw_reader));
    esp_audio_input_stream_add(_gt_player, http_stream_init(&http_cfg));

    // Add decoders and encoders to esp_audio
    ESP_LOGI(TAG, "[3.0] esp_audio_codec_lib_add!");
    wav_decoder_cfg_t  wav_dec_cfg  = DEFAULT_WAV_DECODER_CONFIG();
    wav_dec_cfg.stack_in_ext = true;
    esp_audio_codec_lib_add(_gt_player, AUDIO_CODEC_TYPE_DECODER, wav_decoder_init(&wav_dec_cfg));
    mp3_decoder_cfg_t  mp3_dec_cfg  = DEFAULT_MP3_DECODER_CONFIG();
    wav_dec_cfg.stack_in_ext = true;
    esp_audio_codec_lib_add(_gt_player, AUDIO_CODEC_TYPE_DECODER, mp3_decoder_init(&mp3_dec_cfg));

    // Create writers and add to esp_audio
// #if (CONFIG_ESP32_S3_GT_KORVO2_V3_BOARD == 1) && (CONFIG_AFE_MIC_NUM == 1)
//     i2s_stream_cfg_t i2s_writer = I2S_STREAM_CFG_DEFAULT_WITH_PARA(I2S_NUM_0, GT_AUDIO_I2C_RATE, I2S_DATA_BIT_WIDTH_16BIT, AUDIO_STREAM_WRITER);
// #else
//     i2s_stream_cfg_t i2s_writer = I2S_STREAM_CFG_DEFAULT_WITH_PARA(I2S_NUM_0, GT_AUDIO_I2C_RATE, CODEC_ADC_BITS_PER_SAMPLE, AUDIO_STREAM_WRITER);
//     i2s_writer.need_expand = (CODEC_ADC_BITS_PER_SAMPLE != 16);
// #endif
#if (CONFIG_ESP32_S3_GT_KORVO2_V3_BOARD == 1) && (USE_HTTP_STREAM == 1)
    i2s_stream_cfg_t i2s_writer = I2S_STREAM_CFG_DEFAULT_WITH_PARA(I2S_NUM_0, GT_AUDIO_I2C_RATE, I2S_DATA_BIT_WIDTH_16BIT, AUDIO_STREAM_WRITER);
#else //!USE_HTTP_STREAM
    i2s_stream_cfg_t i2s_writer = I2S_STREAM_CFG_DEFAULT_WITH_PARA(I2S_NUM_0, GT_AUDIO_I2C_RATE, CODEC_ADC_BITS_PER_SAMPLE, AUDIO_STREAM_WRITER);
    i2s_writer.need_expand = (CODEC_ADC_BITS_PER_SAMPLE != 16);
#endif //!USE_HTTP_STREAM
    i2s_writer.stack_in_ext = true;
    audio_element_handle_t i2s_stream_writer = i2s_stream_init(&i2s_writer);
    esp_audio_output_stream_add(_gt_player, i2s_stream_writer);

    // Set default volume
    esp_audio_vol_set(_gt_player, 60);
    //log
    AUDIO_MEM_SHOW(TAG);
    ESP_LOGI(TAG, "esp_audio instance is:%p\r\n", _gt_player);
}

void gt_audio_player_destroy(void)
{
    if(!_gt_player){
        ESP_LOGW(TAG, "player is not init!");
        return;
    }
    esp_audio_destroy(_gt_player);
    _gt_player = NULL;
}

audio_err_t gt_audio_player_start(const char *uri)
{
    ESP_LOGI(TAG, "start player music!");
    if(!_gt_player || !uri){
        ESP_LOGW(TAG, "player is not init or uri is null!");
        return ESP_ERR_AUDIO_FAIL;
    }
    // return esp_audio_sync_play(_gt_player, uri, 0);
    return esp_audio_play(_gt_player, AUDIO_CODEC_TYPE_DECODER, uri, 0);
}

audio_err_t gt_audio_player_stop(void)
{
    ESP_LOGI(TAG, "stop player music!");
    if(!_gt_player){
        ESP_LOGW(TAG, "player is not init!");
        return ESP_ERR_AUDIO_FAIL;
    }
    return esp_audio_stop(_gt_player, AUDIO_CODEC_TYPE_DECODER);
}

audio_err_t gt_audio_player_pause(void)
{
    ESP_LOGI(TAG, "pause player music!");
    if(!_gt_player){
        ESP_LOGW(TAG, "player is not init!");
        return ESP_ERR_AUDIO_FAIL;
    }
    return esp_audio_pause(_gt_player);
}

audio_err_t gt_audio_player_resume(void)
{
    ESP_LOGI(TAG, "resume player music!");
    if(!_gt_player){
        ESP_LOGW(TAG, "player is not init!");
        return ESP_ERR_AUDIO_FAIL;
    }
    return esp_audio_resume(_gt_player);
}


int gt_audio_player_state_get(void)
{
    if(!_gt_player){
        ESP_LOGW(TAG, "player is not init!");
        return ESP_ERR_AUDIO_FAIL;
    }
    esp_audio_state_t state;
    if(ESP_ERR_AUDIO_NO_ERROR != esp_audio_state_get(_gt_player, &state)){
        ESP_LOGE(TAG, "get player state failed!");
        return ESP_ERR_AUDIO_FAIL;
    }

    return state.status;
}

audio_err_t gt_audio_player_vol_set(int vol)
{
    if(!_gt_player){
        ESP_LOGW(TAG, "player is not init!");
        return ESP_ERR_AUDIO_FAIL;
    }
    return esp_audio_vol_set(_gt_player, vol);
}

audio_err_t gt_audio_player_vol_get(int* vol)
{
    if(!_gt_player){
        ESP_LOGW(TAG, "player is not init!");
        return ESP_ERR_AUDIO_FAIL;
    }
    return esp_audio_vol_get(_gt_player, vol);
}

audio_err_t gt_audio_player_stop_and_prepare_next(void)
{
    ESP_LOGI(TAG, "stop and prepare for next player music!");
    if (!_gt_player) {
        ESP_LOGW(TAG, "player is not init!");
        return ESP_ERR_AUDIO_FAIL;
    }

    esp_err_t err = esp_audio_stop(_gt_player, TERMINATION_TYPE_NOW);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to stop player immediately!");
        return ESP_ERR_AUDIO_FAIL;
    }

    esp_audio_state_t state;
    esp_audio_state_get(_gt_player, &state);
    state.status = AUDIO_STATUS_FINISHED;
    ESP_LOGI(TAG, "Player state set to FINISHED.");

    return ESP_OK;
}

/* end of file ----------------------------------------------------------*/


