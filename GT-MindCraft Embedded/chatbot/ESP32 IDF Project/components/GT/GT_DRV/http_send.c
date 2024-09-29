#include "http_send.h"
#include "esp_heap_caps.h"
#include "gt_ui.h"
#include "audio_mem.h"

extern QueueHandle_t mYxQueue;
extern QueueHandle_t mYxQueue2;


#define MAX_HTTP_RECV_BUFFER 512
#define MAX_HTTP_OUTPUT_BUFFER 3000//2048
#define MULTIPART_DATA_SIZE 300//multipart_data
#define EXTRA_PARAM_SIZE 800//extra_param

static const char *TAG = "HTTP_CLIENT";

esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    static char *output_buffer;  // Buffer to store response of http request from event handler
    static int output_len;       // Stores number of bytes read
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            // Clean the buffer in case of a new request
            if (output_len == 0 && evt->user_data) {
                // we are just starting to copy the output data into the use
                memset(evt->user_data, 0, MAX_HTTP_OUTPUT_BUFFER);
            }

            if (!esp_http_client_is_chunked_response(evt->client)) {
                // If user_data buffer is configured, copy the response into the buffer
                int copy_len = 0;
                if (evt->user_data) {
                    // The last byte in evt->user_data is kept for the NULL character in case of out-of-bound access.
                    copy_len = MIN(evt->data_len, (MAX_HTTP_OUTPUT_BUFFER - output_len));
                    if (copy_len) {
                        memcpy(evt->user_data + output_len, evt->data, copy_len);
                    }
                } else {
                    int content_len = esp_http_client_get_content_length(evt->client);
                    if (output_buffer == NULL) {
                        // We initialize output_buffer with 0 because it is used by strlen() and similar functions therefore should be null terminated.
                        output_buffer = (char *) calloc(content_len + 1, sizeof(char));
                        output_len = 0;
                        if (output_buffer == NULL) {
                            ESP_LOGE(TAG, "Failed to allocate memory for output buffer");
                            return ESP_FAIL;
                        }
                    }
                    copy_len = MIN(evt->data_len, (content_len - output_len));
                    if (copy_len) {
                        memcpy(output_buffer + output_len, evt->data, copy_len);
                    }
                }
                output_len += copy_len;
            }

            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
            if (output_buffer != NULL) {
                // Response is accumulated in output_buffer. Uncomment the below line to print the accumulated response
                // ESP_LOG_BUFFER_HEX(TAG, output_buffer, output_len);
                free(output_buffer);
                output_buffer = NULL;
            }
            output_len = 0;
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            int mbedtls_err = 0;
            esp_err_t err = esp_tls_get_and_clear_last_error((esp_tls_error_handle_t)evt->data, &mbedtls_err, NULL);
            if (err != 0) {
                ESP_LOGI(TAG, "Last esp error code: 0x%x", err);
                ESP_LOGI(TAG, "Last mbedtls failure: 0x%x", mbedtls_err);
            }
            if (output_buffer != NULL) {
                free(output_buffer);
                output_buffer = NULL;
            }
            output_len = 0;
            break;
        case HTTP_EVENT_REDIRECT:
            ESP_LOGD(TAG, "HTTP_EVENT_REDIRECT");
            esp_http_client_set_header(evt->client, "From", "user@example.com");
            esp_http_client_set_header(evt->client, "Accept", "text/html");
            esp_http_client_set_redirection(evt->client);
            break;
    }
    return ESP_OK;
}

/**
 * @brief 在SD卡中读取WAV文件并将其数据存储在内存中
 *
 * @param file_path 要读取的WAV文件的路径
 * @param wav_data  用于存储读取的WAV数据
 * @param wav_size  用于存储WAV文件的大小（以字节为单位）
 *
 * @note 不再需要WAV数据时，需释放分配的内存（使用audio_free）。
 */
void read_wav_file_from_sd(const char * file_path, uint8_t ** wav_data, size_t * wav_size) {
    FIL file;
    FRESULT res;
    UINT bytes_read;
    // Open the WAV file
    res = f_open(&file, file_path, FA_READ);
    if (res != FR_OK) {
        ESP_LOGE(TAG, "Failed to open WAV file: %s", file_path);
        return;
    }
    // Get file size
    *wav_size = f_size(&file);
    // Allocate memory for WAV data
    *wav_data = (uint8_t *)audio_malloc(*wav_size);
    if (*wav_data == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for WAV data");
        f_close(&file);
        return;
    }
    // Read WAV data
    res = f_read(&file, *wav_data, *wav_size, &bytes_read);
    if (res != FR_OK || bytes_read != *wav_size) {
        ESP_LOGE(TAG, "Failed to read WAV file");
        audio_free(*wav_data);
        f_close(&file);
        return;
    }
    // Close the file
    f_close(&file);
    ESP_LOGI(TAG, "WAV file read successfully: %s", file_path);
}

esp_err_t http_rest_with_url(SendSettingsData* send_data, ReceivedAnswerData* receive_data)
{
    const char *post_data = "{\"field1\":\"value1\"}";
    const char *boundary = "----WebKitFormBoundary7MA4YWxkTrZu0gW";//分隔符
    int written_len = 0;
    char *wav_file_path = "0:rec.wav";
    uint8_t *wav_data = NULL;
    size_t wav_size = 0;
    if (receive_data == NULL) {
        ESP_LOGE(TAG, "Invalid receive_data pointer");
        return ESP_ERR_INVALID_ARG;
    }
    memset(receive_data, 0, sizeof(ReceivedAnswerData));

    char *local_response_buffer = (char *)audio_malloc(MAX_HTTP_OUTPUT_BUFFER + 1);
    memset(local_response_buffer, 0, MAX_HTTP_OUTPUT_BUFFER + 1);

    esp_http_client_config_t config = {
        .url = "http://grayapi.mindcraft.com.cn/v1/agent/chat_bot_v1/",
        .event_handler = _http_event_handler,
        .user_data = local_response_buffer,        // Pass address of local buffer to get response
        .disable_auto_redirect = true,
        .cert_pem = NULL,
        .timeout_ms = 15000, //超时时间
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);//初始化http客户端

    // POST请求
    // Read WAV file from SD card
    read_wav_file_from_sd(wav_file_path, &wav_data, &wav_size);
    ESP_LOGI(TAG, "--------------------wav_size: %d\r\n", wav_size);

    char *multipart_data = (char *)audio_malloc(MULTIPART_DATA_SIZE);
    memset(multipart_data, 0, MULTIPART_DATA_SIZE);
    snprintf(multipart_data, MULTIPART_DATA_SIZE,
        "--%s\r\n"
        "Content-Disposition: form-data; name=\"audio_file\"; filename=\"audiow.wav\"\r\n"
        "Content-Type: application/octet-stream\r\n\r\n",
        boundary);
    size_t multipart_data_len = strlen(multipart_data);

    //要发送给服务器的参数
    char *extra_param = (char *)audio_malloc(EXTRA_PARAM_SIZE);
    memset(extra_param, 0, EXTRA_PARAM_SIZE);
    snprintf(extra_param, EXTRA_PARAM_SIZE,
        "\r\n--%s\r\n"
        "Content-Disposition: form-data; name=\"emotion_output\"\r\n\r\n"
        "%s"
        "\r\n--%s\r\n"
        "Content-Disposition: form-data; name=\"voice_id\"\r\n\r\n"
        "%s"
        "\r\n--%s\r\n"
        "Content-Disposition: form-data; name=\"user_age\"\r\n\r\n"
        "%d"
        "\r\n--%s\r\n"
        "Content-Disposition: form-data; name=\"bot_name\"\r\n\r\n"
        "%s"
        "\r\n--%s\r\n"
        "Content-Disposition: form-data; name=\"bot_character\"\r\n\r\n"
        "%s"
        "\r\n--%s\r\n"
        "Content-Disposition: form-data; name=\"bot_personality\"\r\n\r\n"
        "%s"
        "\r\n--%s\r\n"
        "Content-Disposition: form-data; name=\"output_format\"\r\n\r\n"
        "%s"
        "\r\n--%s\r\n",
        boundary,send_data->emotion_output,boundary,send_data->voice_id,boundary,send_data->user_age,boundary,send_data->bot_name,
        boundary,send_data->bot_character,boundary,send_data->bot_personality,boundary,send_data->output_format, boundary);
    size_t extra_pram_len = strlen(extra_param);

    char content_type_header[100] = {0};
    snprintf(content_type_header, sizeof(content_type_header), "multipart/form-data; boundary=%s", boundary);
    esp_http_client_set_method(client, HTTP_METHOD_POST);//设置 HTTP 请求的方法
    esp_http_client_set_header(client, "Content-Type",content_type_header);//设置 HTTP 请求头
    esp_http_client_set_header(client, "Authorization", "API keys");//设置请求头的时候要加上API keys
    size_t end_boundary_len = strlen(boundary) + 6;
    size_t total_data_len =  wav_size + multipart_data_len + extra_pram_len + end_boundary_len;


    //打开客户端连接服务器
    esp_err_t err = esp_http_client_open(client, total_data_len);
    if(err == ESP_OK)
    {
        //发送音频文件名
        written_len = esp_http_client_write(client, multipart_data, multipart_data_len);

        //发送音频数据
        written_len = esp_http_client_write(client, (const char *) wav_data,  wav_size);
        audio_free(wav_data);
        wav_data = NULL;

        //发送用户设置的参数
        written_len = esp_http_client_write(client, extra_param, extra_pram_len);

        // 发送multipart/form-data结束部分
        char end_boundary[50] = {0};
        snprintf(end_boundary, sizeof(end_boundary), "\r\n--%s--\r\n", boundary);
        written_len = esp_http_client_write(client, end_boundary, strlen(end_boundary));

        int content_length = 0;
        content_length = esp_http_client_fetch_headers(client);//从服务器获取响应头部
        if(content_length < 0)
        {
            ESP_LOGE(TAG, "HTTP client fetch headers failed");
            err = ESP_FAIL;
            goto FREE_LABEL;
        }else{
            int data_read = esp_http_client_read_response(client, local_response_buffer, MAX_HTTP_OUTPUT_BUFFER);//读取服务器返回的 HTTP 响应主体内容
            ESP_LOGD(TAG, "FILEOK");
            if(data_read >= 0)
            {
                ESP_LOGI(TAG, "Received JSON response: %s", local_response_buffer);
                err = resolve_answer_json(local_response_buffer, receive_data);
            }else{
                ESP_LOGE(TAG, "Failed to read response");
                err = ESP_FAIL;
                goto FREE_LABEL;
            }
        }
    }
FREE_LABEL:
    audio_free(multipart_data);
    multipart_data = NULL;
    audio_free(extra_param);
    extra_param =NULL;
    audio_free(local_response_buffer);
    local_response_buffer = NULL;
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
    return err;
}

void http_test_task(void *pvParameters)
{
    ESP_LOGI(TAG, "-------------------------------------------http_test_task\n");

    ChatbotData* para = (ChatbotData*)pvParameters;

    int received_msg;

    while (1) {
        // 等待接收消息，如果队列中有消息，则接收并处理
        if (xQueueReceive(mYxQueue, &received_msg, portMAX_DELAY) == pdPASS) {
            ESP_LOGI(TAG, "1-------------------received_msg = %d\n", received_msg);
            if (1 == received_msg) {
                esp_err_t result =http_rest_with_url(para->settings, para->answer);
                ESP_LOGI(TAG,">>>>>result = %d\n", result);

                //发送http处理结果到gt_gui_task任务
                int msg = result;  // 发送result作为信号
                BaseType_t xHigherPriorityTaskWoken = pdFALSE;
                xQueueSendFromISR(mYxQueue2, &msg, &xHigherPriorityTaskWoken);

                ESP_LOGI(TAG, "Finish http example\n");
            }
        }
    }


#if !CONFIG_IDF_TARGET_LINUX
    vTaskDelete(NULL);
    vTaskDelay(1000);
#endif
}


esp_err_t resolve_answer_json(char *jbuf, ReceivedAnswerData* receive_buf) {
    // 判断接收服务器数据的结构体申请的堆空间是否为空
    if (receive_buf->asr_content != NULL) {
        audio_free(receive_buf->asr_content);
        receive_buf->asr_content = NULL;
    }
    if (receive_buf->llm_response != NULL) {
        audio_free(receive_buf->llm_response);
        receive_buf->llm_response = NULL;
    }
    if (receive_buf->emotion_value != NULL) {
        audio_free(receive_buf->emotion_value);
        receive_buf->emotion_value = NULL;
    }
    if (receive_buf->tts_audio != NULL) {
        audio_free(receive_buf->tts_audio);
        receive_buf->tts_audio = NULL;
    }

    // 解析 JSON 响应
    cJSON *json = cJSON_Parse(jbuf);
    if (json == NULL) {
        ESP_LOGE(TAG, "Failed to parse JSON");
        return ESP_FAIL;  // 返回失败
    }

    cJSON *data = cJSON_GetObjectItem(json, "data");
    if (data == NULL || !cJSON_IsObject(data)) {
        ESP_LOGE(TAG, "Invalid data format");
        cJSON_Delete(json);
        return ESP_FAIL;  // 返回失败
    }

    cJSON *asr_content = cJSON_GetObjectItem(data, "asr_content");//解析json数据，获取用户语音的文字内容
    cJSON *llm_response = cJSON_GetObjectItem(data, "llm_response");//解析json数据,获取回复用户的文字内容
    cJSON *emotion_value = cJSON_GetObjectItem(data, "emotion_value");//解析json数据，获取情绪值
    cJSON *tts_audio = cJSON_GetObjectItem(data, "tts_audio");//解析json数据，获取音频链接
    cJSON *audio_seconds = cJSON_GetObjectItem(data, "audio_seconds");//解析json数据，获取音频总时长

    if (asr_content == NULL || llm_response == NULL || tts_audio == NULL || emotion_value == NULL || audio_seconds == NULL) {
        ESP_LOGE(TAG, "Missing required JSON fields");
        cJSON_Delete(json);
        return ESP_FAIL;  // 返回失败
    }

    // 检查字段是否为空字符串
    if (asr_content->valuestring == NULL || llm_response->valuestring == NULL || emotion_value->valuestring == NULL || tts_audio->valuestring == NULL) {
        ESP_LOGE(TAG, "JSON fields are null");
        cJSON_Delete(json);
        return ESP_FAIL;  // 返回失败
    }

    receive_buf->asr_content = (char *)audio_malloc(strlen(asr_content->valuestring) + 1);
    if (receive_buf->asr_content == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for asr_content");
        cJSON_Delete(json);
        return ESP_FAIL;
    }
    strcpy(receive_buf->asr_content, asr_content->valuestring);

    receive_buf->llm_response = (char *)audio_malloc(strlen(llm_response->valuestring) + 1);
    if (receive_buf->llm_response == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for llm_response");
        cJSON_Delete(json);
        audio_free(receive_buf->asr_content);
        return ESP_FAIL;
    }
    strcpy(receive_buf->llm_response, llm_response->valuestring);

    receive_buf->emotion_value = (char *)audio_malloc(strlen(emotion_value->valuestring) + 1);
    if (receive_buf->emotion_value == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for emotion_value");
        cJSON_Delete(json);
        audio_free(receive_buf->asr_content);
        audio_free(receive_buf->llm_response);
        return ESP_FAIL;
    }
    strcpy(receive_buf->emotion_value, emotion_value->valuestring);

    receive_buf->tts_audio = (char *)audio_malloc(strlen(tts_audio->valuestring) + 1);
    if (receive_buf->tts_audio == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for tts_audio");
        cJSON_Delete(json);
        audio_free(receive_buf->asr_content);
        audio_free(receive_buf->llm_response);
        audio_free(receive_buf->emotion_value);
        return ESP_FAIL;
    }
    strcpy(receive_buf->tts_audio, tts_audio->valuestring);

    // 处理 audio_seconds，检查它是否为数字类型
    if (cJSON_IsNumber(audio_seconds)) {
        receive_buf->audio_seconds = (float)audio_seconds->valuedouble;
    } else {
        ESP_LOGE(TAG, "audio_seconds is not a number");
        receive_buf->audio_seconds = 0.0f;  // 设为默认值
    }

    ESP_LOGI(TAG, "------------------receive_buf->asr_content: %s\n", receive_buf->asr_content);
    ESP_LOGI(TAG, "------------------receive_buf->llm_response: %s\n", receive_buf->llm_response);
    ESP_LOGI(TAG, "------------------receive_buf->emotion_value: %s\n", receive_buf->emotion_value);
    ESP_LOGI(TAG, "------------------receive_buf->tts_audio: %s\n", receive_buf->tts_audio);
    ESP_LOGI(TAG, "------------------receive_buf->audio_seconds: %f\n", receive_buf->audio_seconds);

    cJSON_Delete(json);
    return ESP_OK;  // 返回成功
}

