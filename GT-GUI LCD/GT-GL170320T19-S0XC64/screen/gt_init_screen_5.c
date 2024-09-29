#include "gt_ui.h"


/** screen_5 */
gt_obj_st * screen_5 = NULL;
static gt_obj_st * img9 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * btn2 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * btn3 = NULL;
static gt_obj_st * btn4 = NULL;
static gt_obj_st * btn5 = NULL;

/** 按下加载回主界面 */
static void img9_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载字词界面 */
static void btn1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_4, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_5(void)
{
	screen_5 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_5, gt_color_hex(0x000000));

	

	/** img9 */
	/** 返回图标 */
	img9 = gt_img_create(screen_5);
	gt_obj_set_pos(img9, 10, 16);
	gt_obj_set_size(img9, 16, 16);
	gt_img_set_src(img9, "f:img_16x16_icon_left.png");
	gt_obj_add_event_cb(img9, img9_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** btn1 */
	/** 字词按钮 */
	btn1 = gt_btn_create(screen_5);
	gt_obj_set_pos(btn1, 29, 11);
	gt_obj_set_size(btn1, 118, 36);
	gt_btn_set_font_color(btn1, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn1, 20);
	gt_btn_set_font_family_cn(btn1, 130);
	gt_btn_set_font_align(btn1, GT_ALIGN_CENTER_MID);
	gt_btn_set_space(btn1, 1, 0);
	gt_btn_set_text(btn1, "字词");
	gt_btn_set_color_background(btn1, gt_color_hex(0x384158));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn1, gt_color_hex(0x000000));
	gt_btn_set_radius(btn1, 10);
	gt_obj_add_event_cb(btn1, btn1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** btn2 */
	/** 句子按钮 */
	btn2 = gt_btn_create(screen_5);
	gt_obj_set_pos(btn2, 148, 11);
	gt_obj_set_size(btn2, 118, 36);
	gt_btn_set_font_color(btn2, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn2, 20);
	gt_btn_set_font_family_cn(btn2, 130);
	gt_btn_set_font_align(btn2, GT_ALIGN_CENTER_MID);
	gt_btn_set_space(btn2, 1, 0);
	gt_btn_set_text(btn2, "句子");
	gt_btn_set_color_background(btn2, gt_color_hex(0x6d5cff));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn2, gt_color_hex(0x000000));
	gt_btn_set_radius(btn2, 10);

	

	/** imgbtn1 */
	/** 删除图标 */
	imgbtn1 = gt_imgbtn_create(screen_5);
	gt_obj_set_pos(imgbtn1, 278, 18);
	gt_obj_set_size(imgbtn1, 28, 28);
	gt_obj_set_opa(imgbtn1, GT_OPA_80);
	gt_imgbtn_set_src(imgbtn1, "f:img_28x28_7_ic.png");

	

	/** btn3 */
	/** 英文句子，英文标准8x16 */
	btn3 = gt_btn_create(screen_5);
	gt_obj_set_pos(btn3, 29, 55);
	gt_obj_set_size(btn3, 240, 32);
	gt_btn_set_font_color(btn3, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn3, 16);
	gt_btn_set_font_family_en(btn3, 30);
	gt_btn_set_font_align(btn3, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn3, "It does not matter how…");
	gt_btn_set_color_background(btn3, gt_color_hex(0x171a20));
	gt_btn_set_color_pressed(btn3, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn3, gt_color_hex(0x000000));
	gt_btn_set_radius(btn3, 15);

	

	/** btn4 */
	/** 中文句子，优黑16x16 */
	btn4 = gt_btn_create(screen_5);
	gt_obj_set_pos(btn4, 27, 90);
	gt_obj_set_size(btn4, 240, 32);
	gt_btn_set_font_color(btn4, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn4, 16);
	gt_btn_set_font_family_cn(btn4, 24);
	gt_btn_set_font_align(btn4, GT_ALIGN_CENTER_MID);
	gt_btn_set_space(btn4, 1, 0);
	gt_btn_set_text(btn4, "为了对这个幽灵进行…");
	gt_btn_set_color_background(btn4, gt_color_hex(0x171a20));
	gt_btn_set_color_pressed(btn4, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn4, gt_color_hex(0x000000));
	gt_btn_set_radius(btn4, 15);

	

	/** btn5 */
	/** 英文句子，英文标准8x16 */
	btn5 = gt_btn_create(screen_5);
	gt_obj_set_pos(btn5, 27, 127);
	gt_obj_set_size(btn5, 240, 32);
	gt_btn_set_font_color(btn5, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn5, 16);
	gt_btn_set_font_family_cn(btn5, 24);
	gt_btn_set_font_family_en(btn5, 30);
	gt_btn_set_font_align(btn5, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(btn5, "Where is the party in op…");
	gt_btn_set_color_background(btn5, gt_color_hex(0x171a20));
	gt_btn_set_color_pressed(btn5, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn5, gt_color_hex(0x000000));
	gt_btn_set_radius(btn5, 15);


	return screen_5;
}

