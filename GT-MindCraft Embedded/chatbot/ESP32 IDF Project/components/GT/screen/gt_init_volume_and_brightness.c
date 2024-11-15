#include "gt_ui.h"
#include "gt_font_config.h"


/** volume_and_brightness */
gt_obj_st * volume_and_brightness = NULL;
static gt_obj_st * VolumeSettings = NULL;
static gt_obj_st * Volume_progress_bar = NULL;
static gt_obj_st * Screenbrightness = NULL;
static gt_obj_st * Brightness_progress_bar = NULL;
static gt_obj_st * Volume_Up = NULL;
static gt_obj_st * Volume_Down = NULL;
static gt_obj_st * Brightness_Plus = NULL;
static gt_obj_st * Brightness_down = NULL;

static void screen_home_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

static void Volume_Up_0_cb(gt_event_st * e) {
	gt_obj_st * target = (gt_obj_st * )e->user_data;
	gt_event_send(target, GT_EVENT_TYPE_INPUT_SCROLL_DOWN, NULL);
}

static void Volume_Down_0_cb(gt_event_st * e) {
	gt_obj_st * target = (gt_obj_st * )e->user_data;
	gt_event_send(target, GT_EVENT_TYPE_INPUT_SCROLL_UP, NULL);
}

static void Brightness_Plus_0_cb(gt_event_st * e) {
	gt_obj_st * target = (gt_obj_st * )e->user_data;
	gt_event_send(target, GT_EVENT_TYPE_INPUT_SCROLL_DOWN, NULL);
}

static void Brightness_down_0_cb(gt_event_st * e) {
	gt_obj_st * target = (gt_obj_st * )e->user_data;
	gt_event_send(target, GT_EVENT_TYPE_INPUT_SCROLL_UP, NULL);
}

gt_obj_st * gt_init_volume_and_brightness(void)
{
	volume_and_brightness = gt_obj_create(NULL);
	gt_obj_add_event_cb(volume_and_brightness, screen_home_0_cb, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
	gt_screen_set_bgcolor(volume_and_brightness, gt_color_hex(0x000000));


	

	/** VolumeSettings */
	/** 音量设置 */
	VolumeSettings = gt_label_create(volume_and_brightness);
	gt_obj_set_pos(VolumeSettings, 30, 8);
	gt_obj_set_size(VolumeSettings, 84, 27);
	gt_label_set_font_color(VolumeSettings, gt_color_hex(0xc0c0c0));
	gt_label_set_font_family(VolumeSettings, gray_black_16);
	gt_label_set_font_cjk(VolumeSettings, 0);
	gt_label_set_font_align(VolumeSettings, GT_ALIGN_LEFT_MID);
	gt_label_set_text(VolumeSettings, "音量设置");

	

	/** Volume_progress_bar */
	/** 音量进度条 */
	Volume_progress_bar = gt_progress_bar_create(volume_and_brightness);
	gt_obj_set_pos(Volume_progress_bar, 46, 88);
	gt_obj_set_size(Volume_progress_bar, 35, 180);
	gt_progress_bar_set_start_end(Volume_progress_bar, 0, 100);
	gt_progress_bar_set_pos(Volume_progress_bar, 50);
	gt_progress_bar_set_color_act(Volume_progress_bar, gt_color_hex(0x409eff));
	gt_progress_bar_set_color_ina(Volume_progress_bar, gt_color_hex(0x181B22));
	gt_progress_bar_set_dir(Volume_progress_bar, GT_BAR_DIR_VER_D2U);

	

	/** Screenbrightness */
	/** 屏幕亮度 */
	Screenbrightness = gt_label_create(volume_and_brightness);
	gt_obj_set_pos(Screenbrightness, 140, 8);
	gt_obj_set_size(Screenbrightness, 84, 27);
	gt_label_set_font_color(Screenbrightness, gt_color_hex(0xc0c0c0));
	gt_label_set_font_family(Screenbrightness, gray_black_16);
	gt_label_set_font_cjk(Screenbrightness, 0);
	gt_label_set_font_align(Screenbrightness, GT_ALIGN_LEFT_MID);
	gt_label_set_text(Screenbrightness, "屏幕亮度");

	

	/** Brightness_progress_bar */
	/** 亮度进度条 */
	Brightness_progress_bar = gt_progress_bar_create(volume_and_brightness);
	gt_obj_set_pos(Brightness_progress_bar, 155, 88);
	gt_obj_set_size(Brightness_progress_bar, 35, 180);
	gt_progress_bar_set_start_end(Brightness_progress_bar, 0, 100);
	gt_progress_bar_set_pos(Brightness_progress_bar, 50);
	gt_progress_bar_set_color_act(Brightness_progress_bar, gt_color_hex(0xfcb838));
	gt_progress_bar_set_color_ina(Brightness_progress_bar, gt_color_hex(0x181B22));
	gt_progress_bar_set_dir(Brightness_progress_bar, GT_BAR_DIR_VER_D2U);

	

	/** Volume_Up */
	/** 音量加 */
	Volume_Up = gt_imgbtn_create(volume_and_brightness);
	gt_obj_set_pos(Volume_Up, 53, 53);
	gt_obj_set_size(Volume_Up, 24, 24);
	gt_imgbtn_set_src(Volume_Up, "f:img_VolumeUp_24x24.png");
	gt_obj_add_event_cb(Volume_Up, Volume_Up_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, Volume_progress_bar);
	

	/** Volume_Down */
	/** 音量减 */
	Volume_Down = gt_imgbtn_create(volume_and_brightness);
	gt_obj_set_pos(Volume_Down, 53, 282);
	gt_obj_set_size(Volume_Down, 24, 24);
	gt_imgbtn_set_src(Volume_Down, "f:img_VolumeDown_24x24.png");
	gt_obj_add_event_cb(Volume_Down, Volume_Down_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, Volume_progress_bar);
	

	/** Brightness_Plus */
	/** 亮度加 */
	Brightness_Plus = gt_imgbtn_create(volume_and_brightness);
	gt_obj_set_pos(Brightness_Plus, 162, 53);
	gt_obj_set_size(Brightness_Plus, 24, 24);
	gt_imgbtn_set_src(Brightness_Plus, "f:img_BrightnessPlus_24x24.png");
	gt_obj_add_event_cb(Brightness_Plus, Brightness_Plus_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, Brightness_progress_bar);
	

	/** Brightness_down */
	/** 亮度减 */
	Brightness_down = gt_imgbtn_create(volume_and_brightness);
	gt_obj_set_pos(Brightness_down, 161, 282);
	gt_obj_set_size(Brightness_down, 24, 24);
	gt_imgbtn_set_src(Brightness_down, "f:img_Brightnessreduction_24x24.png");
	gt_obj_add_event_cb(Brightness_down, Brightness_down_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, Brightness_progress_bar);


	return volume_and_brightness;
}

