/**
 * @file gt_recording.h
 * @author Yang (your@email.com)
 * @brief
 * @version 0.1
 * @date 2024-08-27 09:59:50
 * @copyright Copyright (c) 2014-2024, Company Genitop. Co., Ltd.
 */
#ifndef _GT_RECORDING_H_
#define _GT_RECORDING_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "esp_bit_defs.h"

/* define ---------------------------------------------------------------*/
//
#define GT_RECORING_I2C_RATE  (16000)
/* typedef --------------------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
/**
 * @brief init recording
 *
 */
void gt_recording_init(void);
/**
 * @brief deinit recording
 *
 */
void gt_recording_deinit(void);

/**
 * @brief start recording
 *
 */
void gt_recording_start(void);

/**
 * @brief stop recording
 *
 */
void gt_recording_stop(void);

/**
 * @brief Get the recording state
 *
 * @return char @ audio_element_state_t
 */
char gt_recording_state_get(void);

/**
 * @brief Set the path for saving recorded files
 *
 * @param path file path  example: "/sdcard/x.wav"
 */
void gt_recording_path_set(char* path);

/**
 * @brief Get the path for saving recorded files
 *
 * @return char*  NULL or file path
 */
char* gt_recording_path_get(void);



#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_GT_RECORDING_H_

/* end of file ----------------------------------------------------------*/


