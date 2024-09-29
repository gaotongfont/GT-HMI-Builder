#include "gt_ui.h"
#include "gt_font_config.h"


/** screen_jz */
gt_obj_st * screen_jz = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * player2 = NULL;
static gt_obj_st * player1Copy = NULL;
static gt_obj_st * lab2Copy = NULL;

static void screen_home_0_cb(gt_event_st * e) {
	
}

static void img1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_SETUP, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void player2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_SUBTITLE, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void player1Copy_0_cb(gt_event_st * e) {
	
}

gt_obj_st * gt_init_screen_jz(void)
{
	screen_jz = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_jz, gt_color_hex(0x000000));


	

	/** img1 */
	img1 = gt_img_create(screen_jz);
	gt_obj_set_pos(img1, 183, 17);
	gt_obj_set_size(img1, 26, 26);
	gt_img_set_src(img1, ".:img_1723686274619_26x26.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn1 */
	imgbtn1 = gt_imgbtn_create(screen_jz);
	gt_obj_set_pos(imgbtn1, 38, 253);
	gt_obj_set_size(imgbtn1, 170, 44);
	gt_imgbtn_set_src(imgbtn1, ".:img_aj_170x44.png");

	

	/** player2 */
	player2 = gt_player_create(screen_jz);
	gt_obj_set_pos(player2, 90, 264);
	gt_obj_set_size(player2, 60, 21);
	gt_player_add_item(player2, ".:img_05_00_60x21.png", sizeof(".:img_05_00_60x21.png"));
	gt_player_add_item(player2, ".:img_05_01_60x21.png", sizeof(".:img_05_01_60x21.png"));
	gt_player_add_item(player2, ".:img_05_02_60x21.png", sizeof(".:img_05_02_60x21.png"));
	gt_player_add_item(player2, ".:img_05_03_60x21.png", sizeof(".:img_05_03_60x21.png"));
	gt_player_add_item(player2, ".:img_05_04_60x21.png", sizeof(".:img_05_04_60x21.png"));
	gt_player_add_item(player2, ".:img_05_05_60x21.png", sizeof(".:img_05_05_60x21.png"));
	gt_player_add_item(player2, ".:img_05_06_60x21.png", sizeof(".:img_05_06_60x21.png"));
	gt_player_add_item(player2, ".:img_05_07_60x21.png", sizeof(".:img_05_07_60x21.png"));
	gt_player_add_item(player2, ".:img_05_08_60x21.png", sizeof(".:img_05_08_60x21.png"));
	gt_player_add_item(player2, ".:img_05_09_60x21.png", sizeof(".:img_05_09_60x21.png"));
	gt_player_add_item(player2, ".:img_05_10_60x21.png", sizeof(".:img_05_10_60x21.png"));
	gt_player_add_item(player2, ".:img_05_11_60x21.png", sizeof(".:img_05_11_60x21.png"));
	gt_player_add_item(player2, ".:img_05_12_60x21.png", sizeof(".:img_05_12_60x21.png"));
	gt_player_add_item(player2, ".:img_05_13_60x21.png", sizeof(".:img_05_13_60x21.png"));
	gt_player_add_item(player2, ".:img_05_14_60x21.png", sizeof(".:img_05_14_60x21.png"));
	gt_player_add_item(player2, ".:img_05_15_60x21.png", sizeof(".:img_05_15_60x21.png"));
	gt_player_add_item(player2, ".:img_05_16_60x21.png", sizeof(".:img_05_16_60x21.png"));
	gt_player_add_item(player2, ".:img_05_17_60x21.png", sizeof(".:img_05_17_60x21.png"));
	gt_player_add_item(player2, ".:img_05_18_60x21.png", sizeof(".:img_05_18_60x21.png"));
	gt_player_add_item(player2, ".:img_05_19_60x21.png", sizeof(".:img_05_19_60x21.png"));
	gt_player_add_item(player2, ".:img_05_20_60x21.png", sizeof(".:img_05_20_60x21.png"));
	gt_player_add_item(player2, ".:img_05_21_60x21.png", sizeof(".:img_05_21_60x21.png"));
	gt_player_add_item(player2, ".:img_05_22_60x21.png", sizeof(".:img_05_22_60x21.png"));
	gt_player_add_item(player2, ".:img_05_23_60x21.png", sizeof(".:img_05_23_60x21.png"));
	gt_player_set_type(player2, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player2, GT_PLAYER_MODE_LOOP);
	gt_player_set_auto_play_period(player2, 35);
	gt_player_play(player2);
	gt_obj_add_event_cb(player2, player2_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	/** player1Copy */
	/** 开心 */
	player1Copy = gt_player_create(screen_jz);
	gt_obj_set_pos(player1Copy, 4, 78);
	gt_obj_set_size(player1Copy, 225, 116);
	gt_player_add_item(player1Copy, ".:img_03_06_6_225x116.jpg", sizeof(".:img_03_06_6_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_07_225x116.jpg", sizeof(".:img_03_07_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_08_225x116.jpg", sizeof(".:img_03_08_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_09_225x116.jpg", sizeof(".:img_03_09_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_10_225x116.jpg", sizeof(".:img_03_10_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_11_225x116.jpg", sizeof(".:img_03_11_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_12_225x116.jpg", sizeof(".:img_03_12_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_13_225x116.jpg", sizeof(".:img_03_13_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_14_225x116.jpg", sizeof(".:img_03_14_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_15_225x116.jpg", sizeof(".:img_03_15_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_16_225x116.jpg", sizeof(".:img_03_16_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_17_225x116.jpg", sizeof(".:img_03_17_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_18_225x116.jpg", sizeof(".:img_03_18_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_19_225x116.jpg", sizeof(".:img_03_19_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_20_225x116.jpg", sizeof(".:img_03_20_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_21_225x116.jpg", sizeof(".:img_03_21_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_22_225x116.jpg", sizeof(".:img_03_22_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_23_225x116.jpg", sizeof(".:img_03_23_225x116.jpg"));
	gt_player_add_item(player1Copy, ".:img_03_24_7_225x116.jpg", sizeof(".:img_03_24_7_225x116.jpg"));
	gt_player_set_type(player1Copy, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player1Copy, GT_PLAYER_MODE_LOOP);
	gt_player_set_auto_play_period(player1Copy, 35);
	gt_player_play(player1Copy);
	gt_obj_add_event_cb(player1Copy, player1Copy_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab2Copy */
	lab2Copy = gt_label_create(screen_jz);
	gt_obj_set_pos(lab2Copy, 25, 215);
	gt_obj_set_size(lab2Copy, 187, 30);
	gt_label_set_font_color(lab2Copy, gt_color_hex(0x5b8ad9));
	gt_label_set_font_family(lab2Copy, gray_black_16);
	gt_label_set_font_cjk(lab2Copy, 0);
	gt_label_set_font_align(lab2Copy, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2Copy, "正在思考，请稍等");



	return screen_jz;
}

