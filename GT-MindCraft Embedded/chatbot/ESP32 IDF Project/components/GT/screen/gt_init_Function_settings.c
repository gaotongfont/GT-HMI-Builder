#include "gt_ui.h"
#include "gt_font_config.h"

static const char *TAG = "SCREEN_FUNCTION_SETTINGS";

/** Function_settings */
gt_obj_st * Function_settings = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * btn2 = NULL;
static gt_obj_st * btn_emotion = NULL;
static gt_obj_st * lab_emotion = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * btn3 = NULL;
static gt_obj_st * imgbtn7 = NULL;
static gt_obj_st * imgbtn8 = NULL;
static gt_obj_st * imgbtn9 = NULL;
static gt_obj_st * imgbtn10 = NULL;
static gt_obj_st * imgbtn11 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st* list1 = NULL;
static gt_obj_st * input1 = NULL;
static uint8_t funct_list_option = AI_SETTING_NONE;

static void screen_setup_0_cb(gt_event_st * e) {
	funct_list_option = AI_SETTING_NONE;
    gt_scr_id_t pre_screen_id = gt_scr_stack_get_prev_id();
    ESP_LOGI(TAG,"--------------------pre_screen_id = %d\n", pre_screen_id);
    if (pre_screen_id == GT_ID_SCREEN_SETUP)
    {
        gt_disp_stack_go_back(2);

    } else {
        gt_disp_stack_go_back(1);
    }

}

static void img1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void keypay_common_key_cb(gt_event_st * e) {
    gt_obj_st * target_obj = e->target;
    char *text = gt_btn_get_text(target_obj);
    ESP_LOGI(TAG,"-------------------------%s\n", text);
    gt_input_append_value(input1, text);
}

static void keypay_ok_key_cb(gt_event_st * e) {
    char *text = gt_input_get_value(input1);
    ESP_LOGI(TAG,"-------------------------%s\n", text);
    gt_obj_st * target_obj = (gt_obj_st * )e->origin->parent;
    gt_dialog_close(target_obj);
    cb_data.settings->max_output_size = atoi(text);
    ESP_LOGI(TAG,"-------------------------%d\n", cb_data.settings->max_output_size);
    cb_data.settings->max_output_size = (cb_data.settings->max_output_size < 50) ? 50 : cb_data.settings->max_output_size;
    cb_data.settings->max_output_size = (cb_data.settings->max_output_size > 4000) ? 4000 : cb_data.settings->max_output_size;
    gt_input_set_value(input1, " %d", cb_data.settings->max_output_size);
}

static void keypay_delete_key_cb(gt_event_st * e) {
    gt_input_del_value(input1);
}

gt_obj_st * _Numeric_Keypad_dialog1Copy_init() {


	gt_obj_st * dialog1Copy = NULL;
	gt_obj_st * d = NULL;
	gt_obj_st * c = NULL;
	gt_obj_st * b = NULL;
	gt_obj_st * a = NULL;
	gt_obj_st * h = NULL;
	gt_obj_st * OK = NULL;
	gt_obj_st * g = NULL;
	gt_obj_st * Delete = NULL;
	gt_obj_st * j = NULL;
	gt_obj_st * f = NULL;
	gt_obj_st * e = NULL;
	gt_obj_st * i = NULL;


	/** dialog1Copy */
	dialog1Copy = gt_dialog_create(false);
	gt_obj_set_pos(dialog1Copy, 9, 81);
	gt_obj_set_size(dialog1Copy, 219, 164);
	gt_dialog_set_bgcolor(dialog1Copy, gt_color_hex(0x181B22));
	gt_dialog_set_border_color(dialog1Copy, gt_color_hex(0xc7c7c7));
	gt_dialog_set_border_width(dialog1Copy, 0);
	gt_dialog_set_border_radius(dialog1Copy, 15);


	/** d */
	d = gt_btn_create(dialog1Copy);
	gt_obj_set_pos(d, 166, 94);
	gt_obj_set_size(d, 44, 44);
	gt_btn_set_font_color(d, gt_color_hex(0xffffff));
	gt_btn_set_font_family(d, gray_black_16);
	gt_btn_set_font_cjk(d, 0);
	gt_btn_set_font_align(d, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(d, "4");
	gt_btn_set_color_background(d, gt_color_hex(0x30384A));
	gt_btn_set_color_pressed(d, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(d, gt_color_hex(0x000000));
	gt_btn_set_radius(d, 8);
	gt_obj_add_event_cb(d, keypay_common_key_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** c */
	c = gt_btn_create(dialog1Copy);
	gt_obj_set_pos(c, 120, 94);
	gt_obj_set_size(c, 44, 44);
	gt_btn_set_font_color(c, gt_color_hex(0xffffff));
	gt_btn_set_font_family(c, gray_black_16);
	gt_btn_set_font_cjk(c, 0);
	gt_btn_set_font_align(c, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(c, "3");
	gt_btn_set_color_background(c, gt_color_hex(0x30384A));
	gt_btn_set_color_pressed(c, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(c, gt_color_hex(0x000000));
	gt_btn_set_radius(c, 8);
	gt_obj_add_event_cb(c, keypay_common_key_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** b */
	b = gt_btn_create(dialog1Copy);
	gt_obj_set_pos(b, 74, 94);
	gt_obj_set_size(b, 44, 44);
	gt_btn_set_font_color(b, gt_color_hex(0xffffff));
	gt_btn_set_font_family(b, gray_black_16);
	gt_btn_set_font_cjk(b, 0);
	gt_btn_set_font_align(b, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(b, "2");
	gt_btn_set_color_background(b, gt_color_hex(0x30384A));
	gt_btn_set_color_pressed(b, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(b, gt_color_hex(0x000000));
	gt_btn_set_radius(b, 8);
	gt_obj_add_event_cb(b, keypay_common_key_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** a */
	a = gt_btn_create(dialog1Copy);
	gt_obj_set_pos(a, 28, 94);
	gt_obj_set_size(a, 44, 44);
	gt_btn_set_font_color(a, gt_color_hex(0xffffff));
	gt_btn_set_font_family(a, gray_black_16);
	gt_btn_set_font_cjk(a, 0);
	gt_btn_set_font_align(a, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(a, "1");
	gt_btn_set_color_background(a, gt_color_hex(0x30384A));
	gt_btn_set_color_pressed(a, gt_color_hex(0x1A589F));
	gt_btn_set_font_color_pressed(a, gt_color_hex(0x000000));
	gt_btn_set_radius(a, 8);
	gt_obj_add_event_cb(a, keypay_common_key_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** h */
	h = gt_btn_create(dialog1Copy);
	gt_obj_set_pos(h, 166, 141);
	gt_obj_set_size(h, 44, 44);
	gt_btn_set_font_color(h, gt_color_hex(0xffffff));
	gt_btn_set_font_family(h, gray_black_16);
	gt_btn_set_font_cjk(h, 0);
	gt_btn_set_font_align(h, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(h, "8");
	gt_btn_set_color_background(h, gt_color_hex(0x30384A));
	gt_btn_set_color_pressed(h, gt_color_hex(0x1A589F));
	gt_btn_set_font_color_pressed(h, gt_color_hex(0x000000));
	gt_btn_set_radius(h, 8);
	gt_obj_add_event_cb(h, keypay_common_key_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** OK */
	/** 确认键 */
	OK = gt_imgbtn_create(dialog1Copy);
	gt_obj_set_pos(OK, 166, 188);
	gt_obj_set_size(OK, 44, 44);
	gt_imgbtn_set_src(OK, "f:img_3110_44x44.png");
	gt_imgbtn_set_src_press(OK, "f:img_3116_44x44.png");
	gt_imgbtn_add_state_item(OK, "f:img_3117_44x44.png");
	gt_obj_add_event_cb(OK, keypay_ok_key_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** g */
	g = gt_btn_create(dialog1Copy);
	gt_obj_set_pos(g, 120, 141);
	gt_obj_set_size(g, 44, 44);
	gt_btn_set_font_color(g, gt_color_hex(0xffffff));
	gt_btn_set_font_family(g, gray_black_16);
	gt_btn_set_font_cjk(g, 0);
	gt_btn_set_font_align(g, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(g, "7");
	gt_btn_set_color_background(g, gt_color_hex(0x30384A));
	gt_btn_set_color_pressed(g, gt_color_hex(0x1A589F));
	gt_btn_set_font_color_pressed(g, gt_color_hex(0x000000));
	gt_btn_set_radius(g, 8);
	gt_obj_add_event_cb(g, keypay_common_key_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** Delete */
	/** 删除键 */
	Delete = gt_imgbtn_create(dialog1Copy);
	gt_obj_set_pos(Delete, 120, 188);
	gt_obj_set_size(Delete, 44, 44);
	gt_imgbtn_set_src(Delete, "f:img_3111_44x44.png");
	gt_imgbtn_add_state_item(Delete, "f:img_3118_44x44.png");
	gt_obj_add_event_cb(Delete, keypay_delete_key_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** j */
	j = gt_btn_create(dialog1Copy);
	gt_obj_set_pos(j, 74, 188);
	gt_obj_set_size(j, 44, 44);
	gt_btn_set_font_color(j, gt_color_hex(0xffffff));
	gt_btn_set_font_family(j, gray_black_16);
	gt_btn_set_font_cjk(j, 0);
	gt_btn_set_font_align(j, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(j, "0");
	gt_btn_set_color_background(j, gt_color_hex(0x30384A));
	gt_btn_set_color_pressed(j, gt_color_hex(0x1A589F));
	gt_btn_set_font_color_pressed(j, gt_color_hex(0x000000));
	gt_btn_set_radius(j, 8);
	gt_obj_add_event_cb(j, keypay_common_key_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** f */
	f = gt_btn_create(dialog1Copy);
	gt_obj_set_pos(f, 74, 141);
	gt_obj_set_size(f, 44, 44);
	gt_btn_set_font_color(f, gt_color_hex(0xffffff));
	gt_btn_set_font_family(f, gray_black_16);
	gt_btn_set_font_cjk(f, 0);
	gt_btn_set_font_align(f, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(f, "6");
	gt_btn_set_color_background(f, gt_color_hex(0x30384A));
	gt_btn_set_color_pressed(f, gt_color_hex(0x1A589F));
	gt_btn_set_font_color_pressed(f, gt_color_hex(0x000000));
	gt_btn_set_radius(f, 8);
	gt_obj_add_event_cb(f, keypay_common_key_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** e */
	e = gt_btn_create(dialog1Copy);
	gt_obj_set_pos(e, 28, 141);
	gt_obj_set_size(e, 44, 44);
	gt_btn_set_font_color(e, gt_color_hex(0xffffff));
	gt_btn_set_font_family(e, gray_black_16);
	gt_btn_set_font_cjk(e, 0);
	gt_btn_set_font_align(e, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(e, "5");
	gt_btn_set_color_background(e, gt_color_hex(0x30384A));
	gt_btn_set_color_pressed(e, gt_color_hex(0x1A589F));
	gt_btn_set_font_color_pressed(e, gt_color_hex(0x000000));
	gt_btn_set_radius(e, 8);
	gt_obj_add_event_cb(e, keypay_common_key_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** i */
	i = gt_btn_create(dialog1Copy);
	gt_obj_set_pos(i, 28, 188);
	gt_obj_set_size(i, 44, 44);
	gt_btn_set_font_color(i, gt_color_hex(0xffffff));
	gt_btn_set_font_family(i, gray_black_16);
	gt_btn_set_font_cjk(i, 0);
	gt_btn_set_font_align(i, GT_ALIGN_CENTER_MID);
	gt_btn_set_text(i, "9");
	gt_btn_set_color_background(i, gt_color_hex(0x30384A));
	gt_btn_set_color_pressed(i, gt_color_hex(0x1A589F));
	gt_btn_set_font_color_pressed(i, gt_color_hex(0x000000));
	gt_btn_set_radius(i, 8);
	gt_obj_add_event_cb(i, keypay_common_key_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);




	gt_dialog_show(dialog1Copy);

	return dialog1Copy;
}

static void btn3_0_cb(gt_event_st * e) {
	_Numeric_Keypad_dialog1Copy_init();
}

static void imgbtn10_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_SETUP, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static uint8_t get_func_funct_list_option(gt_obj_st* obj)
{
	if(!obj) return AI_SETTING_NONE;

	if(obj == btn1) return AI_SETTING_MODEL;
	else if(obj == btn2) return AI_SETTING_REPLY_STYLE;
	else if(obj == btn_emotion) return AI_SETTING_EMOTION_VALUE;
	return AI_SETTING_NONE;
}

static void disp_list_cb(gt_event_st * e) {
	gt_obj_st* obj = e->target;
	int x = obj->area.x;
	int y = obj->area.y;
	uint16_t h = obj->area.h;
	uint8_t tmp_option = get_func_funct_list_option(obj);

	uint8_t visible = gt_obj_get_visible(list1);

	if(AI_SETTING_NONE == tmp_option){
		gt_obj_set_visible(list1, GT_INVISIBLE);
		funct_list_option = tmp_option;
		return;
	}

	printf("tmp_option = %d\r\n",tmp_option);
	if(AI_SETTING_EMOTION_VALUE == tmp_option){
		gt_obj_set_pos(list1, x, y-3-list1->area.h);
		printf("y = %d\r\n", y-3-list1->area.h);
	}
	else{
		gt_obj_set_pos(list1, x, y+h+3);
	}

	if(funct_list_option == tmp_option){
		gt_obj_set_visible(list1, !visible);
	}
	else {
		gt_obj_set_visible(list1, GT_VISIBLE);
	}
	set_items_in_listview(list1, tmp_option);
	funct_list_option = tmp_option;
}

static void list_item_cb(gt_event_st * e) {
    gt_size_t selected_idx = gt_listview_get_idx_selected(list1);
    ESP_LOGI(TAG,"----------------selected_idx = %d\n", selected_idx);
    if (selected_idx < 0)
    {
        return;
    }
    char * selectedItem = gt_listview_get_selected_item_text(list1);
    ESP_LOGI(TAG, "-------------------selectedItem=%s\n", selectedItem);
	switch(funct_list_option){
		case AI_SETTING_MODEL:
			gt_btn_set_text(btn1, " %s", selectedItem);
			sprintf(cb_data.settings->mode, "%s", gt_mode_en_string_get(selectedItem));
            if (strcmp(cb_data.settings->mode, "pro") == 0 || strcmp(cb_data.settings->mode, "pro_character") == 0) {
                sprintf(cb_data.settings->voice_id,"%s","cute_boy");
            } else if (strcmp(cb_data.settings->mode, "standard") == 0 || strcmp(cb_data.settings->mode, "standard_character") == 0) {
                sprintf(cb_data.settings->voice_id,"%s","301000");
            }
			break;
		case AI_SETTING_REPLY_STYLE:
			gt_btn_set_text(btn2, " %s", selectedItem);
			sprintf(cb_data.settings->bot_response_style, "%s", gt_reply_style_en_string_get(selectedItem));
			break;
		case AI_SETTING_EMOTION_VALUE:
			gt_btn_set_text(btn_emotion, " %s", selectedItem);
			sprintf(cb_data.settings->emotion_value, "%s", selectedItem);
			break;
		default:
			break;
	}
	gt_obj_set_visible(list1, GT_INVISIBLE);
}


gt_obj_st * gt_init_Function_settings(void)
{
	Function_settings = gt_obj_create(NULL);
	gt_obj_add_event_cb(Function_settings, screen_setup_0_cb, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
	gt_screen_set_bgcolor(Function_settings, gt_color_hex(0x000000));




	/** img1 */
	img1 = gt_img_create(Function_settings);
	gt_obj_set_pos(img1, 8, 10);
	gt_obj_set_size(img1, 16, 16);
	gt_img_set_src(img1, "f:img_fh_16x16.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** lab1 */
	lab1 = gt_label_create(Function_settings);
	gt_obj_set_pos(lab1, 35, 3);
	gt_obj_set_size(lab1, 55, 26);
    gt_label_set_font_family(lab1, gray_black_16);
	gt_label_set_font_cjk(lab1, 0);
	gt_label_set_font_color(lab1, gt_color_hex(0x94a5b3));
	gt_label_set_font_align(lab1, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab1, "设置");



	/** btn1 */
	btn1 = gt_btn_create(Function_settings);
	gt_obj_set_pos(btn1, 12, 106);
	gt_obj_set_size(btn1, 216, 36);
	gt_btn_set_font_color(btn1, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn1, gray_black_16);
	gt_btn_set_font_cjk(btn1, 0);
	gt_btn_set_font_align(btn1, GT_ALIGN_LEFT_MID);
	// gt_btn_set_text(btn1, " 专家模式");
	gt_btn_set_text(btn1, " %s", gt_mode_cn_string_get(cb_data.settings->mode));
	gt_btn_set_color_background(btn1, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn1, gt_color_hex(0x000000));
	gt_btn_set_radius(btn1, 8);
	gt_obj_add_event_cb(btn1, disp_list_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	/** lab2 */
	lab2 = gt_label_create(Function_settings);
	gt_obj_set_pos(lab2, 12, 79);
	gt_obj_set_size(lab2, 83, 23);
	gt_label_set_font_color(lab2, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab2, gray_black_16);
	gt_label_set_font_cjk(lab2, 0);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab2, "模式：");



	/** btn2 */
	btn2 = gt_btn_create(Function_settings);
	gt_obj_set_pos(btn2, 12, 182);
	gt_obj_set_size(btn2, 217, 36);
	gt_btn_set_font_color(btn2, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn2, gray_black_16);
	gt_btn_set_font_cjk(btn2, 0);
	gt_btn_set_font_align(btn2, GT_ALIGN_LEFT_MID);
	// gt_btn_set_text(btn2, " 正常");
	gt_btn_set_text(btn2, " %s", gt_reply_style_cn_string_get(cb_data.settings->bot_response_style));
	gt_btn_set_color_background(btn2, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn2, gt_color_hex(0x000000));
	gt_btn_set_radius(btn2, 6);
	gt_obj_add_event_cb(btn2, disp_list_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);



	/** lab4 */
	lab4 = gt_label_create(Function_settings);
	gt_obj_set_pos(lab4, 12, 154);
	gt_obj_set_size(lab4, 84, 21);
	gt_label_set_font_color(lab4, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab4, gray_black_16);
	gt_label_set_font_cjk(lab4, 0);
	gt_label_set_font_align(lab4, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab4, "回复风格：");



	/** lab5 */
	lab5 = gt_label_create(Function_settings);
	gt_obj_set_pos(lab5, 12, 230);
	gt_obj_set_size(lab5, 84, 23);
	gt_label_set_font_color(lab5, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab5, gray_black_16);
	gt_label_set_font_cjk(lab5, 0);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, "最大输出：");

	lab_emotion = gt_label_create(Function_settings);
	gt_obj_set_pos(lab_emotion, 12, 320);
	gt_obj_set_size(lab_emotion, 84, 23);
	gt_label_set_font_color(lab_emotion, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab_emotion, gray_black_16);
	gt_label_set_font_cjk(lab_emotion, 0);
	gt_label_set_font_align(lab_emotion, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab_emotion, "情绪识别：");

	btn_emotion = gt_btn_create(Function_settings);
	gt_obj_set_pos(btn_emotion, 12, 350);
	gt_obj_set_size(btn_emotion, 217, 36);
	gt_btn_set_font_color(btn_emotion, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn_emotion, gray_black_16);
	gt_btn_set_font_cjk(btn_emotion, 0);
	gt_btn_set_font_align(btn_emotion, GT_ALIGN_LEFT_MID);
	gt_btn_set_text(btn_emotion, " %s", cb_data.settings->emotion_value);
	gt_btn_set_color_background(btn_emotion, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn_emotion, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn_emotion, gt_color_hex(0x000000));
	gt_btn_set_radius(btn_emotion, 6);
	gt_obj_add_event_cb(btn_emotion, disp_list_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


#if 0
	/** btn3 */
	btn3 = gt_btn_create(Function_settings);
	gt_obj_set_pos(btn3, 12, 260);
	gt_obj_set_size(btn3, 217, 36);
	gt_btn_set_font_color(btn3, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn3, gray_black_16);
	gt_btn_set_font_cjk(btn3, 0);
	gt_btn_set_font_align(btn3, GT_ALIGN_LEFT_MID);
	// gt_btn_set_text(btn3, " 50");
	gt_btn_set_text(btn3, " %d", cb_data.settings->max_output_size);
	gt_btn_set_color_background(btn3, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn3, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn3, gt_color_hex(0x000000));
	gt_btn_set_radius(btn3, 6);
	gt_obj_add_event_cb(btn3, btn3_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
#else
	/** input1 */
	input1 = gt_input_create(Function_settings);
	gt_obj_set_pos(input1, 12, 260);
	gt_obj_set_size(input1, 216, 36);
	gt_input_set_font_color(input1, gt_color_hex(0x4193fb));
	gt_input_set_font_align(input1, GT_ALIGN_LEFT_MID);
	gt_input_set_placeholder(input1, "50~4000");
    gt_input_set_value(input1, " %d", cb_data.settings->max_output_size);
	gt_input_set_border_width(input1, 2);
	gt_input_set_bg_color(input1, gt_color_hex(0x181b22));
    gt_input_set_border_color(input1, gt_color_hex(0x181b22));
	gt_obj_add_event_cb(input1, btn3_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
#endif

	/** imgbtn7 */
	imgbtn7 = gt_imgbtn_create(Function_settings);
	gt_obj_set_pos(imgbtn7, 198, 116);
	gt_obj_set_size(imgbtn7, 27, 20);
	gt_imgbtn_set_src(imgbtn7, "f:img_down1_27x20.png");
	gt_imgbtn_add_state_item(imgbtn7, "f:img_down2_27x20.png");


	/** imgbtn8 */
	imgbtn8 = gt_imgbtn_create(Function_settings);
	gt_obj_set_pos(imgbtn8, 198, 190);
	gt_obj_set_size(imgbtn8, 27, 20);
	gt_imgbtn_set_src(imgbtn8, "f:img_down1_27x20.png");
	gt_imgbtn_add_state_item(imgbtn8, "f:img_up1_27x20.png");


	/** imgbtn9 */
	imgbtn9 = gt_imgbtn_create(Function_settings);
	gt_obj_set_pos(imgbtn9, 198, 269);
	gt_obj_set_size(imgbtn9, 27, 20);
	gt_imgbtn_set_src(imgbtn9, "f:img_down1_27x20.png");
	gt_imgbtn_add_state_item(imgbtn9, "f:img_up1_27x20.png");


	/** imgbtn10 */
	imgbtn10 = gt_imgbtn_create(Function_settings);
	gt_obj_set_pos(imgbtn10, 10, 33);
	gt_obj_set_size(imgbtn10, 109, 39);
	gt_imgbtn_set_src(imgbtn10, "f:img_1AI_Settings_n_109x39.png");
	gt_imgbtn_set_src_press(imgbtn10, "f:img_1AI_Settings_p_109x39.png");
	gt_obj_add_event_cb(imgbtn10, imgbtn10_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** imgbtn11 */
	imgbtn11 = gt_imgbtn_create(Function_settings);
	gt_obj_set_pos(imgbtn11, 120, 33);
	gt_obj_set_size(imgbtn11, 109, 39);
	gt_imgbtn_set_src(imgbtn11, "f:img_1Function_settings_p_109x39.png");
	gt_imgbtn_set_src_press(imgbtn11, "f:img_1Function_settings_n_109x39.png");


	/** lab6 */
	lab6 = gt_label_create(Function_settings);
	gt_obj_set_pos(lab6, 12, 292);
	gt_obj_set_size(lab6, 142, 26);
	gt_label_set_font_color(lab6, gt_color_hex(0x4C5872));
	gt_label_set_font_family(lab6, gray_black_16);
	gt_label_set_font_cjk(lab6, 0);
	gt_label_set_font_align(lab6, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab6, "范围：50~4000");



	list1 = gt_listview_create(Function_settings);
	gt_obj_set_pos(list1, 19, 180);
	gt_obj_set_size(list1, 216, 80);
	// gt_listview_set_font_color(list1, gt_color_hex(0xcadded));
	gt_listview_set_font_family(list1, gray_black_16);
	gt_listview_set_font_cjk(list1, 0);
	gt_listview_set_font_align(list1, GT_ALIGN_CENTER_MID);
	gt_listview_set_item_height(list1, 40);
	gt_listview_set_border_color(list1,gt_color_hex(0x454d5a));
	gt_listview_set_border_width(list1, 1);
	gt_listview_set_septal_line(list1, 0);
	gt_listview_set_highlight_mode(list1, 1);
	// gt_listview_set_bg_color(list1, gt_color_hex(0x1d2026));
	gt_listview_set_bg_color(list1, gt_color_hex(0xffffff));
	gt_listview_set_item_reduce(list1, 2);
	gt_listview_set_item_radius(list1, 6);
	gt_listview_set_scale(list1, 25, 75);
	gt_listview_set_scale_triple(list1, 20, 60, 20);
	gt_listview_set_next_row_item_count(list1, 1);
    gt_obj_set_visible(list1, GT_INVISIBLE);
	gt_obj_add_event_cb(list1, list_item_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


	return Function_settings;
}

