#ifndef GT_RECORD_HTTP_H
#define GT_RECORD_HTTP_H


#include <sys/param.h>
#include "esp_log.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"
#include "protocol_examples_utils.h"
#include "esp_tls.h"
#include "esp_http_client.h"
#include "audio_mem.h"
#include "cJSON.h"
#include "gt_nvs_store.h"

#define HISTORY_GROUP_COUNT 6 ///获得消息记录的组数

typedef struct{
   int message_id;
   char* message_meta;
   int session_id;
   char* session_token;
   char* message_category;
   char* message_content;
   char* created_at;
}HistoricalMessage;


esp_err_t create_room_http();//创建房间
esp_err_t get_historical_message_http();//获取历史记录
esp_err_t clear_historical_message_http();//清空历史记录
int resolve_roomid_json(char* response_buffer, char* receive_buf);//解析房间号
int resolve_historical_message_json(char* response_buffer);//解析历史记录
char* malloc_receive_buf();//申请获取房间号的堆内存
void creat_historyData();//申请获取历史记录堆内存
HistoricalMessage** get_historyData();//获取历史记录
void set_session_token(char* session_token);//设置房间号
char* get_session_token();//获取房间

#endif // !GT_RECORD_H