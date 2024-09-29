#include "gt_ui.h"


/** screen_12 */
gt_obj_st * screen_12 = NULL;
static gt_obj_st * img7 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * slider1 = NULL;
static gt_obj_st * img4 = NULL;
static gt_obj_st * clock1 = NULL;
static gt_obj_st * lab1 = NULL;

/** 按下加载回K12列表界面 */
static void img7_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_8, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载时钟的开启暂停 */
static void imgbtn1_0_cb(gt_event_st * e) {
	gt_clock_toggle(clock1);
}

static void slider1_0_cb(gt_event_st * e) {
	gt_clock_turn_next_second(clock1);
}

gt_obj_st * gt_init_screen_12(void)
{
	screen_12 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_12, gt_color_hex(0x000000));

	

	/** img7 */
	/** 返回图标 */
	img7 = gt_img_create(screen_12);
	gt_obj_set_pos(img7, 8, 14);
	gt_obj_set_size(img7, 16, 16);
	gt_img_set_src(img7, "f:img_16x16_icon_left.png");
	gt_obj_add_event_cb(img7, img7_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img2 */
	/** 上一曲图标 */
	img2 = gt_img_create(screen_12);
	gt_obj_set_pos(img2, 27, 65);
	gt_obj_set_size(img2, 36, 36);
	gt_img_set_src(img2, "f:img_36x36_54_previous.png");

	

	/** img3 */
	/** 下一曲图标 */
	img3 = gt_img_create(screen_12);
	gt_obj_set_pos(img3, 260, 67);
	gt_obj_set_size(img3, 36, 36);
	gt_img_set_src(img3, "f:img_36x36_45_next.png");

	

	/** imgbtn1 */
	/** 暂停/播放图标 */
	imgbtn1 = gt_imgbtn_create(screen_12);
	gt_obj_set_pos(imgbtn1, 125, 48);
	gt_obj_set_size(imgbtn1, 68, 68);
	gt_imgbtn_set_src(imgbtn1, "f:img_68x68_2372.png");
	gt_imgbtn_add_state_item(imgbtn1, "f:img_68x68_2060.png");
	gt_obj_add_event_cb(imgbtn1, imgbtn1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** slider1 */
	/** 时间滑动条 */
	slider1 = gt_slider_create(screen_12);
	gt_obj_set_pos(slider1, 46, 137);
	gt_obj_set_size(slider1, 180, 16);
	gt_slider_set_start_end(slider1, 0, 30);
	gt_slider_set_pos(slider1, 0);
	gt_slider_set_color_act(slider1, gt_color_hex(0x409eff));
	gt_slider_set_color_ina(slider1, gt_color_hex(0xebeef5));
	gt_slider_set_tag_visible(slider1, 1);
	gt_slider_set_dir(slider1, GT_BAR_DIR_HOR_L2R);
	gt_obj_add_event_cb(slider1, slider1_0_cb, GT_EVENT_TYPE_INPUT_SCROLL, NULL);
	

	/** img4 */
	/** 音量图标 */
	img4 = gt_img_create(screen_12);
	gt_obj_set_pos(img4, 14, 133);
	gt_obj_set_size(img4, 24, 24);
	gt_img_set_src(img4, "f:img_24x24_85_volume_notice.png");

	

	/** clock1 */
	/** 播放倒计时 */
	clock1 = gt_clock_create(screen_12);
	gt_obj_set_pos(clock1, 236, 129);
	gt_obj_set_size(clock1, 78, 32);
	gt_clock_set_font_color(clock1, gt_color_hex(0xffffff));
	gt_clock_set_font_size(clock1, 16);
	gt_clock_set_font_family_en(clock1, 39);
	gt_clock_set_font_align(clock1, GT_ALIGN_LEFT);
	gt_clock_set_time(clock1, 0, 0, 0);
	gt_clock_set_alert_time(clock1, 0, 0, 30);
	gt_clock_set_format(clock1, "hh:mm:ss");
	gt_clock_start(clock1);

	

	/** lab1 */
	lab1 = gt_label_create(screen_12);
	gt_obj_set_pos(lab1, 34, 13);
	gt_obj_set_size(lab1, 95, 30);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 20);
	gt_label_set_font_family_cn(lab1, 130);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT);
	gt_label_set_space(lab1, 1, 0);
	gt_label_set_text(lab1, "儿童启蒙");


	return screen_12;
}

