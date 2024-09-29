#include "gt_ui.h"


/** screen_2 */
gt_obj_st * screen_2 = NULL;
static gt_obj_st * img6 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * lab20 = NULL;

/** 按下加载翻译界面 */
static void img6_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载翻译界面 */
static void lab1_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_3, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载翻译界面 */
static void lab3_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_3, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到中英互译界面 */
static void btn1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_3, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_2(void)
{
	screen_2 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_2, gt_color_hex(0x000000));

	

	/** img6 */
	/** 返回图标 */
	img6 = gt_img_create(screen_2);
	gt_obj_set_pos(img6, 8, 14);
	gt_obj_set_size(img6, 16, 16);
	gt_img_set_src(img6, "f:img_16x16_icon_left.png");
	gt_obj_add_event_cb(img6, img6_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab1 */
	/** 扫描翻译文字，英文圆角16点不等宽 */
	lab1 = gt_label_create(screen_2);
	gt_obj_set_pos(lab1, 30, 13);
	gt_obj_set_size(lab1, 260, 25);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 16);
	gt_label_set_font_family_en(lab1, 39);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT);
	gt_label_set_text(lab1, "It does not matter how slowly ");
	gt_obj_add_event_cb(lab1, lab1_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab3 */
	/** 扫描翻译文字，英文圆角16点不等宽 */
	lab3 = gt_label_create(screen_2);
	gt_obj_set_pos(lab3, 18, 36);
	gt_obj_set_size(lab3, 260, 24);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 16);
	gt_label_set_font_family_en(lab3, 39);
	gt_label_set_font_align(lab3, GT_ALIGN_LEFT);
	gt_label_set_text(lab3, " go as long as  do not stop.");
	gt_obj_add_event_cb(lab3, lab3_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** btn1 */
	/** 进入翻译页按钮 */
	btn1 = gt_btn_create(screen_2);
	gt_obj_set_pos(btn1, 80, 108);
	gt_obj_set_size(btn1, 150, 38);
	gt_btn_set_font_color(btn1, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn1, 16);
	gt_btn_set_font_family_cn(btn1, 24);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_space(btn1, 1, 0);
	gt_btn_set_text(btn1, "进入翻译页");
	gt_btn_set_color_background(btn1, gt_color_hex(0xffae07));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn1, gt_color_hex(0x000000));
	gt_btn_set_radius(btn1, 10);
	gt_obj_add_event_cb(btn1, btn1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab20 */
	/** 扫描翻译文字，英文圆角16点不等宽 */
	lab20 = gt_label_create(screen_2);
	gt_obj_set_pos(lab20, 28, 66);
	gt_obj_set_size(lab20, 254, 24);
	gt_label_set_font_color(lab20, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab20, 16);
	gt_label_set_font_family_cn(lab20, 24);
	gt_label_set_font_family_en(lab20, 39);
	gt_label_set_font_align(lab20, GT_ALIGN_LEFT);
	gt_label_set_text(lab20, "From the movie \"Zhou Ji Ji\"");


	return screen_2;
}

