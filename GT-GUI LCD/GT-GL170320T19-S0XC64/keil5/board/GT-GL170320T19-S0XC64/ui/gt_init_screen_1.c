#include "gt_ui.h"


/** screen_1 */
gt_obj_st * screen_1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * img4 = NULL;
static gt_obj_st * img5 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * group1 = NULL;
static gt_obj_st * radio2 = NULL;
static gt_obj_st * radio1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;

/** 按下加载主界面 */
static void img4_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载多行扫描翻译界面 */
static void radio2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_2, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载单行扫描翻译界面 */
static void radio1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_6, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载单行扫描翻译界面 */
static void lab2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_6, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载多行扫描翻译界面 */
static void lab3_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_2, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_1(void)
{
	screen_1 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_1, gt_color_hex(0x000000));

	

	/** img1 */
	/** 文字背景图 */
	img1 = gt_img_create(screen_1);
	gt_obj_set_pos(img1, 15, 22);
	gt_obj_set_size(img1, 207, 87);
	gt_img_set_src(img1, "f:img_207x87_5_c.png");

	

	/** img4 */
	/** 返回图标 */
	img4 = gt_img_create(screen_1);
	gt_obj_set_pos(img4, 10, 16);
	gt_obj_set_size(img4, 16, 16);
	gt_img_set_src(img4, "f:img_16x16_icon_left.png");
	gt_obj_add_event_cb(img4, img4_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img5 */
	/** 扫描图片 */
	img5 = gt_img_create(screen_1);
	gt_obj_set_pos(img5, 211, 53);
	gt_obj_set_size(img5, 101, 94);
	gt_img_set_src(img5, "f:img_101x94_6_c.png");

	

	/** lab1 */
	/** 界面文字内容,高通优黑点阵16x16 */
	lab1 = gt_label_create(screen_1);
	gt_obj_set_pos(lab1, 27, 33);
	gt_obj_set_size(lab1, 194, 26);
	gt_label_set_font_color(lab1, gt_color_hex(0xc0c0c0));
	gt_label_set_font_size(lab1, 16);
	gt_label_set_font_family_cn(lab1, 24);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT);
	gt_label_set_space(lab1, 1, 0);
	gt_label_set_text(lab1, "将笔头对准内容，底部向");

	

	/** group1 */
	group1 = gt_group_create(screen_1);
	gt_obj_set_pos(group1, 22, 133);
	gt_obj_set_size(group1, 3, 2);

	

	/** radio2 */
	/** 单选框 */
	radio2 = gt_radio_create(group1);
	gt_obj_set_pos(radio2, 120, 124);
	gt_obj_set_size(radio2, 75, 24);
	gt_radio_set_font_color(radio2, gt_color_hex(0x000000));
	gt_radio_set_font_size(radio2, 16);
	gt_radio_set_text(radio2, "");
	gt_radio_set_selected(radio2);
	gt_radio_set_font_point_offset(radio2, 0, 0);
	gt_obj_add_event_cb(radio2, radio2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** radio1 */
	/** 单选框 */
	radio1 = gt_radio_create(group1);
	gt_obj_set_pos(radio1, 18, 124);
	gt_obj_set_size(radio1, 84, 24);
	gt_radio_set_font_color(radio1, gt_color_hex(0x000000));
	gt_radio_set_font_size(radio1, 16);
	gt_radio_set_text(radio1, "");
	gt_radio_set_font_point_offset(radio1, 0, 0);
	gt_obj_add_event_cb(radio1, radio1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab2 */
	/** 单行扫描文字，优黑16x16 */
	lab2 = gt_label_create(screen_1);
	gt_obj_set_pos(lab2, 43, 124);
	gt_obj_set_size(lab2, 75, 24);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 16);
	gt_label_set_font_family_cn(lab2, 24);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT);
	gt_label_set_space(lab2, 1, 0);
	gt_label_set_text(lab2, "单行扫描");
	gt_obj_add_event_cb(lab2, lab2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab3 */
	/** 多行扫描文字,优黑16x16 */
	lab3 = gt_label_create(screen_1);
	gt_obj_set_pos(lab3, 144, 124);
	gt_obj_set_size(lab3, 74, 24);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 16);
	gt_label_set_font_family_cn(lab3, 24);
	gt_label_set_font_align(lab3, GT_ALIGN_LEFT);
	gt_label_set_space(lab3, 1, 0);
	gt_label_set_text(lab3, "多行扫描");
	gt_obj_add_event_cb(lab3, lab3_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab4 */
	/** 界面文字内容，高通优黑点阵16x16 */
	lab4 = gt_label_create(screen_1);
	gt_obj_set_pos(lab4, 27, 60);
	gt_obj_set_size(lab4, 194, 24);
	gt_label_set_font_color(lab4, gt_color_hex(0xc0c0c0));
	gt_label_set_font_size(lab4, 16);
	gt_label_set_font_family_cn(lab4, 24);
	gt_label_set_font_align(lab4, GT_ALIGN_LEFT);
	gt_label_set_space(lab4, 1, 0);
	gt_label_set_text(lab4, "下按压，开始扫描翻译。");


	return screen_1;
}

