#include "gt_ui.h"


/** screen_9 */
gt_obj_st * screen_9 = NULL;
static gt_obj_st * img7 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * btn2 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * btn3 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * img2 = NULL;

/** 按下加载回K12列表界面 */
static void img7_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_8, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到美人鱼故事界面 */
static void btn1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_10, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到美人鱼故事界面 */
static void lab1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_10, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void lab2_0_cb(gt_event_st * e) {
	
}

gt_obj_st * gt_init_screen_9(void)
{
	screen_9 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_9, gt_color_hex(0x000000));

	

	/** img7 */
	/** 返回图标 */
	img7 = gt_img_create(screen_9);
	gt_obj_set_pos(img7, 10, 16);
	gt_obj_set_size(img7, 16, 16);
	gt_img_set_src(img7, ".:img_16x16_icon_left.png");
	gt_obj_add_event_cb(img7, img7_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** btn1 */
	/** 美人鱼按钮 */
	btn1 = gt_btn_create(screen_9);
	gt_obj_set_pos(btn1, 25, 41);
	gt_obj_set_size(btn1, 280, 36);
	gt_btn_set_font_color(btn1, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn1, 16);
	gt_btn_set_font_align(btn1, GT_ALIGN_LEFT);
	gt_btn_set_text(btn1, "");
	gt_btn_set_color_background(btn1, gt_color_hex(0x22272c));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn1, gt_color_hex(0x000000));
	gt_btn_set_radius(btn1, 10);
	gt_obj_add_event_cb(btn1, btn1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab1 */
	/** 美人鱼文字，优黑16x16 */
	lab1 = gt_label_create(screen_9);
	gt_obj_set_pos(lab1, 46, 46);
	gt_obj_set_size(lab1, 120, 24);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 16);
	gt_label_set_font_family_cn(lab1, 24);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT);
	gt_label_set_space(lab1, 1, 0);
	gt_label_set_text(lab1, "美人鱼");
	gt_obj_add_event_cb(lab1, lab1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** btn2 */
	/** 孟母三迁按钮 */
	btn2 = gt_btn_create(screen_9);
	gt_obj_set_pos(btn2, 25, 81);
	gt_obj_set_size(btn2, 280, 36);
	gt_btn_set_font_color(btn2, gt_color_hex(0x000000));
	gt_btn_set_font_size(btn2, 16);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn2, "");
	gt_btn_set_color_background(btn2, gt_color_hex(0x22272c));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn2, gt_color_hex(0x000000));
	gt_btn_set_radius(btn2, 10);

	

	/** lab2 */
	/** 孟母三迁文字，优黑16x16 */
	lab2 = gt_label_create(screen_9);
	gt_obj_set_pos(lab2, 46, 86);
	gt_obj_set_size(lab2, 120, 24);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 16);
	gt_label_set_font_family_cn(lab2, 24);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT);
	gt_label_set_space(lab2, 1, 0);
	gt_label_set_text(lab2, "孟母三迁");
	gt_obj_add_event_cb(lab2, lab2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** btn3 */
	/** 桃园三结义按钮 */
	btn3 = gt_btn_create(screen_9);
	gt_obj_set_pos(btn3, 25, 121);
	gt_obj_set_size(btn3, 280, 36);
	gt_btn_set_font_color(btn3, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn3, 16);
	gt_btn_set_font_align(btn3, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn3, "");
	gt_btn_set_color_background(btn3, gt_color_hex(0x22272c));
	gt_btn_set_color_pressed(btn3, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn3, gt_color_hex(0x000000));
	gt_btn_set_radius(btn3, 10);

	

	/** lab3 */
	/** 桃园三结义文字，优黑16x16 */
	lab3 = gt_label_create(screen_9);
	gt_obj_set_pos(lab3, 46, 127);
	gt_obj_set_size(lab3, 120, 24);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 16);
	gt_label_set_font_family_cn(lab3, 24);
	gt_label_set_font_align(lab3, GT_ALIGN_LEFT);
	gt_label_set_space(lab3, 1, 0);
	gt_label_set_text(lab3, "桃园三结义");

	

	/** lab4 */
	/** 益智故事文字，优黑20x20 */
	lab4 = gt_label_create(screen_9);
	gt_obj_set_pos(lab4, 31, 12);
	gt_obj_set_size(lab4, 90, 24);
	gt_label_set_font_color(lab4, gt_color_hex(0xc0c0c0));
	gt_label_set_font_size(lab4, 20);
	gt_label_set_font_family_cn(lab4, 130);
	gt_label_set_font_align(lab4, GT_ALIGN_LEFT);
	gt_label_set_space(lab4, 1, 0);
	gt_label_set_text(lab4, "益智故事");

	

	/** img2 */
	img2 = gt_img_create(screen_9);
	gt_obj_set_pos(img2, 281, 52);
	gt_obj_set_size(img2, 12, 20);
	gt_img_set_src(img2, ".:img_12x20__images_arrow_right.png");


	return screen_9;
}

