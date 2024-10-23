#ifndef _GT_PIPESEND_H_
#define _GT_PIPESEND_H_



#ifdef __cplusplus
extern "C" {
#endif


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

#ifdef __cplusplus
} /*extern "C"*/
#endif



#endif