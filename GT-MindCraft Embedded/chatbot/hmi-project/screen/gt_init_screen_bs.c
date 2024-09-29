#include "gt_ui.h"


/** screen_bs */
gt_obj_st * screen_bs = NULL;
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

gt_obj_st * gt_init_screen_bs(void)
{
	screen_bs = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_bs, gt_color_hex(0x000000));


	

	/** img1 */
	img1 = gt_img_create(screen_bs);
	gt_obj_set_pos(img1, 206, 7);
	gt_obj_set_size(img1, 24, 24);
	gt_img_set_src(img1, "f:img_1723686274619_24x24.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn1 */
	imgbtn1 = gt_imgbtn_create(screen_bs);
	gt_obj_set_pos(imgbtn1, 38, 253);
	gt_obj_set_size(imgbtn1, 170, 44);
	gt_imgbtn_set_src(imgbtn1, "f:img_aj_170x44.png");

	

	/** lab1 */
	lab1 = gt_label_create(screen_bs);
	gt_obj_set_pos(lab1, 60, 260);
	gt_obj_set_size(lab1, 125, 30);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_family(lab1, 1);
	gt_label_set_font_cjk(lab1, 0);
	gt_label_set_font_align(lab1, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab1, "请长按说话");

	

	/** player1 */
	/** 悲伤 */
	player1 = gt_player_create(screen_bs);
	gt_obj_set_pos(player1, 9, 84);
	gt_obj_set_size(player1, 222, 112);
	gt_player_add_item(player1, "f:img_03_11_11_222x112.jpg", sizeof("f:img_03_11_11_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_12_222x112.jpg", sizeof("f:img_03_12_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_13_222x112.jpg", sizeof("f:img_03_13_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_14_222x112.jpg", sizeof("f:img_03_14_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_15_222x112.jpg", sizeof("f:img_03_15_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_16_222x112.jpg", sizeof("f:img_03_16_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_17_222x112.jpg", sizeof("f:img_03_17_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_18_222x112.jpg", sizeof("f:img_03_18_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_19_222x112.jpg", sizeof("f:img_03_19_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_21_222x112.jpg", sizeof("f:img_03_21_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_23_222x112.jpg", sizeof("f:img_03_23_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_25_222x112.jpg", sizeof("f:img_03_25_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_27_222x112.jpg", sizeof("f:img_03_27_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_29_222x112.jpg", sizeof("f:img_03_29_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_31_222x112.jpg", sizeof("f:img_03_31_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_33_222x112.jpg", sizeof("f:img_03_33_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_35_222x112.jpg", sizeof("f:img_03_35_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_37_222x112.jpg", sizeof("f:img_03_37_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_39_222x112.jpg", sizeof("f:img_03_39_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_41_222x112.jpg", sizeof("f:img_03_41_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_43_222x112.jpg", sizeof("f:img_03_43_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_45_222x112.jpg", sizeof("f:img_03_45_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_47_222x112.jpg", sizeof("f:img_03_47_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_49_222x112.jpg", sizeof("f:img_03_49_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_51_222x112.jpg", sizeof("f:img_03_51_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_53_222x112.jpg", sizeof("f:img_03_53_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_55_222x112.jpg", sizeof("f:img_03_55_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_57_222x112.jpg", sizeof("f:img_03_57_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_59_222x112.jpg", sizeof("f:img_03_59_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_61_222x112.jpg", sizeof("f:img_03_61_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_63_222x112.jpg", sizeof("f:img_03_63_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_65_222x112.jpg", sizeof("f:img_03_65_222x112.jpg"));
	gt_player_add_item(player1, "f:img_03_67_222x112.jpg", sizeof("f:img_03_67_222x112.jpg"));
	gt_player_set_type(player1, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player1, GT_PLAYER_MODE_LOOP);
	gt_player_set_auto_play_period(player1, 35);
	gt_player_play(player1);

	

	/** lab2Copy */
	lab2Copy = gt_label_create(screen_bs);
	gt_obj_set_pos(lab2Copy, 25, 219);
	gt_obj_set_size(lab2Copy, 187, 30);
	gt_label_set_font_color(lab2Copy, gt_color_hex(0x5b8ad9));
	gt_label_set_font_family(lab2Copy, 0);
	gt_label_set_font_cjk(lab2Copy, 0);
	gt_label_set_font_align(lab2Copy, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2Copy, "识别失败，请重试");



	return screen_bs;
}

