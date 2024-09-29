#include "gt_ui.h"

static const char *TAG = "SCREEN_SUBTITLE";

extern audio_board_handle_t gt_board_handle;

/** screen_subtitle */
gt_obj_st * screen_subtitle = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * player1 = NULL;

//手势左滑返回到上一个界面
static void screen_subtitle_0_cb(gt_event_st * e) {
	gt_audio_player_pause();
	gt_disp_stack_go_back(1);
}

//跳转到设置界面
static void img1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_SETUP, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

//跳转到主界面
static void imgbtn1_0_cb(gt_event_st * e) {
	gt_audio_player_pause();
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}


gt_obj_st * gt_init_screen_subtitle(void)
{
	screen_subtitle = gt_obj_create(NULL);
	gt_obj_add_event_cb(screen_subtitle, screen_subtitle_0_cb, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
	gt_screen_set_bgcolor(screen_subtitle, gt_color_hex(0x000000));

	/** img2 */
	img2 = gt_img_create(screen_subtitle);
	gt_obj_set_pos(img2, 3, 220);
	gt_obj_set_size(img2, 230, 97);
	gt_obj_set_opa(img2, GT_OPA_65);
	gt_img_set_src(img2, "f:img_10_230x97.png");



	/** lab2 */
	lab2 = gt_label_create(screen_subtitle);
	gt_obj_set_pos(lab2, 26, 265);
	gt_obj_set_size(lab2, 192, 30);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_family(lab2, 1);
	gt_label_set_font_cjk(lab2, 0);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, cb_data.answer->llm_response);
    gt_label_set_auto_scroll_single_line(lab2, true);
    gt_label_set_auto_scroll_total_time(lab2, cb_data.answer->audio_seconds * 1000);

	/** rect1 */
	gt_obj_st* rect1 = gt_rect_create(screen_subtitle);
	gt_obj_set_pos(rect1, 200, 0);
	gt_obj_set_size(rect1, 40, 40);
	gt_obj_set_opa(rect1, GT_OPA_TRANSP);
	gt_obj_add_event_cb(rect1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	/** img1 */
	img1 = gt_img_create(rect1);
	gt_obj_set_pos(img1, 206, 7);
	gt_obj_set_size(img1, 26, 26);
	gt_img_set_src(img1, "f:img_1723686274619_26x26.png");
	gt_obj_set_touch_parent(img1, true);

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
	gt_obj_set_pos(player1, 4, 84);
	gt_obj_set_size(player1, 228, 116);
	gt_player_set_type(player1, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player1, GT_PLAYER_MODE_LOOP);
	gt_player_set_auto_play_period(player1, 35);
    //根据返回的情绪值设置不同的表情
    if (strcmp(cb_data.answer->emotion_value, "开心") == 0) {
        set_emojis_in_player(player1, AI_EMOJIS_HAPPY);
    } else if (strcmp(cb_data.answer->emotion_value, "同情") == 0) {
	    set_emojis_in_player(player1, AI_EMOJIS_SYMPATHY);
    } else if (strcmp(cb_data.answer->emotion_value, "鼓励") == 0) {
	    set_emojis_in_player(player1, AI_EMOJIS_ENCOURAGE);
    } else {
        // set_emojis_in_player(player1, AI_EMOJIS_WAITING);
	    set_emojis_in_player(player1, AI_EMOJIS_SPEAKING);
    }

    ESP_LOGI(TAG, "--------------start play wav");
    ESP_LOGI(TAG, "------------------cb_data.answer->asr_content: %s\n", cb_data.answer->asr_content);
    ESP_LOGI(TAG, "------------------cb_data.answer->llm_response: %s\n", cb_data.answer->llm_response);
    ESP_LOGI(TAG, "------------------cb_data.answer->tts_audio: %s\n", cb_data.answer->tts_audio);
    ESP_LOGI(TAG, "------------------cb_data.answer->emotion_value: %s\n", cb_data.answer->emotion_value);
    ESP_LOGI(TAG, "------------------cb_data.answer->audio_seconds: %f\n", cb_data.answer->audio_seconds);

	return screen_subtitle;
}

