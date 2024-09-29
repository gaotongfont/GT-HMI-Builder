#include "gt_ui.h"
#include "gt_font_config.h"


/** screen_recording */
gt_obj_st * screen_recording = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * player1Copy = NULL;
static gt_obj_st * player1 = NULL;

static void screen_recording_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

static void img1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_SETUP, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void player1Copy_0_cb(gt_event_st * e) {
	
}

static void player1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_JZ, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_recording(void)
{
	screen_recording = gt_obj_create(NULL);
	gt_obj_add_event_cb(screen_recording, screen_recording_0_cb, GT_EVENT_TYPE_INPUT_HOME_GESTURE_RIGHT, NULL);
	gt_screen_set_bgcolor(screen_recording, gt_color_hex(0x000000));


	

	/** imgbtn1 */
	imgbtn1 = gt_imgbtn_create(screen_recording);
	gt_obj_set_pos(imgbtn1, 38, 253);
	gt_obj_set_size(imgbtn1, 170, 44);
	gt_imgbtn_set_src(imgbtn1, ".:img_aj_170x44.png");

	

	/** lab2 */
	lab2 = gt_label_create(screen_recording);
	gt_obj_set_pos(lab2, 25, 215);
	gt_obj_set_size(lab2, 187, 30);
	gt_label_set_font_color(lab2, gt_color_hex(0x5b8ad9));
	gt_label_set_font_family(lab2, gray_black_16);
	gt_label_set_font_cjk(lab2, 0);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, "松手发送，上移取消");

	

	/** img1 */
	img1 = gt_img_create(screen_recording);
	gt_obj_set_pos(img1, 183, 17);
	gt_obj_set_size(img1, 24, 24);
	gt_img_set_src(img1, ".:img_1723686274619_24x24.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** player1Copy */
	/** 语音 */
	player1Copy = gt_player_create(screen_recording);
	gt_obj_set_pos(player1Copy, 4, 78);
	gt_obj_set_size(player1Copy, 222, 112);
	gt_player_add_item(player1Copy, ".:img_01_01_2_222x112.jpg", sizeof(".:img_01_01_2_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_02_222x112.jpg", sizeof(".:img_01_02_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_03_222x112.jpg", sizeof(".:img_01_03_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_04_222x112.jpg", sizeof(".:img_01_04_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_05_222x112.jpg", sizeof(".:img_01_05_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_06_222x112.jpg", sizeof(".:img_01_06_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_07_222x112.jpg", sizeof(".:img_01_07_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_08_222x112.jpg", sizeof(".:img_01_08_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_09_222x112.jpg", sizeof(".:img_01_09_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_10_222x112.jpg", sizeof(".:img_01_10_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_11_222x112.jpg", sizeof(".:img_01_11_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_12_222x112.jpg", sizeof(".:img_01_12_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_13_222x112.jpg", sizeof(".:img_01_13_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_14_222x112.jpg", sizeof(".:img_01_14_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_15_222x112.jpg", sizeof(".:img_01_15_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_16_222x112.jpg", sizeof(".:img_01_16_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_17_222x112.jpg", sizeof(".:img_01_17_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_18_222x112.jpg", sizeof(".:img_01_18_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_19_222x112.jpg", sizeof(".:img_01_19_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_20_222x112.jpg", sizeof(".:img_01_20_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_21_222x112.jpg", sizeof(".:img_01_21_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_22_222x112.jpg", sizeof(".:img_01_22_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_23_222x112.jpg", sizeof(".:img_01_23_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_24_222x112.jpg", sizeof(".:img_01_24_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_25_222x112.jpg", sizeof(".:img_01_25_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_26_222x112.jpg", sizeof(".:img_01_26_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_27_222x112.jpg", sizeof(".:img_01_27_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_28_222x112.jpg", sizeof(".:img_01_28_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_30_222x112.jpg", sizeof(".:img_01_30_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_31_222x112.jpg", sizeof(".:img_01_31_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_32_222x112.jpg", sizeof(".:img_01_32_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_33_222x112.jpg", sizeof(".:img_01_33_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_34_222x112.jpg", sizeof(".:img_01_34_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_35_222x112.jpg", sizeof(".:img_01_35_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_36_222x112.jpg", sizeof(".:img_01_36_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_37_6_222x112.jpg", sizeof(".:img_01_37_6_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_43_222x112.jpg", sizeof(".:img_01_43_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_44_222x112.jpg", sizeof(".:img_01_44_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_45_222x112.jpg", sizeof(".:img_01_45_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_46_222x112.jpg", sizeof(".:img_01_46_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_47_222x112.jpg", sizeof(".:img_01_47_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_48_222x112.jpg", sizeof(".:img_01_48_222x112.jpg"));
	gt_player_add_item(player1Copy, ".:img_01_29_t2_222x112.jpg", sizeof(".:img_01_29_t2_222x112.jpg"));
	gt_player_set_type(player1Copy, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player1Copy, GT_PLAYER_MODE_LOOP);
	gt_player_set_auto_play_period(player1Copy, 35);
	gt_player_play(player1Copy);
	gt_obj_add_event_cb(player1Copy, player1Copy_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** player1 */
	player1 = gt_player_create(screen_recording);
	gt_obj_set_pos(player1, 85, 261);
	gt_obj_set_size(player1, 80, 30);
	gt_player_add_item(player1, ".:img_09_00_80x30.png", sizeof(".:img_09_00_80x30.png"));
	gt_player_add_item(player1, ".:img_09_01_80x30.png", sizeof(".:img_09_01_80x30.png"));
	gt_player_add_item(player1, ".:img_09_02_80x30.png", sizeof(".:img_09_02_80x30.png"));
	gt_player_add_item(player1, ".:img_09_03_80x30.png", sizeof(".:img_09_03_80x30.png"));
	gt_player_add_item(player1, ".:img_09_04_80x30.png", sizeof(".:img_09_04_80x30.png"));
	gt_player_add_item(player1, ".:img_09_05_80x30.png", sizeof(".:img_09_05_80x30.png"));
	gt_player_add_item(player1, ".:img_09_06_80x30.png", sizeof(".:img_09_06_80x30.png"));
	gt_player_add_item(player1, ".:img_09_07_80x30.png", sizeof(".:img_09_07_80x30.png"));
	gt_player_add_item(player1, ".:img_09_08_80x30.png", sizeof(".:img_09_08_80x30.png"));
	gt_player_add_item(player1, ".:img_09_09_80x30.png", sizeof(".:img_09_09_80x30.png"));
	gt_player_add_item(player1, ".:img_09_10_80x30.png", sizeof(".:img_09_10_80x30.png"));
	gt_player_add_item(player1, ".:img_09_11_80x30.png", sizeof(".:img_09_11_80x30.png"));
	gt_player_add_item(player1, ".:img_09_12_80x30.png", sizeof(".:img_09_12_80x30.png"));
	gt_player_add_item(player1, ".:img_09_13_80x30.png", sizeof(".:img_09_13_80x30.png"));
	gt_player_add_item(player1, ".:img_09_14_80x30.png", sizeof(".:img_09_14_80x30.png"));
	gt_player_add_item(player1, ".:img_09_15_80x30.png", sizeof(".:img_09_15_80x30.png"));
	gt_player_add_item(player1, ".:img_09_16_80x30.png", sizeof(".:img_09_16_80x30.png"));
	gt_player_add_item(player1, ".:img_09_17_80x30.png", sizeof(".:img_09_17_80x30.png"));
	gt_player_add_item(player1, ".:img_09_18_80x30.png", sizeof(".:img_09_18_80x30.png"));
	gt_player_add_item(player1, ".:img_09_19_80x30.png", sizeof(".:img_09_19_80x30.png"));
	gt_player_set_type(player1, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player1, GT_PLAYER_MODE_LOOP);
	gt_player_set_auto_play_period(player1, 35);
	gt_player_play(player1);
	gt_obj_add_event_cb(player1, player1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	return screen_recording;
}

