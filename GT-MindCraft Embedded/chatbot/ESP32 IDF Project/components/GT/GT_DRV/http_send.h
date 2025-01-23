#ifndef _HTTP_SEND_H_
#define _HTTP_SEND_H_


#include <sys/param.h>
#include "esp_log.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"
#include "protocol_examples_utils.h"
#include "esp_tls.h"
#if CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
#include "esp_crt_bundle.h"
#endif
#include "esp_system.h"

#include "esp_http_client.h"

#include "cJSON.h"
#include <stdio.h>
#include <string.h>
#include "gt_recording.h"
#include "ff.h"

#include "gt_pipe_send.h"
#include "gt_record_http.h"

#define USE_HTTP_STREAM 1 //使用流式代码宏,1:流式，0:非流式

typedef struct{
//AI SETTINGS
    char emotion_output[10];
    char output_format[10];

    char user_name[120];
    int  user_age;

    char bot_name[10];
    char bot_description[250];
    char voice_id[80];
    char *bot_personality[4];
    char bot_tone[200];

    // char bot_personality[10];
    char bot_character[20];             //not used

//FUNCT SETTING
    char mode[30];
    char bot_response_style[15];
    int max_output_size;
    char emotion_value[10];
}SendSettingsData;

typedef struct{
    char *socket_type;
    char *llm_response;
    char *emotion_value;
    char *tts_audio;
    float audio_seconds;
#if USE_HTTP_STREAM
    bool is_first_response;
#endif //!USE_HTTP_STREAM
} ReceivedAnswerData;

typedef struct{

    SendSettingsData* settings;
    ReceivedAnswerData* answer;

}ChatbotData;

#if USE_HTTP_STREAM
esp_err_t resolve_stream_answer_json(char *jbuf, ReceivedAnswerData* receive_buf);
#else //!USE_HTTP_STREAM
esp_err_t resolve_answer_json(char *jbuf, ReceivedAnswerData* receive_buf);
#endif //!USE_HTTP_STREAM

void http_test_task(void *pvParameters);

#if USE_HTTP_STREAM
esp_err_t  stream_http_rest_with_url(SendSettingsData* send_data);
#else //!USE_HTTP_STREAM
esp_err_t http_rest_with_url(SendSettingsData* send_data, ReceivedAnswerData* receive_data);
#endif //!USE_HTTP_STREAM

#endif