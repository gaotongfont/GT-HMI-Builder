/**
 * @file gt_role_emote.h
 * @author Yang
 * @brief
 * @version 0.1
 * @date 2025-01-17 11:16:41
 * @copyright Copyright (c) 2014-2025, Company Genitop. Co., Ltd.
 */
#ifndef _GT_ROLE_EMOTE_H_
#define _GT_ROLE_EMOTE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "audio_mem.h"

/* define ---------------------------------------------------------------*/
//
#define GT_ROLE_EMOTE_ELEM_DATA_MIN_SIZE  (48 * 1024)
//
#define GT_ROLE_NAME_MAX_LEN  100

//
#if 01
#define GT_ROLE_MALLOC(x)       audio_malloc((x))
#define GT_ROLE_FREE(x)         audio_free((x))
#define GT_ROLE_REALLOC(x,y)    audio_realloc((x),(y))
#else
#define GT_ROLE_MALLOC(x)       malloc((x))
#define GT_ROLE_FREE(x)         free((x))
#define GT_ROLE_REALLOC(x,y)    realloc((x),(y))
#endif

/* typedef --------------------------------------------------------------*/
typedef enum {
    GT_EMOTE_ELEM_STATE_NONE = 0,
    GT_EMOTE_ELEM_STATE_DOWNLOADING,
    GT_EMOTE_ELEM_STATE_FINISHED,
}gt_emote_elem_state_te;

typedef struct{
    uint8_t *data;
    uint32_t size;
    uint32_t count;
    uint32_t width;
    uint32_t height;
    uint8_t state : 2; // @ gt_emote_elem_state_te
}gt_emote_elem_st;

typedef struct{
    char name[GT_ROLE_NAME_MAX_LEN];
    char *url;
    uint32_t count;
    uint32_t pos;
    gt_emote_elem_st ** elems;
}gt_emote_st;

typedef struct {
    char name[GT_ROLE_NAME_MAX_LEN];
    uint32_t count;
    gt_emote_st ** emotes;
}gt_role_st;


typedef struct {
    uint32_t count;
    gt_role_st ** roles;
}gt_role_list_st;

/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/
void gt_role_emote_init(void);
gt_role_st* gt_role_find(const char* role);
int gt_role_add_emote(const char* role, const char* emote, uint32_t count, const char* url);
void gt_role_list_printf(void);
uint8_t* gt_role_emote_get_data(const char* role, const char* emote, uint32_t index, uint32_t *size);
uint8_t* gt_role_emote_next_data(const char* role, const char* emote, uint32_t *size);
uint8_t* gt_role_emote_prev_data(const char* role, const char* emote, uint32_t *size);
uint32_t gt_rolr_emote_get_count(const char* role, const char* emote);


void gt_role_remove_role(const char* role);
void gt_role_remove_emote(const char* role, const char* emote);
void gt_role_remove_all(void);

void gt_role_updata_emote_http(const char* role, const char* emote, uint32_t index);
void gt_role_updata_emote_http_all(const char* role, const char* emote);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_GT_ROLE_EMOTE_H_

/* end of file ----------------------------------------------------------*/


