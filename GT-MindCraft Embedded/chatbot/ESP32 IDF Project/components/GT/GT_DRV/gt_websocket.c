/*
 * SPDX-FileCopyrightText: 2022-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
/* ESP HTTP Client Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/


#include <stdio.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
// #include "protocol_examples_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

#include "esp_log.h"
#include "esp_websocket_client.h"
#include "esp_event.h"
#include <cJSON.h>

#include "gt_websocket.h"

#define NO_DATA_TIMEOUT_SEC 60

static const char *TAG = "websocket";

static TimerHandle_t shutdown_signal_timer;
static SemaphoreHandle_t shutdown_sema;


static esp_websocket_client_handle_t client;
static TimerHandle_t gt_timer;
static SemaphoreHandle_t checkroom_semaphore;
static SemaphoreHandle_t create_semaphore;
static int sem_takecount = 0;
static WEBSOCKET_RECEIVED_DATA* clock_buf = NULL;

static bool isFirstAudiouri = false;
ReceivedAnswerData* chat_bot_receive = NULL;
static char* chatbot_audio_uri = NULL;
static int audio_uri_len = 0;

static gt_obj_st* serve_dialog = NULL;

extern ChatbotData cb_data;
extern QueueHandle_t mYxQueue3;
extern SemaphoreHandle_t tts_audio_sem;


static void log_error_if_nonzero(const char *message, int error_code)
{
    if (error_code != 0) {
        ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);
    }
}

static void shutdown_signaler(TimerHandle_t xTimer)
{
    ESP_LOGI(TAG, "No data received for %d seconds, signaling shutdown", NO_DATA_TIMEOUT_SEC);
    // xSemaphoreGive(shutdown_sema);
}

#if CONFIG_WEBSOCKET_URI_FROM_STDIN
static void get_string(char *line, size_t size)
{
    int count = 0;
    while (count < size) {
        int c = fgetc(stdin);
        if (c == '\n') {
            line[count] = '\0';
            break;
        } else if (c > 0 && c < 127) {
            line[count] = c;
            ++count;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

#endif /* CONFIG_WEBSOCKET_URI_FROM_STDIN */

static void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_websocket_event_data_t *data = (esp_websocket_event_data_t *)event_data;
    switch (event_id) {
    case WEBSOCKET_EVENT_CONNECTED:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_CONNECTED");
        gt_dialog_close(serve_dialog);
        gt_websocket_client_request();

        break;
    case WEBSOCKET_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_DISCONNECTED");
        log_error_if_nonzero("HTTP status code",  data->error_handle.esp_ws_handshake_status_code);
        if (data->error_handle.error_type == WEBSOCKET_ERROR_TYPE_TCP_TRANSPORT) {
            log_error_if_nonzero("reported from esp-tls", data->error_handle.esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", data->error_handle.esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno",  data->error_handle.esp_transport_sock_errno);
        }
        break;
    case WEBSOCKET_EVENT_DATA:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_DATA");
        ESP_LOGI(TAG, "Received opcode=%d", data->op_code);
        if (data->op_code == 0x08 && data->data_len == 2) {
            ESP_LOGW(TAG, "Received closed message with code=%d", 256 * data->data_ptr[0] + data->data_ptr[1]);
        } else {
            ESP_LOGW(TAG, "Received=%.*s\n\n", data->data_len, (char *)data->data_ptr);
        }

        char* jbuf = (char*)audio_malloc(data->data_len+1);
        memset(jbuf, 0, data->data_len+1);
        memcpy(jbuf, data->data_ptr, data->data_len);

        chat_bot_receive = (ReceivedAnswerData*)audio_malloc(sizeof(ReceivedAnswerData));
        memset(chat_bot_receive, 0, sizeof(ReceivedAnswerData));

        if(websocket_chatbot_json_parse(jbuf, chat_bot_receive) != -1)
        {
            BaseType_t xHigherPriorityTaskWoken = pdFALSE;
            xQueueSendFromISR(mYxQueue3, &chat_bot_receive, &xHigherPriorityTaskWoken);
            if(isFirstAudiouri == true)
            {
                if(chat_bot_receive->tts_audio != NULL)
                {
                    ESP_LOGE(TAG, "clock_buf->recover_data.tts_audio != NULL");
                    if(chat_bot_receive->tts_audio != NULL && strcmp(chat_bot_receive->tts_audio, "") != 0)
                    {
                        ESP_LOGE(TAG, "clock_buf->recover_data.tts_audio = %s", chat_bot_receive->tts_audio);
                        set_chatbot_audio_uri(chat_bot_receive->tts_audio);
                        // xSemaphoreGive(tts_audio_sem);
                        if (xSemaphoreGive(tts_audio_sem) == pdPASS) {
                            ESP_LOGI(TAG, "Semaphore successfully given");
                        }
                        isFirstAudiouri = false;
                    }
                }
            }
        }
        else
        {
            audio_free(chat_bot_receive);
            chat_bot_receive = NULL;
            ESP_LOGW(TAG, "chat_bot_receive = NULL");
        }
        audio_free(jbuf);
        jbuf = NULL;

        // If received data contains json structure it succeed to parse
        // cJSON *root = cJSON_Parse(data->data_ptr);
        // if (root) {
        //     for (int i = 0 ; i < cJSON_GetArraySize(root) ; i++) {
        //         cJSON *elem = cJSON_GetArrayItem(root, i);
        //         cJSON *id = cJSON_GetObjectItem(elem, "id");
        //         cJSON *name = cJSON_GetObjectItem(elem, "name");
        //         ESP_LOGW(TAG, "Json={'id': '%s', 'name': '%s'}", id->valuestring, name->valuestring);
        //     }
        //     cJSON_Delete(root);
        // }

        ESP_LOGW(TAG, "Total payload length=%d, data_len=%d, current payload offset=%d\r\n", data->payload_len, data->data_len, data->payload_offset);
        xTimerReset(shutdown_signal_timer, portMAX_DELAY);

        break;
    case WEBSOCKET_EVENT_ERROR:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_ERROR");
        serve_dialog_init();
        log_error_if_nonzero("HTTP status code",  data->error_handle.esp_ws_handshake_status_code);
        if (data->error_handle.error_type == WEBSOCKET_ERROR_TYPE_TCP_TRANSPORT) {
            log_error_if_nonzero("reported from esp-tls", data->error_handle.esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", data->error_handle.esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno",  data->error_handle.esp_transport_sock_errno);
        }
        break;
    }
}


void gt_websocket_client_request()
{
    char data[] = {"{\"socket_type\":\"agent_event\",\"event_name\":\"auth_token\",\"event_params\": \
                    {\"token\":\"API keys\"}}"};//设置请求头的时候要加上API keys
    esp_websocket_client_send_text(client, data, strlen(data), portMAX_DELAY);
    // esp_websocket_client_send_text_partial(client, data, strlen(data), portMAX_DELAY);
}

int check_opcode(unsigned char opcode)
{
    if(opcode == 1002 || opcode == 1007)
    {
        xTimerDelete(shutdown_signal_timer, portMAX_DELAY);
        vSemaphoreDelete(shutdown_sema);
        esp_websocket_client_start(client);
        gt_websocket_client_request();
        return ESP_FAIL;
    }

    return ESP_OK;
}

void gt_websocket_client_checkroom_isexist()
{
    char data_create[] = {"{\"socket_type\":\"interface_call\",\"event_name\":\"session_check\",\"event_params\": \
                            {\"session_token\":\"bd88b6e8-d797-4144-8f38-e33913046bbb\"}}"};
    esp_websocket_client_send_text(client, data_create, strlen(data_create), portMAX_DELAY);
    // esp_websocket_client_send_text_partial(client, data_create, strlen(data_create), portMAX_DELAY);
    // esp_websocket_client_send_fin(client, portMAX_DELAY);
}

void gt_websocket_client_create_room()
{
    char data_create[] = {"{\"socket_type\":\"interface_call\",\"event_name\":\"create_session\",\"event_params\":\
                            {\"session_name\":\"test\",\"session_remark\":\"{}\",\"config_data\":{},\"model\": \
                            \"deepseek-chat\",\"prompt\":\"#\",\"temperature\":0.2,\"max_tokens\":4000,\"history_length\":8}}"};
    esp_websocket_client_send_text(client, data_create, strlen(data_create), portMAX_DELAY);
    // esp_websocket_client_send_cont_msg(client, data_create, strlen(data_create), portMAX_DELAY);
}

void gt_websocket_client_create_task()
{
    int i = 0;
    char buf[30] = {0};
    char personality[20] = {0};
    // char emotion_output[10] = {0};
    bool emotion_output = true;
    char data_create_2[2500] = {0};
    emotion_output = strcmp(cb_data.settings->emotion_value, "打开") == 0 ? true : false;
    sprintf(buf, "%s,%s,%s,%s", cb_data.settings->bot_personality[0], cb_data.settings->bot_personality[1], cb_data.settings->bot_personality[2], cb_data.settings->bot_personality[3]);
    snprintf(data_create_2, 2500, "{\"socket_type\": \"agent_event\",\"event_name\": \"agent_action\",\
                            \"event_params\": { \"agent_name\": \"chat_bot_v2\",\"upload_format\": \"pcm\",\
                            \"upload_sample_rate\": 16000,\"mode\": \"customize\",\
                            \"emotion_output\": %d,\"voice_id\": \"%s\",\
                            \"speed\": 1, \"user_name\": \"%s\",\"user_age\": %d,\"bot_name\": \"%s\",\
                            \"bot_character_description\": \"%s\",\
                            \"bot_character\": \"朋友\",\"bot_personality\": \"%s\",\
                            \"bot_tone\": \"%s\",\"llm_model\": \"abab6.5s-chat\",\
                            \"max_tokens\": 100,\"tts_model\": \"MM_TTSL_realtime_speech-01-turbo\",\
                            \"language\": \"中文\"}}",\
                            emotion_output, cb_data.settings->voice_id,cb_data.settings->user_name, cb_data.settings->user_age, cb_data.settings->bot_name,\
                            cb_data.settings->bot_description, buf, cb_data.settings->bot_tone);

    printf("--------------------------------data_create_2 = %s\n", data_create_2);

    char data_create[] = {"{\"socket_type\": \"agent_event\",\"event_name\": \"agent_action\", \
                            \"event_params\": { \"agent_name\": \"chat_bot_v2\",\"upload_format\": \"pcm\", \
                            \"upload_sample_rate\": 16000,\"mode\": \"customize\", \
                            \"emotion_output\": true,\"voice_id\": \"cute_boy\", \
                            \"speed\": 1,\"user_age\": 5,\"bot_name\": \"智酱\", \
                            \"bot_description\": \"你是住在芯片王国里的AI机器人，可以帮助用户解决各式各样的问题\", \
                            \"bot_character\": \"朋友\",\"bot_personality\": \"有趣\", \
                            \"bot_response_style\": \"normal\",\"llm_model\": \"abab6.5s-chat\", \
                            \"max_tokens\": 100,\"tts_model\": \"MM_TTSL_realtime_speech-01-turbo\",\"asr_model\": \"BD_ASR_realtime\"}}"};
    esp_websocket_client_send_text(client, data_create_2, strlen(data_create_2), portMAX_DELAY);
}

void gt_websocket_client_get_history_message()
{
    char data_create[] = {"{\"socket_type\":\"interface_call\",\"event_name\":\"message_list\",\"event_params\": \
                            {\"session_token\":\"bd88b6e8-d797-4144-8f38-e33913046bbb\",\"size\":8}}"};
    esp_websocket_client_send_text(client, data_create, strlen(data_create), portMAX_DELAY);
}

void gt_websocket_client_clear_history_message()
{
    char data_create[] = {"{\"socket_type\":\"interface_call\",\"event_name\":\"message_clear\",\"event_params\": \
                            {\"session_token\":\"bd88b6e8-d797-4144-8f38-e33913046bbb\"}}"};
    esp_websocket_client_send_text(client, data_create, strlen(data_create), portMAX_DELAY);
}

void gt_websocket_client_stop_send_audio_data()
{
    char data_create[] = {"{\"socket_type\": \"intervent_event\", \"event_name\":\"agent_action\"}"};
    esp_websocket_client_send_text(client, data_create, strlen(data_create), portMAX_DELAY);
}

void gt_websocket_client_stop_receive_data()
{
    char data_create[] = {"{\"socket_type\": \"intervent_event\",\"event_name\": \"stream_output\"}"};
    esp_websocket_client_send_text(client, data_create, strlen(data_create), portMAX_DELAY);
    ESP_LOGE(TAG, "gt_websocket_client_stop_receive_data !!!!!!!!!!!!!!");
}

void gt_websocket_client_init()
{
    esp_websocket_client_config_t websocket_cfg = {};
    clock_buf = (WEBSOCKET_RECEIVED_DATA*)audio_malloc(sizeof(WEBSOCKET_RECEIVED_DATA));
    memset(clock_buf, 0, sizeof(WEBSOCKET_RECEIVED_DATA));
    shutdown_signal_timer = xTimerCreate("Websocket shutdown timer", NO_DATA_TIMEOUT_SEC * 1000 / portTICK_PERIOD_MS,
                                         pdFALSE, NULL, shutdown_signaler);
    // shutdown_sema = xSemaphoreCreateBinary();

    websocket_cfg.uri = "ws://api.mindcraft.com.cn/socket-v1/?type=mcu&response_detail=1";
    websocket_cfg.reconnect_timeout_ms = 10000;
    websocket_cfg.network_timeout_ms = 6000;
    websocket_cfg.buffer_size = 4096;
    websocket_cfg.pingpong_timeout_sec = 15;
    websocket_cfg.task_prio = 3;
    ESP_LOGI(TAG, "Connecting to %s...", websocket_cfg.uri);
    clock_buf = (WEBSOCKET_RECEIVED_DATA*)audio_calloc(1, sizeof(WEBSOCKET_RECEIVED_DATA));
    client = esp_websocket_client_init(&websocket_cfg);
    esp_websocket_register_events(client, WEBSOCKET_EVENT_ANY, websocket_event_handler, (void *)client);
    esp_websocket_client_start(client);
    xTimerStart(shutdown_signal_timer, portMAX_DELAY);
    // gt_websocket_client_request();
    // xSemaphoreTake(shutdown_sema, portMAX_DELAY);
    ESP_LOGE(TAG, "esp_websocket_client close connect !!!!!!!");
}

void gt_websocket_send_data(char* data)
{
    if (esp_websocket_client_is_connected(client))
    {
        esp_websocket_client_send_bin(client, data, 2048, portMAX_DELAY);
        esp_websocket_client_send_bin(client, data+2048, 2048, portMAX_DELAY);
        // esp_websocket_client_send_bin_partial(client, data, 2048, portMAX_DELAY);
        // esp_websocket_client_send_cont_msg(client, data+2048, 2048, portMAX_DELAY);
        // esp_websocket_client_send_fin(client, portMAX_DELAY);
        ESP_LOGI(TAG, "esp_websocket_client send successfull !!!!!!!");
    }
    else
    {
        ESP_LOGE(TAG, "esp_websocket_client is not connected");
    }

}

void gt_websocket_client_start()
{
    int gt_res = 0;
    gt_res = esp_websocket_client_start(client);
    if(gt_res == ESP_FAIL)
    {
        ESP_LOGE(TAG, "esp_websocket_client_start is FAIL");
    }
    else
    {
        ESP_LOGI(TAG, "esp_websocket_client_start is OK");
    }
}

void gt_websocket_client_close()
{
    int gt_res = 0;
    gt_res = esp_websocket_client_close(client, portMAX_DELAY);
    if(gt_res == ESP_FAIL)
    {
        ESP_LOGE(TAG, "gt_websocket_client_close is FAIL");
    }
}

void gt_websocket_client_destroy()
{
    int gt_res = 0;
    gt_res = esp_websocket_client_destroy(client);
    if(gt_res == ESP_FAIL)
    {
        ESP_LOGE(TAG, "gt_websocket_client_destroy is FAIL");
    }
}


void set_isFirstAudiouri(bool value)
{
    isFirstAudiouri = value;
}

void set_chatbot_audio_uri(char* audio_uri)
{
    if(chatbot_audio_uri != NULL)
    {
        audio_free(chatbot_audio_uri);
        chatbot_audio_uri = NULL;
    }
    chatbot_audio_uri = audio_uri;
    // chatbot_audio_uri = (char*)audio_malloc(strlen(audio_uri)+1);
    // memset(chatbot_audio_uri, 0, strlen(audio_uri)+1);
    // strcpy(chatbot_audio_uri, audio_uri);
}

char* get_chatbot_audio_uri()
{
    if(chatbot_audio_uri != NULL)
    {
        ESP_LOGE(TAG, "chatbot_audio_uri is not NULL");
        return chatbot_audio_uri;
    }
    else
    {
        ESP_LOGE(TAG, "chatbot_audio_uri is NULL");
        return NULL;
    }
}

void free_chatbot_audio_uri()
{
    if(chatbot_audio_uri != NULL)
    {
        audio_free(chatbot_audio_uri);
        chatbot_audio_uri = NULL;
    }
    else
    {
        ESP_LOGE(TAG, "chatbot_audio_uri is NULL");
    }

}

void serve_dialog_init()
{
    serve_dialog = serve_disconnect_dialog();
}

/**
 * @brief 解析口语json数据
 *
 * @param json_obj
 * @param clock_buf
 */
void web_oral_pratice_json_parse(cJSON* json_obj, WEBSOCKET_RECEIVED_DATA* clock_buf)
{
    cJSON* oral_pratice_json = NULL;
    cJSON* preferred_responses_for_next_round = NULL;
    cJSON* round = NULL;
    do{
        GET_VALUESTRING(oral_pratice_json, json_obj, "english_response", clock_buf->web_oral_pratice.english_response);
        GET_VALUESTRING(oral_pratice_json, json_obj, "query_translation", clock_buf->web_oral_pratice.query_translation);
        GET_VALUESTRING(oral_pratice_json, json_obj, "response_translation", clock_buf->web_oral_pratice.response_translation);
        GET_VALUESTRING(oral_pratice_json, json_obj, "tts_audio", clock_buf->web_oral_pratice.oral_pratice_tts_audio);


        preferred_responses_for_next_round = cJSON_GetObjectItem(json_obj, "preferred_responses_for_next_round");
        round = cJSON_GetArrayItem(preferred_responses_for_next_round, 0);
        clock_buf->web_oral_pratice.preferred_responses_for_next_round[0] = (char*)audio_calloc(1, strlen(round->valuestring) + 1);
        strcpy(clock_buf->web_oral_pratice.preferred_responses_for_next_round[0], round->valuestring);
        round = cJSON_GetArrayItem(preferred_responses_for_next_round, 1);
        clock_buf->web_oral_pratice.preferred_responses_for_next_round[1] = (char*)audio_calloc(1, strlen(round->valuestring) + 1);
        strcpy(clock_buf->web_oral_pratice.preferred_responses_for_next_round[1], round->valuestring);
        round = cJSON_GetArrayItem(preferred_responses_for_next_round, 2);
        clock_buf->web_oral_pratice.preferred_responses_for_next_round[2] = (char*)audio_calloc(1, strlen(round->valuestring) + 1);
        strcpy(clock_buf->web_oral_pratice.preferred_responses_for_next_round[2], round->valuestring);
    }while(0);
}

/**
 * @brief 解析实时天气
 *
 * @param json_obj
 * @param clock_buf
 */
void web_weather_realtime_data_json_parse(cJSON* json_obj, WEBSOCKET_RECEIVED_DATA* clock_buf)
{
    int weather_arry_item = 0, weather_days = 0;
    cJSON* weather = NULL;
    cJSON* weather_data = NULL;
    cJSON* weathers = NULL;
    cJSON* weather_arry = NULL;
    cJSON* data_value = NULL;
    cJSON* data_response_json = NULL;
    do{
        if(weather_days == 0)
        {
            data_value = cJSON_GetObjectItem(json_obj, "data_value");
            GET_VALUEINT(data_response_json, data_value, "time_stamp", clock_buf->time_stamp);
            weather = cJSON_GetObjectItem(data_value, "weather");
            // GET_VALUESTRING(data_response_json, weather, "ip_address", clock_buf->clock_weather.ip_address);
            weather_data = cJSON_GetObjectItem(weather, "weather_data");
            weathers = cJSON_GetObjectItem(weather_data, "weathers");
        }
        weather_arry = cJSON_GetArrayItem(weathers, weather_arry_item);
        if(weather_arry != NULL)
        {
            GET_VALUESTRING(data_response_json, weather_arry, "valid", clock_buf->weather_data[weather_days].valid);
            GET_VALUESTRING(data_response_json, weather_arry, "cap", clock_buf->weather_data[weather_days].cap);
            GET_VALUESTRING(data_response_json, weather_arry, "cap_type", clock_buf->weather_data[weather_days].cap_type);
            GET_VALUEDOUBLE(data_response_json, weather_arry, "precip", clock_buf->weather_data[weather_days].precip);
            GET_VALUEDOUBLE(data_response_json, weather_arry, "windMax", clock_buf->weather_data[weather_days].windMax);
            GET_VALUEDOUBLE(data_response_json, weather_arry, "windMaxDir", clock_buf->weather_data[weather_days].windMaxDir);
            GET_VALUEDOUBLE(data_response_json, weather_arry, "rhHi", clock_buf->weather_data[weather_days].rhHi);
            GET_VALUEDOUBLE(data_response_json, weather_arry, "tempHi", clock_buf->weather_data[weather_days].tempHi);
            GET_VALUEDOUBLE(data_response_json, weather_arry, "tempLo", clock_buf->weather_data[weather_days].tempLo);
            weather_arry_item++;
        }
        weather_days++;
    }while(weather_arry_item < WEATHER_DATA_RESPONSE_DAYS);

}

/**
 * @brief 解析机器人回复
 *
 * @param json_obj
 * @param clock_buf
 */
void web_bot_recover_json_parse(cJSON* json_obj, WEBSOCKET_RECEIVED_DATA* clock_buf)
{
    cJSON* recover_json = NULL;
    do{
        GET_VALUESTRING(recover_json, json_obj, "llm_response", clock_buf->recover_data.llm_response);
        GET_VALUESTRING(recover_json, json_obj, "tts_audio", clock_buf->recover_data.tts_audio);
        GET_VALUESTRING(recover_json, json_obj, "user_input", clock_buf->user_input);
        // GET_VALUEDOUBLE(recover_json, agent_output, "audio_seconds", clock_buf->recover_data.audio_seconds);
    }while(0);
}


/**
 * @brief 解析闹钟的数据
 *
 * @param json_obj
 * @param clock_buf
 */
void web_set_alarm_data_json_parse(cJSON* json_obj, WEBSOCKET_RECEIVED_DATA* clock_buf)
{
    cJSON* clock_json = NULL;
    do{
        GET_VALUESTRING(clock_json, json_obj, "instruct_type", clock_buf->clock_data.instruct_type);
        if(strcmp(clock_buf->clock_data.instruct_type, "create_alarm") == 0)
        {
            GET_VALUESTRING(clock_json, json_obj, "alarm_date", clock_buf->clock_data.alarm_date);
            GET_VALUESTRING(clock_json, json_obj, "alarm_time", clock_buf->clock_data.alarm_time);
            GET_VALUESTRING(clock_json, json_obj, "period", clock_buf->clock_data.period);
            GET_VALUESTRING(clock_json, json_obj, "alarm_purpose", clock_buf->clock_data.alarm_purpose);
            GET_VALUESTRING(clock_json, json_obj, "alarm_repeat", clock_buf->clock_data.alarm_repeat);
        }
        else if(strcmp(clock_buf->clock_data.instruct_type, "check_alarm") == 0)
        {
            GET_VALUESTRING(clock_json, json_obj, "alarm_date", clock_buf->clock_data.alarm_date);
        }
        else if(strcmp(clock_buf->clock_data.instruct_type, "edit_alarm") == 0)
        {
            GET_VALUESTRING(clock_json, json_obj, "alarm_date", clock_buf->clock_data.alarm_date);
            GET_VALUESTRING(clock_json, json_obj, "alarm_time", clock_buf->clock_data.alarm_time);
            GET_VALUESTRING(clock_json, json_obj, "period", clock_buf->clock_data.period);
            GET_VALUESTRING(clock_json, json_obj, "new_alarm_time", clock_buf->clock_data.new_alarm_time);
            GET_VALUESTRING(clock_json, json_obj, "new_period", clock_buf->clock_data.new_period);
        }
        else if(strcmp(clock_buf->clock_data.instruct_type, "delete_alarm") == 0)
        {
            GET_VALUESTRING(clock_json, json_obj, "alarm_date", clock_buf->clock_data.alarm_date);
            GET_VALUESTRING(clock_json, json_obj, "alarm_time", clock_buf->clock_data.alarm_time);
            GET_VALUESTRING(clock_json, json_obj, "period", clock_buf->clock_data.period);
        }
    }while(0);
}

/**
 * @brief 解析查询天气的数据
 *
 * @param json_obj
 * @param clock_buf
 */
void web_check_weather_json_parse(cJSON* json_obj, WEBSOCKET_RECEIVED_DATA* clock_buf)
{
    int days =  0, array_item = 0;
    cJSON* weathers = NULL;
    cJSON* weathers_json = NULL, *future_w = NULL;
    cJSON* reveal_data = NULL;
    do{
        if(days == 0)
        {
            GET_VALUESTRING(weathers_json, json_obj, "address", clock_buf->weather_data[days].address);
            GET_VALUESTRING(weathers_json, json_obj, "tts_audio", clock_buf->weather_tts_audio);
            reveal_data = cJSON_GetObjectItem(json_obj, "reveal_data");
            if(reveal_data == NULL)
            {break;}

            GET_VALUESTRING(weathers_json, reveal_data, "valid", clock_buf->weather_data[days].valid)
            GET_VALUESTRING(weathers_json, reveal_data, "cap", clock_buf->weather_data[days].cap);
            GET_VALUESTRING(weathers_json, reveal_data, "cap_type", clock_buf->weather_data[days].cap_type);
            GET_VALUEDOUBLE(weathers_json, reveal_data, "precip", clock_buf->weather_data[days].precip);
            GET_VALUEDOUBLE(weathers_json, reveal_data, "windMax", clock_buf->weather_data[days].windMax);
            GET_VALUEDOUBLE(weathers_json, reveal_data, "windMaxDir", clock_buf->weather_data[days].windMaxDir);
            GET_VALUEDOUBLE(weathers_json, reveal_data, "rhHi", clock_buf->weather_data[days].rhHi);
            GET_VALUEDOUBLE(weathers_json, reveal_data, "tempHi", clock_buf->weather_data[days].tempHi);
            GET_VALUEDOUBLE(weathers_json, reveal_data, "tempLo", clock_buf->weather_data[days].tempLo);
            weathers = cJSON_GetObjectItem(json_obj, "weathers");
        }
        else if(days > 0)
        {
            if(weathers != NULL)
            {
                future_w = cJSON_GetArrayItem(weathers, array_item);
                if(future_w != NULL)
                {
                    GET_VALUESTRING(weathers_json, future_w, "valid", clock_buf->weather_data[days].valid);
                    GET_VALUESTRING(weathers_json, future_w, "cap", clock_buf->weather_data[days].cap);
                    GET_VALUESTRING(weathers_json, future_w, "cap_type", clock_buf->weather_data[days].cap_type);
                    GET_VALUEDOUBLE(weathers_json, future_w, "precip", clock_buf->weather_data[days].precip);
                    GET_VALUEDOUBLE(weathers_json, future_w, "windMax", clock_buf->weather_data[days].windMax);
                    GET_VALUEDOUBLE(weathers_json, future_w, "windMaxDir", clock_buf->weather_data[days].windMaxDir);
                    GET_VALUEDOUBLE(weathers_json, future_w, "rhHi", clock_buf->weather_data[days].rhHi);
                    GET_VALUEDOUBLE(weathers_json, future_w, "tempHi", clock_buf->weather_data[days].tempHi);
                    GET_VALUEDOUBLE(weathers_json, future_w, "tempLo", clock_buf->weather_data[days].tempLo);
                }
                array_item++;
            }
        }
        days++;
    }while(days < WEATHER_DAYS);
}


/**
 * @brief 解析倒计时数据
 *
 * @param json_obj
 * @param clock_buf
 */
static void web_set_countdown_json_parse(cJSON* json_obj, WEBSOCKET_RECEIVED_DATA* clock_buf)
{
    cJSON* countdown_json = NULL;
    do{
        GET_VALUESTRING(countdown_json, json_obj, "countdown", clock_buf->countdown);
    }while(0);
}

/**
 * @brief 解析设备设置数据
 *
 * @param json_obj
 * @param clock_buf
 */
static void web_device_config_json_parse(cJSON* json_obj, WEBSOCKET_RECEIVED_DATA* clock_buf)
{
    cJSON* config_json = NULL;
    do{
        GET_VALUESTRING(config_json, json_obj, "config_name", clock_buf->web_sys_config.config_name);
        GET_VALUESTRING(config_json, json_obj, "countdown", clock_buf->web_sys_config.config_value);
    }while(0);
}

/**
 * @brief 解析口语练习数据
 *
 * @param json_obj
 * @param clock_buf
 */
static void web_english_oral_practice_json_parse(cJSON* json_obj, WEBSOCKET_RECEIVED_DATA* clock_buf)
{
    cJSON* oral_pratice_json = NULL;
    cJSON* preferred_responses_for_next_round = NULL;
    cJSON* round = NULL;
    do{
        GET_VALUESTRING(oral_pratice_json, json_obj, "english_response", clock_buf->web_oral_pratice.english_response);
        GET_VALUESTRING(oral_pratice_json, json_obj, "query_translation", clock_buf->web_oral_pratice.query_translation);
        GET_VALUESTRING(oral_pratice_json, json_obj, "response_translation", clock_buf->web_oral_pratice.response_translation);
        GET_VALUESTRING(oral_pratice_json, json_obj, "tts_audio", clock_buf->web_oral_pratice.oral_pratice_tts_audio);

        preferred_responses_for_next_round = cJSON_GetObjectItem(json_obj, "preferred_responses_for_next_round");
        round = cJSON_GetArrayItem(preferred_responses_for_next_round, 0);
        clock_buf->web_oral_pratice.preferred_responses_for_next_round[0] = (char*)audio_calloc(1, strlen(round->valuestring) + 1);
        strcpy(clock_buf->web_oral_pratice.preferred_responses_for_next_round[0], round->valuestring);

        round = cJSON_GetArrayItem(preferred_responses_for_next_round, 1);
        clock_buf->web_oral_pratice.preferred_responses_for_next_round[1] = (char*)audio_calloc(1, strlen(round->valuestring) + 1);
        strcpy(clock_buf->web_oral_pratice.preferred_responses_for_next_round[1], round->valuestring);

        round = cJSON_GetArrayItem(preferred_responses_for_next_round, 2);
        clock_buf->web_oral_pratice.preferred_responses_for_next_round[2] = (char*)audio_calloc(1, strlen(round->valuestring) + 1);
        strcpy(clock_buf->web_oral_pratice.preferred_responses_for_next_round[2], round->valuestring);
    }while(0);

}


/**
 * @brief 解析创建房间数据
 *
 * @param json_obj
 * @param clock_buf
 */
void web_create_session_json_parse(cJSON* json_obj, WEBSOCKET_RECEIVED_DATA* clock_buf)
{
    cJSON* interface_call_json = NULL;
    do{
         GET_VALUESTRING(interface_call_json, json_obj, "session_token", clock_buf->session_token);
    }while(0);

}

#if 0
int websocket_json_parse(char *jbuf, WEBSOCKET_RECEIVED_DATA* clock_buf)
{
    // 解析 JSON 响应

    cJSON *json = cJSON_Parse(jbuf);
    if (json == NULL) {
        // GT_LOGE(TAG, "Failed to parse JSON");
        return -1;  // 返回失败
    }
    cJSON *user_input = NULL;//解析json数据,获取回复用户的文字内容
    cJSON *socket_type = NULL;//解析json数据，获取情绪值
    cJSON *socket_data = cJSON_GetObjectItem(json, "socket_data");//解析json数据，获取音频链接
    cJSON *data_name = NULL;
    cJSON *data_value = NULL, *agent_type = NULL, *agent_output = NULL;

    do{
        GET_VALUESTRING(socket_type, json, "socket_type", clock_buf->socket_type);
    }while(0);

    if(strcmp(socket_type->valuestring, "data_response") == 0)///数据回复
    {
        cJSON* data_response_json = NULL;
        do{
            GET_VALUESTRING(data_response_json, socket_data, "data_name", clock_buf->data_name);
        }while(0);
        if(strcmp(clock_buf->data_name, "clock_weather") == 0)
        {
            int weather_arry_item = 0, weather_days = 0;
            cJSON* weather = NULL;
            cJSON* weather_data = NULL;
            cJSON* weathers = NULL;
            cJSON* weather_arry = NULL;
            do{
                if(weather_days == 0)
                {
                    data_value = cJSON_GetObjectItem(socket_data, "data_value");
                    GET_VALUEINT(data_response_json, data_value, "time_stamp", clock_buf->clock_weather.time_stamp);
                    weather = cJSON_GetObjectItem(data_value, "weather");
                    GET_VALUESTRING(data_response_json, weather, "ip_address", clock_buf->clock_weather.ip_address);
                    weather_data = cJSON_GetObjectItem(weather, "weather_data");
                    weathers = cJSON_GetObjectItem(weather_data, "weathers");
                }
                weather_arry = cJSON_GetArrayItem(weathers, weather_arry_item);
                if(weather_arry != NULL)
                {
                    GET_VALUESTRING(data_response_json, weather_arry, "valid", clock_buf->clock_weather.weather_data[weather_days].valid);
                    GET_VALUESTRING(data_response_json, weather_arry, "cap", clock_buf->clock_weather.weather_data[weather_days].cap);
                    GET_VALUESTRING(data_response_json, weather_arry, "cap_type", clock_buf->clock_weather.weather_data[weather_days].cap_type);
                    GET_VALUEDOUBLE(data_response_json, weather_arry, "precip", clock_buf->clock_weather.weather_data[weather_days].precip);
                    GET_VALUEDOUBLE(data_response_json, weather_arry, "windMax", clock_buf->clock_weather.weather_data[weather_days].windMax);
                    GET_VALUEDOUBLE(data_response_json, weather_arry, "windMaxDir", clock_buf->clock_weather.weather_data[weather_days].windMaxDir);
                    GET_VALUEDOUBLE(data_response_json, weather_arry, "rhHi", clock_buf->clock_weather.weather_data[weather_days].rhHi);
                    GET_VALUEDOUBLE(data_response_json, weather_arry, "tempHi", clock_buf->clock_weather.weather_data[weather_days].tempHi);
                    GET_VALUEDOUBLE(data_response_json, weather_arry, "tempLo", clock_buf->clock_weather.weather_data[weather_days].tempLo);
                    weather_arry_item++;
                }
                weather_days++;
            }while(weather_arry_item < WEATHER_DATA_RESPONSE_DAYS);
        }
        if(strcmp(clock_buf->data_name, "calendar") == 0)
        {
            data_value = cJSON_GetObjectItem(socket_data, "data_value");
            // GET_VALUESTRING(data_response_json, data_value, "time_stamp", clock_buf->clock_weather.time_stamp);
        }
    }
    else if(strcmp(socket_type->valuestring, "agent_response") == 0) //机器人回复
    {
        do{
            GET_VALUESTRING(agent_type, json, "agent_type", clock_buf->agent_type);
        }while(0);
        agent_output = cJSON_GetObjectItem(json, "agent_output");
        if(strcmp(agent_type->valuestring, "text") == 0)
        {
            web_bot_recover_json_parse(agent_output, clock_buf);
        }
        else if(strcmp(agent_type->valuestring, "set_alarm") == 0)
        {
            web_set_alarm_data_json_parse(agent_output, clock_buf);
        }
        else if(strcmp(agent_type->valuestring, "check_weather") == 0)
        {
            web_check_weather_json_parse(agent_output, clock_buf);
        }
        else if(strcmp(agent_type->valuestring, "set_countdown") == 0)
        {
            web_set_countdown_json_parse(agent_output, clock_buf);
        }
        else if(strcmp(agent_type->valuestring, "modify_device_config") == 0)
        {
            web_device_config_json_parse(agent_output, clock_buf);
        }
        else if(strcmp(agent_type->valuestring, "english_oral_practice") == 0)
        {
            web_english_oral_practice_json_parse(agent_output, clock_buf);
        }
    }
    else if(strcmp(socket_type->valuestring, "response_event") == 0) //请求回复
    {

    }

    cJSON_Delete(json);
    return 0;  // -1:解析失败 0:解析成功

}

#elif 0
int websocket_json_parse(char *jbuf, WEBSOCKET_RECEIVED_DATA* clock_buf)
{
    // 解析 JSON 响应
    printf("jbuf = %s\r\n", jbuf);
    ESP_LOGI(TAG, "jbuf = %s", jbuf);

    cJSON *json = cJSON_Parse(jbuf);
    if (json == NULL) {
        ESP_LOGE(TAG, "Failed to parse JSON");
        return -1;  // 返回失败
    }
    else
    {
        ESP_LOGI(TAG, "Successfull to parse JSON");
    }
    cJSON *user_input = NULL;//解析json数据,获取回复用户的文字内容
    cJSON *socket_type = NULL;//解析json数据，获取情绪值

    cJSON *data_name = NULL;
    cJSON *data_value = NULL, *agent_type = NULL, *agent_output = NULL;
    cJSON *socket_data = cJSON_GetObjectItem(json, "socket_data");//解析json数据，获取音频链接
    agent_output = cJSON_GetObjectItem(json, "agent_output");
    if(socket_data == NULL && agent_output == NULL)
    {
        ESP_LOGE(TAG, "Failed to parse socket_data or agent_output");
        return -1;
    }
    do{
        GET_VALUESTRING(socket_type, json, "socket_type", clock_buf->socket_type);
    }while(0);

    if(strcmp(socket_type->valuestring, "data_response") == 0)///数据回复
    {
        cJSON* data_response_json = NULL;
        do{
            GET_VALUESTRING(data_response_json, socket_data, "data_name", clock_buf->data_name);
        }while(0);
        if(strcmp(clock_buf->data_name, "clock_weather") == 0)
        {
            int weather_arry_item = 0, weather_days = 0;
            cJSON* weather = NULL;
            cJSON* weather_data = NULL;
            cJSON* weathers = NULL;
            cJSON* weather_arry = NULL;
            do{
                if(weather_days == 0)
                {
                    data_value = cJSON_GetObjectItem(socket_data, "data_value");
                    GET_VALUEINT(data_response_json, data_value, "time_stamp", clock_buf->time_stamp);
                    weather = cJSON_GetObjectItem(data_value, "weather");
                    weather_data = cJSON_GetObjectItem(weather, "weather_data");
                    GET_VALUESTRING(data_response_json, weather_data, "address", clock_buf->weather_data[weather_days].address);
                    weathers = cJSON_GetObjectItem(weather_data, "weathers");
                }
                if(weather_days > 0)
                {
                    weather_arry = cJSON_GetArrayItem(weathers, weather_arry_item);
                    if(weather_arry != NULL)
                    {
                        GET_VALUESTRING(data_response_json, weather_arry, "valid", clock_buf->weather_data[weather_days].valid);
                        GET_VALUESTRING(data_response_json, weather_arry, "cap", clock_buf->weather_data[weather_days].cap);
                        GET_VALUESTRING(data_response_json, weather_arry, "cap_type", clock_buf->weather_data[weather_days].cap_type);
                        GET_VALUEDOUBLE(data_response_json, weather_arry, "precip", clock_buf->weather_data[weather_days].precip);
                        GET_VALUEDOUBLE(data_response_json, weather_arry, "windMax", clock_buf->weather_data[weather_days].windMax);
                        GET_VALUEDOUBLE(data_response_json, weather_arry, "windMaxDir", clock_buf->weather_data[weather_days].windMaxDir);
                        GET_VALUEDOUBLE(data_response_json, weather_arry, "rhHi", clock_buf->weather_data[weather_days].rhHi);
                        GET_VALUEDOUBLE(data_response_json, weather_arry, "tempHi", clock_buf->weather_data[weather_days].tempHi);
                        GET_VALUEDOUBLE(data_response_json, weather_arry, "tempLo", clock_buf->weather_data[weather_days].tempLo);
                        weather_arry_item++;
                    }
                }
                weather_days++;
            }while(weather_days < WEATHER_DATA_RESPONSE_DAYS);
        }
        if(strcmp(clock_buf->data_name, "calendar") == 0)
        {
            data_value = cJSON_GetObjectItem(socket_data, "data_value");
            // GET_VALUESTRING(data_response_json, data_value, "time_stamp", clock_buf->clock_weather.time_stamp);
        }
    }
    else if(strcmp(socket_type->valuestring, "agent_response") == 0) //机器人回复
    {
        printf("clock_buf->socket_type = %s\r\n", clock_buf->socket_type);
        cJSON* recover_json = NULL;
        do{
            GET_VALUESTRING(recover_json, agent_output, "llm_response", clock_buf->recover_data.llm_response);
            GET_VALUESTRING(recover_json, agent_output, "tts_audio", clock_buf->recover_data.tts_audio);
            // GET_VALUESTRING(recover_json, agent_output, "user_input", clock_buf->user_input);
            // GET_VALUEDOUBLE(recover_json, agent_output, "audio_seconds", clock_buf->recover_data.audio_seconds);
        }while(0);
        do{
            GET_VALUESTRING(agent_type, json, "agent_type", clock_buf->agent_type);
        }while(0);
        agent_output = cJSON_GetObjectItem(json, "agent_output");
        if(strcmp(agent_type->valuestring, "text") == 0)
        {
            cJSON* recover_json = NULL;
            do{
                GET_VALUESTRING(recover_json, agent_output, "llm_response", clock_buf->recover_data.llm_response);
                GET_VALUESTRING(recover_json, agent_output, "tts_audio", clock_buf->recover_data.tts_audio);
                GET_VALUESTRING(recover_json, agent_output, "user_input", clock_buf->user_input);
                // GET_VALUEDOUBLE(recover_json, agent_output, "audio_seconds", clock_buf->recover_data.audio_seconds);
            }while(0);
        }
        else if(strcmp(agent_type->valuestring, "set_alarm") == 0)
        {
            cJSON* clock_json = NULL;
            do{
                GET_VALUESTRING(clock_json, agent_output, "instruct_type", clock_buf->clock_data.instruct_type);
                if(strcmp(clock_buf->clock_data.instruct_type, "create_alarm") == 0)
                {
                    GET_VALUESTRING(clock_json, agent_output, "alarm_date", clock_buf->clock_data.alarm_date);
                    GET_VALUESTRING(clock_json, agent_output, "alarm_time", clock_buf->clock_data.alarm_time);
                    GET_VALUESTRING(clock_json, agent_output, "period", clock_buf->clock_data.period);
                    GET_VALUESTRING(clock_json, agent_output, "alarm_purpose", clock_buf->clock_data.alarm_purpose);
                    GET_VALUESTRING(clock_json, agent_output, "alarm_repeat", clock_buf->clock_data.alarm_repeat);
                }
                else if(strcmp(clock_buf->clock_data.instruct_type, "check_alarm") == 0)
                {
                    GET_VALUESTRING(clock_json, agent_output, "alarm_date", clock_buf->clock_data.alarm_date);
                }
                else if(strcmp(clock_buf->clock_data.instruct_type, "edit_alarm") == 0)
                {
                    GET_VALUESTRING(clock_json, agent_output, "alarm_date", clock_buf->clock_data.alarm_date);
                    GET_VALUESTRING(clock_json, agent_output, "alarm_time", clock_buf->clock_data.alarm_time);
                    GET_VALUESTRING(clock_json, agent_output, "period", clock_buf->clock_data.period);
                    GET_VALUESTRING(clock_json, agent_output, "new_alarm_time", clock_buf->clock_data.new_alarm_time);
                    GET_VALUESTRING(clock_json, agent_output, "new_period", clock_buf->clock_data.new_period);
                }
                else if(strcmp(clock_buf->clock_data.instruct_type, "delete_alarm") == 0)
                {
                    GET_VALUESTRING(clock_json, agent_output, "alarm_date", clock_buf->clock_data.alarm_date);
                    GET_VALUESTRING(clock_json, agent_output, "alarm_time", clock_buf->clock_data.alarm_time);
                    GET_VALUESTRING(clock_json, agent_output, "period", clock_buf->clock_data.period);
                }
            }while(0);
        }
        else if(strcmp(agent_type->valuestring, "check_weather") == 0)
        {
            int days =  0, array_item = 0;
            cJSON* weathers = NULL;
            cJSON* weathers_json = NULL, *future_w = NULL;
            cJSON* reveal_data = NULL;
            do{
                if(days == 0)
                {
                    GET_VALUESTRING(weathers_json, agent_output, "address", clock_buf->weather_data[days].address);
                    GET_VALUESTRING(weathers_json, agent_output, "tts_audio", clock_buf->weather_tts_audio);
                    reveal_data = cJSON_GetObjectItem(agent_output, "reveal_data");
                    if(reveal_data == NULL)
                    {break;}

                    GET_VALUESTRING(weathers_json, reveal_data, "valid", clock_buf->weather_data[days].valid);
                    GET_VALUESTRING(weathers_json, reveal_data, "cap", clock_buf->weather_data[days].cap);
                    GET_VALUESTRING(weathers_json, reveal_data, "cap_type", clock_buf->weather_data[days].cap_type);
                    GET_VALUEDOUBLE(weathers_json, reveal_data, "precip", clock_buf->weather_data[days].precip);
                    GET_VALUEDOUBLE(weathers_json, reveal_data, "windMax", clock_buf->weather_data[days].windMax);
                    GET_VALUEDOUBLE(weathers_json, reveal_data, "windMaxDir", clock_buf->weather_data[days].windMaxDir);
                    GET_VALUEDOUBLE(weathers_json, reveal_data, "rhHi", clock_buf->weather_data[days].rhHi);
                    GET_VALUEDOUBLE(weathers_json, reveal_data, "tempHi", clock_buf->weather_data[days].tempHi);
                    GET_VALUEDOUBLE(weathers_json, reveal_data, "tempLo", clock_buf->weather_data[days].tempLo);
                    weathers = cJSON_GetObjectItem(agent_output, "weathers");
                }
                else if(days > 0)
                {
                    if(weathers != NULL)
                    {
                        future_w = cJSON_GetArrayItem(weathers, array_item);
                        if(future_w != NULL)
                        {
                            GET_VALUESTRING(weathers_json, reveal_data, "valid", clock_buf->weather_data[days].valid)
                            GET_VALUESTRING(weathers_json, reveal_data, "cap", clock_buf->weather_data[days].cap);
                            GET_VALUESTRING(weathers_json, reveal_data, "cap_type", clock_buf->weather_data[days].cap_type);
                            GET_VALUEDOUBLE(weathers_json, reveal_data, "precip", clock_buf->weather_data[days].precip);
                            GET_VALUEDOUBLE(weathers_json, reveal_data, "windMax", clock_buf->weather_data[days].windMax);
                            GET_VALUEDOUBLE(weathers_json, reveal_data, "windMaxDir", clock_buf->weather_data[days].windMaxDir);
                            GET_VALUEDOUBLE(weathers_json, reveal_data, "rhHi", clock_buf->weather_data[days].rhHi);
                            GET_VALUEDOUBLE(weathers_json, reveal_data, "tempHi", clock_buf->weather_data[days].tempHi);
                            GET_VALUEDOUBLE(weathers_json, reveal_data, "tempLo", clock_buf->weather_data[days].tempLo);
                        }
                        array_item++;
                    }
                }
                days++;
            }while(days < WEATHER_DAYS);
        }
        else if(strcmp(agent_type->valuestring, "set_countdown") == 0)
        {
            do{
                cJSON* countdown_json = NULL;
                GET_VALUESTRING(countdown_json, agent_output, "countdown", clock_buf->countdown);
            }while(0);
        }
        else if(strcmp(agent_type->valuestring, "modify_device_config") == 0)
        {
            cJSON* config_json = NULL;
            do{
                GET_VALUESTRING(config_json, agent_output, "config_name", clock_buf->web_sys_config.config_name);
                GET_VALUESTRING(config_json, agent_output, "countdown", clock_buf->web_sys_config.config_value);

            }while(0);
        }
        else if(strcmp(agent_type->valuestring, "english_oral_practice") == 0)
        {
            cJSON* oral_pratice_json = NULL;
            cJSON* preferred_responses_for_next_round = NULL;
            cJSON* round = NULL;
            do{
                GET_VALUESTRING(oral_pratice_json, agent_output, "english_response", clock_buf->web_oral_pratice.english_response);
                GET_VALUESTRING(oral_pratice_json, agent_output, "query_translation", clock_buf->web_oral_pratice.query_translation);
                GET_VALUESTRING(oral_pratice_json, agent_output, "response_translation", clock_buf->web_oral_pratice.response_translation);
                GET_VALUESTRING(oral_pratice_json, agent_output, "tts_audio", clock_buf->web_oral_pratice.oral_pratice_tts_audio);

                preferred_responses_for_next_round = cJSON_GetObjectItem(agent_output, "preferred_responses_for_next_round");
                round = cJSON_GetArrayItem(preferred_responses_for_next_round, 0);
                clock_buf->web_oral_pratice.preferred_responses_for_next_round[0] = (char*)audio_calloc(1, strlen(round->valuestring) + 1);
                strcpy(clock_buf->web_oral_pratice.preferred_responses_for_next_round[0], round->valuestring);

                round = cJSON_GetArrayItem(preferred_responses_for_next_round, 1);
                clock_buf->web_oral_pratice.preferred_responses_for_next_round[1] = (char*)audio_calloc(1, strlen(round->valuestring) + 1);
                strcpy(clock_buf->web_oral_pratice.preferred_responses_for_next_round[1], round->valuestring);

                round = cJSON_GetArrayItem(preferred_responses_for_next_round, 2);
                clock_buf->web_oral_pratice.preferred_responses_for_next_round[2] = (char*)audio_calloc(1, strlen(round->valuestring) + 1);
                strcpy(clock_buf->web_oral_pratice.preferred_responses_for_next_round[2], round->valuestring);
            }while(0);
        }
    }
    else if(strcmp(socket_type->valuestring, "interface_call") == 0)
    {
        cJSON* interface_call_json = NULL;
        do{
            GET_VALUESTRING(interface_call_json, socket_data, "interface_name", clock_buf->interface_name);
            if(strcmp(clock_buf->interface_name, "create_session") == 0)
            {
                do{
                    GET_VALUESTRING(interface_call_json, socket_data, "session_token", clock_buf->session_token);
                    ESP_LOGE(TAG, "clock_buf->session_token = %s",clock_buf->session_token);
                           ESP_LOGE(TAG, "333333333333333333333");

                }while(0);
            }
            else if(strcmp(clock_buf->interface_name, "session_check") == 0)
            {
                do{
                    GET_VALUEINT(interface_call_json, socket_data, "check_status", clock_buf->check_status);
                    // GET_VALUESTRING(interface_call_json, socket_data, "session_token", clock_buf->session_token_check);
                    ESP_LOGE(TAG, "clock_buf->check_status = %d", clock_buf->check_status);
                }while(0);
            }
        }while(0);
    }
    else if(strcmp(socket_type->valuestring, "response_event") == 0) //请求回复
    {

    }

    cJSON_Delete(json);
    return 0;  // -1:解析失败 0:解析成功

}

#else
int websocket_parse_socket_message(char *jbuf)
{
    cJSON *json = cJSON_Parse(jbuf);
    if (json == NULL) {
        ESP_LOGE(TAG, "Failed to parse JSON");
        return -1;  // 返回失败
    }
    else
    {
        ESP_LOGI(TAG, "Successfull to parse JSON");
    }
    cJSON *socket_message = NULL;
    socket_message = cJSON_GetObjectItem(json, "socket_message");
    if(socket_message != NULL)
    {
        if(strcmp(socket_message->valuestring, "connection_established") == 0)
        {
            return ESP_OK;
        }
    }
    return ESP_FAIL;
}

int websocket_chatbot_json_parse(char *jbuf, ReceivedAnswerData* receive_buf)
{
    // 解析 JSON 响应
    ESP_LOGI(TAG, "jbuf = %s", jbuf);
    cJSON *json = cJSON_Parse(jbuf);
    if (json == NULL) {
        ESP_LOGE(TAG, "Failed to parse JSON");
        return -1;  // 返回失败
    }
    else
    {
        ESP_LOGI(TAG, "Successfull to parse JSON");
    }
    cJSON *socket_type = NULL;
    cJSON *agent_output = NULL, *socket_data = NULL, *event_name = NULL;
    agent_output = cJSON_GetObjectItem(json, "agent_output");
    if(agent_output == NULL)
    {
        ESP_LOGE(TAG, "Failed to parse socket_data or agent_output");
        return -1;
    }
    do{
        GET_VALUESTRING(socket_type, json, "socket_type", receive_buf->socket_type);
    }while(0);

    if(strcmp(socket_type->valuestring, "agent_event") == 0) //机器人回复
    {
        printf("clock_buf->socket_type = %s\r\n", receive_buf->socket_type);
        cJSON* recover_json = NULL;
        do{
            GET_VALUESTRING(recover_json, agent_output, "llm_response", receive_buf->llm_response);
            GET_VALUESTRING(recover_json, agent_output, "tts_audio", receive_buf->tts_audio);
            GET_VALUEDOUBLE(recover_json, agent_output, "to_sleep", receive_buf->audio_seconds);
            GET_VALUESTRING(recover_json, agent_output, "emotion_value", receive_buf->emotion_value);
            // GET_VALUESTRING(recover_json, agent_output, "user_input", clock_buf->user_input);

        }while(0);
    }

    cJSON_Delete(json);
    return 0;  // -1:解析失败 0:解析成功

}
#endif
    // if(strcmp(agent_type->valuestring, "text") == 0)
    // {
    //     cJSON* recover_json = NULL;
    //     do{
    //         GET_VALUESTRING(recover_json, agent_output, "llm_response", clock_buf->recover_data.llm_response);
    //         GET_VALUESTRING(recover_json, agent_output, "tts_audio", clock_buf->recover_data.tts_audio);
    //         // GET_VALUESTRING(recover_json, json, "user_input", clock_buf->recover_data.user_input);
    //         // GET_VALUEDOUBLE(recover_json, agent_output, "audio_seconds", clock_buf->recover_data.audio_seconds);
    //     }while(0);
    // }
    // else if(strcmp(agent_type->valuestring, "set_alarm") == 0)
    // {
    //     cJSON* clock_json = NULL;
    //     do{
    //         GET_VALUESTRING(clock_json, agent_output, "instruct_type", clock_buf->clock_data.instruct_type);
    //         if(strcmp(clock_buf->clock_data.instruct_type, "create_alarm") == 0)
    //         {
    //             GET_VALUESTRING(clock_json, agent_output, "alarm_date", clock_buf->clock_data.alarm_date);
    //             GET_VALUESTRING(clock_json, agent_output, "alarm_time", clock_buf->clock_data.alarm_time);
    //             GET_VALUESTRING(clock_json, agent_output, "period", clock_buf->clock_data.period);
    //             GET_VALUESTRING(clock_json, agent_output, "alarm_purpose", clock_buf->clock_data.alarm_purpose);
    //             GET_VALUESTRING(clock_json, agent_output, "alarm_repeat", clock_buf->clock_data.alarm_repeat);
    //         }
    //         else if(strcmp(clock_buf->clock_data.instruct_type, "check_alarm") == 0)
    //         {
    //             GET_VALUESTRING(clock_json, agent_output, "alarm_date", clock_buf->clock_data.alarm_date);
    //         }
    //         else if(strcmp(clock_buf->clock_data.instruct_type, "edit_alarm") == 0)
    //         {
    //             GET_VALUESTRING(clock_json, agent_output, "alarm_date", clock_buf->clock_data.alarm_date);
    //             GET_VALUESTRING(clock_json, agent_output, "alarm_time", clock_buf->clock_data.alarm_time);
    //             GET_VALUESTRING(clock_json, agent_output, "period", clock_buf->clock_data.period);
    //             GET_VALUESTRING(clock_json, agent_output, "new_alarm_time", clock_buf->clock_data.new_alarm_time);
    //             GET_VALUESTRING(clock_json, agent_output, "new_period", clock_buf->clock_data.new_period);
    //         }
    //         else if(strcmp(clock_buf->clock_data.instruct_type, "delete_alarm") == 0)
    //         {
    //             GET_VALUESTRING(clock_json, agent_output, "alarm_date", clock_buf->clock_data.alarm_date);
    //             GET_VALUESTRING(clock_json, agent_output, "alarm_time", clock_buf->clock_data.alarm_time);
    //             GET_VALUESTRING(clock_json, agent_output, "period", clock_buf->clock_data.period);
    //         }
    //     }while(0);
    // }
    // else if(strcmp(agent_type->valuestring, "check_weather") == 0)
    // {
    //     int days =  0, array_item = 0;
    //     cJSON* weathers = NULL;
    //     cJSON* weathers_json = NULL, *future_w = NULL;
    //     cJSON* reveal_data = NULL;
    //     do{
    //         if(days == 0)
    //         {
    //             GET_VALUESTRING(weathers_json, agent_output, "address", clock_buf->weather_data[days].address);
    //             reveal_data = cJSON_GetObjectItem(agent_output, "reveal_data");
    //             if(reveal_data == NULL)
    //             {break;}

    //             GET_VALUESTRING(weathers_json, reveal_data, "valid", clock_buf->weather_data[days].valid)
    //             GET_VALUESTRING(weathers_json, reveal_data, "cap", clock_buf->weather_data[days].cap);
    //             GET_VALUESTRING(weathers_json, reveal_data, "cap_type", clock_buf->weather_data[days].cap_type);
    //             GET_VALUEDOUBLE(weathers_json, reveal_data, "precip", clock_buf->weather_data[days].precip);
    //             GET_VALUEDOUBLE(weathers_json, reveal_data, "windMax", clock_buf->weather_data[days].windMax);
    //             GET_VALUEDOUBLE(weathers_json, reveal_data, "windMaxDir", clock_buf->weather_data[days].windMaxDir);
    //             GET_VALUEDOUBLE(weathers_json, reveal_data, "rhHi", clock_buf->weather_data[days].rhHi);
    //             GET_VALUEDOUBLE(weathers_json, reveal_data, "tempHi", clock_buf->weather_data[days].tempHi);
    //             GET_VALUEDOUBLE(weathers_json, reveal_data, "tempLo", clock_buf->weather_data[days].tempLo);
    //             weathers = cJSON_GetObjectItem(agent_output, "weathers");
    //         }
    //         else if(days > 0)
    //         {
    //             if(weathers != NULL)
    //             {
    //                 future_w = cJSON_GetArrayItem(weathers, array_item);
    //                 if(future_w != NULL)
    //                 {
    //                     GET_VALUESTRING(weathers_json, future_w, "valid", clock_buf->weather_data[days].valid);
    //                     GET_VALUESTRING(weathers_json, future_w, "cap", clock_buf->weather_data[days].cap);
    //                     GET_VALUESTRING(weathers_json, future_w, "cap_type", clock_buf->weather_data[days].cap_type);
    //                     GET_VALUEDOUBLE(weathers_json, future_w, "precip", clock_buf->weather_data[days].precip);
    //                     GET_VALUEDOUBLE(weathers_json, future_w, "windMax", clock_buf->weather_data[days].windMax);
    //                     GET_VALUEDOUBLE(weathers_json, future_w, "windMaxDir", clock_buf->weather_data[days].windMaxDir);
    //                     GET_VALUEDOUBLE(weathers_json, future_w, "rhHi", clock_buf->weather_data[days].rhHi);
    //                     GET_VALUEDOUBLE(weathers_json, future_w, "tempHi", clock_buf->weather_data[days].tempHi);
    //                     GET_VALUEDOUBLE(weathers_json, future_w, "tempLo", clock_buf->weather_data[days].tempLo);
    //                 }
    //                 array_item++;
    //             }
    //         }
    //         days++;
    //     }while(days < WEATHER_DAYS);
    // }
    // else if(strcmp(agent_type->valuestring, "set_countdown") == 0)
    // {
    //     do{
    //         cJSON* countdown_json = NULL;
    //         GET_VALUESTRING(countdown_json, agent_output, "countdown", clock_buf->countdown);
    //     }while(0);
    // }








// void app_main(void)
// {
//     ESP_LOGI(TAG, "[APP] Startup..");
//     ESP_LOGI(TAG, "[APP] Free memory: %" PRIu32 " bytes", esp_get_free_heap_size());
//     ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());
//     esp_log_level_set("*", ESP_LOG_INFO);
//     esp_log_level_set("websocket_client", ESP_LOG_DEBUG);
//     esp_log_level_set("transport_ws", ESP_LOG_DEBUG);
//     esp_log_level_set("trans_tcp", ESP_LOG_DEBUG);

//     ESP_ERROR_CHECK(nvs_flash_init());
//     ESP_ERROR_CHECK(esp_netif_init());
//     ESP_ERROR_CHECK(esp_event_loop_create_default());

//     /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
//      * Read "Establishing Wi-Fi or Ethernet Connection" section in
//      * examples/protocols/README.md for more information about this function.
//      */
//     ESP_ERROR_CHECK(example_connect());

//     websocket_app_start();
// }


void websocket_app_start(void)
{
    esp_websocket_client_config_t websocket_cfg = {};

    shutdown_signal_timer = xTimerCreate("Websocket shutdown timer", NO_DATA_TIMEOUT_SEC * 1000 / portTICK_PERIOD_MS,
                                         pdFALSE, NULL, shutdown_signaler);
    shutdown_sema = xSemaphoreCreateBinary();

// #if CONFIG_WEBSOCKET_URI_FROM_STDIN
//     char line[128];

//     ESP_LOGI(TAG, "Please enter uri of websocket endpoint");
//     get_string(line, sizeof(line));

//     websocket_cfg.uri = line;
//     ESP_LOGI(TAG, "Endpoint uri: %s\n", line);

// #else
    websocket_cfg.uri = "ws://api.mindcraft.com.cn/socket-v1/?EIO=4&transport=websocket"; //CONFIG_WEBSOCKET_URI;
    websocket_cfg.reconnect_timeout_ms = 10000;
    websocket_cfg.network_timeout_ms = 6000;
// #endif /* CONFIG_WEBSOCKET_URI_FROM_STDIN */

// #if CONFIG_WS_OVER_TLS_MUTUAL_AUTH
//     /* Configuring client certificates for mutual authentification */
//     extern const char cacert_start[] asm("_binary_ca_cert_pem_start"); // CA certificate
//     extern const char cert_start[] asm("_binary_client_cert_pem_start"); // Client certificate
//     extern const char cert_end[]   asm("_binary_client_cert_pem_end");
//     extern const char key_start[] asm("_binary_client_key_pem_start"); // Client private key
//     extern const char key_end[]   asm("_binary_client_key_pem_end");

//     websocket_cfg.cert_pem = cacert_start;
//     websocket_cfg.client_cert = cert_start;
//     websocket_cfg.client_cert_len = cert_end - cert_start;
//     websocket_cfg.client_key = key_start;
//     websocket_cfg.client_key_len = key_end - key_start;
// #elif CONFIG_WS_OVER_TLS_SERVER_AUTH
//     extern const char cacert_start[] asm("_binary_ca_certificate_public_domain_pem_start"); // CA cert of wss://echo.websocket.event, modify it if using another server
//     websocket_cfg.cert_pem = cacert_start;
// #endif

// #if CONFIG_WS_OVER_TLS_SKIP_COMMON_NAME_CHECK
//     websocket_cfg.skip_cert_common_name_check = true;
// #endif

    ESP_LOGI(TAG, "Connecting to %s...", websocket_cfg.uri);

    client = esp_websocket_client_init(&websocket_cfg);

    esp_websocket_register_events(client, WEBSOCKET_EVENT_ANY, websocket_event_handler, (void *)client);

    esp_websocket_client_start(client);
    xTimerStart(shutdown_signal_timer, portMAX_DELAY);


#if 1
    // char data[] = {"{\"event_name\":\"auth_token\",\"event_params\":{\"token\":\"MC-demo\"}}"};
    char data[] = {"{\"socket_type\":\"custom_event\",\"event_name\":\"auth_token\",\"event_params\":{\"token\":\"API keys\"}}"};\"}}"};//设置请求头的时候要加上API keys
    esp_websocket_client_send_text(client, data, strlen(data), portMAX_DELAY);

    char sendData[] = {"{\"socket_type\":\"custom_event\",\"event_name\":\"action_agent\",\"event_params\":{\"agent_name\":\"llm_socket\",\"model\":\"deepseek-chat\",\"asr_text\":\"给我讲一讲小红帽和大灰狼的故事吧\"}}"};
    esp_websocket_client_send_text(client, sendData, strlen(sendData), portMAX_DELAY);
    // esp_websocket_client_send_text_partial(client, data, sizeof(data), portMAX_DELAY);
#else
    char data[32];
    int i = 0;
    while (i < 5) {
        if (esp_websocket_client_is_connected(client)) {
            int len = sprintf(data, "hello %04d", i++);
            ESP_LOGI(TAG, "Sending %s", data);
            esp_websocket_client_send_text(client, data, len, portMAX_DELAY);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
#endif
    // ESP_LOGI(TAG, "Sending fragmented message");
    // vTaskDelay(1000 / portTICK_PERIOD_MS);
    // memset(data, 'a', sizeof(data));
    // esp_websocket_client_send_text_partial(client, data, sizeof(data), portMAX_DELAY);
    // memset(data, 'b', sizeof(data));
    // esp_websocket_client_send_cont_msg(client, data, sizeof(data), portMAX_DELAY);
    // esp_websocket_client_send_fin(client, portMAX_DELAY);

    xSemaphoreTake(shutdown_sema, portMAX_DELAY);
    ESP_LOGI(TAG, "Remaining stack for Tmr Svc: %d", uxTaskGetStackHighWaterMark(NULL));
    esp_websocket_client_close(client, portMAX_DELAY);
    ESP_LOGI(TAG, "Websocket Stopped");
    esp_websocket_client_destroy(client);
}