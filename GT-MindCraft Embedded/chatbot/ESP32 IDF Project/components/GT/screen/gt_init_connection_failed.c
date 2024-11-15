#include "gt_ui.h"
#include "gt_font_config.h"


/** connection_failed */
gt_obj_st * connection_failed = NULL;
static gt_obj_st * VolumeSettings = NULL;
static gt_obj_st * wifiicon = NULL;
static gt_obj_st * Cancel = NULL;
static gt_obj_st * Sure = NULL;


static void connection_failed_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

static void Cancel_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

static void Sure_0_cb(gt_event_st * e) {
    ESP_LOGE("TAG", "---------------scan_wifi_list[selected_idx].password: %s\n", scan_wifi_list[selected_idx].password);
    wifi_sta_connect(scan_wifi_list[selected_idx].name, scan_wifi_list[selected_idx].password);
}

gt_obj_st * gt_init_connection_failed(void)
{
	connection_failed = gt_obj_create(NULL);
	gt_obj_add_event_cb(connection_failed, connection_failed_0_cb, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
	gt_screen_set_bgcolor(connection_failed, gt_color_hex(0x000000));




	/** VolumeSettings */
	/** 音量设置 */
	VolumeSettings = gt_label_create(connection_failed);
	gt_obj_set_pos(VolumeSettings, 39, 151);
	gt_obj_set_size(VolumeSettings, 158, 27);
	gt_label_set_font_color(VolumeSettings, gt_color_hex(0xffffff));
	gt_label_set_font_family(VolumeSettings, gray_black_20);
	gt_label_set_font_cjk(VolumeSettings, 0);
	gt_label_set_font_align(VolumeSettings, GT_ALIGN_CENTER_MID);
	gt_label_set_text(VolumeSettings, "网络连接失败");



	/** wifiicon */
	/** 图标 */
	wifiicon = gt_img_create(connection_failed);
	gt_obj_set_pos(wifiicon, 74, 50);
	gt_obj_set_size(wifiicon, 82, 82);
	gt_img_set_src(wifiicon, "f:img_3107_82x82.png");



	/** Cancel */
	/** 取消键 */
	Cancel = gt_btn_create(connection_failed);
	gt_obj_set_pos(Cancel, 27, 208);
	gt_obj_set_size(Cancel, 80, 40);
	gt_btn_set_font_color(Cancel, gt_color_hex(0xffffff));
	gt_btn_set_font_family(Cancel, gray_black_16);
	gt_btn_set_font_cjk(Cancel, 0);
	gt_btn_set_font_align(Cancel, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(Cancel, "取消");
	gt_btn_set_color_background(Cancel, gt_color_hex(0x0075FD));
	gt_btn_set_color_pressed(Cancel, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(Cancel, gt_color_hex(0x000000));
	gt_btn_set_radius(Cancel, 8);
	gt_obj_add_event_cb(Cancel, Cancel_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** Sure */
	/** 确认键 */
	Sure = gt_btn_create(connection_failed);
	gt_obj_set_pos(Sure, 132, 208);
	gt_obj_set_size(Sure, 80, 40);
	gt_btn_set_font_color(Sure, gt_color_hex(0xffffff));
	gt_btn_set_font_family(Sure, gray_black_16);
	gt_btn_set_font_cjk(Sure, 0);
	gt_btn_set_font_align(Sure, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(Sure, "重试");
	gt_btn_set_color_background(Sure, gt_color_hex(0xEB4558));
	gt_btn_set_color_pressed(Sure, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(Sure, gt_color_hex(0x000000));
	gt_btn_set_radius(Sure, 8);
	gt_obj_add_event_cb(Sure, Sure_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	return connection_failed;
}

