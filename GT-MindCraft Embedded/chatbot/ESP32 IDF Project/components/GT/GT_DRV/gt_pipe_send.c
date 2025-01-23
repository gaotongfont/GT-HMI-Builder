#include "gt_pipe_send.h"
#include "periph_service.h"
#include "input_key_service.h"
#include "i2s_stream.h"
#include "audio_mem.h"
#include "wav_encoder.h"
#include "esp_http_client.h"
#include "audio_element.h"
#include "fatfs_stream.h"
#include "http_stream.h"
#include "audio_pipeline.h"
#include "esp_log.h"
#include "cJSON.h"


#define EXAMPLE_AUDIO_SAMPLE_RATE  (48000)
#define EXAMPLE_AUDIO_BITS         (16)
#define EXAMPLE_AUDIO_CHANNELS     (1)

#define DEMO_EXIT_BIT (BIT0)
static EventGroupHandle_t EXIT_FLAG;

static const char *TAG = "GT_PIPE_SEND";
static audio_pipeline_handle_t pipeline = NULL;
static audio_element_handle_t fs_reader = NULL;
static audio_element_handle_t http_stream = NULL;


#define EXTRA_PARAM_SIZE 900//extra_param
#define MAX_HTTP_OUTPUT_BUFFER 1024//2048

static const char *boundary = "----WebKitFormBoundary7MA4YWxkTrZu0gW";//分隔符

Pipe_ReceivedAnswerData * api_key_data = NULL;
static char* user_asr_uuid = NULL;
#if 0
esp_err_t _http_stream_event_handle(http_stream_event_msg_t *msg)
{
    esp_http_client_handle_t http = (esp_http_client_handle_t)msg->http_client;

    char len_buf[16];
    static int total_write = 0;

    if (msg->event_id == HTTP_STREAM_PRE_REQUEST) {
        // set header
        ESP_LOGI(TAG, "[ + ] HTTP client HTTP_STREAM_PRE_REQUEST, lenght=%d", msg->buffer_len);


        char content_type_header[100] = {0};
        size_t wav_size = 1;
        uint8_t wav_data = 8;
        snprintf(content_type_header, sizeof(content_type_header), "multipart/form-data; boundary=%s", boundary);
        esp_http_client_set_method(http, HTTP_METHOD_POST);//设置 HTTP 请求的方法
        // esp_http_client_set_header(http, "Content-Type",content_type_header);//设置 HTTP 请求头
        //esp_http_client_set_header(http, "Content-Type","text/html; charset=utf-8");//设置 HTTP 请求头
        esp_http_client_set_header(http, "Content-Type","multipart/form-data; charset=utf-8");
        esp_http_client_set_header(http, "Connection","keep-alive");//设置 HTTP 请求头
        esp_http_client_set_header(http, "Accept-Encoding","gzip, deflate");//设置 HTTP 请求头
        esp_http_client_set_header(http, "Accept","*/*");//设置 HTTP 请求头
        if(api_key_data->update_uuid == NULL)
        {
            ESP_LOGE(TAG, "update uuid NULL");
        }
        esp_http_client_set_header(http, "Authorization", api_key_data->update_uuid);//设置请求头的时候要加上API keys
        size_t end_boundary_len = strlen(boundary) + 6;


        esp_http_client_set_post_field(http, NULL, 0);
        esp_err_t err = esp_http_client_perform(http);
        if (err == ESP_OK) {
            int status_code = esp_http_client_get_status_code(http);
            // ESP_LOGI(TAG, "HTTP POST Status = %d, content_length = %d", status_code, esp_http_client_get_content_length(http));
            ESP_LOGE(TAG, "HTTP POST request ok: %s", esp_err_to_name(err));
        } else {
            ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
            err = ESP_FAIL;
        }


        total_write = 0;
        return ESP_OK;
    }

    if (msg->event_id == HTTP_STREAM_ON_REQUEST) {
        // write data
        esp_http_client_delete_header(http, "Transfer-Encoding");
        // esp_http_client_delete_header(http, "Content-Type");
        // esp_http_client_set_header(http, "Content-Type","text/html; charset=utf-8");//设置 HTTP 请求头
        esp_http_client_set_post_field(http, msg->buffer, msg->buffer_len);
        esp_err_t rret = esp_http_client_open(http, msg->buffer_len);
        if (esp_http_client_write(http, msg->buffer, msg->buffer_len) <= 0) {
            return ESP_FAIL;
        }
        esp_http_client_close(http);

        total_write += msg->buffer_len;
        printf("\033[A\33[2K\rTotal bytes written: %d\n", total_write);
        return msg->buffer_len;
    }

    if (msg->event_id == HTTP_STREAM_POST_REQUEST) {
        ESP_LOGI(TAG, "[ + ] HTTP client HTTP_STREAM_POST_REQUEST, write end chunked marker");
        // if (esp_http_client_write(http, "0\r\n\r\n", 5) <= 0) {
        //     return ESP_FAIL;
        // }
        return ESP_OK;
    }

    if (msg->event_id == HTTP_STREAM_FINISH_REQUEST) {
        ESP_LOGI(TAG, "[ + ] HTTP client HTTP_STREAM_FINISH_REQUEST");
        //esp_http_client_close(http);
        // char *buf = calloc(1, 64);
        // assert(buf);
        // int read_len = esp_http_client_read(http, buf, 64);
        // if (read_len <= 0) {
        //     free(buf);
        //     return ESP_FAIL;
        // }
        // buf[read_len] = 0;
        // ESP_LOGI(TAG, "Got HTTP Response = %s", (char *)buf);
        // free(buf);
        return ESP_OK;
    }
    return ESP_OK;
}


void gt_pipe_send_init(void)
{
    ESP_LOGI("gt_pipe_send", ">>>>>>>gt_pipe_send_init");
    // 创建并初始化音频管道
    audio_pipeline_cfg_t pipeline_cfg = DEFAULT_AUDIO_PIPELINE_CONFIG();
    pipeline = audio_pipeline_init(&pipeline_cfg);
    if (pipeline == NULL) {
        ESP_LOGE(TAG, "Failed to create audio pipeline");
        return;
    }

    http_stream_cfg_t http_cfg = HTTP_STREAM_CFG_DEFAULT();
    http_cfg.type = AUDIO_STREAM_WRITER;
    http_cfg.event_handle = _http_stream_event_handle;
    http_stream = http_stream_init(&http_cfg);

    printf("http_cfg.request_size ============ %d\n",http_cfg.request_size);

    //注：播放器和录音的数据格式要保持一致，都是48000,16
    i2s_stream_cfg_t i2s_cfg = I2S_STREAM_CFG_DEFAULT_WITH_PARA(CODEC_ADC_I2S_PORT, 48000, 16, AUDIO_STREAM_READER);
    i2s_cfg.type = AUDIO_STREAM_READER;
    i2s_cfg.out_rb_size = 64 * 1024;//16 * 1024; // Increase buffer to avoid missing data in bad network conditions
    fs_reader = i2s_stream_init(&i2s_cfg);


    // 注册流到音频管道
    audio_pipeline_register(pipeline, fs_reader, "file_reader");
    audio_pipeline_register(pipeline, http_stream, "http_writer");

    // 链接文件流和HTTP上传流
    const char *link_tag[2] = {"file_reader", "http_writer"};
    audio_pipeline_link(pipeline, &link_tag[0], 2);


    if(api_key_data == NULL)
    {
        api_key_data = (Pipe_ReceivedAnswerData *)audio_malloc(sizeof(Pipe_ReceivedAnswerData));
        assert(api_key_data);
        memset(api_key_data, 0, sizeof(Pipe_ReceivedAnswerData));
    }

}


void gt_pipe_send_start(void)
{
    // 开始播放和上传
    ESP_LOGE(TAG, "[ * ] [Rec] input key event, resuming pipeline ...");
    /*
        * There is no effect when follow APIs output warning message on the first time record
        */
    audio_pipeline_stop(pipeline);
    audio_pipeline_wait_for_stop(pipeline);
    audio_pipeline_reset_ringbuffer(pipeline);
    audio_pipeline_reset_elements(pipeline);
    audio_pipeline_terminate(pipeline);

    audio_element_set_uri(http_stream, "http://api.mindcraft.com.cn/v1/data/chunk_update_file/");
    audio_pipeline_run(pipeline);
}


void release_resources()
{
    // 等待上传完成
    audio_pipeline_wait_for_stop(pipeline);
    // 终止管道并释放资源
    audio_pipeline_terminate(pipeline);
    audio_pipeline_unregister(pipeline, fs_reader);
    audio_pipeline_unregister(pipeline, http_stream);
    audio_pipeline_deinit(pipeline);
}


void gt_pipe_send_stop()
{
    if(!pipeline) {
        ESP_LOGI(TAG, "No Stopping recording...");
        return ;
    }
    ESP_LOGI(TAG, "Stopping recording...");
    // 停止管道
    audio_pipeline_stop(pipeline);
    audio_pipeline_wait_for_stop(pipeline);
}


void set_ringbuf_done()
{
    if (fs_reader != NULL) {
        ESP_LOGI(TAG, "Valid audio element handle");
        audio_element_set_ringbuf_done(fs_reader);
        audio_element_set_ringbuf_done(http_stream);

    } else {
        ESP_LOGE(TAG, "Invalid audio element handle");// 处理空指针的情况
    }
}

char* get_uuid()
{
    if(api_key_data->update_uuid != NULL){
        return api_key_data->update_uuid;
    }
    else{
        return NULL;
    }
}
/**
 * @brief 解析get请求得到的json文件，获取api_key
 *
 * @param jbuf
 * @param receive_buf
 * @return esp_err_t
 */
static esp_err_t resolve_answer_json(char *jbuf, Pipe_ReceivedAnswerData* receive_buf)
{
    //判断接收服务器数据的结构体申请的堆空间是否为空
    if (receive_buf->update_uuid != NULL)
    {
        audio_free(receive_buf->update_uuid);
        receive_buf->update_uuid = NULL;
    }

    // Parse JSON response
    cJSON *data = NULL;
    cJSON *json = cJSON_Parse(jbuf);
    if (json == NULL) {
        ESP_LOGE(TAG, "Failed to parse JSON");
        return ESP_FAIL; // 返回失败
    }

    data = cJSON_GetObjectItem(json, "data");
    if (data == NULL || !cJSON_IsObject(data)) {
        ESP_LOGE(TAG, "Invalid data format");
        cJSON_Delete(json);
        return ESP_FAIL; // 返回失败
    }

    cJSON *update_uuid = cJSON_GetObjectItem(data, "update_uuid");//解析json数据，获取api_key

    if (update_uuid == NULL)
    {
        ESP_LOGE(TAG, "Missing required JSON fields");
        cJSON_Delete(json);
        return ESP_FAIL; // 返回失败
    }

    // 检查字段是否为空字符串
    if (update_uuid->valuestring == NULL)
    {
        ESP_LOGE(TAG, "JSON fields are null");
        cJSON_Delete(json);
        return ESP_FAIL; // 返回失败
    }

    receive_buf->update_uuid = (char *)audio_malloc(strlen(update_uuid->valuestring) + 1);
    if (receive_buf->update_uuid == NULL)
    {
        ESP_LOGE(TAG, "Failed to allocate memory for update_uuid");
        cJSON_Delete(json);
        return ESP_FAIL;
    }

    strcpy(receive_buf->update_uuid, update_uuid->valuestring);

    ESP_LOGI(TAG, "------------------receive_buf->update_uuid: %s\n", receive_buf->update_uuid);

    cJSON_Delete(json);
    return ESP_OK; // 返回成功
}




/**
 * @brief get请求，获取发送数据的api_key
 *
 */
void get_pipe_send_api_key(void)
{
    char *local_response_buffer = (char *)audio_malloc(MAX_HTTP_OUTPUT_BUFFER + 1);
    memset(local_response_buffer, 0, MAX_HTTP_OUTPUT_BUFFER + 1);
    esp_http_client_config_t config = {
        .url = "http://api.mindcraft.com.cn/v1/data/chunk_update_file/",
        .event_handler = NULL,
        .user_data = local_response_buffer,        // Pass address of local buffer to get response
        .disable_auto_redirect = true,
        .cert_pem = NULL,
        .timeout_ms = 15000, //超时时间
    };
    esp_http_client_handle_t get_api_key = esp_http_client_init(&config);//初始化http客户端

    char content_type_header[100] = {0};
    snprintf(content_type_header, sizeof(content_type_header), "multipart/form-data; boundary=%s", boundary);
    esp_http_client_set_method(get_api_key, HTTP_METHOD_GET);//设置 HTTP 请求的方法
    esp_http_client_set_header(get_api_key, "Content-Type",content_type_header);//设置 HTTP 请求头
    esp_http_client_set_header(get_api_key, "Authorization", "API keys");//设置请求头的时候要加上API keys
    size_t end_boundary_len = strlen(boundary) + 6;


    //打开客户端连接服务器
    esp_err_t err = esp_http_client_open(get_api_key, 0);
    if(err == ESP_OK)
    {
        int content_length = 0;
        content_length = esp_http_client_fetch_headers(get_api_key);//从服务器获取响应头部
        if(content_length < 0)
        {
            ESP_LOGE(TAG, "HTTP client fetch headers failed");
            err = ESP_FAIL;
            goto FREE_LABEL;
        }
        else
        {
            int data_read = esp_http_client_read_response(get_api_key, local_response_buffer, MAX_HTTP_OUTPUT_BUFFER);//读取服务器返回的 HTTP 响应主体内容
            ESP_LOGD(TAG, "FILEOK");
            if(data_read >= 0)
            {
                ESP_LOGI(TAG, "Received JSON response: %s", local_response_buffer);
                err = resolve_answer_json(local_response_buffer, api_key_data);
                printf("api_key_data: %s\r\n", api_key_data->update_uuid);
            }else{
                ESP_LOGE(TAG, "Failed to read response");
                err = ESP_FAIL;
                goto FREE_LABEL;
            }
        }
    }


FREE_LABEL:
    audio_free(local_response_buffer);
    local_response_buffer = NULL;
    esp_http_client_close(get_api_key);
    esp_http_client_cleanup(get_api_key);

    return ;
}

#else

esp_err_t _http_stream_event_handle(http_stream_event_msg_t *msg)
{
    esp_http_client_handle_t http = (esp_http_client_handle_t)msg->http_client;

    char len_buf[16];
    static int total_write = 0;
    unsigned char headerbuff[] = {
    'R', 'I', 'F', 'F', 0x24, 0x10, 0x00, 0x00, // RIFF chunk descriptor
    'W', 'A', 'V', 'E',                         // "WAVE" format
    'f', 'm', 't', ' ', 0x10, 0x00, 0x00, 0x00, // fmt chunk descriptor
    0x01, 0x00, 0x02, 0x00, 0x80, 0xbb, 0x00, 0x00, // Format info (PCM, stereo, sample rate)
    0x00, 0xee, 0x02, 0x00, 0x04, 0x00, 0x10, 0x00, // More format details
    'd', 'a', 't', 'a', 0x00, 0x10, 0x00, 0x00  // Data chunk descriptor
    };

    if (msg->event_id == HTTP_STREAM_PRE_REQUEST) {
        // set header
        ESP_LOGI(TAG, "[ + ] HTTP client HTTP_STREAM_PRE_REQUEST, lenght=%d", msg->buffer_len);


        char content_type_header[100] = {0};
        size_t wav_size = 1;
        uint8_t wav_data = 8;
        snprintf(content_type_header, sizeof(content_type_header), "multipart/form-data; boundary=%s", boundary);
        esp_http_client_set_method(http, HTTP_METHOD_POST);//设置 HTTP 请求的方法
        // esp_http_client_set_header(http, "Content-Type",content_type_header);//设置 HTTP 请求头
        //esp_http_client_set_header(http, "Content-Type","text/html; charset=utf-8");//设置 HTTP 请求头
        esp_http_client_set_header(http, "Content-Type","multipart/form-data; charset=utf-8");
        esp_http_client_set_header(http, "Connection","keep-alive");//设置 HTTP 请求头
        esp_http_client_set_header(http, "Accept-Encoding","gzip, deflate");//设置 HTTP 请求头
        esp_http_client_set_header(http, "Accept","*/*");//设置 HTTP 请求头
        if(user_asr_uuid == NULL)
        {
            ESP_LOGE(TAG, "update uuid NULL");
        }
        esp_http_client_set_header(http, "Authorization", user_asr_uuid);//设置请求头的时候要加上API keys
        size_t end_boundary_len = strlen(boundary) + 6;


        esp_http_client_set_post_field(http, NULL, 0);
        esp_err_t err = esp_http_client_perform(http);
        if (err == ESP_OK) {
            int status_code = esp_http_client_get_status_code(http);
            // ESP_LOGI(TAG, "HTTP POST Status = %d, content_length = %d", status_code, esp_http_client_get_content_length(http));
            ESP_LOGE(TAG, "HTTP POST request ok: %s", esp_err_to_name(err));
        } else {
            ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
            err = ESP_FAIL;
        }


        total_write = 0;
        return ESP_OK;
    }

    if (msg->event_id == HTTP_STREAM_ON_REQUEST) {
        // write data
        esp_http_client_delete_header(http, "Transfer-Encoding");
        // esp_http_client_delete_header(http, "Content-Type");
        // esp_http_client_set_header(http, "Content-Type","text/html; charset=utf-8");//设置 HTTP 请求头

#if 0
        char* allBuff = (char*)audio_malloc(sizeof(headerbuff)+msg->buffer_len);
        memset(allBuff, 0, sizeof(headerbuff)+msg->buffer_len);
        memcpy(allBuff, headerbuff, sizeof(headerbuff));
        memcpy(allBuff+sizeof(headerbuff),  msg->buffer, msg->buffer_len);
        // ESP_LOGE("allBuff =================================%s\n",(char*)allBuff);
        // esp_http_client_set_post_field(http, msg->buffer, msg->buffer_len);
        esp_http_client_set_post_field(http, allBuff, sizeof(headerbuff)+msg->buffer_len);
        esp_err_t rret = esp_http_client_open(http, sizeof(headerbuff)+msg->buffer_len);
        if (esp_http_client_write(http, allBuff,sizeof(headerbuff)+msg->buffer_len) <= 0) {
            return ESP_FAIL;
        }
        esp_http_client_close(http);

        total_write += sizeof(headerbuff)+msg->buffer_len+1;
        printf("\033[A\33[2K\rTotal bytes written: %d\n", total_write);
        audio_free(allBuff);
        return msg->buffer_len;

#elif 1
        esp_http_client_set_post_field(http, msg->buffer, msg->buffer_len);
        esp_err_t rret = esp_http_client_open(http, msg->buffer_len);
        if (esp_http_client_write(http, msg->buffer, msg->buffer_len) <= 0) {
            return ESP_FAIL;
        }
        esp_http_client_close(http);

        total_write += msg->buffer_len;
        printf("\033[A\33[2K\rTotal bytes written: %d\n", total_write);
        return msg->buffer_len;
#endif
    }

    if (msg->event_id == HTTP_STREAM_POST_REQUEST) {
        ESP_LOGI(TAG, "[ + ] HTTP client HTTP_STREAM_POST_REQUEST, write end chunked marker");
        // if (esp_http_client_write(http, "0\r\n\r\n", 5) <= 0) {
        //     return ESP_FAIL;
        // }
        return ESP_OK;
    }

    if (msg->event_id == HTTP_STREAM_FINISH_REQUEST) {
        ESP_LOGI(TAG, "[ + ] HTTP client HTTP_STREAM_FINISH_REQUEST");
        //esp_http_client_close(http);
        // char *buf = calloc(1, 64);
        // assert(buf);
        // int read_len = esp_http_client_read(http, buf, 64);
        // if (read_len <= 0) {
        //     free(buf);
        //     return ESP_FAIL;
        // }
        // buf[read_len] = 0;
        // ESP_LOGI(TAG, "Got HTTP Response = %s", (char *)buf);
        // free(buf);
        return ESP_OK;
    }
    return ESP_OK;
}


void gt_pipe_send_init(void)
{
    ESP_LOGI("gt_pipe_send", ">>>>>>>gt_pipe_send_init");
    // 创建并初始化音频管道
    audio_pipeline_cfg_t pipeline_cfg = DEFAULT_AUDIO_PIPELINE_CONFIG();
    pipeline = audio_pipeline_init(&pipeline_cfg);
    if (pipeline == NULL) {
        ESP_LOGE(TAG, "Failed to create audio pipeline");
        return;
    }

    http_stream_cfg_t http_cfg = HTTP_STREAM_CFG_DEFAULT();
    http_cfg.type = AUDIO_STREAM_WRITER;
    http_cfg.event_handle = _http_stream_event_handle;
    http_stream = http_stream_init(&http_cfg);

    printf("http_cfg.request_size ============ %d\n",http_cfg.request_size);

    //注：播放器和录音的数据格式要保持一致，都是48000,16
    i2s_stream_cfg_t i2s_cfg = I2S_STREAM_CFG_DEFAULT_WITH_PARA(CODEC_ADC_I2S_PORT, 16000, 16, AUDIO_STREAM_READER);
    i2s_cfg.type = AUDIO_STREAM_READER;
    i2s_cfg.out_rb_size = 64 * 1024;//16 * 1024; // Increase buffer to avoid missing data in bad network conditions
    fs_reader = i2s_stream_init(&i2s_cfg);


    // 注册流到音频管道
    audio_pipeline_register(pipeline, fs_reader, "file_reader");
    audio_pipeline_register(pipeline, http_stream, "http_writer");

    // 链接文件流和HTTP上传流
    const char *link_tag[2] = {"file_reader", "http_writer"};
    audio_pipeline_link(pipeline, &link_tag[0], 2);


    if(api_key_data == NULL)
    {
        api_key_data = (Pipe_ReceivedAnswerData *)audio_malloc(sizeof(Pipe_ReceivedAnswerData));
        assert(api_key_data);
        memset(api_key_data, 0, sizeof(Pipe_ReceivedAnswerData));
    }

}


void gt_pipe_send_start(void)
{
    // 开始播放和上传
    ESP_LOGE(TAG, "[ * ] [Rec] input key event, resuming pipeline ...");
    /*
        * There is no effect when follow APIs output warning message on the first time record
        */
    audio_pipeline_stop(pipeline);
    audio_pipeline_wait_for_stop(pipeline);
    audio_pipeline_reset_ringbuffer(pipeline);
    audio_pipeline_reset_elements(pipeline);
    audio_pipeline_terminate(pipeline);

    audio_element_set_uri(http_stream, "http://api.mindcraft.com.cn/v1/mode_chunk/update/");

    audio_pipeline_run(pipeline);
}


void release_resources()
{
    // 等待上传完成
    audio_pipeline_wait_for_stop(pipeline);
    // 终止管道并释放资源
    audio_pipeline_terminate(pipeline);
    audio_pipeline_unregister(pipeline, fs_reader);
    audio_pipeline_unregister(pipeline, http_stream);
    audio_pipeline_deinit(pipeline);
}


void gt_pipe_send_stop()
{
    if(!pipeline) {
        ESP_LOGI(TAG, "No Stopping recording...");
        return ;
    }
    ESP_LOGI(TAG, "Stopping recording...");
    // 停止管道
    audio_pipeline_stop(pipeline);
    audio_pipeline_wait_for_stop(pipeline);
}


void set_ringbuf_done()
{
    if (fs_reader != NULL) {
        ESP_LOGI(TAG, "Valid audio element handle");
        audio_element_set_ringbuf_done(fs_reader);
        audio_element_set_ringbuf_done(http_stream);

    } else {
        ESP_LOGE(TAG, "Invalid audio element handle");// 处理空指针的情况
    }
}

char* get_uuid()
{
    if(api_key_data->update_uuid != NULL){
        return api_key_data->update_uuid;
    }
    else{
        return NULL;
    }
}
/**
 * @brief 解析get请求得到的json文件，获取api_key
 *
 * @param jbuf
 * @param receive_buf
 * @return esp_err_t
 */
static esp_err_t resolve_answer_json(char *jbuf)
{

    // Parse JSON response
    cJSON *data = NULL;
    cJSON *asr_uuid = NULL;
    cJSON *json = cJSON_Parse(jbuf);
    if (json == NULL) {
        ESP_LOGE(TAG, "Failed to parse JSON");
        return ESP_FAIL; // 返回失败
    }

    data = cJSON_GetObjectItem(json, "data");
    if(data != NULL){
        asr_uuid = cJSON_GetObjectItem(data, "asr_uuid");
        if(asr_uuid != NULL){
            user_asr_uuid = (char* )audio_malloc(strlen(asr_uuid->valuestring) + 1);
            strcpy(user_asr_uuid, asr_uuid->valuestring);
            ESP_LOGI(TAG, "------------------asr_uuid->valuestring： %s\n", asr_uuid->valuestring);
            ESP_LOGI(TAG, "------------------user_asr_uuid： %s\n",user_asr_uuid);
        }
    }


    cJSON_Delete(json);
    return ESP_OK; // 返回
}




/**
 * @brief get请求，获取发送数据的api_key
 *
 */
// void get_pipe_send_api_key(void)
// {
//     char *local_response_buffer = (char *)audio_malloc(MAX_HTTP_OUTPUT_BUFFER + 1);
//     memset(local_response_buffer, 0, MAX_HTTP_OUTPUT_BUFFER + 1);
//     esp_http_client_config_t config = {
//         .url =  "http://api.mindcraft.com.cn/v1/mode_chunk/",
//         .event_handler = NULL,
//         .user_data = local_response_buffer,        // Pass address of local buffer to get response
//         .disable_auto_redirect = true,
//         .cert_pem = NULL,
//         .timeout_ms = 15000, //超时时间
//     };
//     esp_http_client_handle_t get_api_key = esp_http_client_init(&config);//初始化http客户端

//     char content_type_header[100] = {0};
//     snprintf(content_type_header, sizeof(content_type_header), "multipart/form-data; boundary=%s", boundary);
//     esp_http_client_set_method(get_api_key, HTTP_METHOD_POST);//设置 HTTP 请求的方法
//     esp_http_client_set_header(get_api_key, "Content-Type",content_type_header);//设置 HTTP 请求头
//     esp_http_client_set_header(get_api_key, "Authorization", "API keys");//设置请求头的时候要加上API keys
//     size_t end_boundary_len = strlen(boundary) + 6;


//     //打开客户端连接服务器
//       char *extra_param = (char *)audio_malloc(1300);
//     memset(extra_param, 0, 1300);
//     snprintf(extra_param, 1300,
//         "\r\n--%s\r\n"
//         "Content-Disposition: form-data; name=\"category\"\r\n\r\n"
//         "%s"
//         "\r\n--%s\r\n"
//         "Content-Disposition: form-data; name=\"model\"\r\n\r\n"
//         "%s"
//         "\r\n--%s\r\n"
//         "Content-Disposition: form-data; name=\"format\"\r\n\r\n"
//         "%s"
//         "\r\n--%s\r\n"
//         "Content-Disposition: form-data; name=\"word_info\"\r\n\r\n"
//         "%d"
//         "\r\n--%s\r\n"
//         "Content-Disposition: form-data; name=\"language\"\r\n\r\n"
//         "%d"
//         "\r\n--%s\r\n"
//         "Content-Disposition: form-data; name=\"sample_rate\"\r\n\r\n"
//         "%d"
//         "\r\n--%s\r\n",
//         boundary,"tencent_stream_asr",boundary,"16k_zh",boundary,"wav",boundary, 0, boundary, "auto", boundary,16000,boundary);
//     size_t extra_pram_len = strlen(extra_param);
//     size_t total_data_len =  extra_pram_len + end_boundary_len;



//     //打开客户端连接服务器
//     esp_err_t err = esp_http_client_open(get_api_key, total_data_len);
//     if(err == ESP_OK)
//     {
//         //发送用户设置的参数
//         esp_http_client_write(get_api_key, extra_param, extra_pram_len);

//         // 发送multipart/form-data结束部分
//         char end_boundary[50] = {0};
//         snprintf(end_boundary, sizeof(end_boundary), "\r\n--%s--\r\n", boundary);
//         esp_http_client_write(get_api_key, end_boundary, strlen(end_boundary));

//         int content_length = 0;
//         content_length = esp_http_client_fetch_headers(get_api_key);//从服务器获取响应头部
//         if(content_length < 0)
//         {
//             ESP_LOGE(TAG, "HTTP client fetch headers failed");
//             err = ESP_FAIL;
//             goto FREE_LABEL;
//         }
//         else
//         {
//             int data_read = esp_http_client_read_response(get_api_key, local_response_buffer, MAX_HTTP_OUTPUT_BUFFER);//读取服务器返回的 HTTP 响应主体内容
//             ESP_LOGD(TAG, "FILEOK");
//             if(data_read >= 0)
//             {
//                 ESP_LOGI(TAG, "asr_uuid Received JSON response: %s", local_response_buffer);
//                 err = resolve_answer_json(local_response_buffer);
//                 printf("api_key_data: %s\r\n", user_asr_uuid);
//             }else{
//                 ESP_LOGE(TAG, "Failed to read response");
//                 err = ESP_FAIL;
//                 goto FREE_LABEL;
//             }
//         }
//     }


// FREE_LABEL:
//     audio_free(local_response_buffer);
//     local_response_buffer = NULL;
//     esp_http_client_close(get_api_key);
//     esp_http_client_cleanup(get_api_key);

//     return ;
// }

void get_pipe_send_api_key(void)
{
    char *local_response_buffer = (char *)audio_malloc(MAX_HTTP_OUTPUT_BUFFER + 1);
    memset(local_response_buffer, 0, MAX_HTTP_OUTPUT_BUFFER + 1);
    esp_http_client_config_t config = {
        .url =  "http://api.mindcraft.com.cn/v1/mode_chunk/",
        .event_handler = NULL,
        .user_data = local_response_buffer,        // Pass address of local buffer to get response
        .disable_auto_redirect = true,
        .cert_pem = NULL,
        .timeout_ms = 15000, //超时时间
    };
    esp_http_client_handle_t get_api_key = esp_http_client_init(&config);//初始化http客户端

    char content_type_header[100] = {0};
    snprintf(content_type_header, sizeof(content_type_header), "multipart/form-data; boundary=%s", boundary);
    esp_http_client_set_method(get_api_key, HTTP_METHOD_POST);//设置 HTTP 请求的方法
    esp_http_client_set_header(get_api_key, "Content-Type",content_type_header);//设置 HTTP 请求头
    esp_http_client_set_header(get_api_key, "Authorization", "API keys");//设置请求头的时候要加上API keys
    size_t end_boundary_len = strlen(boundary) + 6;



    //打开客户端连接服务器
    esp_err_t err = esp_http_client_open(get_api_key, 0);
    if(err == ESP_OK)
    {
        int content_length = 0;
        content_length = esp_http_client_fetch_headers(get_api_key);//从服务器获取响应头部
        if(content_length < 0)
        {
            ESP_LOGE(TAG, "HTTP client fetch headers failed");
            err = ESP_FAIL;
            goto FREE_LABEL;
        }
        else
        {
            int data_read = esp_http_client_read_response(get_api_key, local_response_buffer, MAX_HTTP_OUTPUT_BUFFER);//读取服务器返回的 HTTP 响应主体内容
            ESP_LOGD(TAG, "FILEOK");
            if(data_read >= 0)
            {
                ESP_LOGI(TAG, "asr_uuid Received JSON response: %s", local_response_buffer);
                err = resolve_answer_json(local_response_buffer);
                printf("api_key_data: %s\r\n", user_asr_uuid);
            }else{
                ESP_LOGE(TAG, "Failed to read response");
                err = ESP_FAIL;
                goto FREE_LABEL;
            }
        }
    }


FREE_LABEL:
    audio_free(local_response_buffer);
    local_response_buffer = NULL;
    esp_http_client_close(get_api_key);
    esp_http_client_cleanup(get_api_key);

    return ;
}

char* get_user_asr_uuid()
{
    return user_asr_uuid;
}

#endif