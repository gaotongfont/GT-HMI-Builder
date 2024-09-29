#include "gt_ui.h"


/** screen_home */
gt_obj_st * screen_home = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * imgbtn2 = NULL;
static gt_obj_st * imgbtn4 = NULL;
static gt_obj_st * imgbtn5 = NULL;
static gt_obj_st * imgbtn6 = NULL;
static gt_obj_st * imgbtn7 = NULL;
static gt_obj_st * imgbtn8 = NULL;
static gt_obj_st * imgbtn9 = NULL;
static gt_obj_st * imgbtn10 = NULL;
static gt_obj_st * imgbtn11 = NULL;
static gt_obj_st * imgbtn12 = NULL;
static gt_obj_st * imgbtn13 = NULL;
static gt_obj_st * player1 = NULL;
static gt_obj_st * player2 = NULL;
static gt_obj_st * player3 = NULL;
static gt_obj_st * player4 = NULL;
static gt_obj_st * player5 = NULL;
static gt_obj_st * player6 = NULL;
static gt_obj_st * player8 = NULL;
static gt_obj_st * imgbtn14 = NULL;

/** 按下加载左侧温度档位下一个图片 */
static void imgbtn1_0_cb(gt_event_st * e) {
	gt_player_turn_next(player1);
}

/** 按下加载左侧温度数字下一个图片 */
static void imgbtn1_1_cb(gt_event_st * e) {
	gt_player_turn_next(player3);
}

/** 按下加载右侧温度档下一个图片 */
static void imgbtn2_0_cb(gt_event_st * e) {
	gt_player_turn_next(player2);
}

/** 按下加载右侧温度数字下一个图片 */
static void imgbtn2_1_cb(gt_event_st * e) {
	gt_player_turn_next(player4);
}

/** 按下加载左侧温度档位上一个图片 */
static void imgbtn5_0_cb(gt_event_st * e) {
	gt_player_turn_prev(player1);
}

/** 按下加载左侧温度数字上一个图片 */
static void imgbtn5_1_cb(gt_event_st * e) {
	gt_player_turn_prev(player3);
}

/** 按下加载右侧温度档上一个图片 */
static void imgbtn6_0_cb(gt_event_st * e) {
	gt_player_turn_prev(player2);
}

/** 按下加载右侧温度数字上一个图片 */
static void imgbtn6_1_cb(gt_event_st * e) {
	gt_player_turn_prev(player4);
}

/** 按下后左侧座椅加载下一个图片 */
static void imgbtn10_0_cb(gt_event_st * e) {
	gt_player_turn_next(player6);
}

/** 按下后右侧座椅加载下一个图片 */
static void imgbtn11_0_cb(gt_event_st * e) {
	gt_player_turn_next(player8);
}

/** 按下加载中部温度数字上一个图片 */
static void imgbtn12_0_cb(gt_event_st * e) {
	gt_player_turn_prev(player5);
}

/** 按下加载中部温度数字下一个图片 */
static void imgbtn13_0_cb(gt_event_st * e) {
	gt_player_turn_next(player5);
}

gt_obj_st * gt_init_screen_home(void)
{
	screen_home = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_home, gt_color_hex(0x000000));

	

	/** img1 */
	/** 背景图片 */
	img1 = gt_img_create(screen_home);
	gt_obj_set_pos(img1, 0, 0);
	gt_obj_set_size(img1, 800, 480);
	gt_img_set_src(img1, ".:img_800x480_bjcz.png");

	

	/** img3 */
	img3 = gt_img_create(screen_home);
	gt_obj_set_pos(img3, 114, 18);
	gt_obj_set_size(img3, 9, 9);
	gt_img_set_src(img3, ".:img_9x9_15_9x9752x28.png");

	

	/** imgbtn1 */
	/** 左侧加号 */
	imgbtn1 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn1, 61, 83);
	gt_obj_set_size(imgbtn1, 34, 34);
	gt_imgbtn_set_src(imgbtn1, ".:img_34x34_19_34x3453x95.png");
	gt_imgbtn_set_src_press(imgbtn1, ".:img_34x34_19_p.png");
	gt_obj_add_event_cb(imgbtn1, imgbtn1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	gt_obj_add_event_cb(imgbtn1, imgbtn1_1_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn2 */
	/** 右侧加号 */
	imgbtn2 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn2, 691, 83);
	gt_obj_set_size(imgbtn2, 34, 34);
	gt_imgbtn_set_src(imgbtn2, ".:img_34x34_19_34x3453x95.png");
	gt_imgbtn_set_src_press(imgbtn2, ".:img_34x34_19_p.png");
	gt_obj_add_event_cb(imgbtn2, imgbtn2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	gt_obj_add_event_cb(imgbtn2, imgbtn2_1_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn4 */
	imgbtn4 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn4, 746, 18);
	gt_obj_set_size(imgbtn4, 9, 9);
	gt_imgbtn_set_src(imgbtn4, ".:img_9x9_17_9x9109x28.png");

	

	/** imgbtn5 */
	/** 左侧减号 */
	imgbtn5 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn5, 61, 374);
	gt_obj_set_size(imgbtn5, 34, 34);
	gt_imgbtn_set_src(imgbtn5, ".:img_34x34_20_34x3453x382.png");
	gt_imgbtn_set_src_press(imgbtn5, ".:img_34x34_20_p.png");
	gt_obj_add_event_cb(imgbtn5, imgbtn5_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	gt_obj_add_event_cb(imgbtn5, imgbtn5_1_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn6 */
	/** 右侧减号 */
	imgbtn6 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn6, 691, 373);
	gt_obj_set_size(imgbtn6, 34, 34);
	gt_imgbtn_set_src(imgbtn6, ".:img_34x34_20_34x3453x382.png");
	gt_imgbtn_set_src_press(imgbtn6, ".:img_34x34_20_p.png");
	gt_obj_add_event_cb(imgbtn6, imgbtn6_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	gt_obj_add_event_cb(imgbtn6, imgbtn6_1_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn7 */
	/** A/C图标 */
	imgbtn7 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn7, 140, 417);
	gt_obj_set_size(imgbtn7, 84, 63);
	gt_imgbtn_set_src(imgbtn7, ".:img_84x63_1_84x63122x417.png");
	gt_imgbtn_set_src_press(imgbtn7, ".:img_84x63_1_p.png");

	

	/** imgbtn8 */
	/** AUTO图标 */
	imgbtn8 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn8, 230, 417);
	gt_obj_set_size(imgbtn8, 84, 63);
	gt_imgbtn_set_src(imgbtn8, ".:img_84x63_2_84x63219x417.png");
	gt_imgbtn_set_src_press(imgbtn8, ".:img_84x63_2_p.png");

	

	/** imgbtn9 */
	/** 除雾图标 */
	imgbtn9 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn9, 319, 417);
	gt_obj_set_size(imgbtn9, 84, 63);
	gt_imgbtn_set_src(imgbtn9, ".:img_84x63_3_84x63316x417.png");
	gt_imgbtn_set_src_press(imgbtn9, ".:img_84x63_3_p.png");

	

	/** imgbtn10 */
	/** 左侧座椅加热图标 */
	imgbtn10 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn10, 400, 417);
	gt_obj_set_size(imgbtn10, 84, 63);
	gt_imgbtn_set_src(imgbtn10, ".:img_84x63_4_84x63412x417.png");
	gt_imgbtn_set_src_press(imgbtn10, ".:img_84x63_4_p.png");
	gt_obj_add_event_cb(imgbtn10, imgbtn10_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn11 */
	/** 右侧座椅加热图标 */
	imgbtn11 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn11, 474, 417);
	gt_obj_set_size(imgbtn11, 84, 63);
	gt_imgbtn_set_src(imgbtn11, ".:img_84x63_5_84x63507x417.png");
	gt_imgbtn_set_src_press(imgbtn11, ".:img_84x63_5_p.png");
	gt_obj_add_event_cb(imgbtn11, imgbtn11_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn12 */
	/** 中部减号 */
	imgbtn12 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn12, 381, 282);
	gt_obj_set_size(imgbtn12, 34, 34);
	gt_imgbtn_set_src(imgbtn12, ".:img_34x34_27_34x34383x277.png");
	gt_imgbtn_set_src_press(imgbtn12, ".:img_34x34_27_p.png");
	gt_obj_add_event_cb(imgbtn12, imgbtn12_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn13 */
	/** 中部加号 */
	imgbtn13 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn13, 381, 161);
	gt_obj_set_size(imgbtn13, 34, 34);
	gt_imgbtn_set_src(imgbtn13, ".:img_34x34_26_34x34383x167.png");
	gt_imgbtn_set_src_press(imgbtn13, ".:img_34x34_26_p.png");
	gt_obj_add_event_cb(imgbtn13, imgbtn13_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** player1 */
	/** 左侧温度档位图标 */
	player1 = gt_player_create(screen_home);
	gt_obj_set_pos(player1, 16, 110);
	gt_obj_set_size(player1, 100, 261);
	gt_player_add_item(player1, ".:img_100x261_wdl_0.png", sizeof(".:img_100x261_wdl_0.png"));
	gt_player_add_item(player1, ".:img_100x261_wdl_1.png", sizeof(".:img_100x261_wdl_1.png"));
	gt_player_add_item(player1, ".:img_100x261_wdl_2.png", sizeof(".:img_100x261_wdl_2.png"));
	gt_player_add_item(player1, ".:img_100x261_wdl_3.png", sizeof(".:img_100x261_wdl_3.png"));
	gt_player_add_item(player1, ".:img_100x261_wdl_4.png", sizeof(".:img_100x261_wdl_4.png"));
	gt_player_add_item(player1, ".:img_100x261_wdl_5.png", sizeof(".:img_100x261_wdl_5.png"));
	gt_player_set_type(player1, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player1, GT_PLAYER_MODE_ONCE);

	

	/** player2 */
	/** 右侧温度档位图标 */
	player2 = gt_player_create(screen_home);
	gt_obj_set_pos(player2, 681, 108);
	gt_obj_set_size(player2, 100, 271);
	gt_player_add_item(player2, ".:img_100x271_wdr_0.png", sizeof(".:img_100x271_wdr_0.png"));
	gt_player_add_item(player2, ".:img_100x271_wdr_1.png", sizeof(".:img_100x271_wdr_1.png"));
	gt_player_add_item(player2, ".:img_100x271_wdr_2.png", sizeof(".:img_100x271_wdr_2.png"));
	gt_player_add_item(player2, ".:img_100x271_wdr_3.png", sizeof(".:img_100x271_wdr_3.png"));
	gt_player_add_item(player2, ".:img_100x271_wdr_4.png", sizeof(".:img_100x271_wdr_4.png"));
	gt_player_add_item(player2, ".:img_100x271_wdr_5.png", sizeof(".:img_100x271_wdr_5.png"));
	gt_player_set_type(player2, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player2, GT_PLAYER_MODE_ONCE);

	

	/** player3 */
	/** 左侧温度数字图标 */
	player3 = gt_player_create(screen_home);
	gt_obj_set_pos(player3, 50, 33);
	gt_obj_set_size(player3, 59, 30);
	gt_player_add_item(player3, ".:img_59x30_18_59x3045x33.png", sizeof(".:img_59x30_18_59x3045x33.png"));
	gt_player_add_item(player3, ".:img_59x30_20_59x3045x33.png", sizeof(".:img_59x30_20_59x3045x33.png"));
	gt_player_add_item(player3, ".:img_59x30_23_59x3045x33.png", sizeof(".:img_59x30_23_59x3045x33.png"));
	gt_player_add_item(player3, ".:img_59x30_26_59x3045x33.png", sizeof(".:img_59x30_26_59x3045x33.png"));
	gt_player_add_item(player3, ".:img_59x30_29_59x3045x33.png", sizeof(".:img_59x30_29_59x3045x33.png"));
	gt_player_add_item(player3, ".:img_59x30_32_59x3045x33.png", sizeof(".:img_59x30_32_59x3045x33.png"));
	gt_player_set_type(player3, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player3, GT_PLAYER_MODE_ONCE);

	

	/** player4 */
	/** 右侧温度数字图标 */
	player4 = gt_player_create(screen_home);
	gt_obj_set_pos(player4, 678, 31);
	gt_obj_set_size(player4, 59, 30);
	gt_player_add_item(player4, ".:img_59x30_18_59x3045x33.png", sizeof(".:img_59x30_18_59x3045x33.png"));
	gt_player_add_item(player4, ".:img_59x30_20_59x3045x33.png", sizeof(".:img_59x30_20_59x3045x33.png"));
	gt_player_add_item(player4, ".:img_59x30_23_59x3045x33.png", sizeof(".:img_59x30_23_59x3045x33.png"));
	gt_player_add_item(player4, ".:img_59x30_26_59x3045x33.png", sizeof(".:img_59x30_26_59x3045x33.png"));
	gt_player_add_item(player4, ".:img_59x30_29_59x3045x33.png", sizeof(".:img_59x30_29_59x3045x33.png"));
	gt_player_add_item(player4, ".:img_59x30_32_59x3045x33.png", sizeof(".:img_59x30_32_59x3045x33.png"));
	gt_player_set_type(player4, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player4, GT_PLAYER_MODE_ONCE);

	

	/** player5 */
	/** 中部数值 */
	player5 = gt_player_create(screen_home);
	gt_obj_set_pos(player5, 383, 111);
	gt_obj_set_size(player5, 32, 17);
	gt_player_add_item(player5, ".:img_32x17_1_32x17.png", sizeof(".:img_32x17_1_32x17.png"));
	gt_player_add_item(player5, ".:img_32x17_2_32x17.png", sizeof(".:img_32x17_2_32x17.png"));
	gt_player_add_item(player5, ".:img_32x17_3_32x17.png", sizeof(".:img_32x17_3_32x17.png"));
	gt_player_add_item(player5, ".:img_32x17_4_32x17.png", sizeof(".:img_32x17_4_32x17.png"));
	gt_player_add_item(player5, ".:img_32x17_5_32x17.png", sizeof(".:img_32x17_5_32x17.png"));
	gt_player_add_item(player5, ".:img_32x17_6_32x17.png", sizeof(".:img_32x17_6_32x17.png"));
	gt_player_add_item(player5, ".:img_32x17_7_32x17.png", sizeof(".:img_32x17_7_32x17.png"));
	gt_player_add_item(player5, ".:img_32x17_8_32x17.png", sizeof(".:img_32x17_8_32x17.png"));
	gt_player_add_item(player5, ".:img_32x17_9_32x17.png", sizeof(".:img_32x17_9_32x17.png"));
	gt_player_add_item(player5, ".:img_32x17_10_32x17.png", sizeof(".:img_32x17_10_32x17.png"));
	gt_player_add_item(player5, ".:img_32x17_11_32x17.png", sizeof(".:img_32x17_11_32x17.png"));
	gt_player_set_type(player5, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player5, GT_PLAYER_MODE_ONCE);

	

	/** player6 */
	/** 左侧座椅图标 */
	player6 = gt_player_create(screen_home);
	gt_obj_set_pos(player6, 193, 102);
	gt_obj_set_size(player6, 174, 258);
	gt_player_add_item(player6, ".:img_174x258_zyl_1.png", sizeof(".:img_174x258_zyl_1.png"));
	gt_player_add_item(player6, ".:img_174x258_zyl_2.png", sizeof(".:img_174x258_zyl_2.png"));
	gt_player_set_type(player6, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player6, GT_PLAYER_MODE_LOOP);

	

	/** player8 */
	/** 右侧座椅图标 */
	player8 = gt_player_create(screen_home);
	gt_obj_set_pos(player8, 440, 102);
	gt_obj_set_size(player8, 174, 258);
	gt_player_add_item(player8, ".:img_174x258_zyr_1.png", sizeof(".:img_174x258_zyr_1.png"));
	gt_player_add_item(player8, ".:img_174x258_zyr_2.png", sizeof(".:img_174x258_zyr_2.png"));
	gt_player_set_type(player8, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player8, GT_PLAYER_MODE_LOOP);

	

	/** imgbtn14 */
	/** 内循环图标 */
	imgbtn14 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn14, 559, 417);
	gt_obj_set_size(imgbtn14, 84, 63);
	gt_imgbtn_set_src(imgbtn14, ".:img_84x63_6_p.png");
	gt_imgbtn_set_src_press(imgbtn14, ".:img_84x63_6_83x63603x417.png");


	return screen_home;
}

