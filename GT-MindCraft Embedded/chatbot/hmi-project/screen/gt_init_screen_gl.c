#include "gt_ui.h"
#include "gt_font_config.h"


/** screen_gl */
gt_obj_st * screen_gl = NULL;
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

gt_obj_st * gt_init_screen_gl(void)
{
	screen_gl = gt_obj_create(NULL);
	gt_obj_add_event_cb(screen_gl, screen_subtitle_0_cb, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
	gt_screen_set_bgcolor(screen_gl, gt_color_hex(0x000000));


	

	/** img2 */
	img2 = gt_img_create(screen_gl);
	gt_obj_set_pos(img2, 3, 220);
	gt_obj_set_size(img2, 230, 97);
	gt_obj_set_opa(img2, GT_OPA_65);
	gt_img_set_src(img2, "f:img_10_230x97.png");

	

	/** lab2 */
	lab2 = gt_label_create(screen_gl);
	gt_obj_set_pos(lab2, 26, 265);
	gt_obj_set_size(lab2, 192, 30);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_family(lab2, gray_black_20);
	gt_label_set_font_cjk(lab2, 0);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, "智匠AI是什么？");

	

	/** img1 */
	img1 = gt_img_create(screen_gl);
	gt_obj_set_pos(img1, 183, 17);
	gt_obj_set_size(img1, 24, 24);
	gt_img_set_src(img1, "f:img_1723686274619_24x24.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn1 */
	imgbtn1 = gt_imgbtn_create(screen_gl);
	gt_obj_set_pos(imgbtn1, 13, 10);
	gt_obj_set_size(imgbtn1, 16, 16);
	gt_imgbtn_set_src(imgbtn1, "f:img_fh_16x16.png");
	gt_obj_add_event_cb(imgbtn1, imgbtn1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** player1 */
	/** 鼓励 */
	player1 = gt_player_create(screen_gl);
	gt_obj_set_pos(player1, 4, 78);
	gt_obj_set_size(player1, 228, 117);
	gt_player_add_item(player1, "f:img_04_09_10_228x117.jpg", sizeof("f:img_04_09_10_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_10_228x117.jpg", sizeof("f:img_04_10_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_11_228x117.jpg", sizeof("f:img_04_11_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_12_228x117.jpg", sizeof("f:img_04_12_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_13_228x117.jpg", sizeof("f:img_04_13_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_14_228x117.jpg", sizeof("f:img_04_14_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_15_228x117.jpg", sizeof("f:img_04_15_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_16_228x117.jpg", sizeof("f:img_04_16_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_17_228x117.jpg", sizeof("f:img_04_17_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_18_228x117.jpg", sizeof("f:img_04_18_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_19_228x117.jpg", sizeof("f:img_04_19_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_20_228x117.jpg", sizeof("f:img_04_20_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_21_228x117.jpg", sizeof("f:img_04_21_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_22_228x117.jpg", sizeof("f:img_04_22_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_23_228x117.jpg", sizeof("f:img_04_23_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_24_228x117.jpg", sizeof("f:img_04_24_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_25_228x117.jpg", sizeof("f:img_04_25_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_26_228x117.jpg", sizeof("f:img_04_26_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_27_228x117.jpg", sizeof("f:img_04_27_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_28_228x117.jpg", sizeof("f:img_04_28_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_29_228x117.jpg", sizeof("f:img_04_29_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_30_228x117.jpg", sizeof("f:img_04_30_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_31_228x117.jpg", sizeof("f:img_04_31_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_32_228x117.jpg", sizeof("f:img_04_32_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_33_228x117.jpg", sizeof("f:img_04_33_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_34_4_228x117.jpg", sizeof("f:img_04_34_4_228x117.jpg"));
	gt_player_add_item(player1, "f:img_04_38_9_228x117.jpg", sizeof("f:img_04_38_9_228x117.jpg"));
	gt_player_set_type(player1, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player1, GT_PLAYER_MODE_ONCE);
	gt_player_set_auto_play_period(player1, 35);
	gt_obj_add_event_cb(player1, player1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	return screen_gl;
}

