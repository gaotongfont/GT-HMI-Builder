#include "gt_ui.h"
#include "gt_font_config.h"

static const char *TAG = "SCREEN_KEYBOARD";

/** screen_keyboard */
gt_obj_st * screen_keyboard = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * k_ok = NULL;
static gt_obj_st * k_delete = NULL;
static gt_obj_st * k_aA = NULL;
static gt_obj_st * k_num_symbol = NULL;
static gt_obj_st * input1 = NULL;
static gt_obj_st * keyboard1 = NULL;


static void screen_home_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

static void k_ok_0_cb(gt_event_st * e) {
    gt_disp_stack_go_back(1);
    reset_current_wifi_isConnected();
    redraw_wifi_list();
    ESP_LOGE(TAG, "---------------selected_idx: %u\n", selected_idx);
    ESP_LOGE(TAG, "---------------scan_wifi_list[selected_idx].name: %s\n", scan_wifi_list[selected_idx].name);
    char *passwd = (char *)gt_input_get_value(input1);
    ESP_LOGE(TAG, "---------------passwd: %s\n", passwd);

    if (scan_wifi_list[selected_idx].password != NULL) {
        audio_free(scan_wifi_list[selected_idx].password);
    }
    scan_wifi_list[selected_idx].password = (char *)audio_malloc(strlen(passwd) + 1);
    if (scan_wifi_list[selected_idx].password == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for password");
        return;
    }

    // change_wifi_connect_tip(0x04);
    strcpy(scan_wifi_list[selected_idx].password, (const char *)passwd);
    ESP_LOGE(TAG, "---------------scan_wifi_list[%d].password: %s\n", selected_idx, scan_wifi_list[selected_idx].password);
    //连接wifi代码
    wifi_sta_connect(scan_wifi_list[selected_idx].name, scan_wifi_list[selected_idx].password);
}

static void k_delete_0_cb(gt_event_st * e) {
	gt_input_del_value(input1);
    // char *passwd = (char *)gt_input_get_value(input1);
    // ESP_LOGE(TAG, "---------------passwd: %s\n", passwd);
    // if (passwd == NULL) {
    //     gt_input_set_value(input1, "");
    // }

}

static void k_aA_0_cb(gt_event_st * e) {
    static bool isUpper = false;
    gt_keypad_set_type(keyboard1, isUpper ? GT_KEYPAD_TYPE_LOWER: GT_KEYPAD_TYPE_UPPER);
    isUpper = !isUpper;
	gt_imgbtn_set_src(k_aA, isUpper ? "f:img_3112_44x44.png" : "f:img_3114_44x44.png");
	gt_imgbtn_set_src(k_num_symbol, "f:img_3113_44x44.png");


}

static void k_num_symbol_0_cb(gt_event_st * e) {
	gt_keypad_set_type(keyboard1, GT_KEYPAD_TYPE_NUMBER);
	gt_imgbtn_set_src(k_aA, "f:img_3109_44x44.png");
	gt_imgbtn_set_src(k_num_symbol, "f:img_3115_44x44.png");

}

gt_obj_st * gt_init_keyboard(void)
{
	screen_keyboard = gt_obj_create(NULL);
	gt_obj_add_event_cb(screen_keyboard, screen_home_0_cb, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
	gt_screen_set_bgcolor(screen_keyboard, gt_color_hex(0x000000));


	/** lab2 */
	lab2 = gt_label_create(screen_keyboard);
	gt_obj_set_pos(lab2, 10, 6);
	gt_obj_set_size(lab2, 41, 39);
	gt_label_set_font_color(lab2, gt_color_hex(0xc0c0c0));
	gt_label_set_font_family(lab2, gray_black_20);
	gt_label_set_font_cjk(lab2, 0);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab2, "WiFi");



	/** lab1 */
	lab1 = gt_label_create(screen_keyboard);
	gt_obj_set_pos(lab1, 51, 7);
	gt_obj_set_size(lab1, 114, 33);
	gt_label_set_font_color(lab1, gt_color_hex(0x94A5B3));
	gt_label_set_font_family(lab1, gray_black_16);
	gt_label_set_font_cjk(lab1, 0);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab1, "仅支持2.4G");



	/** k_ok */
	/** 确认键 */
	k_ok = gt_imgbtn_create(screen_keyboard);
	gt_obj_set_pos(k_ok, 191, 93);
	gt_obj_set_size(k_ok, 44, 44);
	gt_imgbtn_set_src(k_ok, "f:img_3110_44x44.png");
	gt_imgbtn_set_src_press(k_ok, "f:img_3117_44x44.png");
	gt_obj_add_event_cb(k_ok, k_ok_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	/** k_delete */
	/** 删除键 */
	k_delete = gt_imgbtn_create(screen_keyboard);
	gt_obj_set_pos(k_delete, 191, 140);
	gt_obj_set_size(k_delete, 44, 44);
	gt_imgbtn_set_src(k_delete, "f:img_3111_44x44.png");
	gt_imgbtn_add_state_item(k_delete, "f:img_3118_44x44.png");
	gt_obj_add_event_cb(k_delete, k_delete_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);




	/** k_aA */
	/** 大小写切换键 */
	k_aA = gt_imgbtn_create(screen_keyboard);
	gt_obj_set_pos(k_aA, 192, 187);
	gt_obj_set_size(k_aA, 44, 44);
	gt_imgbtn_set_src(k_aA, "f:img_3114_44x44.png");
	gt_obj_add_event_cb(k_aA, k_aA_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** k_num_symbol */
	/** 数字符号键 */
	k_num_symbol = gt_imgbtn_create(screen_keyboard);
	gt_obj_set_pos(k_num_symbol, 193, 236);
	gt_obj_set_size(k_num_symbol, 44, 44);
	gt_imgbtn_set_src(k_num_symbol, "f:img_3113_44x44.png");
	gt_obj_add_event_cb(k_num_symbol, k_num_symbol_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	/** input1 */
	input1 = gt_input_create(screen_keyboard);
	gt_obj_set_pos(input1, 4, 45);
	gt_obj_set_size(input1, 230, 41);
	gt_input_set_font_color(input1, gt_color_hex(0xc0c0c0));
	gt_input_set_font_family(input1, gray_black_16);
	gt_input_set_font_cjk(input1, 0);
	gt_input_set_font_align(input1, GT_ALIGN_LEFT_MID);
	gt_input_set_placeholder(input1, " 输入密码");
	gt_input_set_border_width(input1, 0);
	gt_input_set_bg_color(input1, gt_color_hex(0x181B22));
    gt_input_set_value(input1, "");


	/** keyboard1 */
	keyboard1 = gt_keypad_create(screen_keyboard);
	gt_obj_set_pos(keyboard1, 0, 90);
	gt_obj_set_size(keyboard1, 300, 170);
	gt_keypad_set_font_color(keyboard1, gt_color_hex(0xffffff));
	gt_keypad_set_font_family(keyboard1, gray_black_16);
	gt_keypad_set_font_cjk(keyboard1, 0);
    gt_keypad_set_key_radius(keyboard1, 8);
	gt_keypad_set_radius(keyboard1, 6);
	gt_keypad_set_target(keyboard1, input1);
    gt_keypad_set_default_style(keyboard1, GT_KEYPAD_STYLE_OTHER_4x5);
    gt_keypad_set_color_background(keyboard1, gt_color_hex(0x000000));
    gt_keypad_set_key_color_background(keyboard1, gt_color_hex(0x30384A));



	return screen_keyboard;
}

