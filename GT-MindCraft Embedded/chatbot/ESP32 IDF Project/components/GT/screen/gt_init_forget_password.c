#include "gt_ui.h"
#include "gt_font_config.h"


/** forget_password */
gt_obj_st * forget_password = NULL;
static gt_obj_st * VolumeSettings = NULL;
static gt_obj_st * wifiicon = NULL;
static gt_obj_st * Cancel = NULL;
static gt_obj_st * Sure = NULL;

static void screen_home_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

static void Cancel_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

static void Sure_0_cb(gt_event_st * e) {
    allow_reconnect = false;
    // //删掉上次记住的wifi名称和密码
    // esp_wifi_restore();
	//断开网络
    esp_err_t ret = esp_wifi_disconnect();
    if (ret != ESP_OK) {
        ESP_LOGE("TAG", "Failed to disconnect from AP: %s", esp_err_to_name(ret));
    } else {
        ESP_LOGI("TAG", ">>>>Disconnected from AP");
    }
    vTaskDelay(pdMS_TO_TICKS(100));

    gt_disp_stack_go_back(1);
    scan_wifi_list[selected_idx].isConnected = false;
    redraw_wifi_list();

    allow_reconnect = true;
}

gt_obj_st * gt_init_forget_password(void)
{
	forget_password = gt_obj_create(NULL);
	gt_obj_add_event_cb(forget_password, screen_home_0_cb, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
	gt_screen_set_bgcolor(forget_password, gt_color_hex(0x000000));




	/** VolumeSettings */
	/** 音量设置 */
	VolumeSettings = gt_label_create(forget_password);
	gt_obj_set_pos(VolumeSettings, 39, 151);
	gt_obj_set_size(VolumeSettings, 170, 27);
	gt_label_set_font_color(VolumeSettings, gt_color_hex(0xffffff));
	gt_label_set_font_family(VolumeSettings, gray_black_20);
	gt_label_set_font_cjk(VolumeSettings, 0);
	gt_label_set_font_align(VolumeSettings, GT_ALIGN_CENTER_MID);
	// gt_label_set_text(VolumeSettings, "是否忘记密码?");
	gt_label_set_text(VolumeSettings, "是否断开连接?");



	/** wifiicon */
	/** 图标 */
	wifiicon = gt_img_create(forget_password);
	gt_obj_set_pos(wifiicon, 74, 50);
	gt_obj_set_size(wifiicon, 82, 82);
	gt_img_set_src(wifiicon, "f:img_3106_82x82.png");



	/** Cancel */
	/** 取消键 */
	Cancel = gt_btn_create(forget_password);
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
	Sure = gt_btn_create(forget_password);
	gt_obj_set_pos(Sure, 132, 208);
	gt_obj_set_size(Sure, 80, 40);
	gt_btn_set_font_color(Sure, gt_color_hex(0xffffff));
	gt_btn_set_font_family(Sure, gray_black_16);
	gt_btn_set_font_cjk(Sure, 0);
	gt_btn_set_font_align(Sure, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(Sure, "确认");
	gt_btn_set_color_background(Sure, gt_color_hex(0xEB4558));
	gt_btn_set_color_pressed(Sure, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(Sure, gt_color_hex(0x000000));
	gt_btn_set_radius(Sure, 8);
	gt_obj_add_event_cb(Sure, Sure_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	return forget_password;
}

