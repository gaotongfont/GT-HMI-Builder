#include "gt_ui.h"

static const char *TAG = "SCREEN_SUBTITLE";

extern audio_board_handle_t gt_board_handle;

#if USE_HTTP_STREAM
extern QueueHandle_t mYxQueue4;
extern QueueHandle_t audio_uri_queue;
#endif //!USE_HTTP_STREAM

/** screen_subtitle */
gt_obj_st * screen_subtitle = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * stupbt = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * player1 = NULL;
static gt_obj_st * Historybt = NULL;
static gt_obj_st * emptybt = NULL;
static gt_obj_st * Voicebutton3 = NULL;

void set_emojis() {
    if (cb_data.answer->emotion_value == NULL) {
        ESP_LOGE(TAG, "1111111111111111111111111111111\n");
        return;
    }
    if (strcmp(cb_data.settings->bot_name, "蔡机") == 0){
        set_emojis_in_player(player1, AI_EMOJIS_CJ);
        gt_obj_set_pos(player1, 4, 47);
	    gt_obj_set_size(player1, 228, 184);
        gt_player_set_auto_play_period(player1, 20);
        ESP_LOGE(TAG, "2222222222222222222222222222222222\n");

    } else {
        if (strcmp(cb_data.answer->emotion_value, "开心") == 0) {
            set_emojis_in_player(player1, AI_EMOJIS_HAPPY);
        } else if (strcmp(cb_data.answer->emotion_value, "同情") == 0) {
            set_emojis_in_player(player1, AI_EMOJIS_SYMPATHY);
        } else if (strcmp(cb_data.answer->emotion_value, "鼓励") == 0) {
            set_emojis_in_player(player1, AI_EMOJIS_ENCOURAGE);
        } else {
            set_emojis_in_player(player1, AI_EMOJIS_WAITING);
        }
        gt_obj_set_pos(player1, 4, 78);
	    gt_obj_set_size(player1, 228, 116);
        gt_player_set_auto_play_period(player1, 35);
        ESP_LOGE(TAG, "333333333333333333333333333333\n");

    }
}

#if USE_HTTP_STREAM
void update_subtitles(ReceivedAnswerData* receive_data) {
    if (cb_data.answer == NULL) {
        ESP_LOGE(TAG, "cb_data.answer is NULL");
        return;
    }
    // 分配内存并检查 receive_data->emotion_value 是否不为 NULL
    if (receive_data->emotion_value != NULL) {
        cb_data.answer->emotion_value = NULL;
        audio_free(cb_data.answer->emotion_value);
        cb_data.answer->emotion_value = (char *)audio_malloc(strlen(receive_data->emotion_value) + 1);
        if (cb_data.answer->emotion_value == NULL) {
            ESP_LOGE(TAG, "Failed to allocate memory for emotion_value");
            return;
        }
        strcpy(cb_data.answer->emotion_value, receive_data->emotion_value);
    }
    // 分配内存并检查 receive_data->llm_response 是否不为 NULL
    if (receive_data->llm_response != NULL) {
        cb_data.answer->llm_response = NULL;
        audio_free(cb_data.answer->llm_response);
        cb_data.answer->llm_response = (char *)audio_malloc(strlen(receive_data->llm_response) + 1);
        if (cb_data.answer->llm_response == NULL) {
            ESP_LOGE(TAG, "Failed to allocate memory for llm_response");
            return;
        }
        strcpy(cb_data.answer->llm_response, receive_data->llm_response);
    }

    cb_data.answer->audio_seconds = receive_data->audio_seconds;
    if (cb_data.answer->audio_seconds < 1)
    {
        cb_data.answer->audio_seconds = 1;
    }

    ESP_LOGI(TAG, "<<------------------cb_data.answer->emotion_value: %s\n", cb_data.answer->emotion_value);
    ESP_LOGI(TAG, "<<------------------cb_data.answer->llm_response: %s\n", cb_data.answer->llm_response);
    ESP_LOGI(TAG, "<<------------------cb_data.answer->audio_seconds: %f\n", cb_data.answer->audio_seconds);
    gt_label_set_auto_scroll_single_line(lab2, true);
    gt_label_set_text(lab2, cb_data.answer->llm_response);
    // gt_label_set_auto_scroll_total_time(lab2, cb_data.answer->audio_seconds * 1000);
    int total_time_ms = (int)(cb_data.answer->audio_seconds * 1000);
    ESP_LOGI(TAG, "------------------------total_time_ms = %d", total_time_ms);
    gt_label_set_auto_scroll_total_time(lab2, total_time_ms);
    set_emojis();
}
#endif //!USE_HTTP_STREAM

//手势左滑返回到上一个界面
static void screen_subtitle_0_cb(gt_event_st * e) {
#if USE_HTTP_STREAM
    int send_num = -1;
    xQueueReset(audio_uri_queue);
    int num = uxQueueMessagesWaiting(audio_uri_queue);
    ESP_LOGI(TAG, "Stopping HTTP connection from callback...      audio_uri_queue======  %d\n",num);

    xQueueSend(mYxQueue4, &send_num, portMAX_DELAY);

    if(gt_audio_player_state_get() == AUDIO_STATUS_RUNNING)
    {
        gt_audio_player_stop_and_prepare_next();
    }

    gt_disp_stack_go_back(1);
    audio_free(cb_data.answer->emotion_value);
    cb_data.answer->emotion_value = NULL;
    audio_free(cb_data.answer->llm_response);
    cb_data.answer->llm_response = NULL;
    cb_data.answer->audio_seconds = 0.0f;
#else //!USE_HTTP_STREAM
	gt_audio_player_pause();
	gt_disp_stack_go_back(1);
#endif //!USE_HTTP_STREAM
}

//跳转到设置界面
static void stupbt_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_SETUP, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

//跳转到主界面
static void imgbtn1_0_cb(gt_event_st * e) {
#if USE_HTTP_STREAM
    int send_num = -1;
    xQueueReset(audio_uri_queue);
    int num = uxQueueMessagesWaiting(audio_uri_queue);
    ESP_LOGI(TAG, "Stopping HTTP connection from callback...      audio_uri_queue======  %d\n",num);

    xQueueSend(mYxQueue4, &send_num, portMAX_DELAY);
    if(gt_audio_player_state_get() == AUDIO_STATUS_RUNNING)
    {
        gt_audio_player_stop_and_prepare_next();
    }

    gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 50, 0, true);
    audio_free(cb_data.answer->tts_audio);
    cb_data.answer->tts_audio = NULL;
    audio_free(cb_data.answer->emotion_value);
    cb_data.answer->emotion_value = NULL;
    audio_free(cb_data.answer->llm_response);
    cb_data.answer->llm_response = NULL;
    cb_data.answer->audio_seconds = 0.0f;
#else //!USE_HTTP_STREAM
	gt_audio_player_pause();
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
#endif //!USE_HTTP_STREAM
}

static void Historybt_0_cb(gt_event_st * e) {
    set_history_in_chat();
}

static void emptybt_0_cb(gt_event_st * e) {
    // clear_chat_history();
    _Clear_page_dialog1_init();
}

static void speaking_ui_in_subtitle(void) {
    gt_label_set_text(lab2, "正在说话...");
    set_emojis_in_player(player1, AI_EMOJIS_RECORDING);
}
static void identifying_ui_in_subtitle(void) {
    gt_label_set_text(lab2, "正在识别...");
    set_emojis_in_player(player1, AI_EMOJIS_HAPPY);
}
void identifying_failed_ui_in_subtitle(void) {
    gt_label_set_text(lab2, "识别失败，请重试");
    set_emojis_in_player(player1, AI_EMOJIS_SYMPATHY);
}

static void voice_btn_recording_cb(gt_event_st * e) {
    speaking_ui_in_subtitle();
    recording_exe_func();
}

static void voice_btn_send_information_cb(gt_event_st * e) {
    identifying_ui_in_subtitle();
    send_information_exe_func();
}

gt_obj_st * gt_init_screen_subtitle(void)
{
	screen_subtitle = gt_obj_create(NULL);
	gt_obj_add_event_cb(screen_subtitle, screen_subtitle_0_cb, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
	gt_screen_set_bgcolor(screen_subtitle, gt_color_hex(0x000000));

	/** img2 */
	img2 = gt_img_create(screen_subtitle);
	gt_obj_set_pos(img2, 2, 217);
	gt_obj_set_size(img2, 233, 102);
	gt_obj_set_opa(img2, GT_OPA_65);
	gt_img_set_src(img2, "f:img_u10_233x102.png");


	/** lab2 */
	lab2 = gt_label_create(screen_subtitle);
	gt_obj_set_pos(lab2, 30, 245);
	gt_obj_set_size(lab2, 187, 30);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_family(lab2, gray_black_20);
	gt_label_set_font_cjk(lab2, 0);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_auto_scroll_single_line(lab2, true);
    if (cb_data.answer->llm_response != NULL) {
        gt_label_set_text(lab2, cb_data.answer->llm_response);
    } else {
        gt_label_set_text(lab2, "");
    }
    if (cb_data.answer->audio_seconds < 1)
    {
        cb_data.answer->audio_seconds = 1;
    }
    // gt_label_set_auto_scroll_total_time(lab2, cb_data.answer->audio_seconds * 1000);
    int total_time_ms = (int)(cb_data.answer->audio_seconds * 1000);
    ESP_LOGI(TAG, "------------------------total_time_ms = %d", total_time_ms);
    gt_label_set_auto_scroll_total_time(lab2, total_time_ms);

	/** rect1 */
	gt_obj_st* rect1 = gt_rect_create(screen_subtitle);
	gt_obj_set_pos(rect1, 180, 0);
	gt_obj_set_size(rect1, 60, 40);
	gt_obj_set_opa(rect1, GT_OPA_TRANSP);
	gt_obj_add_event_cb(rect1, stupbt_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	/** stupbt */
	/** 设置 */
	stupbt = gt_img_create(rect1);
	gt_obj_set_pos(stupbt, 189, 7);
	gt_obj_set_size(stupbt, 24, 24);
	gt_img_set_src(stupbt, "f:img_Set_up_24x24.png");
    gt_obj_set_touch_parent(stupbt, true);
	/** Historybt */
	/** 历史记录 */
	Historybt = gt_imgbtn_create(screen_subtitle);
	gt_obj_set_pos(Historybt, 64, 8);
	gt_obj_set_size(Historybt, 22, 19);
	gt_imgbtn_set_src(Historybt, "f:img_History_22x19.png");
	gt_imgbtn_set_src_press(Historybt, "f:img_History2_22x19.png");
	gt_obj_add_event_cb(Historybt, Historybt_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** emptybt */
	/** 清空 */
	emptybt = gt_imgbtn_create(screen_subtitle);
	gt_obj_set_pos(emptybt, 129, 9);
	gt_obj_set_size(emptybt, 18, 18);
	gt_imgbtn_set_src(emptybt, "f:img_empty_18x18.png");
	gt_imgbtn_set_src_press(emptybt, "f:img_empty2_18x18.png");
	gt_obj_add_event_cb(emptybt, emptybt_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	/** rect2 */
	gt_obj_st* rect2 = gt_rect_create(screen_subtitle);
	gt_obj_set_pos(rect2, 0, 0);
	gt_obj_set_size(rect2, 35, 30);
	gt_obj_set_opa(rect2, GT_OPA_TRANSP);
	gt_obj_add_event_cb(rect2, imgbtn1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	/** imgbtn1 */
	imgbtn1 = gt_img_create(rect2);
	gt_obj_set_pos(imgbtn1, 13, 10);
	gt_obj_set_size(imgbtn1, 16, 16);
	gt_img_set_src(imgbtn1, "f:img_fh_16x16.png");
	gt_obj_set_touch_parent(imgbtn1, true);


	/** player1 */
	/** 说话 */
	player1 = gt_player_create(screen_subtitle);
	gt_player_set_type(player1, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player1, GT_PLAYER_MODE_LOOP);
	gt_player_set_auto_play_period(player1, 35);
    //根据返回的情绪值设置不同的表情
    set_emojis();


	/** rect1 */
	rect1 = gt_rect_create(screen_subtitle);
	gt_obj_set_pos(rect1, 31, 264);
	gt_obj_set_size(rect1, 176, 49);
	gt_obj_set_opa(rect1, GT_OPA_0);
	gt_rect_set_radius(rect1, 0);
	gt_rect_set_bg_color(rect1, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect1, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 0);
    gt_obj_set_fixed(rect1, false);
    gt_obj_add_event_cb(rect1, voice_btn_recording_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
    gt_obj_add_event_cb(rect1, voice_btn_send_information_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
    gt_obj_add_event_cb(rect1, voice_btn_send_information_cb, GT_EVENT_TYPE_INPUT_SCROLL_END, NULL);
    // gt_obj_add_event_cb(rect1, voice_btn_cancel_recording_cb, GT_EVENT_TYPE_INPUT_PRESS_LOST, NULL);

	/** Voicebutton3 */
	/** 语音键 */
	Voicebutton3 = gt_imgbtn_create(rect1);
	gt_obj_set_pos(Voicebutton3, 107, 283);
	gt_obj_set_size(Voicebutton3, 21, 30);
	gt_imgbtn_set_src(Voicebutton3, "f:img_Voicebutton_21x30.png");
    gt_obj_set_touch_parent(Voicebutton3, true);


	return screen_subtitle;
}

