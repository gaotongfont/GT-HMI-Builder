#ifndef GT_AUDIO_STORAGE
#define GT_AUDIO_STORAGE


#ifdef __cplusplus
extern "C"{
#endif


/* include --------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "esp_bit_defs.h"
#include "gt_websocket.h"
#include "gt_protocol_config.h"

/* define ---------------------------------------------------------------*/
//
#define GT_AUDIO_MEMORY_I2C_RATE  (16000)

void gt_audio_storage_init(void);
void gt_audio_storage_deinit(void);
void gt_audio_storage_start(void);
void gt_audio_storage_stop(void);
void get_pcm_data(void);

// char* get_audio_memory_buffer();

// void gt_audio_storage_init(void);
// void gt_audio_storage_deinit(void);
// void gt_audio_storage_start(void);
// void gt_audio_storage_stop(void);
// char gt_audio_storage_state_get(void);



#ifdef __cplusplus
}
#endif


#endif // !GT_AUDIO_STORAGE