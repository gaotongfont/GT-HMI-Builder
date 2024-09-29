#include "gt_ui.h"


/** screen_3 */
gt_obj_st * screen_3 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * player8 = NULL;
static gt_obj_st * player9 = NULL;
static gt_obj_st * player10 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;

/** 按下加载回翻译界面 */
static void img3_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下触发控件的开始/暂停功能 */
static void player8_cb(gt_event_st * e) {
	gt_player_toggle(player8);
}

/** 按下触发控件的开始/暂停功能 */
static void player9_cb(gt_event_st * e) {
	gt_player_toggle(player9);
}

/** 按下触发控件的下一个图片模式 */
static void player10_cb(gt_event_st * e) {
	gt_player_turn_next(player10);
}

gt_obj_st * gt_init_screen_3(void)
{
	screen_3 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_3, gt_color_hex(0x000000));

	

	/** img3 */
	/** 返回图标 */
	img3 = gt_img_create(screen_3);
	gt_obj_set_pos(img3, 10, 16);
	gt_obj_set_size(img3, 16, 16);
	gt_img_set_src(img3, "f:img_16x16_icon_left.png");
	gt_obj_add_event_cb(img3, img3_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab10 */
	/** 扫描翻译文字，英文圆角16点不等宽 */
	lab10 = gt_label_create(screen_3);
	gt_obj_set_pos(lab10, 28, 11);
	gt_obj_set_size(lab10, 260, 25);
	gt_label_set_font_color(lab10, gt_color_hex(0x8edbff));
	gt_label_set_font_size(lab10, 16);
	gt_label_set_font_family_en(lab10, 39);
	gt_label_set_font_align(lab10, GT_ALIGN_LEFT);
	gt_label_set_space(lab10, 0, 0);
	gt_label_set_text(lab10, "It does not matter how slowly");

	

	/** lab9 */
	/** 扫描翻译文字，英文圆角16点不等宽 */
	lab9 = gt_label_create(screen_3);
	gt_obj_set_pos(lab9, 28, 36);
	gt_obj_set_size(lab9, 260, 24);
	gt_label_set_font_color(lab9, gt_color_hex(0x8edbff));
	gt_label_set_font_size(lab9, 16);
	gt_label_set_font_family_en(lab9, 39);
	gt_label_set_font_align(lab9, GT_ALIGN_LEFT);
	gt_label_set_space(lab9, 0, 0);
	gt_label_set_text(lab9, "go as long as do not stop.");

	

	/** player8 */
	/** 译文读音图标，模式设置为循环播放 */
	player8 = gt_player_create(screen_3);
	gt_obj_set_pos(player8, 292, 65);
	gt_obj_set_size(player8, 20, 20);
	gt_player_add_item(player8, "f:img_20x20_v1_icon.png", sizeof("f:img_20x20_v1_icon.png"));
	gt_player_add_item(player8, "f:img_20x20_v2_icon.png", sizeof("f:img_20x20_v2_icon.png"));
	gt_player_add_item(player8, "f:img_20x20_v3_icon.png", sizeof("f:img_20x20_v3_icon.png"));
	gt_player_set_type(player8, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player8, GT_PLAYER_MODE_LOOP);
	gt_player_set_auto_play_period(player8, 500);
	gt_obj_add_event_cb(player8, player8_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** player9 */
	/** 原文读音图标，模式设置为循环播放 */
	player9 = gt_player_create(screen_3);
	gt_obj_set_pos(player9, 294, 17);
	gt_obj_set_size(player9, 20, 20);
	gt_player_add_item(player9, "f:img_20x20_v4_icon.png", sizeof("f:img_20x20_v4_icon.png"));
	gt_player_add_item(player9, "f:img_20x20_v5_icon.png", sizeof("f:img_20x20_v5_icon.png"));
	gt_player_add_item(player9, "f:img_20x20_v6_icon.png", sizeof("f:img_20x20_v6_icon.png"));
	gt_player_set_type(player9, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player9, GT_PLAYER_MODE_LOOP);
	gt_player_set_auto_play_period(player9, 500);
	gt_player_play(player9);
	gt_obj_add_event_cb(player9, player9_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** player10 */
	/** 收藏图标，模式设置为来回播放 */
	player10 = gt_player_create(screen_3);
	gt_obj_set_pos(player10, 293, 119);
	gt_obj_set_size(player10, 17, 17);
	gt_player_add_item(player10, "f:img_17x17_s2_c.png", sizeof("f:img_17x17_s2_c.png"));
	gt_player_add_item(player10, "f:img_17x17_s1_c.png", sizeof("f:img_17x17_s1_c.png"));
	gt_player_set_type(player10, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player10, GT_PLAYER_MODE_PLAYBACK);
	gt_obj_add_event_cb(player10, player10_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab8 */
	/** 扫描翻译文字，优黑16x16 */
	lab8 = gt_label_create(screen_3);
	gt_obj_set_pos(lab8, 28, 94);
	gt_obj_set_size(lab8, 275, 28);
	gt_label_set_font_color(lab8, gt_color_hex(0xc0c0c0));
	gt_label_set_font_size(lab8, 16);
	gt_label_set_font_family_cn(lab8, 24);
	gt_label_set_font_align(lab8, GT_ALIGN_LEFT);
	gt_label_set_space(lab8, 1, 0);
	gt_label_set_text(lab8, "不论走得有多慢，只要不停下来。");

	

	/** lab4 */
	/** 扫描翻译文字，英文圆角16点不等宽 */
	lab4 = gt_label_create(screen_3);
	gt_obj_set_pos(lab4, 28, 67);
	gt_obj_set_size(lab4, 255, 24);
	gt_label_set_font_color(lab4, gt_color_hex(0x8edbff));
	gt_label_set_font_size(lab4, 16);
	gt_label_set_font_align(lab4, GT_ALIGN_LEFT);
	gt_label_set_text(lab4, "From the movie \"Zhou Ji Ji\"");

	

	/** lab5 */
	/** 扫描翻译文字，优黑16x16 */
	lab5 = gt_label_create(screen_3);
	gt_obj_set_pos(lab5, 28, 124);
	gt_obj_set_size(lab5, 180, 24);
	gt_label_set_font_color(lab5, gt_color_hex(0xc0c0c0));
	gt_label_set_font_size(lab5, 16);
	gt_label_set_font_family_cn(lab5, 24);
	gt_label_set_font_align(lab5, GT_ALIGN_LEFT);
	gt_label_set_space(lab5, 1, 0);
	gt_label_set_text(lab5, "出自电影《编舟记》");


	return screen_3;
}

