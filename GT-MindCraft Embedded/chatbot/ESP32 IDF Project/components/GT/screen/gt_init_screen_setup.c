#include "gt_ui.h"
#include "gt_font_config.h"
#include "gt_websocket.h"

static const char *TAG = "SCREEN_SETUP";

/** screen_setup */
gt_obj_st * screen_setup = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * btn2 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * btn3 = NULL;
static gt_obj_st * imgbtn7 = NULL;
static gt_obj_st * imgbtn8 = NULL;
static gt_obj_st * imgbtn9 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * btn4 = NULL;
static gt_obj_st * imgbtn9Copy = NULL;
static gt_obj_st * txt1 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * btn5 = NULL;
static gt_obj_st * imgbtn9CopyCopy = NULL;
static gt_obj_st * imgbtn10 = NULL;
static gt_obj_st * imgbtn11 = NULL;

static gt_obj_st * btn_personality[4] = {NULL};
static gt_obj_st * txt_tone = NULL;

uint32_t btn_bgcolor_hex[4] = {0x452a0d, 0x48420c, 0x063e04, 0x2c4405};
uint32_t btn_font_color_hex[4] = {0xd4731d, 0xe0c324, 0x2d9b14, 0x7bc004};
/* -------------------------------------------------------------------------- */
static gt_obj_st* go_back_rect = NULL;
static gt_obj_st* list1 = NULL;
static uint8_t list_option = AI_SETTING_NONE;
/* -------------------------------------------------------------------------- */
static uint8_t get_list_option(gt_obj_st* obj)
{
	if(!obj) return AI_SETTING_NONE;
#if 0
	if(obj == btn2) return AI_SETTING_AGE;
	else if(obj == btn4) return AI_SETTING_ROLE;
	else if(obj == btn5) return AI_SETTING_CHAR;
	else if(obj == btn3) return AI_SETTING_TIMBRE;
	else if(obj == btn1) return AI_SETTING_AI_NAME;
#else
	if(obj == btn3) return AI_SETTING_AGE;
	else if(obj == btn2) return AI_SETTING_USER_NAME;
	else if(obj == btn1) return AI_SETTING_AI_NAME;
#endif
	return AI_SETTING_NONE;
}

static void go_back_to_previous_page(gt_event_st * e) {
	list_option = AI_SETTING_NONE;
	gt_disp_stack_go_back(1);
    if (strcmp(cb_data.settings->bot_name, "小智") == 0)
    {
        set_emote_data_to_ram(AI_EMOTE_XIAOZHI_DISGUST);
        set_emote_data_to_ram(AI_EMOTE_XIAOZHI_FEAR);
        // set_emote_data_to_ram(AI_EMOTE_XIAOZHI_SADNESS);
        set_emote_data_to_ram(AI_EMOTE_XIAOZHI_SURPRISE);
        set_emote_data_to_ram(AI_EMOTE_XIAOZHI_ANGER);
        set_emote_data_to_ram(AI_EMOTE_XIAOZHI_HAPPY);
    } else if (strcmp(cb_data.settings->bot_name, "菜机") == 0)
    {
        set_emote_data_to_ram(AI_EMOTE_CAIJI_DISGUST);
        set_emote_data_to_ram(AI_EMOTE_CAIJI_FEAR);
        // set_emote_data_to_ram(AI_EMOTE_CAIJI_SADNESS);
        set_emote_data_to_ram(AI_EMOTE_CAIJI_SURPRISE);
        set_emote_data_to_ram(AI_EMOTE_CAIJI_ANGER);
        set_emote_data_to_ram(AI_EMOTE_CAIJI_HAPPY);
    }
}
/**
 * @brief 按钮点击回调，根据点击对象，给列表设置不同的选项内容与显示位置
 *
 */
static void disp_list_cb(gt_event_st * e) {
	gt_obj_st* obj = e->target;
	int x = obj->area.x;
	int y = obj->area.y;
	uint16_t h = obj->area.h;
	uint8_t tmp_option = get_list_option(obj);
	uint8_t visible = gt_obj_get_visible(list1);

	if(AI_SETTING_NONE == tmp_option){
		gt_obj_set_visible(list1, GT_INVISIBLE);
		list_option = tmp_option;
		return;
	}

	if(AI_SETTING_AGE == tmp_option || AI_SETTING_USER_NAME == tmp_option){
		gt_obj_set_pos(list1, x, y-3-list1->area.h);
	}
	else{
		gt_obj_set_pos(list1, x, y+h+3);
	}

	if(list_option == tmp_option){
		gt_obj_set_visible(list1, !visible);
	}
	else {
		gt_obj_set_visible(list1, GT_VISIBLE);
	}
    set_items_in_listview(list1, tmp_option);
	list_option = tmp_option;

    gt_disp_invalid_area(screen_setup);
}
/**
 * @brief 列表点击回调，设置选中项的内容到对应的btn显示，同时更新settings数据
 *
 */
static void list_item_cb(gt_event_st * e) {
    gt_size_t selected_idx = gt_listview_get_idx_selected(list1);
    ESP_LOGI(TAG,"----------------selected_idx = %d\n", selected_idx);
    if (selected_idx < 0)
    {
        return;
    }
    char * selectedItem = gt_listview_get_selected_item_text(list1);
    ESP_LOGI(TAG, "-------------------selectedItem=%s\n", selectedItem);
	switch(list_option){
        case AI_SETTING_AI_NAME:
			gt_btn_set_text(btn1, " %s", selectedItem);
			sprintf(cb_data.settings->bot_name, "%s", selectedItem);

            gt_ai_bot_role_st ai_bot_role_info = gt_get_ai_bot_infos(cb_data.settings->bot_name);
            memcpy(cb_data.settings->bot_personality, ai_bot_role_info.personality, sizeof(ai_bot_role_info.personality));
            for (size_t i = 0; i < 4; i++)
            {
                gt_btn_set_text(btn_personality[i], cb_data.settings->bot_personality[i]);
            }
			sprintf(cb_data.settings->bot_description, "%s", ai_bot_role_info.character_desc);
            gt_textarea_set_text(txt1, cb_data.settings->bot_description);

			sprintf(cb_data.settings->voice_id, "%s", ai_bot_role_info.voice_id);
			gt_btn_set_text(btn4, " %s", gt_timber_string_get(cb_data.settings->voice_id));

            sprintf(cb_data.settings->bot_tone, "%s", ai_bot_role_info.tone);
            gt_textarea_set_text(txt_tone, cb_data.settings->bot_tone);

            gt_websocket_client_clear_history_message();

            if (strcmp(cb_data.settings->bot_name, "小智") == 0)
            {
                set_emote_data_to_ram(AI_EMOTE_XIAOZHI_NEUTRAL);
                set_emote_data_to_ram(AI_EMOTE_XIAOZHI_SADNESS);
            } else if (strcmp(cb_data.settings->bot_name, "菜机") == 0)
            {
                set_emote_data_to_ram(AI_EMOTE_CAIJI_NEUTRAL);
                set_emote_data_to_ram(AI_EMOTE_CAIJI_SADNESS);
            }

			break;
		case AI_SETTING_AGE:
			gt_btn_set_text(btn3, " %s", selectedItem);
			cb_data.settings->user_age = atoi(selectedItem);
			break;
		case AI_SETTING_USER_NAME:
			gt_btn_set_text(btn2, " %s", selectedItem);
			sprintf(cb_data.settings->user_name, "%s", selectedItem);
			break;
#if 0
    	case AI_SETTING_TIMBRE:
			gt_btn_set_text(btn3, " %s", selectedItem);
			sprintf(cb_data.settings->voice_id, "%s", gt_vocie_id_string_get(selectedItem));
			break;
		case AI_SETTING_ROLE:
			gt_btn_set_text(btn4, " %s", selectedItem);
			sprintf(cb_data.settings->bot_character, "%s", selectedItem);
			break;
		case AI_SETTING_CHAR:
			gt_btn_set_text(btn5, " %s", selectedItem);
			sprintf(cb_data.settings->bot_personality, "%s", selectedItem);
			break;
#endif
		default:
			break;
	}
	gt_obj_set_visible(list1, GT_INVISIBLE);
}


static void imgbtn11_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_FUNCTION_SETTINGS, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_setup(void)
{
	screen_setup = gt_obj_create(NULL);
	gt_obj_add_event_cb(screen_setup, go_back_to_previous_page, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
	gt_screen_set_bgcolor(screen_setup, gt_color_hex(0x000000));




	/** img1 */
	img1 = gt_img_create(screen_setup);
	gt_obj_set_pos(img1, 8, 10);
	gt_obj_set_size(img1, 16, 16);
	gt_img_set_src(img1, "f:img_fh_16x16.png");
    gt_obj_set_touch_expand_area(img1, 100, 40);
    gt_obj_add_event_cb(img1, go_back_to_previous_page, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	/** lab1 */
	lab1 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab1, 35, 3);
	gt_obj_set_size(lab1, 55, 26);
	gt_label_set_font_color(lab1, gt_color_hex(0x94a5b3));
    gt_label_set_font_family(lab1, gray_black_16);
	gt_label_set_font_cjk(lab1, 0);
	gt_label_set_font_align(lab1, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab1, "设置");



	/** imgbtn10 */
	imgbtn10 = gt_imgbtn_create(screen_setup);
	gt_obj_set_pos(imgbtn10, 10, 33);
	gt_obj_set_size(imgbtn10, 109, 39);
	gt_imgbtn_set_src(imgbtn10, "f:img_1AI_Settings_p_109x39.png");
	gt_imgbtn_set_src_press(imgbtn10, "f:img_1AI_Settings_n_109x39.png");


	/** imgbtn11 */
	imgbtn11 = gt_imgbtn_create(screen_setup);
	gt_obj_set_pos(imgbtn11, 120, 33);
	gt_obj_set_size(imgbtn11, 109, 39);
	gt_imgbtn_set_src(imgbtn11, "f:img_1Function_settings_n_109x39.png");
	gt_imgbtn_set_src_press(imgbtn11, "f:img_1Function_settings_p_109x39.png");
	gt_obj_add_event_cb(imgbtn11, imgbtn11_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);



	/** btn1 */
	btn1 = gt_btn_create(screen_setup);
	gt_obj_set_pos(btn1, 12, 106);
	gt_obj_set_size(btn1, 216, 36);
	gt_btn_set_font_color(btn1, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn1, gray_black_16);
	gt_btn_set_font_cjk(btn1, 0);
	gt_btn_set_font_align(btn1, GT_ALIGN_LEFT_MID);
	gt_btn_set_text(btn1, " %s", cb_data.settings->bot_name);
	gt_btn_set_color_background(btn1, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn1, gt_color_hex(0x000000));
	gt_btn_set_radius(btn1, 8);
	gt_obj_add_event_cb(btn1, disp_list_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
    gt_obj_set_fixed(btn1, true);


	/** lab2 */
	lab2 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab2, 12, 79);
	gt_obj_set_size(lab2, 83, 23);
	gt_label_set_font_color(lab2, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab2, gray_black_16);
	gt_label_set_font_cjk(lab2, 0);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2, "AI昵称：");



	/** lab3 */
	lab3 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab3, 12, 146);
	gt_obj_set_size(lab3, 90, 22);
	gt_label_set_font_color(lab3, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab3, gray_black_16);
	gt_label_set_font_cjk(lab3, 0);
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, "角色介绍：");



	/** btn2 */
	btn2 = gt_btn_create(screen_setup);
	gt_obj_set_pos(btn2, 12, 265);
	gt_obj_set_size(btn2, 216, 36);
	gt_btn_set_font_color(btn2, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn2, gray_black_16);
	gt_btn_set_font_cjk(btn2, 0);
	gt_btn_set_font_align(btn2, GT_ALIGN_LEFT_MID);
    gt_btn_set_text(btn2, " %s", cb_data.settings->user_name);
	gt_btn_set_color_background(btn2, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn2, gt_color_hex(0x000000));
	gt_btn_set_radius(btn2, 6);
	gt_obj_add_event_cb(btn2, disp_list_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
    gt_obj_set_fixed(btn2, true);



	/** lab4 */
	lab4 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab4, 12, 239);
	gt_obj_set_size(lab4, 90, 21);
	gt_label_set_font_color(lab4, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab4, gray_black_16);
	gt_label_set_font_cjk(lab4, 0);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, "用户昵称：");



	/** lab5 */
	lab5 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab5, 12, 311);
	gt_obj_set_size(lab5, 90, 23);
	gt_label_set_font_color(lab5, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab5, gray_black_16);
	gt_label_set_font_cjk(lab5, 0);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, "用户年龄：");



	/** btn3 */
	btn3 = gt_btn_create(screen_setup);
	gt_obj_set_pos(btn3, 12, 338);
	gt_obj_set_size(btn3, 216, 36);
	gt_btn_set_font_color(btn3, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn3, gray_black_16);
	gt_btn_set_font_cjk(btn3, 0);
	gt_btn_set_font_align(btn3, GT_ALIGN_LEFT_MID);
    gt_btn_set_text(btn3, " %d", cb_data.settings->user_age);
	gt_btn_set_color_background(btn3, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn3, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn3, gt_color_hex(0x000000));
	gt_btn_set_radius(btn3, 6);
	gt_obj_add_event_cb(btn3, disp_list_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
    gt_obj_set_fixed(btn3, true);



	/** imgbtn7 */
	imgbtn7 = gt_imgbtn_create(screen_setup);
	gt_obj_set_pos(imgbtn7, 198, 116);
	gt_obj_set_size(imgbtn7, 27, 20);
	gt_imgbtn_set_src(imgbtn7, "f:img_down1_27x20.png");
	gt_imgbtn_add_state_item(imgbtn7, "f:img_down1_27x20.png");



	/** imgbtn8 */
	imgbtn8 = gt_imgbtn_create(screen_setup);
	gt_obj_set_pos(imgbtn8, 198, 270);
	gt_obj_set_size(imgbtn8, 27, 20);
	gt_imgbtn_set_src(imgbtn8, "f:img_down1_27x20.png");
	gt_imgbtn_add_state_item(imgbtn8, "f:img_up1_27x20.png");



	/** imgbtn9 */
	imgbtn9 = gt_imgbtn_create(screen_setup);
	gt_obj_set_pos(imgbtn9, 198, 346);
	gt_obj_set_size(imgbtn9, 27, 20);
	gt_imgbtn_set_src(imgbtn9, "f:img_down1_27x20.png");
	gt_imgbtn_add_state_item(imgbtn9, "f:img_up1_27x20.png");



	/** lab6 */
	lab6 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab6, 12, 387);
	gt_obj_set_size(lab6, 90, 23);
	gt_label_set_font_color(lab6, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab6, gray_black_16);
	gt_label_set_font_cjk(lab6, 0);
	gt_label_set_font_align(lab6, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab6, "音色设定：");



	/** btn4 */
	btn4 = gt_btn_create(screen_setup);
	gt_obj_set_pos(btn4, 12, 409);
	gt_obj_set_size(btn4, 216, 36);
	gt_btn_set_font_color(btn4, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn4, gray_black_16);
	gt_btn_set_font_cjk(btn4, 0);
	gt_btn_set_font_align(btn4, GT_ALIGN_LEFT_MID);
    gt_btn_set_text(btn4, " %s", gt_timber_string_get(cb_data.settings->voice_id));
	gt_btn_set_color_background(btn4, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn4, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn4, gt_color_hex(0x000000));
	gt_btn_set_radius(btn4, 6);
	// gt_obj_add_event_cb(btn4, disp_list_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
    gt_obj_set_fixed(btn4, true);


	// /** imgbtn9Copy */
	// imgbtn9Copy = gt_imgbtn_create(screen_setup);
	// gt_obj_set_pos(imgbtn9Copy, 198, 417);
	// gt_obj_set_size(imgbtn9Copy, 27, 20);
	// gt_imgbtn_set_src(imgbtn9Copy, "f:img_down1_27x20.png");
	// gt_imgbtn_add_state_item(imgbtn9Copy, "f:img_up1_27x20.png");



	/** txt1 */
	txt1 = gt_textarea_create(screen_setup);
	gt_obj_set_pos(txt1, 12, 173);
	gt_obj_set_size(txt1, 217, 58);
	gt_textarea_set_font_family(txt1, gray_black_16);
	gt_textarea_set_font_cjk(txt1, 0);
	gt_textarea_set_font_align(txt1, GT_ALIGN_LEFT);
	gt_textarea_set_font_color(txt1, gt_color_hex(0x4193fb));
    gt_textarea_set_text(txt1, cb_data.settings->bot_description);
	gt_textarea_set_bg_color(txt1, gt_color_hex(0x181b22));
    gt_textarea_set_border_color(txt1, gt_color_hex(0x272d38));
    // gt_obj_set_fixed(txt1, true);


	/** lab7 */
	lab7 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab7, 12, 457);
	gt_obj_set_size(lab7, 90, 23);
	gt_label_set_font_color(lab7, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab7, gray_black_16);
	gt_label_set_font_cjk(lab7, 0);
	gt_label_set_font_align(lab7, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab7, "性格设定：");



	// /** btn5 */
	// btn5 = gt_btn_create(screen_setup);
	// gt_obj_set_pos(btn5, 12, 479);
	// gt_obj_set_size(btn5, 216, 36);
	// gt_btn_set_font_color(btn5, gt_color_hex(0x4193fb));
	// gt_btn_set_font_family(btn5, gray_black_16);
	// gt_btn_set_font_cjk(btn5, 0);
	// gt_btn_set_font_align(btn5, GT_ALIGN_LEFT_MID);
	// gt_btn_set_text(btn5, " %s", cb_data.settings->bot_personality);
	// gt_btn_set_color_background(btn5, gt_color_hex(0x181b22));
	// gt_btn_set_color_pressed(btn5, gt_color_hex(0x00a8ff));
	// gt_btn_set_font_color_pressed(btn5, gt_color_hex(0x000000));
	// gt_btn_set_radius(btn5, 6);
	// gt_obj_add_event_cb(btn5, disp_list_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
    // gt_obj_set_fixed(btn5, true);

    for (size_t i = 0; i < 4; i++)
    {
        btn_personality[i] = gt_btn_create(screen_setup);
	    gt_obj_set_pos(btn_personality[i], 12 + (50 + 5) * i, 480);
	    gt_obj_set_size(btn_personality[i], 50, 35);
        gt_btn_set_font_color(btn_personality[i], gt_color_hex(btn_font_color_hex[i]));
        gt_btn_set_font_family(btn_personality[i], gray_black_16);
	    gt_btn_set_font_cjk(btn_personality[i], 0);
	    gt_btn_set_font_align(btn_personality[i], GT_ALIGN_CENTER_MID);
        gt_btn_set_text(btn_personality[i], cb_data.settings->bot_personality[i]);
	    gt_btn_set_color_background(btn_personality[i], gt_color_hex(btn_bgcolor_hex[i]));
	    gt_btn_set_color_pressed(btn_personality[i], gt_color_hex(btn_bgcolor_hex[i]));
	    gt_btn_set_font_color_pressed(btn_personality[i], gt_color_hex(btn_font_color_hex[i]));
	    gt_btn_set_radius(btn_personality[i], 4);
    }


	/** lab7 */
	lab7 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab7, 12, 527);
	gt_obj_set_size(lab7, 90, 23);
	gt_label_set_font_color(lab7, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab7, gray_black_16);
	gt_label_set_font_cjk(lab7, 0);
	gt_label_set_font_align(lab7, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab7, "沟通风格");



	/** txt_tone */
	txt_tone = gt_textarea_create(screen_setup);
	gt_obj_set_pos(txt_tone, 12, 549);
	gt_obj_set_size(txt_tone, 217, 58);
	gt_textarea_set_font_family(txt_tone, gray_black_16);
	gt_textarea_set_font_cjk(txt_tone, 0);
	gt_textarea_set_font_align(txt_tone, GT_ALIGN_LEFT);
	gt_textarea_set_font_color(txt_tone, gt_color_hex(0x4193fb));
    gt_textarea_set_text(txt_tone, cb_data.settings->bot_tone);
	gt_textarea_set_bg_color(txt_tone, gt_color_hex(0x181b22));
    gt_textarea_set_border_color(txt_tone, gt_color_hex(0x272d38));
    // gt_obj_set_fixed(txt_tone, true);



	list1 = gt_listview_create(screen_setup);
	gt_obj_set_pos(list1, 19, 180);
	gt_obj_set_size(list1, 216, 80);
	// gt_listview_set_font_color(list1, gt_color_hex(0x191919));
	gt_listview_set_font_family(list1, gray_black_16);
	gt_listview_set_font_cjk(list1, 0);
	gt_listview_set_font_align(list1, GT_ALIGN_CENTER_MID);
	gt_listview_set_item_height(list1, 40);
	gt_listview_set_border_color(list1,gt_color_hex(0x454d5a));
	gt_listview_set_border_width(list1, 1);
	gt_listview_set_septal_line(list1, 0);
    gt_listview_set_highlight_mode(list1, false);
	gt_listview_set_bg_color(list1, gt_color_hex(0xffffff));
	gt_listview_set_item_reduce(list1, 0);
	gt_listview_set_item_radius(list1, 6);
	gt_listview_set_scale(list1, 25, 75);
	gt_listview_set_scale_triple(list1, 20, 60, 20);
	gt_listview_set_next_row_item_count(list1, 1);
    gt_obj_set_visible(list1, GT_INVISIBLE);
	gt_obj_add_event_cb(list1, list_item_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	return screen_setup;
}