#ifndef _GT_PIPESEND_H_
#define _GT_PIPESEND_H_



#ifdef __cplusplus
extern "C" {
#endif


#define API_KEY

//创建任务url
#define CREATE_TASK_URL "http://api.mindcraft.com.cn/v1/stream_asr/"

//提交数据url
#define SUMBIT_DATA_URL "http://api.mindcraft.com.cn/v1/stream_asr/update/"

//参数设置
#define CATEGORY "tencent_stream_asr"
#define MODEL "16k_zh"
#define FORMAT "wav"
#define WORD_INFO 0
#define LANGUAGE "auto"
#define SAMPLE_RATE 16000


typedef struct{
    char *update_uuid;
} Pipe_ReceivedAnswerData;



void gt_pipe_send_init(void);

void gt_pipe_send_start(void);

void gt_pipe_send_stop(void);

void release_resources();

void get_pipe_send_api_key(void);

void set_ringbuf_done();

char* get_uuid();

char* get_user_asr_uuid();
#ifdef __cplusplus
} /*extern "C"*/
#endif



#endif