#include "gt_ui.h"


/** screen_7 */
gt_obj_st * screen_7 = NULL;
static gt_obj_st * img7 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * player6 = NULL;
static gt_obj_st * img2 = NULL;

/** 按下加载回翻译界面 */
static void img7_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void player6_cb(gt_event_st * e) {
	gt_player_toggle(player6);
}

/** 按下加载到诗词解析界面 */
static void img2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_13, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_7(void)
{
	screen_7 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_7, gt_color_hex(0x000000));

	

	/** img7 */
	/** 返回图标 */
	img7 = gt_img_create(screen_7);
	gt_obj_set_pos(img7, 8, 14);
	gt_obj_set_size(img7, 16, 16);
	gt_img_set_src(img7, ".:img_16x16_icon_left.png");
	gt_obj_add_event_cb(img7, img7_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab1 */
	/** 古诗词，优黑20x20 */
	lab1 = gt_label_create(screen_7);
	gt_obj_set_pos(lab1, 30, 13);
	gt_obj_set_size(lab1, 276, 25);
	gt_label_set_font_color(lab1, gt_color_hex(0x8edbff));
	gt_label_set_font_size(lab1, 20);
	gt_label_set_font_family_cn(lab1, 130);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT);
	gt_label_set_space(lab1, 2, 0);
	gt_label_set_text(lab1, "牧童骑黄牛，歌声振林樾。");

	

	/** lab2 */
	/** 古诗词，优黑20x20 */
	lab2 = gt_label_create(screen_7);
	gt_obj_set_pos(lab2, 28, 39);
	gt_obj_set_size(lab2, 276, 25);
	gt_label_set_font_color(lab2, gt_color_hex(0x8edbff));
	gt_label_set_font_size(lab2, 20);
	gt_label_set_font_family_cn(lab2, 130);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT);
	gt_label_set_space(lab2, 2, 0);
	gt_label_set_text(lab2, "意欲捕鸣蝉，忽然闭口立。");

	

	/** lab3 */
	/** 文字，优黑16x16 */
	lab3 = gt_label_create(screen_7);
	gt_obj_set_pos(lab3, 28, 79);
	gt_obj_set_size(lab3, 276, 25);
	gt_label_set_font_color(lab3, gt_color_hex(0xdedede));
	gt_label_set_font_size(lab3, 16);
	gt_label_set_font_family_cn(lab3, 24);
	gt_label_set_font_align(lab3, GT_ALIGN_LEFT);
	gt_label_set_text(lab3, "出自");

	

	/** lab4 */
	/** 文字，优黑16x16 */
	lab4 = gt_label_create(screen_7);
	gt_obj_set_pos(lab4, 26, 105);
	gt_obj_set_size(lab4, 276, 25);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 16);
	gt_label_set_font_family_cn(lab4, 24);
	gt_label_set_font_align(lab4, GT_ALIGN_LEFT);
	gt_label_set_space(lab4, 1, 0);
	gt_label_set_text(lab4, "————《所见》袁枚");

	

	/** lab5 */
	/** 文字，优黑16x16 */
	lab5 = gt_label_create(screen_7);
	gt_obj_set_pos(lab5, 28, 133);
	gt_obj_set_size(lab5, 250, 25);
	gt_label_set_font_color(lab5, gt_color_hex(0xdedede));
	gt_label_set_font_size(lab5, 16);
	gt_label_set_font_family_cn(lab5, 24);
	gt_label_set_font_align(lab5, GT_ALIGN_LEFT);
	gt_label_set_text(lab5, "译文");

	

	/** player6 */
	/** 原文读音图标，模式设置为循环播放 */
	player6 = gt_player_create(screen_7);
	gt_obj_set_pos(player6, 290, 14);
	gt_obj_set_size(player6, 20, 20);
	gt_player_add_item(player6, ".:img_20x20_v4_icon.png", sizeof(".:img_20x20_v4_icon.png"));
	gt_player_add_item(player6, ".:img_20x20_v5_icon.png", sizeof(".:img_20x20_v5_icon.png"));
	gt_player_add_item(player6, ".:img_20x20_v6_icon.png", sizeof(".:img_20x20_v6_icon.png"));
	gt_player_set_type(player6, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player6, GT_PLAYER_MODE_LOOP);
	gt_player_set_auto_play_period(player6, 500);
	gt_player_play(player6);
	gt_obj_add_event_cb(player6, player6_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img2 */
	/** 翻页图标 */
	img2 = gt_img_create(screen_7);
	gt_obj_set_pos(img2, 293, 143);
	gt_obj_set_size(img2, 20, 20);
	gt_img_set_src(img2, ".:img_20x20_61_chevron_down.png");
	gt_obj_add_event_cb(img2, img2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	return screen_7;
}

