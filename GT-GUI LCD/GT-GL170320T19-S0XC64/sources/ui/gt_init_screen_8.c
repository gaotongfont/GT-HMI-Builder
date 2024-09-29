#include "gt_ui.h"


/** screen_8 */
gt_obj_st * screen_8 = NULL;
static gt_obj_st * img7 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * btn2 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * btn3 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * img4 = NULL;
static gt_obj_st * img5 = NULL;
static gt_obj_st * img6 = NULL;
static gt_obj_st * img8 = NULL;

/** 按下加载回主界面 */
static void img7_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到益智故事界面 */
static void btn1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_9, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到益智故事界面 */
static void img2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_9, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到益智故事界面 */
static void lab1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_9, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到快乐儿歌界面 */
static void btn2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_11, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到快乐儿歌界面 */
static void img3_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_11, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到快乐儿歌界面 */
static void lab2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_11, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到儿童启蒙界面 */
static void btn3_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_12, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到儿童启蒙界面 */
static void lab3_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_12, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到儿童启蒙界面 */
static void img4_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_12, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_8(void)
{
	screen_8 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_8, gt_color_hex(0x000000));

	

	/** img7 */
	/** 返回图标 */
	img7 = gt_img_create(screen_8);
	gt_obj_set_pos(img7, 10, 16);
	gt_obj_set_size(img7, 16, 16);
	gt_img_set_src(img7, ".:img_16x16_icon_left.png");
	gt_obj_add_event_cb(img7, img7_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** btn1 */
	/** 益智故事按钮 */
	btn1 = gt_btn_create(screen_8);
	gt_obj_set_pos(btn1, 25, 15);
	gt_obj_set_size(btn1, 280, 40);
	gt_btn_set_font_color(btn1, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn1, 16);
	gt_btn_set_font_align(btn1, GT_ALIGN_LEFT);
	gt_btn_set_text(btn1, "");
	gt_btn_set_color_background(btn1, gt_color_hex(0x22272c));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn1, gt_color_hex(0x000000));
	gt_btn_set_radius(btn1, 10);
	gt_obj_add_event_cb(btn1, btn1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img2 */
	/** 益智故事图标 */
	img2 = gt_img_create(screen_8);
	gt_obj_set_pos(img2, 41, 20);
	gt_obj_set_size(img2, 19, 25);
	gt_img_set_src(img2, ".:img_19x25_7_c.png");
	gt_obj_add_event_cb(img2, img2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab1 */
	/** 益智故事文字，优黑20x20 */
	lab1 = gt_label_create(screen_8);
	gt_obj_set_pos(lab1, 76, 21);
	gt_obj_set_size(lab1, 120, 24);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 20);
	gt_label_set_font_family_cn(lab1, 130);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT);
	gt_label_set_space(lab1, 1, 0);
	gt_label_set_text(lab1, "益智故事");
	gt_obj_add_event_cb(lab1, lab1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** btn2 */
	/** 快乐儿歌按钮 */
	btn2 = gt_btn_create(screen_8);
	gt_obj_set_pos(btn2, 25, 62);
	gt_obj_set_size(btn2, 280, 40);
	gt_btn_set_font_color(btn2, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn2, 16);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn2, "");
	gt_btn_set_color_background(btn2, gt_color_hex(0x22272c));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn2, gt_color_hex(0x000000));
	gt_btn_set_radius(btn2, 10);
	gt_obj_add_event_cb(btn2, btn2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img3 */
	/** 快乐儿歌图标 */
	img3 = gt_img_create(screen_8);
	gt_obj_set_pos(img3, 41, 70);
	gt_obj_set_size(img3, 21, 21);
	gt_img_set_src(img3, ".:img_21x21_8_c.png");
	gt_obj_add_event_cb(img3, img3_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab2 */
	/** 快乐儿歌文字，优黑20x20 */
	lab2 = gt_label_create(screen_8);
	gt_obj_set_pos(lab2, 74, 69);
	gt_obj_set_size(lab2, 120, 24);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 20);
	gt_label_set_font_family_cn(lab2, 130);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT);
	gt_label_set_space(lab2, 1, 0);
	gt_label_set_text(lab2, "快乐儿歌");
	gt_obj_add_event_cb(lab2, lab2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** btn3 */
	/** 儿童启蒙按钮 */
	btn3 = gt_btn_create(screen_8);
	gt_obj_set_pos(btn3, 25, 109);
	gt_obj_set_size(btn3, 280, 40);
	gt_btn_set_font_color(btn3, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn3, 16);
	gt_btn_set_font_align(btn3, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn3, "");
	gt_btn_set_color_background(btn3, gt_color_hex(0x22272c));
	gt_btn_set_color_pressed(btn3, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn3, gt_color_hex(0x000000));
	gt_btn_set_radius(btn3, 10);
	gt_obj_add_event_cb(btn3, btn3_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab3 */
	/** 儿童启蒙文字，优黑20x20 */
	lab3 = gt_label_create(screen_8);
	gt_obj_set_pos(lab3, 74, 116);
	gt_obj_set_size(lab3, 120, 24);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 20);
	gt_label_set_font_family_cn(lab3, 130);
	gt_label_set_font_align(lab3, GT_ALIGN_LEFT);
	gt_label_set_space(lab3, 1, 0);
	gt_label_set_text(lab3, "儿童启蒙");
	gt_obj_add_event_cb(lab3, lab3_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img4 */
	/** 儿童启蒙图标 */
	img4 = gt_img_create(screen_8);
	gt_obj_set_pos(img4, 41, 121);
	gt_obj_set_size(img4, 21, 19);
	gt_img_set_src(img4, ".:img_21x19_9_c.png");
	gt_obj_add_event_cb(img4, img4_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img5 */
	/** 箭头图标 */
	img5 = gt_img_create(screen_8);
	gt_obj_set_pos(img5, 276, 28);
	gt_obj_set_size(img5, 12, 20);
	gt_img_set_src(img5, ".:img_12x20__images_arrow_right.png");

	

	/** img6 */
	/** 箭头图标 */
	img6 = gt_img_create(screen_8);
	gt_obj_set_pos(img6, 277, 75);
	gt_obj_set_size(img6, 12, 20);
	gt_img_set_src(img6, ".:img_12x20__images_arrow_right.png");

	

	/** img8 */
	/** 箭头图标 */
	img8 = gt_img_create(screen_8);
	gt_obj_set_pos(img8, 278, 124);
	gt_obj_set_size(img8, 12, 20);
	gt_img_set_src(img8, ".:img_12x20__images_arrow_right.png");


	return screen_8;
}

