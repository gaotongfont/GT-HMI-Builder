#include "gt_record_http.h"

#define MAX_HTTP_OUTPUT_BUFFER 1024 * 8
#define SEND_DATA 800

static const char *RECORD = "HTTP_RECORD";

static char* receive_buf = NULL;
char* receive_historical_buf = NULL;
static HistoricalMessage* historyData[HISTORY_GROUP_COUNT*2] = {NULL};



//创建对话
esp_err_t create_room_http()
{
    // 停止播放和上传
    ESP_LOGI(RECORD, "create_room_http============================================ ...");


    const char boundary[] = {"----WebKitFormBoundary7MA4YWxkTrZu0gW"};//分隔符

    char *local_response_buffer = (char *)audio_malloc(MAX_HTTP_OUTPUT_BUFFER);
    memset(local_response_buffer, 0, MAX_HTTP_OUTPUT_BUFFER);

    malloc_receive_buf();//recerve_buf申请堆空间

    esp_http_client_config_t config = {
        .url = "http://api.mindcraft.com.cn/v1/session/",
        .user_data = NULL,//local_response_buffer,        // Pass address of local buffer to get response
        .buffer_size = 1024,
        .disable_auto_redirect = true,
        .cert_pem = NULL,
        .timeout_ms = 15000, //超时时间
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);//初始化http客户端

    // POST请求
    //要发送给服务器的参数
    char *extra_param = (char *)audio_malloc(SEND_DATA);
    memset(extra_param, 0, SEND_DATA);
    snprintf(extra_param, SEND_DATA,
        "\r\n--%s\r\n"
        "Content-Disposition: form-data; name=\"session_name\"\r\n\r\n"
        "%s"
        "\r\n--%s\r\n"
        "Content-Disposition: form-data; name=\"model\"\r\n\r\n"
        "%s"
        "\r\n--%s\r\n"
        "Content-Disposition: form-data; name=\"prompt\"\r\n\r\n"
        "%s"
        "\r\n--%s\r\n"
        "Content-Disposition: form-data; name=\"temperature\"\r\n\r\n"
        "%.1f"
        "\r\n--%s\r\n"
        "Content-Disposition: form-data; name=\"history_length\"\r\n\r\n"
        "%d"
        "\r\n--%s\r\n",
        boundary,"test",boundary,"deepseek-chat",boundary,"#",boundary,0.2,boundary,8,boundary);
    size_t extra_pram_len = strlen(extra_param);


    char content_type_header[100] = {0};
    snprintf(content_type_header, sizeof(content_type_header), "multipart/form-data; boundary=%s", boundary);
    esp_http_client_set_method(client, HTTP_METHOD_POST);//设置 HTTP 请求的方法
    esp_http_client_set_header(client, "Content-Type",content_type_header);//设置 HTTP 请求头
    esp_http_client_set_header(client, "Authorization", "API keys");//设置请求头的时候要加上API keys

    size_t end_boundary_len = strlen(boundary) + 6;
    size_t total_data_len = extra_pram_len + end_boundary_len;


    //打开客户端连接服务器
    esp_err_t err = esp_http_client_open(client, total_data_len);
    if(err == ESP_OK)
    {
        //发送用户设置的参数
        esp_http_client_write(client, extra_param, extra_pram_len);

        // 发送multipart/form-data结束部分
        char end_boundary[50] = {0};
        snprintf(end_boundary, sizeof(end_boundary), "\r\n--%s--\r\n", boundary);
        esp_http_client_write(client, end_boundary, strlen(end_boundary));

        int content_length = 0;
        content_length = esp_http_client_fetch_headers(client);//从服务器获取响应头部
        if(content_length < 0)
        {
            ESP_LOGE(RECORD, "HTTP client fetch headers failed");
            err = ESP_FAIL;
            goto FREE_LABEL;
        }else{
            int status = esp_http_client_get_status_code(client);
            ESP_LOGI(RECORD, "esp_http_client_get_status_code: %d", status);
            int data_read = esp_http_client_read_response(client, local_response_buffer, MAX_HTTP_OUTPUT_BUFFER);//读取服务器返回的 HTTP 响应主体内容
            ESP_LOGD(RECORD, "FILEOK");
            if(data_read >= 0)
            {
                ESP_LOGI(RECORD, "Received JSON response: %s", local_response_buffer);
                err = resolve_roomid_json(local_response_buffer, receive_buf);
                if (err == ESP_OK)
                {
                    store_data_in_nvs("room_id", receive_buf);
                }

            }else{
                ESP_LOGE(RECORD, "Failed to read response");
                err = ESP_FAIL;
                goto FREE_LABEL;
            }
        }
    }
FREE_LABEL:
    audio_free(extra_param);
    extra_param =NULL;
    audio_free(local_response_buffer);
    local_response_buffer = NULL;
    esp_http_client_close(client);
    return err;
}


int resolve_roomid_json(char* response_buffer, char* receive_buf)
{

// 解析 JSON 响应
    cJSON *json = cJSON_Parse(response_buffer);
    if (json == NULL) {
        ESP_LOGE(RECORD, "Failed to parse JSON");
        return ESP_FAIL;  // 返回失败
    }
    cJSON *session_token = NULL;
    cJSON *data = cJSON_GetObjectItem(json, "data");//解析json数据,获取回复用户的文字内容
    if(data != NULL){
        session_token = cJSON_GetObjectItem(data, "session_token");//解析json数据，获取情绪值
        if(session_token != NULL){
            strcpy(receive_buf, session_token->valuestring);
        }
    }
    ESP_LOGI(RECORD, "------------------session_token->valuestring: %s\n", session_token->valuestring);
    ESP_LOGI(RECORD, "------------------receive_buf: %s\n", receive_buf);

    cJSON_Delete(json);
    return ESP_OK;  // 返回成功

}


char* malloc_receive_buf()
{
    if(receive_buf == NULL){
        receive_buf = (char*)audio_malloc(MAX_HTTP_OUTPUT_BUFFER);
    }
    return receive_buf;
}

void set_session_token(char* session_token)
{
    if (receive_buf != NULL)
    {
        audio_free(receive_buf);
    }
    receive_buf = (char *)audio_malloc(strlen(session_token) + 1);
    if (receive_buf != NULL) {
        strcpy(receive_buf, session_token);
    } else {
        ESP_LOGE(RECORD, "Failed to allocate memory for session token");
    }
}

char* get_session_token()
{
    return receive_buf;
}



esp_err_t get_historical_message_http()
{
    // 停止播放和上传
    ESP_LOGI(RECORD, "create_room_http============================================ ...");


    const char boundary[] = {"----WebKitFormBoundary7MA4YWxkTrZu0gW"};//分隔符

    char *local_response_buffer = (char *)audio_malloc(MAX_HTTP_OUTPUT_BUFFER);
    memset(local_response_buffer, 0, MAX_HTTP_OUTPUT_BUFFER);

    creat_historyData();//申请历史记录的堆空间

    char urlString[255] = {0};
    sprintf(urlString, "https://api.mindcraft.com.cn/v1/message/?size=%d&session_token=%s",HISTORY_GROUP_COUNT*2, receive_buf);
    esp_http_client_config_t config = {
        .url = urlString,//"https://api.mindcraft.com.cn/v1/message/?size=3&session_token=868f5d40-a4a7-49c0-a283-09a57d992f11",
        .user_data = NULL,//local_response_buffer,        // Pass address of local buffer to get response
        .buffer_size = 1024,
        .disable_auto_redirect = true,
        .cert_pem = NULL,
        .timeout_ms = 15000, //超时时间
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);//初始化http客户端

    // POST请求

    char content_type_header[100] = {0};
    snprintf(content_type_header, sizeof(content_type_header), "multipart/form-data; boundary=%s", boundary);
    esp_http_client_set_method(client, HTTP_METHOD_GET);//设置 HTTP 请求的方法
    esp_http_client_set_header(client, "Content-Type",content_type_header);//设置 HTTP 请求头
    esp_http_client_set_header(client, "Authorization", "API keys");//设置请求头的时候要加上API keys

    size_t end_boundary_len = strlen(boundary) + 6;
    size_t total_data_len =  end_boundary_len;


    //打开客户端连接服务器
    esp_err_t err = esp_http_client_open(client, 0);
    if(err == ESP_OK)
    {
        int content_length = 0;
        content_length = esp_http_client_fetch_headers(client);//从服务器获取响应头部
        if(content_length < 0)
        {
            ESP_LOGE(RECORD, "HTTP client fetch headers failed");
            err = ESP_FAIL;
            goto FREE_LABEL;
        }else{
            int status = esp_http_client_get_status_code(client);
            ESP_LOGI(RECORD, "esp_http_client_get_status_code: %d", status);
            int data_read = esp_http_client_read_response(client, local_response_buffer, MAX_HTTP_OUTPUT_BUFFER);//读取服务器返回的 HTTP 响应主体内容
            ESP_LOGD(RECORD, "FILEOK");
            if(data_read >= 0)
            {
                ESP_LOGI(RECORD, "Received JSON response: %s", local_response_buffer);
                err =  resolve_historical_message_json(local_response_buffer);

            }else{
                ESP_LOGE(RECORD, "Failed to read response");
                err = ESP_FAIL;
                goto FREE_LABEL;
            }
        }
    }
FREE_LABEL:
    // audio_free(extra_param);
    // extra_param =NULL;
    audio_free(local_response_buffer);
    local_response_buffer = NULL;
    esp_http_client_close(client);

    return err;
}


#define PARSE_HISTORY_JSON(ptr, ptrJson)    if(ptrJson != NULL){\
                                                if(ptr == NULL){ptr = (char* )audio_malloc(strlen(ptrJson->valuestring)+1);\
                                                                strcpy(ptr, ptrJson->valuestring);}\
                                                else{strcpy(ptr, ptrJson->valuestring);}\
                                            }\
                                            else{break;}


int resolve_historical_message_json(char* response_buffer)
{

// 解析 JSON 响应
    cJSON *json = cJSON_Parse(response_buffer);
    if (json == NULL) {
        ESP_LOGE(RECORD, "Failed to parse JSON");
        return ESP_FAIL;  // 返回失败
    }

    cJSON *message_id = NULL, *message_meta = NULL, *session_id = NULL, *session_token = NULL,\
            *message_category = NULL, *message_content = NULL, *created_at = NULL;

    cJSON *result = cJSON_GetObjectItem(json, "results");//解析json数据,获取回复用户的文字内容

    cJSON* result_array = NULL;
    bool isFinish = false;
    int i = 0;
    if(result != NULL){
        while(isFinish == false){
            result_array = cJSON_GetArrayItem(result, i);

            if(result_array != NULL){
                message_id = cJSON_GetObjectItem(result_array, "message_id");
                if(message_id != NULL){
                    historyData[i]->message_id = message_id->valueint;
                }
                else{
                    break;
                }
                session_id = cJSON_GetObjectItem(result_array, "session_id");
                if(session_id != NULL){
                    historyData[i]->session_id = session_id->valueint;
                }
                else{
                    break;
                }
                session_token = cJSON_GetObjectItem(result_array, "session_token");
                PARSE_HISTORY_JSON(historyData[i]->session_token, session_token);
                message_category = cJSON_GetObjectItem(result_array, "message_category");
                PARSE_HISTORY_JSON(historyData[i]->message_category, message_category);
                message_content = cJSON_GetObjectItem(result_array, "message_content");
                PARSE_HISTORY_JSON(historyData[i]->message_content, message_content);
                created_at = cJSON_GetObjectItem(result_array, "created_at");
                PARSE_HISTORY_JSON(historyData[i]->created_at, created_at);
                i++;
            }
            else{
                ESP_LOGI(RECORD, "------------------==========================FAIL RESULT_2");
                isFinish = true;
            }
        }
    }
    cJSON_Delete(json);
    return ESP_OK;  // 返回成功
}

void creat_historyData(){

    for(int i =  0; i<HISTORY_GROUP_COUNT*2; i++){
        if(historyData[i] == NULL){
            historyData[i] = (HistoricalMessage*)audio_malloc(sizeof(HistoricalMessage));
            memset(historyData[i], 0 , sizeof(HistoricalMessage));
        }
    }

}

HistoricalMessage** get_historyData(){
    return historyData;
}


esp_err_t clear_historical_message_http()
{
    // 停止播放和上传
    ESP_LOGI(RECORD, "clear_historical_message_http");

    const char boundary[] = {"----WebKitFormBoundary7MA4YWxkTrZu0gW"};//分隔符    /

    esp_http_client_config_t config = {
        .url = "http://api.mindcraft.com.cn/v1/message/clear/",
        .user_data = NULL,//local_response_buffer,        // Pass address of local buffer to get response
        .buffer_size = 1024,
        .disable_auto_redirect = true,
        .cert_pem = NULL,
        .timeout_ms = 15000, //超时时间
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);//初始化http客户端

    // POST请求
    //要发送给服务器的参数
    char *extra_param = (char *)audio_malloc(SEND_DATA);
    memset(extra_param, 0, SEND_DATA);
    snprintf(extra_param, SEND_DATA,
        "\r\n--%s\r\n"
        "Content-Disposition: form-data; name=\"session_token\"\r\n\r\n"
        "%s"
        "\r\n--%s\r\n",
        boundary, receive_buf, boundary);
    size_t extra_pram_len = strlen(extra_param);


    char content_type_header[100] = {0};
    snprintf(content_type_header, sizeof(content_type_header), "multipart/form-data; boundary=%s", boundary);
    esp_http_client_set_method(client, HTTP_METHOD_POST);//设置 HTTP 请求的方法
    esp_http_client_set_header(client, "Content-Type",content_type_header);//设置 HTTP 请求头
    esp_http_client_set_header(client, "Authorization", "API keys");//设置请求头的时候要加上API keys

    size_t end_boundary_len = strlen(boundary) + 6;
    size_t total_data_len =  extra_pram_len + end_boundary_len;


    //打开客户端连接服务器
    esp_err_t err = esp_http_client_open(client, total_data_len);
    if(err == ESP_OK)
    {
        //发送用户设置的参数
        esp_http_client_write(client, extra_param, extra_pram_len);

        // 发送multipart/form-data结束部分
        char end_boundary[50] = {0};
        snprintf(end_boundary, sizeof(end_boundary), "\r\n--%s--\r\n", boundary);
        esp_http_client_write(client, end_boundary, strlen(end_boundary));

        int content_length = 0;
        content_length = esp_http_client_fetch_headers(client);//从服务器获取响应头部
        if(content_length < 0)
        {
            ESP_LOGE(RECORD, "HTTP client fetch headers failed");
            err = ESP_FAIL;
            goto FREE_LABEL;
        }
        else{
            int status = esp_http_client_get_status_code(client);
            ESP_LOGI(RECORD, "clear_historical_message_http esp_http_client_get_status_code: %d", status);
        }
    }
FREE_LABEL:
    audio_free(extra_param);
    extra_param =NULL;
    esp_http_client_close(client);
    return err;
}
