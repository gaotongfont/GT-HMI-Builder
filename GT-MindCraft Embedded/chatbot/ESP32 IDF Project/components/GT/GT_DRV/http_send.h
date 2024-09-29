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

typedef struct{
    char emotion_output[15];
    char voice_id[15];
    int  user_age;
    char bot_name[10];
    char bot_character[10];
    char bot_personality[10];
    char output_format[10];
}SendSettingsData;

typedef struct{
    char *asr_content;
    char *llm_response;
    char *emotion_value;
    char *tts_audio;
    float audio_seconds;
} ReceivedAnswerData;

typedef struct{

    SendSettingsData* settings;
    ReceivedAnswerData* answer;

}ChatbotData;

esp_err_t resolve_answer_json(char *jbuf, ReceivedAnswerData* receive_buf);
void http_test_task(void *pvParameters);

esp_err_t http_rest_with_url(SendSettingsData* send_data, ReceivedAnswerData* receive_data);

#endif