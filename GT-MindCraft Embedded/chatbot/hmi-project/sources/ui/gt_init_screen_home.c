#include "gt_ui.h"
#include "gt_font_config.h"


/** screen_home */
gt_obj_st * screen_home = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * player1 = NULL;
static gt_obj_st * lab2Copy = NULL;

static void screen_home_0_cb(gt_event_st * e) {
	
}

static void img1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_SETUP, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void lab1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_RECORDING, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void player1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_RECORDING, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_home(void)
{
	screen_home = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_home, gt_color_hex(0x000000));


	

	/** img1 */
	img1 = gt_img_create(screen_home);
	gt_obj_set_pos(img1, 183, 17);
	gt_obj_set_size(img1, 26, 26);
	gt_img_set_src(img1, ".:img_1723686274619_26x26.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn1 */
	imgbtn1 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn1, 38, 253);
	gt_obj_set_size(imgbtn1, 170, 44);
	gt_imgbtn_set_src(imgbtn1, ".:img_aj_170x44.png");

	

	/** lab1 */
	lab1 = gt_label_create(screen_home);
	gt_obj_set_pos(lab1, 46, 257);
	gt_obj_set_size(lab1, 154, 37);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_family(lab1, gray_black_16);
	gt_label_set_font_cjk(lab1, 0);
	gt_label_set_font_align(lab1, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab1, "请长按说话");
	gt_obj_add_event_cb(lab1, lab1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** player1 */
	/** 等待 */
	player1 = gt_player_create(screen_home);
	gt_obj_set_pos(player1, 4, 78);
	gt_obj_set_size(player1, 228, 117);
	gt_player_add_item(player1, ".:img_0_00_3_228x117.jpg", sizeof(".:img_0_00_3_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_01_228x117.jpg", sizeof(".:img_0_01_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_02_228x117.jpg", sizeof(".:img_0_02_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_03_228x117.jpg", sizeof(".:img_0_03_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_05_10_228x117.jpg", sizeof(".:img_0_05_10_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_06_228x117.jpg", sizeof(".:img_0_06_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_07_228x117.jpg", sizeof(".:img_0_07_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_08_228x117.jpg", sizeof(".:img_0_08_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_09_228x117.jpg", sizeof(".:img_0_09_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_10_228x117.jpg", sizeof(".:img_0_10_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_11_228x117.jpg", sizeof(".:img_0_11_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_12_228x117.jpg", sizeof(".:img_0_12_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_13_228x117.jpg", sizeof(".:img_0_13_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_14_228x117.jpg", sizeof(".:img_0_14_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_15_7_228x117.jpg", sizeof(".:img_0_15_7_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_16_228x117.jpg", sizeof(".:img_0_16_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_17_228x117.jpg", sizeof(".:img_0_17_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_18_228x117.jpg", sizeof(".:img_0_18_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_19_12_228x117.jpg", sizeof(".:img_0_19_12_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_20_228x117.jpg", sizeof(".:img_0_20_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_21_228x117.jpg", sizeof(".:img_0_21_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_22_228x117.jpg", sizeof(".:img_0_22_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_23_10_228x117.jpg", sizeof(".:img_0_23_10_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_24_228x117.jpg", sizeof(".:img_0_24_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_25_228x117.jpg", sizeof(".:img_0_25_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_26_9_228x117.jpg", sizeof(".:img_0_26_9_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_27_228x117.jpg", sizeof(".:img_0_27_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_28_228x117.jpg", sizeof(".:img_0_28_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_29_9_228x117.jpg", sizeof(".:img_0_29_9_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_30_228x117.jpg", sizeof(".:img_0_30_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_31_228x117.jpg", sizeof(".:img_0_31_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_32_228x117.jpg", sizeof(".:img_0_32_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_33_8_228x117.jpg", sizeof(".:img_0_33_8_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_34_228x117.jpg", sizeof(".:img_0_34_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_35_3_228x117.jpg", sizeof(".:img_0_35_3_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_36_228x117.jpg", sizeof(".:img_0_36_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_37_228x117.jpg", sizeof(".:img_0_37_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_38_228x117.jpg", sizeof(".:img_0_38_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_39_228x117.jpg", sizeof(".:img_0_39_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_40_228x117.jpg", sizeof(".:img_0_40_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_41_228x117.jpg", sizeof(".:img_0_41_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_42_228x117.jpg", sizeof(".:img_0_42_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_43_228x117.jpg", sizeof(".:img_0_43_228x117.jpg"));
	gt_player_add_item(player1, ".:img_0_44_6_228x117.jpg", sizeof(".:img_0_44_6_228x117.jpg"));
	gt_player_set_type(player1, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player1, GT_PLAYER_MODE_LOOP);
	gt_player_set_auto_play_period(player1, 35);
	gt_player_play(player1);
	gt_obj_add_event_cb(player1, player1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab2Copy */
	lab2Copy = gt_label_create(screen_home);
	gt_obj_set_pos(lab2Copy, 25, 215);
	gt_obj_set_size(lab2Copy, 187, 30);
	gt_label_set_font_color(lab2Copy, gt_color_hex(0x5b8ad9));
	gt_label_set_font_family(lab2Copy, gray_black_16);
	gt_label_set_font_cjk(lab2Copy, 0);
	gt_label_set_font_align(lab2Copy, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2Copy, "正在识别，请稍等...");



	return screen_home;
}

