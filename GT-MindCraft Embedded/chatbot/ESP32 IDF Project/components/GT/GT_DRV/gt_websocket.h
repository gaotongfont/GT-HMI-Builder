#ifndef GT_WEBSOCKET_H
#define GT_WEBSOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "audio_mem.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "gt_ui.h"
#include "http_send.h"

/* typedef --------------------------------------------------------------*/
#define WEATHER_DAYS 8   //查看的日期和一共七天的天数

#define WEATHER_DATA_RESPONSE_DAYS 8

#if 1
#define GET_VALUESTRING(stringjson, pre_object, object, getstring)     stringjson = cJSON_GetObjectItem(pre_object, object); \
                                                                        if(stringjson != NULL){getstring = (char*)audio_calloc(1,strlen(stringjson->valuestring)+1); strcpy(getstring, stringjson->valuestring);}\
                                                                        else{break;}

#define GET_VALUEDOUBLE(numjson, pre_object, object, getdouble)        numjson = cJSON_GetObjectItem(pre_object, object); \
                                                                        if(numjson != NULL){getdouble = (float)numjson->valuedouble;}\
                                                                        else{break;}

#define GET_VALUEINT(int_numjson, pre_object, object, getint)        int_numjson = cJSON_GetObjectItem(pre_object, object); \
                                                                        if(int_numjson != NULL){getint = int_numjson->valueint;}\
                                                                        else{break;}
#endif

typedef struct{
    char* english_response;
    char* query_translation;
    char* response_translation;
    char* preferred_responses_for_next_round[3];
    char* oral_pratice_tts_audio;
}WEB_ORAL_PRACTICE;


typedef struct{
    char* config_name;
    char* config_value;
}WEB_SYSTEM_CONFIG;

typedef struct{
    char* llm_response;
    char* tts_audio;
    double audio_seconds;
}RECOVER;    //对话数据

typedef struct{
    char* instruct_type;
    char* alarm_date;
    char* alarm_time;
    char* period;
    char* alarm_purpose;
    char* alarm_repeat;
    char* new_alarm_time;
    char* new_period;
}CLOCK;  //闹钟数据

typedef struct{
    char* address;
    char* valid;
    char* cap;
    char* cap_type;
    double precip;
    double windMax;
    double windMaxDir;
    double rhHi;
    double tempHi;
    double tempLo;
}WEATHER; //天气数据


typedef struct{
    int time_stamp;
    // char* ip_address;
    WEATHER weather_data[WEATHER_DATA_RESPONSE_DAYS];
}CLOCK_WEATHER;

typedef struct{
    char* socket_type;
    char* agent_type;  //机器人回复分类
    char* data_name;  //数据回复类型 天气 日历
    char* countdown;  //倒计时
    char* weather_tts_audio; //查询天气回复的语音
    char* user_input;
    char* session_token; //获取房间
    char* session_token_check;
    char* interface_name;
    int time_stamp;
    int check_status;
    RECOVER recover_data;
    CLOCK clock_data;
    WEATHER weather_data[WEATHER_DATA_RESPONSE_DAYS];
    WEB_SYSTEM_CONFIG web_sys_config;
    WEB_ORAL_PRACTICE web_oral_pratice;
}WEBSOCKET_RECEIVED_DATA;


void websocket_app_start(void);

int check_opcode(unsigned char opcode);
int websocket_parse_socket_message(char *jbuf);
void gt_websocket_client_request();
void serve_dialog_init();
/**
 * @brief websocket client init
 *
 */
void gt_websocket_client_init(); //websocket 初始化

/**
 * @brief client send data
 *
 * @param data  audio data
 */
void gt_websocket_send_data(char* data); //websocket 发送数据
void gt_esp_websocket_client_send_fin();
/**
 * @brief every time it is create task
 *
 */
void gt_websocket_client_create_task();//创建任务

/**
 * @brief client start websocket
 *
 */
void gt_websocket_client_start(); //websocket 开启

/**
 * @brief client close websocket
 *
 */
void gt_websocket_client_close(); //websocket 关闭

/**
 * @brief destroy client
 *
 */
void gt_websocket_client_destroy(); //websocket 销毁

/**
 * @brief stop send audio data
 *
 */
void gt_websocket_client_stop_send_audio_data();//停止发送音频

/**
 * @brief stop receive data
 *
 */
void gt_websocket_client_stop_receive_data();

/**
 * @brief parse json data
 *
 * @param jbuf json data
 * @param clock_buf storage data after parse json
 * @return int
 */
int websocket_json_parse(char *jbuf, WEBSOCKET_RECEIVED_DATA* clock_buf);

/**
 * @brief
 *
 * @param jbuf
 * @param receive_buf
 * @return int
 */
int websocket_chatbot_json_parse(char *jbuf, ReceivedAnswerData* receive_buf);

/**
 * @brief Set the isFirstAudiouri object
 *
 * @param value
 */
void set_isFirstAudiouri(bool value);

/**
 * @brief Set the chatbot audio uri object
 *
 * @param audio_uri
 */
void set_chatbot_audio_uri(char* audio_uri);

/**
 * @brief Get the chatbot audio uri object
 *
 * @return char*
 */
char* get_chatbot_audio_uri();


void free_chatbot_audio_uri();

void gt_websocket_client_clear_history_message();

#ifdef __cplusplus
}
#endif

#endif // !