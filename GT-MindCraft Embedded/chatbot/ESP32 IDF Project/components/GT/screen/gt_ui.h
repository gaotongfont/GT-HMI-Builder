#ifndef __GT_UI_H__
#define __GT_UI_H__


#include "gt.h"
#include "gt_recording.h"
#include "gt_audio_play.h"
#include "http_send.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "gt_font_config.h"

extern QueueHandle_t mYxQueue;
extern QueueHandle_t mYxQueue2;

extern gt_obj_st * screen_home;
extern gt_obj_st * screen_setup;
extern gt_obj_st * screen_subtitle;

extern ChatbotData cb_data;


void gt_ui_init(void);


gt_obj_st * gt_init_screen_home(void);
gt_obj_st * gt_init_screen_setup(void);
gt_obj_st * gt_init_screen_subtitle(void);

typedef enum {
        GT_ID_SCREEN_HOME = 0,
        GT_ID_SCREEN_SETUP,
        GT_ID_SCREEN_SUBTITLE,
} gt_scr_id_et;

typedef enum {
    AI_EMOJIS_WAITING = 0,
	AI_EMOJIS_RECORDING,
	AI_EMOJIS_SPEAKING,
    AI_EMOJIS_SYMPATHY,
    AI_EMOJIS_ENCOURAGE,
    AI_EMOJIS_HAPPY,
    AI_ANIM_AUDIO,
    AI_ANIM_SMILE,
    AI_ANIM_TOTAL,
}gt_ai_emojis_et;

void set_emojis_in_player(gt_obj_st * obj, gt_ai_emojis_et emojis);

typedef enum {
    AI_SETTING_NONE = 0,
    AI_SETTING_AGE,
	AI_SETTING_ROLE,
	AI_SETTING_CHAR,
	AI_SETTING_TIMBRE,
	AI_SETTING_AI_NAME,
}gt_ai_setting_et;



void set_items_in_listview(gt_obj_st * listview, gt_ai_setting_et option);
char* gt_vocie_id_string_get(char *timbre);
char* gt_timber_string_get(char *voice_id);
void identification_failed_ui();
void wifi_connecting_ui();
void waiting_rec_ui();
void wifi_connected_fail_ui();
#endif

