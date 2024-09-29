#include "gt_ui.h"


/** screen_5 */
gt_obj_st * screen_5 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * img4 = NULL;
static gt_obj_st * img5 = NULL;
static gt_obj_st * img6 = NULL;

/** 按下加载主界面 */
static void img2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载黄色灯光界面 */
static void img4_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_3, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载白色灯光界面 */
static void img5_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_4, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void img6_0_cb(gt_event_st * e) {
	
}

gt_obj_st * gt_init_screen_5(void)
{
	screen_5 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_5, gt_color_hex(0xFFFFFF));

	

	/** img1 */
	/** 调光灯背景图 */
	img1 = gt_img_create(screen_5);
	gt_obj_set_pos(img1, 0, 0);
	gt_obj_set_size(img1, 480, 480);
	gt_img_set_src(img1, "f:img_480x480_1.png");

	

	/** img2 */
	/** 返回图标 */
	img2 = gt_img_create(screen_5);
	gt_obj_set_pos(img2, 19, 22);
	gt_obj_set_size(img2, 15, 26);
	gt_img_set_src(img2, "f:img_15x26_187.png");
	gt_obj_add_event_cb(img2, img2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab1 */
	/** 调光灯文字，矢量24号，4bit */
	lab1 = gt_label_create(screen_5);
	gt_obj_set_pos(lab1, 52, 19);
	gt_obj_set_size(lab1, 80, 32);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 80);
	gt_label_set_font_family_en(lab1, 84);
	gt_label_set_font_gray(lab1, 4);
	gt_label_set_text(lab1, "调光灯                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            ");

	

	/** img3 */
	/** 红色灯图片 */
	img3 = gt_img_create(screen_5);
	gt_obj_set_pos(img3, 98, 0);
	gt_obj_set_size(img3, 289, 289);
	gt_img_set_src(img3, "f:img_289x289_400.png");

	

	/** img4 */
	/** 黄色未选中效果 */
	img4 = gt_img_create(screen_5);
	gt_obj_set_pos(img4, 36, 366);
	gt_obj_set_size(img4, 104, 42);
	gt_img_set_src(img4, "f:img_104x42_617.png");
	gt_obj_add_event_cb(img4, img4_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img5 */
	/** 白色未选中效果 */
	img5 = gt_img_create(screen_5);
	gt_obj_set_pos(img5, 186, 366);
	gt_obj_set_size(img5, 104, 42);
	gt_img_set_src(img5, "f:img_104x42_618.png");
	gt_obj_add_event_cb(img5, img5_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img6 */
	/** 红色选中效果 */
	img6 = gt_img_create(screen_5);
	gt_obj_set_pos(img6, 331, 366);
	gt_obj_set_size(img6, 104, 42);
	gt_img_set_src(img6, "f:img_104x42_615.png");


	return screen_5;
}

