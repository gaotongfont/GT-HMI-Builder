#include "gt_ui.h"


/** screen_10 */
gt_obj_st * screen_10 = NULL;
static gt_obj_st * img7 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * slider1 = NULL;
static gt_obj_st * clock1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * imgbtn2 = NULL;

/** 按下加载回益智故事列表 */
static void img7_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_9, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载时钟的开启暂停 */
static void imgbtn1_0_cb(gt_event_st * e) {
	gt_clock_toggle(clock1);
}

/** 滑动增加1秒 */
static void slider1_0_cb(gt_event_st * e) {
	gt_clock_turn_next_second(clock1);
}

gt_obj_st * gt_init_screen_10(void)
{
	screen_10 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_10, gt_color_hex(0x000000));

	

	/** img7 */
	/** 返回图标 */
	img7 = gt_img_create(screen_10);
	gt_obj_set_pos(img7, 10, 16);
	gt_obj_set_size(img7, 16, 16);
	gt_img_set_src(img7, ".:img_16x16_icon_left.png");
	gt_obj_add_event_cb(img7, img7_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img2 */
	/** 上一曲图标 */
	img2 = gt_img_create(screen_10);
	gt_obj_set_pos(img2, 27, 65);
	gt_obj_set_size(img2, 36, 36);
	gt_img_set_src(img2, ".:img_36x36_54_previous.png");

	

	/** img3 */
	/** 下一曲图标 */
	img3 = gt_img_create(screen_10);
	gt_obj_set_pos(img3, 258, 65);
	gt_obj_set_size(img3, 36, 36);
	gt_img_set_src(img3, ".:img_36x36_45_next.png");

	

	/** imgbtn1 */
	/** 暂停/播放图标 */
	imgbtn1 = gt_imgbtn_create(screen_10);
	gt_obj_set_pos(imgbtn1, 123, 46);
	gt_obj_set_size(imgbtn1, 68, 68);
	gt_imgbtn_set_src(imgbtn1, ".:img_68x68_2372.png");
	gt_imgbtn_add_state_item(imgbtn1, ".:img_68x68_2060.png");
	gt_obj_add_event_cb(imgbtn1, imgbtn1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** slider1 */
	/** 时间滑动条 */
	slider1 = gt_slider_create(screen_10);
	gt_obj_set_pos(slider1, 44, 135);
	gt_obj_set_size(slider1, 180, 16);
	gt_slider_set_start_end(slider1, 0, 30);
	gt_slider_set_pos(slider1, 0);
	gt_slider_set_color_act(slider1, gt_color_hex(0x409eff));
	gt_slider_set_color_ina(slider1, gt_color_hex(0xebeef5));
	gt_slider_set_tag_visible(slider1, 1);
	gt_slider_set_dir(slider1, GT_BAR_DIR_HOR_L2R);
	gt_obj_add_event_cb(slider1, slider1_0_cb, GT_EVENT_TYPE_INPUT_SCROLL, NULL);
	

	/** clock1 */
	/** 播放倒计时 */
	clock1 = gt_clock_create(screen_10);
	gt_obj_set_pos(clock1, 236, 129);
	gt_obj_set_size(clock1, 78, 25);
	gt_clock_set_font_color(clock1, gt_color_hex(0xffffff));
	gt_clock_set_font_size(clock1, 16);
	gt_clock_set_font_family_en(clock1, 39);
	gt_clock_set_font_align(clock1, GT_ALIGN_LEFT);
	gt_clock_set_time(clock1, 0, 0, 0);
	gt_clock_set_alert_time(clock1, 0, 0, 30);
	gt_clock_set_format(clock1, "hh:mm:ss");
	gt_clock_start(clock1);

	

	/** lab1 */
	/** 美人鱼文字，优黑20x20 */
	lab1 = gt_label_create(screen_10);
	gt_obj_set_pos(lab1, 32, 11);
	gt_obj_set_size(lab1, 86, 24);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 20);
	gt_label_set_font_family_cn(lab1, 130);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT);
	gt_label_set_space(lab1, 1, 0);
	gt_label_set_text(lab1, "美人鱼");

	

	/** imgbtn2 */
	/** 音量图标 */
	imgbtn2 = gt_imgbtn_create(screen_10);
	gt_obj_set_pos(imgbtn2, 12, 131);
	gt_obj_set_size(imgbtn2, 24, 24);
	gt_imgbtn_set_src(imgbtn2, ".:img_24x24_85_volume_notice.png");


	return screen_10;
}

