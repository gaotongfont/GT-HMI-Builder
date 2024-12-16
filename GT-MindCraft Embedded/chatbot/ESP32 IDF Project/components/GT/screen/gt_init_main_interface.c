#include "gt_ui.h"
#include "gt_font_config.h"


static const char *TAG = "SCREEN_MAIN_INTERFACE";


/** main_interface */
gt_obj_st * main_interface = NULL;
static gt_obj_st * AIRobots = NULL;
static gt_obj_st * setup = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * imgbtn2 = NULL;


void set_wifi_status_icon(gt_wifi_icon_status_et status) {
    switch (status) {
        case WIFI_NO_CONNECTED:
            gt_imgbtn_set_src(imgbtn1, "f:img_WIFIsignal5_16x12.png");
            break;
        case WIFI_SIGNAL_1:
            gt_imgbtn_set_src(imgbtn1, "f:img_WIFIsignal4_16x12.png");
            break;
        case WIFI_SIGNAL_2:
            gt_imgbtn_set_src(imgbtn1, "f:img_WIFIsignal3_16x12.png");
            break;
        case WIFI_SIGNAL_3:
            gt_imgbtn_set_src(imgbtn1, "f:img_WIFIsignal2_16x12.png");
            break;
        case WIFI_SIGNAL_4:
            gt_imgbtn_set_src(imgbtn1, "f:img_WIFIsignal1_16x12.png");
            break;
    }
    gt_disp_invalid_area(imgbtn1);
}

void update_wifi_icon() {
    gt_wifi_icon_status_et level = get_current_rssi_level();
    ESP_LOGI(TAG, "----------RSSI: %d\n", level);

    set_wifi_status_icon(level);
}

static void AIRobots_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);

    char room_id[40];
#if 0
    erase_data_from_nvs("room_id");
    store_data_in_nvs("room_id", "eeed2c61-65ad-4811-910b-a5072bac257f");
#endif
    read_data_from_nvs("room_id", room_id, 40);
    if (strcmp(room_id, "") == 0) {
        create_room_http();
    } else {
        ESP_LOGI(TAG, "---------room_id: %s\r\n", room_id);
        set_session_token(room_id);
    }
}

static void setup_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SETTING_LIST, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_main_interface(void)
{
	main_interface = gt_obj_create(NULL);

	gt_screen_set_bgcolor(main_interface, gt_color_hex(0x000000));




	/** AIRobots */
	/** AI机器人 */
	AIRobots = gt_imgbtn_create(main_interface);
	gt_obj_set_pos(AIRobots, 13, 34);
	gt_obj_set_size(AIRobots, 101, 124);
	gt_imgbtn_set_src(AIRobots, "f:img_3096_101x124.png");
	gt_obj_add_event_cb(AIRobots, AIRobots_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** setup */
	/** 设置 */
	setup = gt_imgbtn_create(main_interface);
	gt_obj_set_pos(setup, 126, 35);
	gt_obj_set_size(setup, 105, 124);
	gt_imgbtn_set_src(setup, "f:img_3097_105x124.png");
	gt_obj_add_event_cb(setup, setup_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** imgbtn1 */
	imgbtn1 = gt_imgbtn_create(main_interface);
	gt_obj_set_pos(imgbtn1, 177, 4);
	gt_obj_set_size(imgbtn1, 16, 12);
    gt_imgbtn_set_src(imgbtn1, "f:img_WIFIsignal5_16x12.png");



	/** imgbtn2 */
	imgbtn2 = gt_imgbtn_create(main_interface);
	gt_obj_set_pos(imgbtn2, 206, 4);
	gt_obj_set_size(imgbtn2, 22, 12);
	gt_imgbtn_set_src(imgbtn2, "f:img_Battery_22x12.png");



	return main_interface;
}

