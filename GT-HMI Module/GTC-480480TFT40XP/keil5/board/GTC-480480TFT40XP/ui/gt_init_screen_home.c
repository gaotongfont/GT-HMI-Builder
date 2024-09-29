#include "gt_ui.h"


/** screen_home */
gt_obj_st * screen_home = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * img4 = NULL;
static gt_obj_st * img5 = NULL;

/** 按下加载调光灯界面 */
static void img2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_3, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载空调界面 */
static void img5_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_home(void)
{
	screen_home = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_home, gt_color_hex(0xFFFFFF));

	

	/** img1 */
	/** 主界面背景 */
	img1 = gt_img_create(screen_home);
	gt_obj_set_pos(img1, 0, 0);
	gt_obj_set_size(img1, 480, 480);
	gt_img_set_src(img1, "f:img_480x480_bj.png");

	

	/** lab1 */
	/** 时间显示，矢量72号，2bit */
	lab1 = gt_label_create(screen_home);
	gt_obj_set_pos(lab1, 193, 27);
	gt_obj_set_size(lab1, 160, 90);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 72);
	gt_label_set_font_family_cn(lab1, 80);
	gt_label_set_font_family_en(lab1, 84);
	gt_label_set_font_gray(lab1, 2);
	gt_label_set_text(lab1, "9:02");

	

	/** lab2 */
	/** 日期显示，矢量24号，4bit */
	lab2 = gt_label_create(screen_home);
	gt_obj_set_pos(lab2, 126, 126);
	gt_obj_set_size(lab2, 260, 32);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 80);
	gt_label_set_font_family_en(lab2, 84);
	gt_label_set_font_gray(lab2, 4);
	gt_label_set_text(lab2, "2023年5月26日 星期五");

	

	/** img2 */
	/** 调光灯图标 */
	img2 = gt_img_create(screen_home);
	gt_obj_set_pos(img2, 248, 213);
	gt_obj_set_size(img2, 204, 112);
	gt_img_set_src(img2, "f:img_204x112_270.png");
	gt_obj_add_event_cb(img2, img2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img3 */
	/** 电视图标 */
	img3 = gt_img_create(screen_home);
	gt_obj_set_pos(img3, 22, 342);
	gt_obj_set_size(img3, 204, 112);
	gt_img_set_src(img3, "f:img_204x112_267.png");

	

	/** img4 */
	/** 窗帘图标 */
	img4 = gt_img_create(screen_home);
	gt_obj_set_pos(img4, 248, 342);
	gt_obj_set_size(img4, 204, 112);
	gt_img_set_src(img4, "f:img_204x112_268.png");

	

	/** img5 */
	/** 空调图标 */
	img5 = gt_img_create(screen_home);
	gt_obj_set_pos(img5, 22, 213);
	gt_obj_set_size(img5, 204, 112);
	gt_img_set_src(img5, "f:img_204x112_269.png");
	gt_obj_add_event_cb(img5, img5_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	return screen_home;
}

