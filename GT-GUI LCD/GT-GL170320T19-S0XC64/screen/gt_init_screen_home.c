#include "gt_ui.h"


/** screen_home */
gt_obj_st * screen_home = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * imgbtn2 = NULL;
static gt_obj_st * imgbtn3 = NULL;
static gt_obj_st * img3 = NULL;

/** 按下加载扫描翻译界面 */
static void lab1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载生词本界面 */
static void lab2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_4, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载12K乐园界面 */
static void lab3_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_8, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载扫描翻译界面 */
static void imgbtn1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载生词本界面 */
static void imgbtn2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_4, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载12K乐园界面 */
static void imgbtn3_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_8, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_home(void)
{
	screen_home = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_home, gt_color_hex(0x000000));

	

	/** img1 */
	/** wifi图标 */
	img1 = gt_img_create(screen_home);
	gt_obj_set_pos(img1, 230, -1);
	gt_obj_set_size(img1, 30, 30);
	gt_obj_set_opa(img1, GT_OPA_90);
	gt_img_set_src(img1, "f:img_30x30_70_wifi_medium.png");

	

	/** img2 */
	/** 电池图标 */
	img2 = gt_img_create(screen_home);
	gt_obj_set_pos(img2, 282, 2);
	gt_obj_set_size(img2, 26, 26);
	gt_obj_set_opa(img2, GT_OPA_90);
	gt_img_set_src(img2, "f:img_26x26_2_battery_regular.png");

	

	/** lab1 */
	/** 扫描翻译文字，优黑16x16 */
	lab1 = gt_label_create(screen_home);
	gt_obj_set_pos(lab1, 26, 130);
	gt_obj_set_size(lab1, 80, 24);
	gt_label_set_font_color(lab1, gt_color_hex(0xfbfbfb));
	gt_label_set_font_size(lab1, 16);
	gt_label_set_font_family_cn(lab1, 24);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT);
	gt_label_set_space(lab1, 1, 0);
	gt_label_set_text(lab1, "扫描翻译");
	gt_obj_add_event_cb(lab1, lab1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab2 */
	/** 生词本文字 */
	lab2 = gt_label_create(screen_home);
	gt_obj_set_pos(lab2, 135, 130);
	gt_obj_set_size(lab2, 60, 24);
	gt_label_set_font_color(lab2, gt_color_hex(0xfbfbfb));
	gt_label_set_font_size(lab2, 16);
	gt_label_set_font_family_cn(lab2, 24);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT);
	gt_label_set_space(lab2, 1, 0);
	gt_label_set_text(lab2, "生词本");
	gt_obj_add_event_cb(lab2, lab2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab3 */
	/** 12K乐园文字 */
	lab3 = gt_label_create(screen_home);
	gt_obj_set_pos(lab3, 226, 130);
	gt_obj_set_size(lab3, 80, 24);
	gt_label_set_font_color(lab3, gt_color_hex(0xfbfbfb));
	gt_label_set_font_size(lab3, 16);
	gt_label_set_font_family_cn(lab3, 24);
	gt_label_set_font_family_en(lab3, 38);
	gt_label_set_font_align(lab3, GT_ALIGN_LEFT);
	gt_label_set_space(lab3, 1, 0);
	gt_label_set_text(lab3, "12K乐园");
	gt_obj_add_event_cb(lab3, lab3_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn1 */
	/** 扫描翻译图标 */
	imgbtn1 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn1, 15, 38);
	gt_obj_set_size(imgbtn1, 84, 84);
	gt_imgbtn_set_src(imgbtn1, "f:img_84x84_1_c.png");
	gt_obj_add_event_cb(imgbtn1, imgbtn1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn2 */
	/** 生词本图标 */
	imgbtn2 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn2, 115, 37);
	gt_obj_set_size(imgbtn2, 84, 84);
	gt_imgbtn_set_src(imgbtn2, "f:img_84x84_2_c.png");
	gt_obj_add_event_cb(imgbtn2, imgbtn2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn3 */
	/** 12K乐园图标 */
	imgbtn3 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn3, 215, 38);
	gt_obj_set_size(imgbtn3, 84, 84);
	gt_imgbtn_set_src(imgbtn3, "f:img_84x84_0_c.png");
	gt_obj_add_event_cb(imgbtn3, imgbtn3_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img3 */
	/** 授权图标 */
	img3 = gt_img_create(screen_home);
	gt_obj_set_pos(img3, 258, 7);
	gt_obj_set_size(img3, 18, 15);
	gt_obj_set_opa(img3, GT_OPA_90);
	gt_img_set_src(img3, "f:img_18x15_4_c.png");


	return screen_home;
}

