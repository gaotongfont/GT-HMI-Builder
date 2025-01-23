/**
 * @file gt_audio_play.h
 * @author Yang (your@email.com)
 * @brief
 * @version 0.1
 * @date 2024-08-28 17:50:38
 * @copyright Copyright (c) 2014-2024, Company Genitop. Co., Ltd.
 */
#ifndef _GT_AUDIO_PLAY_H_
#define _GT_AUDIO_PLAY_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "board.h"
#include "audio_def.h"
#include "esp_task_wdt.h"
/* define ---------------------------------------------------------------*/
#define GT_AUDIO_I2C_RATE  (16000)


/* typedef --------------------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
/**
 * @brief Initialize the audio player
 *
 * @param board_handle the audio board handle
 */
void gt_audio_player_init(void);

void gt_audio_player_destroy(void);


/**
 * @brief Start playing the audio file. Supports wav and mp3 format.
 *
 * @param uri Such as "file://sdcard/test.mp3" or "http://iot.espressif.com/file/example.mp3".
 * @return audio_err_t
 */
audio_err_t gt_audio_player_start(const char *uri);

/**
 * @brief Stop playing the audio file.
 *
 * @return audio_err_t
 */
audio_err_t gt_audio_player_stop(void);

/**
 * @brief Pause playing the audio file.
 *
 * @return audio_err_t
 */
audio_err_t gt_audio_player_pause(void);

/**
 * @brief Resume playing the audio file.
 *
 * @return audio_err_t
 */
audio_err_t gt_audio_player_resume(void);

/**
 * @brief Get the current state of the audio player.
 *
 * @return int
 */
int gt_audio_player_state_get(void);

/**
 * @brief Set the volume of the audio player.
 *
 * @param vol
 * @return audio_err_t
 */
audio_err_t gt_audio_player_vol_set(int vol);

/**
 * @brief Get the volume of the audio player.
 *
 * @param vol
 * @return audio_err_t
 */
audio_err_t gt_audio_player_vol_get(int* vol);

/**
 * @brief Set the time_ms of the audio player
 * 
 * @param time_ms 
 * @return audio_err_t 
 */
audio_err_t gt_esp_audio_play_timeout_set(int time_ms);


audio_err_t gt_audio_player_stop_and_prepare_next(void);

/**
 * @brief stop play audio    TERMINATION_TYPE_NOW 
 * 
 * @return audio_err_t 
 */
audio_err_t gt_audio_stop_now(void);

/**
 * @brief play audio is finishing 
 * 
 * @return audio_err_t 
 */
audio_err_t gt_audio_isFinish_stop(void);

/**
 * @brief get audio prefer type ; it is set start speed
 * 
 */
audio_err_t gt_audio_prefer_type_get(void);


audio_err_t gt_audio_player_start_sync(const char *uri);

esp_err_t gt_audio_element_report_status(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_GT_AUDIO_PLAY_H_

/* end of file ----------------------------------------------------------*/


