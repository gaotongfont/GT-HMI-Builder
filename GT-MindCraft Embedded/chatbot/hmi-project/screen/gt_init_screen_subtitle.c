#include "gt_ui.h"
#include "gt_font_config.h"


/** screen_subtitle */
gt_obj_st * screen_subtitle = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * player1 = NULL;

static void screen_subtitle_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

static void img1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_SETUP, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void imgbtn1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void player1_0_cb(gt_event_st * e) {
	
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
	gt_label_set_font_family(lab2, gray_black_20);
	gt_label_set_font_cjk(lab2, 0);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, "智匠AI是什么？");

	

	/** img1 */
	img1 = gt_img_create(screen_subtitle);
	gt_obj_set_pos(img1, 183, 17);
	gt_obj_set_size(img1, 24, 24);
	gt_img_set_src(img1, "f:img_1723686274619_24x24.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn1 */
	imgbtn1 = gt_imgbtn_create(screen_subtitle);
	gt_obj_set_pos(imgbtn1, 13, 10);
	gt_obj_set_size(imgbtn1, 16, 16);
	gt_imgbtn_set_src(imgbtn1, "f:img_fh_16x16.png");
	gt_obj_add_event_cb(imgbtn1, imgbtn1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** player1 */
	/** 说话 */
	player1 = gt_player_create(screen_subtitle);
	gt_obj_set_pos(player1, 3, 78);
	gt_obj_set_size(player1, 228, 116);
	gt_player_add_item(player1, "f:img_08_07_6_228x116.jpg", sizeof("f:img_08_07_6_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_08_228x116.jpg", sizeof("f:img_08_08_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_09_228x116.jpg", sizeof("f:img_08_09_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_10_228x116.jpg", sizeof("f:img_08_10_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_11_228x116.jpg", sizeof("f:img_08_11_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_12_228x116.jpg", sizeof("f:img_08_12_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_13_228x116.jpg", sizeof("f:img_08_13_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_14_228x116.jpg", sizeof("f:img_08_14_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_15_228x116.jpg", sizeof("f:img_08_15_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_16_228x116.jpg", sizeof("f:img_08_16_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_17_228x116.jpg", sizeof("f:img_08_17_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_18_228x116.jpg", sizeof("f:img_08_18_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_19_228x116.jpg", sizeof("f:img_08_19_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_20_228x116.jpg", sizeof("f:img_08_20_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_20_t02_228x116.jpg", sizeof("f:img_08_20_t02_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_21_228x116.jpg", sizeof("f:img_08_21_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_22_228x116.jpg", sizeof("f:img_08_22_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_23_228x116.jpg", sizeof("f:img_08_23_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_24_228x116.jpg", sizeof("f:img_08_24_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_25_228x116.jpg", sizeof("f:img_08_25_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_26_228x116.jpg", sizeof("f:img_08_26_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_27_228x116.jpg", sizeof("f:img_08_27_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_28_228x116.jpg", sizeof("f:img_08_28_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_29_228x116.jpg", sizeof("f:img_08_29_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_30_228x116.jpg", sizeof("f:img_08_30_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_31_228x116.jpg", sizeof("f:img_08_31_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_32_228x116.jpg", sizeof("f:img_08_32_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_33_228x116.jpg", sizeof("f:img_08_33_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_34_228x116.jpg", sizeof("f:img_08_34_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_35_228x116.jpg", sizeof("f:img_08_35_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_36_228x116.jpg", sizeof("f:img_08_36_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_37_228x116.jpg", sizeof("f:img_08_37_228x116.jpg"));
	gt_player_add_item(player1, "f:img_08_38_228x116.jpg", sizeof("f:img_08_38_228x116.jpg"));
	gt_player_set_type(player1, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player1, GT_PLAYER_MODE_ONCE);
	gt_player_set_auto_play_period(player1, 35);
	gt_obj_add_event_cb(player1, player1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	return screen_subtitle;
}

