/**
 * @file gt_role_emote.c
 * @author Yang
 * @brief
 * @version 0.1
 * @date 2025-01-17 16:08:34
 * @copyright Copyright (c) 2014-2025, Company Genitop. Co., Ltd.
 */

/* include --------------------------------------------------------------*/
#include "gt_role_emote.h"
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_http_client.h"
#include "esp_spiffs.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_err.h"
/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/
typedef struct {
    gt_emote_st* emote;
    uint32_t index;
}_emote_http_queue_st;


/* static prototypes ----------------------------------------------------*/
static const char* TAG = "ROLE_EMOTE";


/* static variables -----------------------------------------------------*/
static gt_role_list_st _role_list = {0};
static QueueHandle_t _emote_http_request_queue;

/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/
static gt_role_st* _role_find(gt_role_list_st* role_list, const char* name)
{
    if(!role_list) {
        return NULL;
    }
    for (uint32_t i = 0; i < role_list->count; i++) {
        if(!role_list->roles[i]){
            continue;
        }
        if (strcmp(role_list->roles[i]->name, name) == 0) {
            return role_list->roles[i];
        }
    }
    return NULL;
}

static gt_role_st* _role_add(gt_role_list_st* role_list, const char* name)
{
    if(!role_list || !name) {
        return NULL;
    }
    uint32_t pos = 0;
    while(pos < role_list->count){
        if(!role_list->roles[pos]){
            break;
        }
        ++pos;
    }

    if(pos >= role_list->count){
        role_list->roles = (gt_role_st**) GT_ROLE_REALLOC(role_list->roles, sizeof(gt_role_st*) * (role_list->count + 1));
        if(!role_list->roles){
            ESP_LOGE(TAG, "realloc role list failed\n");
            return NULL;
        }
        pos = role_list->count;
        role_list->roles[pos] = NULL;
        ++role_list->count;
    }

    gt_role_st* role = (gt_role_st*) GT_ROLE_MALLOC(sizeof(gt_role_st));
    if(!role){
        ESP_LOGE(TAG, "malloc role failed\n");
        return NULL;
    }
    memset(role, 0, sizeof(gt_role_st));
    role_list->roles[pos] = role;

    int len = strlen(name);
    if(len > GT_ROLE_NAME_MAX_LEN){
        len = GT_ROLE_NAME_MAX_LEN;
    }
    memcpy(role->name, name, len);

    return role;
}


static gt_emote_st* _emote_fine(gt_role_st* role, const char* emote_name)
{
    if(!role || !role->emotes) {
        return NULL;
    }

    for (uint32_t i = 0; i < role->count; i++) {
        if(!role->emotes[i]){
            continue;
        }
        if (strcmp(role->emotes[i]->name, emote_name) == 0) {
            return role->emotes[i];
        }
    }
    return NULL;
}

static bool _elem_check_url(gt_emote_st* emote, const char* url)
{
    if(!emote || !url || !emote->url) {
        return false;
    }

    return (0 == strcmp(emote->url, url));
}


static void _emote_elem_clear(gt_emote_st* emote)
{
    if(emote->url){
        GT_ROLE_FREE(emote->url);
        emote->url = NULL;
    }

    if(emote->elems){
        for(uint32_t i = 0; i < emote->count; ++i){
            if(emote->elems[i]){
                if(emote->elems[i]->data){
                    GT_ROLE_FREE(emote->elems[i]->data);
                    emote->elems[i]->data = NULL;
                }
                GT_ROLE_FREE(emote->elems[i]);
                emote->elems[i] = NULL;
            }
        }
        GT_ROLE_FREE(emote->elems);
        emote->elems = NULL;
    }
}

static void _emote_elem_creat(gt_emote_st* emote, uint32_t count, const char* url)
{
    if(!emote || !url || 0 == count) {
        return;
    }

    bool is_old = _elem_check_url(emote, url);
    if(is_old && emote->count == count){
        return;
    }
    // clear old
    _emote_elem_clear(emote);

    char* new_url = (char*) GT_ROLE_MALLOC(strlen(url) + 1);
    if(!new_url){
        ESP_LOGE(TAG, "malloc emote url failed\n");
        return;
    }
    strcpy(new_url, url);


    gt_emote_elem_st* new_elem = (gt_emote_elem_st*) GT_ROLE_MALLOC(sizeof(gt_emote_elem_st) * count);
    if(!new_elem){
        ESP_LOGE(TAG, "malloc emote elem failed\n");
        if(new_url){
            GT_ROLE_FREE(new_url);
            new_url = NULL;
        }
        return;
    }
    memset(new_elem, 0, sizeof(gt_emote_elem_st) * count);

    gt_emote_elem_st** elems = (gt_emote_elem_st**) GT_ROLE_MALLOC(sizeof(gt_emote_elem_st*) * count);
    if(!elems){
        ESP_LOGE(TAG, "malloc emote elem list failed\n");
        if(new_url){
            GT_ROLE_FREE(new_url);
            new_url = NULL;
        }
        if(new_elem){
            GT_ROLE_FREE(new_elem);
            new_elem = NULL;
        }
        return;
    }
    memset(elems, 0, sizeof(gt_emote_elem_st*) * count);
    for(uint32_t i = 0; i < count; ++i){
        elems[i] = &new_elem[i];
    }
    //
    emote->elems = elems;
    emote->url = new_url;
    emote->count = count;
    emote->pos = 0;
}

static gt_emote_st* _emote_add(gt_role_st* role, const char* emote_name, uint32_t count, const char* url)
{

    if(!role || !emote_name || !url || 0 == count) {
        return NULL;
    }

    gt_emote_st* emote_ptr = _emote_fine(role, emote_name);
    if(emote_ptr){
        //set emote
        goto _set_emote_elem;
    }

    uint32_t pos = 0;
    while(pos < role->count){
        if(!role->emotes[pos]){
            break;
        }
        ++pos;
    }

    if(pos >= role->count){
        role->emotes = (gt_emote_st**) GT_ROLE_REALLOC(role->emotes, sizeof(gt_emote_st*) * (role->count + 1));
        if(!role->emotes){
            ESP_LOGE(TAG, "realloc emote list failed\n");
            return NULL;
        }
        pos = role->count;
        role->emotes[pos] = NULL;
        ++role->count;
    }

    emote_ptr = (gt_emote_st*) GT_ROLE_MALLOC(sizeof(gt_emote_st));
    if(!emote_ptr){
        ESP_LOGE(TAG, "malloc emote failed\n");
        return NULL;
    }
    memset(emote_ptr, 0, sizeof(gt_emote_st));
    role->emotes[pos] = emote_ptr;

    uint16_t len = strlen(emote_name);
    memcpy(emote_ptr->name, emote_name, len);

_set_emote_elem:
    _emote_elem_creat(emote_ptr, count, url);
    return emote_ptr;
}

static int _role_add_emote(gt_role_list_st* role_list, const char* role, const char* emote_name, uint32_t count, const char* url)
{
    if(!role_list || !role || !emote_name || !url || 0 == count) {
        return -1;
    }

    gt_role_st* role_ptr = _role_find(role_list, role);

    if(!role_ptr){
        role_ptr = _role_add(role_list, role);
        if(!role_ptr){
            ESP_LOGE(TAG, "add role failed,role[%s], emote_name[%s]\n",role, emote_name);
            return -1;
        }
    }

    return _emote_add(role_ptr, emote_name, count, url) ? 0 : -1;
}

static uint8_t* _emote_elem_get_data(gt_emote_st* emote, uint32_t index, uint32_t *size)
{
    if(!emote || !emote->elems){
        return NULL;
    }

    emote->pos = (index) % emote->count;

    while(GT_EMOTE_ELEM_STATE_FINISHED != emote->elems[emote->pos]->state){
        emote->pos = (emote->pos + emote->count - 1) % emote->count;
        if(0 == emote->pos){
            break;
        }
    }

    if(GT_EMOTE_ELEM_STATE_FINISHED != emote->elems[emote->pos]->state){
        return NULL;
    }

    if(size){
        *size = emote->elems[emote->pos]->count;
    }

    return emote->elems[emote->pos]->data;
}

static void _emote_elem_remove(gt_emote_st* emote)
{
    if(!emote){
        return;
    }
    memset(emote->name, 0, GT_ROLE_NAME_MAX_LEN);
    if(emote->url){
        GT_ROLE_FREE(emote->url);
        emote->url = NULL;
    }

    if(emote->elems){
        for(uint32_t i = 0; i < emote->count; ++i){
            if(emote->elems[i]){
                if(emote->elems[i]->data){
                    GT_ROLE_FREE(emote->elems[i]->data);
                    emote->elems[i]->data = NULL;
                }
                GT_ROLE_FREE(emote->elems[i]);
                emote->elems[i] = NULL;
            }
        }
        GT_ROLE_FREE(emote->elems);
        emote->elems = NULL;
    }
    emote->count = 0;
    emote->pos = 0;
}

static void _emote_remove_index(gt_role_st* role, uint32_t index)
{
    if(!role || index >= role->count){
        return;
    }

    if(!role->emotes){
        return;
    }

    _emote_elem_remove(role->emotes[index]);
    role->emotes[index] = NULL;
}

static void _emote_remove(const char* role, const char* emote)
{
    if(!role || !emote){
        return;
    }

    gt_role_st* role_ptr = gt_role_find(role);
    if(!role_ptr){
        ESP_LOGE(TAG, "role[%s] not found\n", role);
        return;
    }

    if(!role_ptr->emotes){
        return;
    }

    for (uint32_t i = 0; i < role_ptr->count; i++) {
        if(!role_ptr->emotes[i]){
            continue;
        }
        if (strcmp(role_ptr->emotes[i]->name, emote) == 0) {
            _emote_remove_index(role_ptr, i);
            break;
        }
    }
}

static void _role_remove_index(gt_role_list_st* role_list, uint32_t index)
{
    if(!role_list || index >= role_list->count){
        return;
    }

    if(!role_list->roles){
        return;
    }

    gt_role_st* role_ptr = role_list->roles[index];
    if(!role_ptr){
        return;
    }

    if(role_ptr->emotes){
        for(uint32_t i = 0; i < role_ptr->count; ++i){
            _emote_remove_index(role_ptr, i);
        }
        GT_ROLE_FREE(role_ptr->emotes);
        role_ptr->emotes = NULL;
    }
    role_ptr->count = 0;
    memset(role_ptr->name, 0, GT_ROLE_NAME_MAX_LEN);
}

static void _role_remove(gt_role_list_st* role_list, const char* role)
{
    if(!role_list || !role){
        return;
    }

    if(!role_list->roles){
        return;
    }

    for (uint32_t i = 0; i < role_list->count; i++) {
        if(!role_list->roles[i]){
            continue;
        }
        if (strcmp(role_list->roles[i]->name, role) == 0) {
            _role_remove_index(role_list, i);
            break;
        }
    }
}

static void _role_remove_all(gt_role_list_st* role_list)
{
    if(!role_list){
        return;
    }

    if(!role_list->roles){
        return;
    }

    for(uint32_t i = 0; i < role_list->count; ++i){
        _role_remove_index(role_list, i);
    }
    GT_ROLE_FREE(role_list->roles);
    role_list->roles = NULL;
    role_list->count = 0;
}

static esp_err_t _elem_http_event_handler(esp_http_client_event_t *evt)
{
    gt_emote_elem_st* elem = (gt_emote_elem_st*)evt->user_data;

    switch (evt->event_id) {
        case HTTP_EVENT_ON_DATA:
            elem->state = GT_EMOTE_ELEM_STATE_DOWNLOADING;
            if(elem->count + evt->data_len > elem->size){
                elem->data = (uint8_t*)GT_ROLE_REALLOC(elem->data, elem->size + GT_ROLE_EMOTE_ELEM_DATA_MIN_SIZE);
                if(!elem->data){
                    elem->state = GT_EMOTE_ELEM_STATE_NONE;
                    elem->count = 0;
                    ESP_LOGE(TAG, "http elem data realloc failed");
                    break;
                }
                elem->size += GT_ROLE_EMOTE_ELEM_DATA_MIN_SIZE;
            }

            memcpy(elem->data + elem->count, evt->data, evt->data_len);
            elem->count += evt->data_len;
            //
            break;

        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI(TAG, "elem HTTP request finished");
            elem->state = GT_EMOTE_ELEM_STATE_FINISHED;
            break;

        case HTTP_EVENT_ERROR:
            ESP_LOGE(TAG, "elem HTTP request error");
            elem->state = GT_EMOTE_ELEM_STATE_NONE;
            elem->count = 0;
            break;

        default:
            break;
    }
    return ESP_OK;
}



static void _emote_elem_updata_http(gt_emote_st* emote, uint32_t index)
{
    if(!emote || !emote->elems || !emote->url){
        return ;
    }
    index = index % emote->count;

    if(!emote->elems[index]){
        return ;
    }

    gt_emote_elem_st* elem = emote->elems[index];

    if(GT_EMOTE_ELEM_STATE_NONE != elem->state){
        return ;
    }
    if(elem->data){
        GT_ROLE_FREE(elem->data);
        elem->data = NULL;
    }
    elem->data = (uint8_t*)GT_ROLE_MALLOC(GT_ROLE_EMOTE_ELEM_DATA_MIN_SIZE);
    if(!elem->data){
        ESP_LOGE(TAG, "elem data malloc failed\n");
        return ;
    }
    memset(elem->data, 0, GT_ROLE_EMOTE_ELEM_DATA_MIN_SIZE);
    elem->size = GT_ROLE_EMOTE_ELEM_DATA_MIN_SIZE;
    elem->count = 0;

    // http download
    if(_emote_http_request_queue){
        _emote_http_queue_st _emote_queue = {
            .index = index,
            .emote = emote,
        };
        xQueueSend(_emote_http_request_queue, &_emote_queue, portMAX_DELAY);
    }
}

static void _emote_elem_http_task(void* arg)
{
    for(;;)
    {
        _emote_http_queue_st _emote_queue;
        if(pdTRUE == xQueueReceive(_emote_http_request_queue, &_emote_queue, portMAX_DELAY)){

            uint32_t index = _emote_queue.index;
            gt_emote_st* emote = _emote_queue.emote;
            gt_emote_elem_st* elem = emote->elems[index];

            // / http download
            // 配置 esp_http_client
            char* url = (char*)GT_ROLE_MALLOC(strlen(emote->url) + 16);
            sprintf(url, "%s/%03d.jpeg", emote->url, index + 1);

            esp_http_client_config_t config = {
                .url = url,
                .event_handler = _elem_http_event_handler,
                .user_data = (void*)elem,
            };

            esp_http_client_handle_t client = esp_http_client_init(&config);
            elem->state = GT_EMOTE_ELEM_STATE_DOWNLOADING;
            esp_err_t err = esp_http_client_perform(client);

            esp_http_client_cleanup(client);
            GT_ROLE_FREE(url);
            url = NULL;
        }

    }
}

/* global functions / API interface -------------------------------------*/
void gt_role_emote_init(void)
{
    _emote_http_request_queue = xQueueCreate(10, sizeof(_emote_http_queue_st));
    xTaskCreate(_emote_elem_http_task, "_emote_elem_http_task", 4096, NULL, 5, NULL);
}

gt_role_st* gt_role_find(const char* role)
{
    return _role_find(&_role_list, role);
}

int gt_role_add_emote(const char* role, const char* emote, uint32_t count, const char* url)
{
    return _role_add_emote(&_role_list, role, emote, count, url);
}

void gt_role_remove_emote(const char* role, const char* emote)
{
    _emote_remove(role, emote);
}

void gt_role_remove_role(const char* role)
{
    _role_remove(&_role_list, role);
}

void gt_role_remove_all(void)
{
    _role_remove_all(&_role_list);
}

uint8_t* gt_role_emote_get_data(const char* role, const char* emote, uint32_t index, uint32_t *size)
{
    gt_role_st* role_ptr = gt_role_find(role);
    if(!role_ptr){
        ESP_LOGW(TAG, "role[%s] not found\n", role);
        return NULL;
    }

    gt_emote_st* emote_ptr = _emote_fine(role_ptr, emote);
    if(!emote_ptr){
        ESP_LOGW(TAG, "emote[%s] not found\n", emote);
        return NULL;
    }

    return _emote_elem_get_data(emote_ptr, index, size);
}

uint8_t* gt_role_emote_next_data(const char* role, const char* emote, uint32_t *size)
{
    gt_role_st* role_ptr = gt_role_find(role);
    if(!role_ptr){
        ESP_LOGW(TAG, "role[%s] not found\n", role);
        return NULL;
    }

    gt_emote_st* emote_ptr = _emote_fine(role_ptr, emote);
    if(!emote_ptr){
        ESP_LOGW(TAG, "emote[%s] not found\n", emote);
        return NULL;
    }

    return _emote_elem_get_data(emote_ptr, emote_ptr->pos + 1, size);
}

uint8_t* gt_role_emote_prev_data(const char* role, const char* emote, uint32_t *size)
{
    gt_role_st* role_ptr = gt_role_find(role);
    if(!role_ptr){
        ESP_LOGW(TAG, "role[%s] not found\n", role);
        return NULL;
    }

    gt_emote_st* emote_ptr = _emote_fine(role_ptr, emote);
    if(!emote_ptr){
        ESP_LOGW(TAG, "emote[%s] not found\n", emote);
        return NULL;
    }

    return _emote_elem_get_data(emote_ptr, emote_ptr->pos + emote_ptr->count - 1, size);
}

uint32_t gt_rolr_emote_get_count(const char* role, const char* emote)
{
    gt_role_st* role_ptr = gt_role_find(role);
    if(!role_ptr){
        ESP_LOGW(TAG, "role[%s] not found\n", role);
        return 0;
    }

    gt_emote_st* emote_ptr = _emote_fine(role_ptr, emote);
    if(!emote_ptr){
        ESP_LOGW(TAG, "emote[%s] not found\n", emote);
        return 0;
    }

    return emote_ptr->count;
}


void gt_role_updata_emote_http(const char* role, const char* emote, uint32_t index)
{
    gt_role_st* role_ptr = gt_role_find(role);
    if(!role_ptr){
        ESP_LOGW(TAG, "role[%s] not found\n", role);
        return;
    }

    gt_emote_st* emote_ptr = _emote_fine(role_ptr, emote);
    if(!emote_ptr){
        ESP_LOGW(TAG, "emote[%s] not found\n", emote);
        return;
    }

    _emote_elem_updata_http(emote_ptr, index);
}

void gt_role_updata_emote_http_all(const char* role, const char* emote)
{
    gt_role_st* role_ptr = gt_role_find(role);
    if(!role_ptr){
        ESP_LOGW(TAG, "role[%s] not found\n", role);
        return;
    }

    gt_emote_st* emote_ptr = _emote_fine(role_ptr, emote);
    if(!emote_ptr){
        ESP_LOGW(TAG, "emote[%s] not found\n", emote);
        return;
    }

    if(!emote_ptr->elems){
        return;
    }

    for(uint32_t i = 0; i < emote_ptr->count; ++i)
    {
        _emote_elem_updata_http(emote_ptr, i);
    }
}



void gt_role_list_printf(void)
{
    gt_role_list_st* list = &_role_list;
    printf("-------------->> role list <<--------------\n");
    printf("role count: %d\n", list->count);
    uint32_t i = 0;

    for(i = 0; i < list->count; ++i)
    {
        printf("\t-------------->> role  <<--------------\n");
        printf("\t[%d]role name: [%s]\n", i , list->roles[i]->name);
        printf("\t[%d]role count: %d\n", i , list->roles[i]->count);
        gt_emote_st** emotes = list->roles[i]->emotes;
        uint32_t j = 0;
        for(j = 0; j < list->roles[i]->count; ++j)
        {
            printf("\t\t-------------->> emote  <<--------------\n");
            printf("\t\t[%d]emote name: [%s]\n", j , emotes[j]->name);
            printf("\t\t[%d]emote url: [%s]\n", j , emotes[j]->url);
            printf("\t\t[%d]emote count: %d\n", j , emotes[j]->count);
            printf("\t\t[%d]emote pos: %d\n", j , emotes[j]->pos);
            gt_emote_elem_st** elems = emotes[j]->elems;

            uint32_t k = 0;
            for(k = 0; k < emotes[j]->count; ++k){
                printf("\t\t\t-------------->> elems  <<--------------\n");
                printf("\t\t\t[%d]elem data: %p\n", k , elems[k]->data);
                printf("\t\t\t[%d]elem size: %d\n", k , elems[k]->size);
                printf("\t\t\t[%d]elem count: %d\n", k , elems[k]->count);
                printf("\t\t\t[%d]elem width: %d\n", k , elems[k]->width);
                printf("\t\t\t[%d]elem height: %d\n", k , elems[k]->height);
                printf("\t\t\t[%d]elem state: %d\n", k , elems[k]->state);
            }
            printf("\t\t\t-------------->> elems  <<--------------\n");
        }
        printf("\t\t-------------->> emote  <<--------------\n\n");
    }
    printf("\t-------------->> role  <<--------------\n\n");
    printf("-------------->> role list <<--------------\n\n");
}

/* end of file ----------------------------------------------------------*/


