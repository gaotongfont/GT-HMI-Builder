#include "gt_ui.h"


/** screen_home2 */
gt_obj_st * screen_home2 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * imgbtn2 = NULL;
static gt_obj_st * imgbtn3 = NULL;
static gt_obj_st * clock1 = NULL;
static gt_obj_st * clock2 = NULL;

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

gt_obj_st * gt_init_screen_home2(void)
{
	screen_home2 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_home2, gt_color_hex(0xFFFFFF));

	

	/** img1 */
	/** 背景图片 */
	img1 = gt_img_create(screen_home2);
	gt_obj_set_pos(img1, 0, 0);
	gt_obj_set_size(img1, 480, 272);
	gt_img_set_src(img1, "f:img_480x272_hjzx4.png");

	

	/** imgbtn1 */
	/** 首页图标 */
	imgbtn1 = gt_imgbtn_create(screen_home2);
	gt_obj_set_pos(imgbtn1, 1, 229);
	gt_obj_set_size(imgbtn1, 160, 41);
	gt_imgbtn_set_src(imgbtn1, "f:img_160x41_sy_p_160x410x231.png");
	gt_obj_add_event_cb(imgbtn1, imgbtn1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn2 */
	/** 吸氧时间图标 */
	imgbtn2 = gt_imgbtn_create(screen_home2);
	gt_obj_set_pos(imgbtn2, 160, 229);
	gt_obj_set_size(imgbtn2, 160, 41);
	gt_imgbtn_set_src(imgbtn2, "f:img_160x41_xy_n_160x41160x231.png");
	gt_obj_add_event_cb(imgbtn2, imgbtn2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** imgbtn3 */
	/** 应用中心图标 */
	imgbtn3 = gt_imgbtn_create(screen_home2);
	gt_obj_set_pos(imgbtn3, 319, 229);
	gt_obj_set_size(imgbtn3, 160, 41);
	gt_imgbtn_set_src(imgbtn3, "f:img_160x41_yyzx_p_160x41320x231.png");
	gt_obj_add_event_cb(imgbtn3, imgbtn3_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** clock1 */
	/** 当次时间显示，模式设置为秒表倒计时 */
	clock1 = gt_clock_create(screen_home2);
	gt_obj_set_pos(clock1, 134, 77);
	gt_obj_set_size(clock1, 180, 48);
	gt_clock_set_font_color(clock1, gt_color_hex(0xffffff));
	gt_clock_set_font_size(clock1, 32);
	gt_clock_set_font_family_en(clock1, 43);
	gt_clock_set_time(clock1, 6, 30, 20);
	gt_clock_set_mode(clock1, GT_CLOCK_MODE_COUNTDOWN);
	gt_clock_set_format(clock1, "HH:mm:ss");
	gt_clock_start(clock1);

	

	/** clock2 */
	/** 当次时间显示，模式设置显示时间 */
	clock2 = gt_clock_create(screen_home2);
	gt_obj_set_pos(clock2, 134, 155);
	gt_obj_set_size(clock2, 200, 47);
	gt_clock_set_font_color(clock2, gt_color_hex(0xffffff));
	gt_clock_set_font_size(clock2, 32);
	gt_clock_set_font_family_en(clock2, 43);
	gt_clock_set_time(clock2, 8, 40, 20);
	gt_clock_set_format(clock2, "HH:mm:ss");
	gt_clock_start(clock2);


	return screen_home2;
}

