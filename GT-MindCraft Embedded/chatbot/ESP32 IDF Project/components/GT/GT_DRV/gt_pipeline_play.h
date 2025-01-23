#ifndef GT_PIPELINE_H
#define GT_PIPELINE_H

#ifdef __cplusplus
extern "C"{
#endif


/* include --------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "esp_log.h"
#include "audio_element.h"
#include "audio_pipeline.h"
#include "audio_event_iface.h"
#include "audio_common.h"
#include "http_stream.h"
#include "i2s_stream.h"
#include "mp3_decoder.h"
#include "board.h"
#include "esp_audio.h"
/* define ---------------------------------------------------------------*/

typedef struct gt_pipeline GTPIPELINE;

void gt_pipeline_init(GTPIPELINE* gt_pipeline_obj);

GTPIPELINE* gt_pipeline_single();

int gt_audio_pipeline_run(GTPIPELINE* gt_pipeline_obj, const char* uri);

audio_event_iface_msg_t* get_iface_msg(GTPIPELINE* gt_pipeline_obj);

audio_event_iface_handle_t get_evt(GTPIPELINE* gt_pipeline_obj);

audio_element_handle_t get_mp3_decoder(GTPIPELINE* gt_pipeline_obj);

audio_element_handle_t get_i2s_stream_writer(GTPIPELINE* gt_pipeline_obj);

audio_element_handle_t get_http_stream_reader(GTPIPELINE* gt_pipeline_obj);

int gt_audio_pipeline_stop(GTPIPELINE* gt_pipeline_obj);

int gt_audio_pipeline_resume(GTPIPELINE* gt_pipeline_obj);

int gt_audio_pipeline_reset_items_state(GTPIPELINE* gt_pipeline_obj);

int gt_audio_event_iface_discard (GTPIPELINE* gt_pipeline_obj);

void set_startListen(GTPIPELINE* gt_pipeline_obj, bool value);

bool get_startListen();

#ifdef __cplusplus
}
#endif


#endif // !GT_PIPELINE_H