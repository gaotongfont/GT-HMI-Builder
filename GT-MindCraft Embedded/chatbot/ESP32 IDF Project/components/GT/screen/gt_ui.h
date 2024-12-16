#ifndef __GT_UI_H__
#define __GT_UI_H__


#include "gt.h"
#include "gt_recording.h"
#include "gt_audio_play.h"
#include "http_send.h"
#include "gt_pipe_send.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "gt_font_config.h"
#include "audio_mem.h"
#include "wifi.h"
#include "gt_record_http.h"
#include "gt_nvs_store.h"

extern QueueHandle_t mYxQueue;
extern QueueHandle_t mYxQueue2;

extern gt_obj_st * screen_home;
extern gt_obj_st * screen_setup;
extern gt_obj_st * screen_subtitle;
extern gt_obj_st * main_interface;
extern gt_obj_st * setting_list;
extern gt_obj_st * volume_and_brightness;
extern gt_obj_st * keyboard;
extern gt_obj_st * forget_password;
extern gt_obj_st * connection_failed;
extern gt_obj_st * wifi_list;
extern gt_obj_st * History_page;
extern gt_obj_st * Function_settings;

extern ChatbotData cb_data;

extern void print_memory_info(void);

extern uint8_t selected_idx;

extern bool allow_reconnect;

void gt_ui_init(void);


gt_obj_st * gt_init_screen_home(void);
gt_obj_st * gt_init_screen_setup(void);
gt_obj_st * gt_init_screen_subtitle(void);
gt_obj_st * gt_init_main_interface(void);
gt_obj_st * gt_init_setting_list(void);
gt_obj_st * gt_init_volume_and_brightness(void);
gt_obj_st * gt_init_keyboard(void);
gt_obj_st * gt_init_forget_password(void);
gt_obj_st * gt_init_connection_failed(void);
gt_obj_st * gt_init_wifi_list(void);
gt_obj_st * gt_init_History_page(void);
gt_obj_st * gt_init_Function_settings(void);
typedef enum {
        GT_ID_SCREEN_HOME = 0,
        GT_ID_SCREEN_SETUP,
        GT_ID_SCREEN_SUBTITLE,
        GT_ID_MAIN_INTERFACE,
        GT_ID_SETTING_LIST,
        GT_ID_VOLUME_AND_BRIGHTNESS,
        GT_ID_KEYBOARD,
        GT_ID_FORGET_PASSWORD,
        GT_ID_CONNECTION_FAILED,
        GT_ID_WIFI_LIST,
        GT_ID_HISTORY_PAGE,
        GT_ID_FUNCTION_SETTINGS
} gt_scr_id_et;

typedef enum {
    AI_EMOJIS_WAITING = 0,
	AI_EMOJIS_RECORDING,
	AI_EMOJIS_SPEAKING,
    AI_EMOJIS_SYMPATHY,
    AI_EMOJIS_ENCOURAGE,
    AI_EMOJIS_HAPPY,
    AI_EMOJIS_CJ,
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
    AI_SETTING_MODEL,
    AI_SETTING_REPLY_STYLE,
}gt_ai_setting_et;



void set_items_in_listview(gt_obj_st * listview, gt_ai_setting_et option);
char* gt_vocie_id_string_get(char *timbre);
char* gt_timber_string_get(char *voice_id);
char* gt_bot_description_string_get(char *ai_name);
char* gt_mode_en_string_get(char *mode);
char* gt_mode_cn_string_get(char *mode);
char* gt_reply_style_en_string_get(char *reply_style);
char* gt_reply_style_cn_string_get(char *reply_style);

void identification_failed_ui();
void wifi_connecting_ui();
void waiting_rec_ui();
void wifi_connected_fail_ui();

void recording_exe_func(void);
void send_information_exe_func(void);
void identifying_failed_ui_in_subtitle(void);

void redraw_wifi_list();
void change_wifi_connect_tip(uint8_t flag);

#if USE_HTTP_STREAM
void update_subtitles(ReceivedAnswerData* receive_data);
#endif //!USE_HTTP_STREAM

typedef enum {
    WIFI_NO_CONNECTED = 0,
    WIFI_SIGNAL_1,
    WIFI_SIGNAL_2,
    WIFI_SIGNAL_3,
    WIFI_SIGNAL_4,
}gt_wifi_icon_status_et;

void update_wifi_icon();

gt_obj_st * _Clear_page_dialog1_init();
void set_history_in_chat();
void clear_chat_history();
gt_obj_st * _Unstable_network_dialog1_init();
void set_wifi_status_icon(gt_wifi_icon_status_et status);
#endif

