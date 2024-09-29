#include "gt_ui.h"


/** screen_jy */
gt_obj_st * screen_jy = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * player1 = NULL;

static void screen_home_0_cb(gt_event_st * e) {
	
}

static void img1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_SETUP, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_jy(void)
{
	screen_jy = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_jy, gt_color_hex(0x000000));


	

	/** img1 */
	img1 = gt_img_create(screen_jy);
	gt_obj_set_pos(img1, 206, 7);
	gt_obj_set_size(img1, 24, 24);
	gt_img_set_src(img1, "f:img_1723686274619_24x24.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn1 */
	imgbtn1 = gt_imgbtn_create(screen_jy);
	gt_obj_set_pos(imgbtn1, 42, 253);
	gt_obj_set_size(imgbtn1, 154, 40);
	gt_imgbtn_set_src(imgbtn1, "f:img_aj_154x40.png");

	

	/** lab1 */
	lab1 = gt_label_create(screen_jy);
	gt_obj_set_pos(lab1, 58, 257);
	gt_obj_set_size(lab1, 125, 30);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_family(lab1, 1);
	gt_label_set_font_cjk(lab1, 0);
	gt_label_set_font_align(lab1, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab1, "请长按说话");

	

	/** player1 */
	player1 = gt_player_create(screen_jy);
	gt_obj_set_pos(player1, 9, 84);
	gt_obj_set_size(player1, 222, 112);
	gt_player_add_item(player1, "f:img_04_00_222x112.jpg", sizeof("f:img_04_00_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_01_222x112.jpg", sizeof("f:img_04_01_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_02_222x112.jpg", sizeof("f:img_04_02_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_03_222x112.jpg", sizeof("f:img_04_03_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_04_222x112.jpg", sizeof("f:img_04_04_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_05_222x112.jpg", sizeof("f:img_04_05_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_06_222x112.jpg", sizeof("f:img_04_06_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_07_222x112.jpg", sizeof("f:img_04_07_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_08_222x112.jpg", sizeof("f:img_04_08_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_09_222x112.jpg", sizeof("f:img_04_09_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_10_222x112.jpg", sizeof("f:img_04_10_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_11_222x112.jpg", sizeof("f:img_04_11_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_12_222x112.jpg", sizeof("f:img_04_12_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_13_222x112.jpg", sizeof("f:img_04_13_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_14_222x112.jpg", sizeof("f:img_04_14_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_15_222x112.jpg", sizeof("f:img_04_15_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_16_222x112.jpg", sizeof("f:img_04_16_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_17_222x112.jpg", sizeof("f:img_04_17_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_18_222x112.jpg", sizeof("f:img_04_18_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_19_222x112.jpg", sizeof("f:img_04_19_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_20_222x112.jpg", sizeof("f:img_04_20_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_21_222x112.jpg", sizeof("f:img_04_21_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_22_222x112.jpg", sizeof("f:img_04_22_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_23_222x112.jpg", sizeof("f:img_04_23_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_24_222x112.jpg", sizeof("f:img_04_24_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_25_222x112.jpg", sizeof("f:img_04_25_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_26_222x112.jpg", sizeof("f:img_04_26_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_27_222x112.jpg", sizeof("f:img_04_27_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_28_222x112.jpg", sizeof("f:img_04_28_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_29_222x112.jpg", sizeof("f:img_04_29_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_30_222x112.jpg", sizeof("f:img_04_30_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_31_222x112.jpg", sizeof("f:img_04_31_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_32_222x112.jpg", sizeof("f:img_04_32_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_33_222x112.jpg", sizeof("f:img_04_33_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_34_222x112.jpg", sizeof("f:img_04_34_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_35_222x112.jpg", sizeof("f:img_04_35_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_36_222x112.jpg", sizeof("f:img_04_36_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_37_222x112.jpg", sizeof("f:img_04_37_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_38_222x112.jpg", sizeof("f:img_04_38_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_39_222x112.jpg", sizeof("f:img_04_39_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_40_222x112.jpg", sizeof("f:img_04_40_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_41_222x112.jpg", sizeof("f:img_04_41_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_42_222x112.jpg", sizeof("f:img_04_42_222x112.jpg"));
	gt_player_add_item(player1, "f:img_04_43_222x112.jpg", sizeof("f:img_04_43_222x112.jpg"));
	gt_player_set_type(player1, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player1, GT_PLAYER_MODE_ONCE);



	return screen_jy;
}

