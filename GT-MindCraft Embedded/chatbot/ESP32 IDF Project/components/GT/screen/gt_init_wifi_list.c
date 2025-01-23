#include "gt_ui.h"
#include "gt_font_config.h"

static const char *TAG = "SCREEN_WIFI_LIST";


/** wifi_list */
gt_obj_st * wifi_list = NULL;
static gt_obj_st * listv1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;

static void set_item_by_wifi_list ();

void redraw_wifi_list() {
    set_item_by_wifi_list();
    gt_disp_invalid_area(listv1);
}

void change_wifi_connect_tip(uint8_t flag) {
    const char *wifi_connect_tip[2] = {"连接中", "已连接"};
    ESP_LOGI(TAG,"--------flag = 0x%x\n", flag);
    switch (flag)
    {
    case 0x04:
        gt_obj_set_visible(lab3, true);
        gt_label_set_text(lab3, wifi_connect_tip[0]);
	    gt_label_set_font_color(lab3, gt_color_hex(0xFF7859));
        ESP_LOGI(TAG,"--------wifi_connect_tip[0] = %s\n", wifi_connect_tip[0]);
        break;
    case 0x01:
        gt_label_set_text(lab3, wifi_connect_tip[1]);
    	gt_label_set_font_color(lab3, gt_color_hex(0x94A5B3));
        ESP_LOGI(TAG,"--------wifi_connect_tip[1] = %s\n", wifi_connect_tip[1]);
        redraw_wifi_list();
        break;

    default:
        break;
    }
    // gt_event_send(wifi_list, GT_EVENT_TYPE_DRAW_START, NULL);
    gt_disp_invalid_area(lab3);
}


static void screen_home_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
    selected_idx = 0;
    //释放wifi列表内存
    if (scan_wifi_list != NULL) {
        for (size_t i = 0; i < ap_count; i++) {
            if (scan_wifi_list[i].name != NULL) {
                audio_free(scan_wifi_list[i].name);
            }
            if (scan_wifi_list[i].password != NULL) {
                audio_free(scan_wifi_list[i].password);
            }
        }
        audio_free(scan_wifi_list);
        ESP_LOGI(TAG, "audio free scan_wifi_list");
    }
}

uint8_t selected_idx = 0;

static void listv1_0_cb(gt_event_st * e) {
    selected_idx = gt_listview_get_idx_selected(listv1);
    if (selected_idx == 0xFF)
    {
        return;
    }

    ESP_LOGI(TAG, "---------------selected_idx: %u\n", selected_idx);
    // 检查 scan_wifi_list[selected_idx].name是否有效
    if (scan_wifi_list[selected_idx].name == NULL) {
        ESP_LOGE(TAG, "Invalid SSID in scan_wifi_list");
        return;
    }
    ESP_LOGI(TAG, "---------------scan_wifi_list[selected_idx].name: %s\n", scan_wifi_list[selected_idx].name);

    wifi_ap_record_t ap_info;
    esp_err_t ret;
    ret = esp_wifi_sta_get_ap_info(&ap_info);
    //TODO:待优化
    if (ret == ESP_OK) {
        // primary：AP的主要信道号，1.primary=0:未连接到 AP; 2.primary!=0:已连接到 AP，信道号有效。通过检查 primary 字段判断是否已连接
        if (ap_info.primary != 0) {
            wifi_config_t wifi_config = get_current_wifi_config();
            if (strcmp(scan_wifi_list[selected_idx].name, (const char *)wifi_config.sta.ssid) == 0 && strcmp(scan_wifi_list[selected_idx].password, (const char *)wifi_config.sta.password) == 0) {
                gt_disp_stack_load_scr_anim(GT_ID_FORGET_PASSWORD, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
                ESP_LOGI(TAG,"11111111111111111\n");
            } else {
                gt_disp_stack_load_scr_anim(GT_ID_KEYBOARD, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
                ESP_LOGI(TAG,"222222222222\n");

            }
        } else {
            gt_disp_stack_load_scr_anim(GT_ID_KEYBOARD, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
            ESP_LOGI(TAG,"333333333333333\n");

        }
    } else {
        ESP_LOGE(TAG, "Failed to get AP info: %s", esp_err_to_name(ret));
        gt_disp_stack_load_scr_anim(GT_ID_KEYBOARD, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
    }
}

typedef enum wifi_list_item_idx_type_e {
    WIFI_LIST_ITEM_IDX_STRING = 0,  //string
    WIFI_LIST_ITEM_IDX_ICON_TYPE,
    /**  --- end ---  **/
    BAIDU_NET_LIST_ITEM_IDX_TOTAL,
} wifi_list_item_idx_type_et;

static void set_item_by_wifi_list () {
    gt_listview_clear_all_items(listv1);
#if 0
	gt_listview_set_scale(listv1, 20, 80);
	gt_listview_set_scale_triple(listv1, 20, 60, 20);
	gt_listview_set_icon_to_right(listv1, 1);
	gt_listview_set_next_row_item_count(listv1, 1);
	// gt_listview_add_item_icon(listv1, "f:img_Connected_220x278.png", "  很长的名长...");
	// // gt_listview_set_next_row_item_count(listv1, 1);
	// gt_listview_add_item_icon(listv1, "f:img_Lock_220x278.png", "  WiFi3");
	// gt_listview_add_item_icon(listv1, "f:img_Lock_220x278.png", "  WiFi4");
	// gt_listview_add_item_icon(listv1, "f:img_Lock_220x278.png", "  WiFi5");
	// gt_listview_add_item_icon(listv1, "f:img_Lock_220x278.png", "  WiFi6");
	// gt_listview_add_item_icon(listv1, "f:img_Lock_220x278.png", "  WiFi7");
    for (size_t i = 0; i < ap_count; i++)
    {
        gt_listview_add_item_icon(listv1, scan_wifi_list[i].isConnected ? "f:img_Connected_220x278.png": "f:img_Lock_220x278.png", scan_wifi_list[i].name);
    }
#else
    for (size_t i = 0; i < ap_count; i++)
    {
        gt_listview_custom_item_st itm = {0};
        itm.item_idx = i;
        uint16_t len = strlen(scan_wifi_list[i].name);
        if (len > 0)
        {
            itm.element_idx = WIFI_LIST_ITEM_IDX_STRING;
            itm.type = GT_LISTVIEW_ELEMENT_TYPE_LABEL;
            itm.area.x = 6;
            itm.area.y = 0;//(52 - 16)>>1;
            itm.area.w = 220 * 0.8;
            itm.area.h = 52;
            itm.src = scan_wifi_list[i].name;
            itm.src_len = len;
            gt_listview_custom_item_set_element(listv1, &itm);
        }
        if (scan_wifi_list[i].isConnected)
        {
            itm.element_idx = WIFI_LIST_ITEM_IDX_ICON_TYPE;
            itm.type = GT_LISTVIEW_ELEMENT_TYPE_IMG;
            itm.area.x = 186;
            itm.area.y = (52 - 14)>>1;
            itm.area.w = 19;
            itm.area.h = 14;
            itm.src = "f:img_Connected_220x278.png";
            gt_listview_custom_item_set_element(listv1, &itm);
        }else {
            itm.element_idx = WIFI_LIST_ITEM_IDX_ICON_TYPE;
            itm.type = GT_LISTVIEW_ELEMENT_TYPE_IMG;
            itm.area.x = 186;
            itm.area.y = (52 - 15)>>1;
            itm.area.w = 13;
            itm.area.h = 15;
            itm.src = "f:img_Lock_220x278.png";
            gt_listview_custom_item_set_element(listv1, &itm);
        }
    }
#endif
}


gt_obj_st * gt_init_wifi_list(void)
{
	wifi_list = gt_obj_create(NULL);
	gt_obj_add_event_cb(wifi_list, screen_home_0_cb, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
	gt_screen_set_bgcolor(wifi_list, gt_color_hex(0x000000));




	/** listv1 */
	listv1 = gt_listview_create(wifi_list);
	gt_obj_set_pos(listv1, 8, 41);
	gt_obj_set_size(listv1, 220, 278);
	gt_listview_set_font_color(listv1, gt_color_hex(0xffffff));
	gt_listview_set_font_family(listv1, gray_black_16);
	gt_listview_set_font_cjk(listv1, 0);
	gt_listview_set_font_align(listv1, GT_ALIGN_LEFT_MID);
	gt_listview_set_item_height(listv1, 52);
	gt_listview_set_border_color(listv1,gt_color_hex(0xc7c7c7));
	gt_listview_set_border_width(listv1, 0);
	gt_listview_set_septal_line(listv1, 0);
	gt_listview_set_highlight_mode(listv1, false);
	gt_listview_set_bg_color(listv1, gt_color_hex(0x000000));
	gt_listview_set_item_bg_color(listv1, gt_color_hex(0x181B22));
	gt_listview_show_item_bg(listv1, true);
	gt_listview_set_item_reduce(listv1, 0);
	gt_listview_set_item_radius(listv1, 8);
    set_item_by_wifi_list();
	gt_obj_add_event_cb(listv1, listv1_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	/** lab1 */
	lab1 = gt_label_create(wifi_list);
	gt_obj_set_pos(lab1, 10, 6);
	gt_obj_set_size(lab1, 55, 31);
	gt_label_set_font_color(lab1, gt_color_hex(0xc0c0c0));
	gt_label_set_font_family(lab1, gray_black_20);
	gt_label_set_font_cjk(lab1, 0);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab1, "WIFi");



	/** lab2 */
	lab2 = gt_label_create(wifi_list);
	gt_obj_set_pos(lab2, 51, 7);
	gt_obj_set_size(lab2, 126, 29);
	gt_label_set_font_color(lab2, gt_color_hex(0x94A5B3));
	gt_label_set_font_family(lab2, gray_black_16);
	gt_label_set_font_cjk(lab2, 0);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab2, "仅支持2.4G");


	/** lab3 */
	lab3 = gt_label_create(wifi_list);
	gt_obj_set_pos(lab3, 170, 7);
	gt_obj_set_size(lab3, 126, 29);
	gt_label_set_font_color(lab3, gt_color_hex(0x94A5B3));
	gt_label_set_font_family(lab3, gray_black_16);
	gt_label_set_font_cjk(lab3, 0);
	gt_label_set_font_align(lab3, GT_ALIGN_LEFT_MID);
    gt_label_set_text(lab3, "");
    gt_obj_set_visible(lab3, false);


	return wifi_list;
}

