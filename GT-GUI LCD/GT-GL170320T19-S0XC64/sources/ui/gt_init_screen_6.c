#include "gt_ui.h"


/** screen_6 */
gt_obj_st * screen_6 = NULL;
static gt_obj_st * img6 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * btn1_copy = NULL;

/** 按下加载回翻译界面 */
static void img6_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到古诗词界面 */
static void lab1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_7, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到古诗词界面 */
static void btn1_copy_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_7, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_6(void)
{
	screen_6 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_6, gt_color_hex(0x000000));

	

	/** img6 */
	/** 返回图标 */
	img6 = gt_img_create(screen_6);
	gt_obj_set_pos(img6, 10, 16);
	gt_obj_set_size(img6, 16, 16);
	gt_img_set_src(img6, ".:img_16x16_icon_left.png");
	gt_obj_add_event_cb(img6, img6_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab1 */
	lab1 = gt_label_create(screen_6);
	gt_obj_set_pos(lab1, 46, 13);
	gt_obj_set_size(lab1, 265, 25);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 20);
	gt_label_set_font_family_cn(lab1, 130);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT);
	gt_label_set_space(lab1, 1, 0);
	gt_label_set_text(lab1, "牧童骑黄牛，歌声振林樾。");
	gt_obj_add_event_cb(lab1, lab1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** btn1_copy */
	btn1_copy = gt_btn_create(screen_6);
	gt_obj_set_pos(btn1_copy, 80, 83);
	gt_obj_set_size(btn1_copy, 150, 38);
	gt_btn_set_font_color(btn1_copy, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn1_copy, 16);
	gt_btn_set_font_family_cn(btn1_copy, 24);
	gt_btn_set_font_align(btn1_copy, GT_ALIGN_CENTER_MID);
	gt_btn_set_space(btn1_copy, 1, 0);
	gt_btn_set_text(btn1_copy, "进入翻译页");
	gt_btn_set_color_background(btn1_copy, gt_color_hex(0xffae07));
	gt_btn_set_color_pressed(btn1_copy, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn1_copy, gt_color_hex(0x000000));
	gt_btn_set_radius(btn1_copy, 10);
	gt_obj_add_event_cb(btn1_copy, btn1_copy_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	return screen_6;
}

