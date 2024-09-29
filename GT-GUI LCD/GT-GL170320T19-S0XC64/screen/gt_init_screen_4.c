#include "gt_ui.h"


/** screen_4 */
gt_obj_st * screen_4 = NULL;
static gt_obj_st * img8 = NULL;
static gt_obj_st * btn7 = NULL;
static gt_obj_st * btn6 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * btn11 = NULL;
static gt_obj_st * btn12 = NULL;
static gt_obj_st * btn13 = NULL;
static gt_obj_st * btn14 = NULL;
static gt_obj_st * btn15 = NULL;
static gt_obj_st * btn16 = NULL;

/** 按下加载回主界面 */
static void img8_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载句子界面 */
static void btn6_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_5, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_4(void)
{
	screen_4 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_4, gt_color_hex(0x000000));

	

	/** img8 */
	/** 返回图标 */
	img8 = gt_img_create(screen_4);
	gt_obj_set_pos(img8, 8, 14);
	gt_obj_set_size(img8, 16, 16);
	gt_img_set_src(img8, "f:img_16x16_icon_left.png");
	gt_obj_add_event_cb(img8, img8_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** btn7 */
	/** 字词按钮 */
	btn7 = gt_btn_create(screen_4);
	gt_obj_set_pos(btn7, 31, 13);
	gt_obj_set_size(btn7, 118, 36);
	gt_btn_set_font_color(btn7, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn7, 20);
	gt_btn_set_font_family_cn(btn7, 130);
	gt_btn_set_font_align(btn7, GT_ALIGN_CENTER_MID);
	gt_btn_set_space(btn7, 1, 0);
	gt_btn_set_text(btn7, "字词");
	gt_btn_set_color_background(btn7, gt_color_hex(0x6d5cff));
	gt_btn_set_color_pressed(btn7, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn7, gt_color_hex(0x000000));
	gt_btn_set_radius(btn7, 10);

	

	/** btn6 */
	/** 句子按钮 */
	btn6 = gt_btn_create(screen_4);
	gt_obj_set_pos(btn6, 148, 11);
	gt_obj_set_size(btn6, 118, 36);
	gt_btn_set_font_color(btn6, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn6, 20);
	gt_btn_set_font_family_cn(btn6, 130);
	gt_btn_set_font_align(btn6, GT_ALIGN_CENTER_MID);
	gt_btn_set_space(btn6, 1, 0);
	gt_btn_set_text(btn6, "句子");
	gt_btn_set_color_background(btn6, gt_color_hex(0x384158));
	gt_btn_set_color_pressed(btn6, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn6, gt_color_hex(0x000000));
	gt_btn_set_radius(btn6, 10);
	gt_obj_add_event_cb(btn6, btn6_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn1 */
	/** 删除图标 */
	imgbtn1 = gt_imgbtn_create(screen_4);
	gt_obj_set_pos(imgbtn1, 278, 18);
	gt_obj_set_size(imgbtn1, 28, 28);
	gt_obj_set_opa(imgbtn1, GT_OPA_80);
	gt_imgbtn_set_src(imgbtn1, "f:img_28x28_7_ic.png");

	

	/** btn11 */
	/** Alliance，英文标准8x16 */
	btn11 = gt_btn_create(screen_4);
	gt_obj_set_pos(btn11, 27, 53);
	gt_obj_set_size(btn11, 118, 32);
	gt_btn_set_font_color(btn11, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn11, 16);
	gt_btn_set_font_family_en(btn11, 30);
	gt_btn_set_font_align(btn11, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn11, "Alliance");
	gt_btn_set_color_background(btn11, gt_color_hex(0x171a20));
	gt_btn_set_color_pressed(btn11, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn11, gt_color_hex(0x000000));
	gt_btn_set_radius(btn11, 15);

	

	/** btn12 */
	/** 的，优黑16x16 */
	btn12 = gt_btn_create(screen_4);
	gt_obj_set_pos(btn12, 149, 53);
	gt_obj_set_size(btn12, 118, 32);
	gt_btn_set_font_color(btn12, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn12, 16);
	gt_btn_set_font_family_cn(btn12, 24);
	gt_btn_set_font_align(btn12, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn12, "的");
	gt_btn_set_color_background(btn12, gt_color_hex(0x171a20));
	gt_btn_set_color_pressed(btn12, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn12, gt_color_hex(0x000000));
	gt_btn_set_radius(btn12, 15);

	

	/** btn13 */
	/** psychol，英文标准8x16 */
	btn13 = gt_btn_create(screen_4);
	gt_obj_set_pos(btn13, 27, 90);
	gt_obj_set_size(btn13, 118, 32);
	gt_btn_set_font_color(btn13, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn13, 16);
	gt_btn_set_font_family_en(btn13, 30);
	gt_btn_set_font_align(btn13, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn13, "psychol");
	gt_btn_set_color_background(btn13, gt_color_hex(0x171a20));
	gt_btn_set_color_pressed(btn13, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn13, gt_color_hex(0x000000));
	gt_btn_set_radius(btn13, 15);

	

	/** btn14 */
	/** All，英文标准8x16 */
	btn14 = gt_btn_create(screen_4);
	gt_obj_set_pos(btn14, 148, 90);
	gt_obj_set_size(btn14, 118, 32);
	gt_btn_set_font_color(btn14, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn14, 16);
	gt_btn_set_font_family_en(btn14, 30);
	gt_btn_set_font_align(btn14, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn14, "All");
	gt_btn_set_color_background(btn14, gt_color_hex(0x171a20));
	gt_btn_set_color_pressed(btn14, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn14, gt_color_hex(0x000000));
	gt_btn_set_radius(btn14, 15);

	

	/** btn15 */
	/** 笔，优黑16x16 */
	btn15 = gt_btn_create(screen_4);
	gt_obj_set_pos(btn15, 27, 127);
	gt_obj_set_size(btn15, 118, 32);
	gt_btn_set_font_color(btn15, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn15, 16);
	gt_btn_set_font_family_cn(btn15, 24);
	gt_btn_set_font_align(btn15, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn15, "笔");
	gt_btn_set_color_background(btn15, gt_color_hex(0x171a20));
	gt_btn_set_color_pressed(btn15, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn15, gt_color_hex(0x000000));
	gt_btn_set_radius(btn15, 15);

	

	/** btn16 */
	/** tree，英文标准8x16 */
	btn16 = gt_btn_create(screen_4);
	gt_obj_set_pos(btn16, 148, 127);
	gt_obj_set_size(btn16, 118, 32);
	gt_btn_set_font_color(btn16, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn16, 16);
	gt_btn_set_font_family_en(btn16, 30);
	gt_btn_set_font_align(btn16, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn16, "tree");
	gt_btn_set_color_background(btn16, gt_color_hex(0x171a20));
	gt_btn_set_color_pressed(btn16, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn16, gt_color_hex(0x000000));
	gt_btn_set_radius(btn16, 15);


	return screen_4;
}

