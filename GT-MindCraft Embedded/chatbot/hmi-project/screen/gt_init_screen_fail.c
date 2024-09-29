#include "gt_ui.h"
#include "gt_font_config.h"


/** screen_fail */
gt_obj_st * screen_fail = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * player1 = NULL;
static gt_obj_st * lab2Copy = NULL;
static gt_obj_st * lab1Copy = NULL;

static void screen_home_0_cb(gt_event_st * e) {
	
}

static void img1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_SETUP, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void player1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_RECORDING, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void lab1Copy_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_RECORDING, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_fail(void)
{
	screen_fail = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_fail, gt_color_hex(0x000000));


	

	/** img1 */
	img1 = gt_img_create(screen_fail);
	gt_obj_set_pos(img1, 183, 17);
	gt_obj_set_size(img1, 26, 26);
	gt_img_set_src(img1, "f:img_1723686274619_26x26.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn1 */
	imgbtn1 = gt_imgbtn_create(screen_fail);
	gt_obj_set_pos(imgbtn1, 38, 253);
	gt_obj_set_size(imgbtn1, 170, 44);
	gt_imgbtn_set_src(imgbtn1, "f:img_aj_170x44.png");

	

	/** player1 */
	/** 同情 */
	player1 = gt_player_create(screen_fail);
	gt_obj_set_pos(player1, 4, 78);
	gt_obj_set_size(player1, 225, 116);
	gt_player_add_item(player1, "f:img_02_01_2_225x116.jpg", sizeof("f:img_02_01_2_225x116.jpg"));
	gt_player_add_item(player1, "f:img_02_02_225x116.jpg", sizeof("f:img_02_02_225x116.jpg"));
	gt_player_add_item(player1, "f:img_02_03_225x116.jpg", sizeof("f:img_02_03_225x116.jpg"));
	gt_player_add_item(player1, "f:img_02_04_225x116.jpg", sizeof("f:img_02_04_225x116.jpg"));
	gt_player_add_item(player1, "f:img_02_05_225x116.jpg", sizeof("f:img_02_05_225x116.jpg"));
	gt_player_add_item(player1, "f:img_02_06_225x116.jpg", sizeof("f:img_02_06_225x116.jpg"));
	gt_player_add_item(player1, "f:img_02_07_225x116.jpg", sizeof("f:img_02_07_225x116.jpg"));
	gt_player_add_item(player1, "f:img_02_08_225x116.jpg", sizeof("f:img_02_08_225x116.jpg"));
	gt_player_add_item(player1, "f:img_02_09_225x116.jpg", sizeof("f:img_02_09_225x116.jpg"));
	gt_player_add_item(player1, "f:img_02_10_225x116.jpg", sizeof("f:img_02_10_225x116.jpg"));
	gt_player_add_item(player1, "f:img_02_11_225x116.jpg", sizeof("f:img_02_11_225x116.jpg"));
	gt_player_add_item(player1, "f:img_02_12_225x116.jpg", sizeof("f:img_02_12_225x116.jpg"));
	gt_player_add_item(player1, "f:img_02_13_225x116.jpg", sizeof("f:img_02_13_225x116.jpg"));
	gt_player_add_item(player1, "f:img_02_14_225x116.jpg", sizeof("f:img_02_14_225x116.jpg"));
	gt_player_add_item(player1, "f:img_02_15_225x116.jpg", sizeof("f:img_02_15_225x116.jpg"));
	gt_player_add_item(player1, "f:img_02_16_225x116.jpg", sizeof("f:img_02_16_225x116.jpg"));
	gt_player_set_type(player1, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player1, GT_PLAYER_MODE_LOOP);
	gt_player_set_auto_play_period(player1, 35);
	gt_player_play(player1);
	gt_obj_add_event_cb(player1, player1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab2Copy */
	lab2Copy = gt_label_create(screen_fail);
	gt_obj_set_pos(lab2Copy, 25, 215);
	gt_obj_set_size(lab2Copy, 187, 30);
	gt_label_set_font_color(lab2Copy, gt_color_hex(0xFF7859));
	gt_label_set_font_family(lab2Copy, gray_black_16);
	gt_label_set_font_cjk(lab2Copy, 0);
	gt_label_set_font_align(lab2Copy, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2Copy, "识别失败，请重试");

	

	/** lab1Copy */
	lab1Copy = gt_label_create(screen_fail);
	gt_obj_set_pos(lab1Copy, 46, 257);
	gt_obj_set_size(lab1Copy, 154, 37);
	gt_label_set_font_color(lab1Copy, gt_color_hex(0xffffff));
	gt_label_set_font_family(lab1Copy, gray_black_16);
	gt_label_set_font_cjk(lab1Copy, 0);
	gt_label_set_font_align(lab1Copy, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab1Copy, "请长按说话");
	gt_obj_add_event_cb(lab1Copy, lab1Copy_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	return screen_fail;
}

