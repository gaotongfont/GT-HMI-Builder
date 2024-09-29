#include "gt_ui.h"


/** screen_home3 */
gt_obj_st * screen_home3 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * imgbtn2 = NULL;
static gt_obj_st * imgbtn3 = NULL;

/** 按下加载到首页 */
static void imgbtn1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到吸氧计时页面 */
static void imgbtn2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME2, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到应用中心页面 */
static void imgbtn3_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME3, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_home3(void)
{
	screen_home3 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_home3, gt_color_hex(0xFFFFFF));

	

	/** img1 */
	/** 背景图片 */
	img1 = gt_img_create(screen_home3);
	gt_obj_set_pos(img1, 0, 0);
	gt_obj_set_size(img1, 480, 272);
	gt_img_set_src(img1, ".:img_480x272_hjzx3.png");

	

	/** imgbtn1 */
	/** 首页图标 */
	imgbtn1 = gt_imgbtn_create(screen_home3);
	gt_obj_set_pos(imgbtn1, 1, 229);
	gt_obj_set_size(imgbtn1, 160, 41);
	gt_imgbtn_set_src(imgbtn1, ".:img_160x41_sy_p_160x410x231.png");
	gt_obj_add_event_cb(imgbtn1, imgbtn1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn2 */
	/** 吸氧计时图标 */
	imgbtn2 = gt_imgbtn_create(screen_home3);
	gt_obj_set_pos(imgbtn2, 160, 229);
	gt_obj_set_size(imgbtn2, 160, 41);
	gt_imgbtn_set_src(imgbtn2, ".:img_160x41_xy.png");
	gt_obj_add_event_cb(imgbtn2, imgbtn2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn3 */
	/** 应用中心图标 */
	imgbtn3 = gt_imgbtn_create(screen_home3);
	gt_obj_set_pos(imgbtn3, 319, 229);
	gt_obj_set_size(imgbtn3, 160, 41);
	gt_imgbtn_set_src(imgbtn3, ".:img_160x41_yyzx.png");
	gt_obj_add_event_cb(imgbtn3, imgbtn3_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	return screen_home3;
}

