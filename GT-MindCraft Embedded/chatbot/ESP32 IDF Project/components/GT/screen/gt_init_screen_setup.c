#include "gt_ui.h"
#include "gt_font_config.h"


/** screen_setup */
gt_obj_st * screen_setup = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * btn1Copy = NULL;
static gt_obj_st * lab2Copy = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * btn5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * btn7 = NULL;
static gt_obj_st * img7 = NULL;
static gt_obj_st * img8 = NULL;
static gt_obj_st * img9 = NULL;
static gt_obj_st * lab7Copy = NULL;
static gt_obj_st * btn7Copy = NULL;
static gt_obj_st * img9Copy = NULL;

/* -------------------------------------------------------------------------- */
static gt_obj_st* go_back_rect = NULL;
static gt_obj_st* list1 = NULL;
static uint8_t list_option = AI_SETTING_NONE;
/* -------------------------------------------------------------------------- */
static uint8_t get_list_option(gt_obj_st* obj)
{
	if(!obj) return AI_SETTING_NONE;

	if(obj == btn1Copy) return AI_SETTING_AGE;
	else if(obj == btn1) return AI_SETTING_ROLE;
	else if(obj == btn5) return AI_SETTING_CHAR;
	else if(obj == btn7) return AI_SETTING_TIMBRE;
	else if(obj == btn7Copy) return AI_SETTING_AI_NAME;
	return AI_SETTING_NONE;
}

static void go_back_to_previous_page(gt_event_st * e) {
	list_option = AI_SETTING_NONE;
	gt_disp_stack_go_back(1);
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

	if(AI_SETTING_TIMBRE == tmp_option || AI_SETTING_AI_NAME == tmp_option){
		gt_obj_set_pos(list1, x, y-3-list1->area.h);
	}
	else{
		gt_obj_set_pos(list1, x, y+h+3);
	}

	if(list_option == tmp_option){
		gt_obj_set_visible(list1, !visible);
	}
	else {
		set_items_in_listview(list1, tmp_option);
		gt_obj_set_visible(list1, GT_VISIBLE);
	}
	list_option = tmp_option;
}
/**
 * @brief 列表点击回调，设置选中项的内容到对应的btn显示，同时更新settings数据
 *
 */
static void list_item_cb(gt_event_st * e) {
    char * selectedItem = gt_listview_get_selected_item_text(list1);
	switch(list_option){
		case AI_SETTING_AGE:
			gt_btn_set_text(btn1Copy, "  %s", selectedItem);
			cb_data.settings->user_age = atoi(selectedItem);
			break;
		case AI_SETTING_ROLE:
			gt_btn_set_text(btn1, "  %s", selectedItem);
			sprintf(cb_data.settings->bot_character, "%s", selectedItem);
			break;
		case AI_SETTING_CHAR:
			gt_btn_set_text(btn5, "  %s", selectedItem);
			sprintf(cb_data.settings->bot_personality, "%s", selectedItem);
			break;
		case AI_SETTING_TIMBRE:
			gt_btn_set_text(btn7, "  %s", selectedItem);
			sprintf(cb_data.settings->voice_id, "%s", gt_vocie_id_string_get(selectedItem));
			break;
		case AI_SETTING_AI_NAME:
			gt_btn_set_text(btn7Copy, "  %s", selectedItem);
			sprintf(cb_data.settings->bot_name, "%s", selectedItem);
			break;
		default:
			break;
	}
	gt_obj_set_visible(list1, GT_INVISIBLE);
}


gt_obj_st * gt_init_screen_setup(void)
{
	screen_setup = gt_obj_create(NULL);
	gt_obj_add_event_cb(screen_setup, go_back_to_previous_page, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
	gt_screen_set_bgcolor(screen_setup, gt_color_hex(0x000000));


	go_back_rect = gt_rect_create(screen_setup);
	gt_obj_set_pos(go_back_rect, 0, 0);
	gt_obj_set_size(go_back_rect, 35, 30);
	gt_obj_set_opa(go_back_rect, GT_OPA_TRANSP);
	gt_obj_add_event_cb(go_back_rect, go_back_to_previous_page, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	/** img1 */
	img1 = gt_img_create(go_back_rect);
	gt_obj_set_pos(img1, 13, 10);
	gt_obj_set_size(img1, 16, 16);
	gt_img_set_src(img1, "f:img_fh_16x16.png");
	gt_obj_set_touch_parent(img1, true);

	/** lab3 */
	lab3 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab3, 36, 5);
	gt_obj_set_size(lab3, 55, 26);
	gt_label_set_font_color(lab3, gt_color_hex(0x94a5b3));
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_font_family(lab3, gray_black_16);
	gt_label_set_text(lab3, "设置");

	/** lab2Copy */
	lab2Copy = gt_label_create(screen_setup);
	gt_obj_set_pos(lab2Copy, 25, 42);
	gt_obj_set_size(lab2Copy, 83, 23);
	gt_label_set_font_color(lab2Copy, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab2Copy, gray_black_16);
	gt_label_set_font_cjk(lab2Copy, 0);
	gt_label_set_font_align(lab2Copy, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab2Copy, "用户年龄：");

	/** btn1Copy */
	btn1Copy = gt_btn_create(screen_setup);
	gt_obj_set_pos(btn1Copy, 21, 70);
	gt_obj_set_size(btn1Copy, 200, 36);
	gt_btn_set_font_color(btn1Copy, gt_color_hex(0x4193fb));
	gt_btn_set_font_align(btn1Copy, GT_ALIGN_LEFT_MID);
	gt_btn_set_color_background(btn1Copy, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn1Copy, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn1Copy, gt_color_hex(0x000000));
	gt_btn_set_radius(btn1Copy, 8);
	gt_btn_set_text(btn1Copy, "  %d", cb_data.settings->user_age);
	gt_obj_add_event_cb(btn1Copy, disp_list_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
    gt_obj_set_fixed(btn1Copy, true);

	/** img7 */
	img7 = gt_img_create(btn1Copy);
	gt_obj_set_pos(img7, 185, 78);
	gt_obj_set_size(img7, 27, 20);
	gt_img_set_src(img7, "f:img_down1_27x20.png");
	gt_obj_set_touch_parent(img7, true);


	/** lab5 */
	lab5 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab5, 25, 113);
	gt_obj_set_size(lab5, 84, 22);
	gt_label_set_font_color(lab5, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab5, gray_black_16);
	gt_label_set_font_cjk(lab5, 0);
	gt_label_set_font_align(lab5, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab5, "角色设定：");

	/** btn1 */
	btn1 = gt_btn_create(screen_setup);
	gt_obj_set_pos(btn1, 19, 141);
	gt_obj_set_size(btn1, 200, 36);
	gt_btn_set_font_color(btn1, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn1, gray_black_16);
	gt_btn_set_font_cjk(btn1, 0);
	gt_btn_set_font_align(btn1, GT_ALIGN_LEFT_MID);
	gt_btn_set_color_background(btn1, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn1, gt_color_hex(0x000000));
	gt_btn_set_radius(btn1, 6);
	gt_btn_set_text(btn1, "  %s", cb_data.settings->bot_character);
	gt_obj_add_event_cb(btn1, disp_list_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
    gt_obj_set_fixed(btn1, true);

	/** img3 */
	img3 = gt_img_create(btn1);
	gt_obj_set_pos(img3, 184, 150);
	gt_obj_set_size(img3, 27, 20);
	gt_img_set_src(img3, "f:img_down1_27x20.png");
	gt_obj_set_touch_parent(img3, true);

	/** lab6 */
	lab6 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab6, 25, 185);
	gt_obj_set_size(lab6, 84, 21);
	gt_label_set_font_color(lab6, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab6, gray_black_16);
	gt_label_set_font_cjk(lab6, 0);
	gt_label_set_font_align(lab6, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab6, "性格设定：");

	/** btn5 */
	btn5 = gt_btn_create(screen_setup);
	gt_obj_set_pos(btn5, 19, 213);
	gt_obj_set_size(btn5, 200, 36);
	gt_btn_set_font_color(btn5, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn5, gray_black_16);
	gt_btn_set_font_cjk(btn5, 0);
	gt_btn_set_font_align(btn5, GT_ALIGN_LEFT_MID);
	gt_btn_set_color_background(btn5, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn5, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn5, gt_color_hex(0x000000));
	gt_btn_set_radius(btn5, 6);
	gt_btn_set_text(btn5, "  %s", cb_data.settings->bot_personality);
	gt_obj_add_event_cb(btn5, disp_list_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
    gt_obj_set_fixed(btn5, true);


	/** img8 */
	img8 = gt_img_create(btn5);
	gt_obj_set_pos(img8, 184, 221);
	gt_obj_set_size(img8, 27, 20);
	gt_img_set_src(img8, "f:img_down1_27x20.png");
	gt_obj_set_touch_parent(img8, true);

	/** lab7 */
	lab7 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab7, 25, 254);
	gt_obj_set_size(lab7, 84, 23);
	gt_label_set_font_color(lab7, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab7, gray_black_16);
	gt_label_set_font_cjk(lab7, 0);
	gt_label_set_font_align(lab7, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab7, "音色设定：");

	/** btn7 */
	btn7 = gt_btn_create(screen_setup);
	gt_obj_set_pos(btn7, 19, 282);
	gt_obj_set_size(btn7, 200, 36);
	gt_btn_set_font_color(btn7, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn7, gray_black_16);
	gt_btn_set_font_cjk(btn7, 0);
	gt_btn_set_font_align(btn7, GT_ALIGN_LEFT_MID);
	gt_btn_set_color_background(btn7, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn7, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn7, gt_color_hex(0x000000));
	gt_btn_set_radius(btn7, 6);
	gt_btn_set_text(btn7, "  %s", gt_timber_string_get(cb_data.settings->voice_id));
	gt_obj_add_event_cb(btn7, disp_list_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
    gt_obj_set_fixed(btn7, true);


	/** img9 */
	img9 = gt_img_create(btn7);
	gt_obj_set_pos(img9, 184, 292);
	gt_obj_set_size(img9, 27, 20);
	gt_img_set_src(img9, "f:img_down1_27x20.png");
	gt_obj_set_touch_parent(img9, true);


	/** lab7Copy */
	lab7Copy = gt_label_create(screen_setup);
	gt_obj_set_pos(lab7Copy, 25, 325);
	gt_obj_set_size(lab7Copy, 84, 23);
	gt_label_set_font_color(lab7Copy, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab7Copy, gray_black_16);
	gt_label_set_font_cjk(lab7Copy, 0);
	gt_label_set_font_align(lab7Copy, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab7Copy, "AI昵称");

	/** btn7Copy */
	btn7Copy = gt_btn_create(screen_setup);
	gt_obj_set_pos(btn7Copy, 17, 353);
	gt_obj_set_size(btn7Copy, 200, 36);
	gt_btn_set_font_color(btn7Copy, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn7Copy, gray_black_16);
	gt_btn_set_font_cjk(btn7Copy, 0);
	gt_btn_set_font_align(btn7Copy, GT_ALIGN_LEFT_MID);
	gt_btn_set_color_background(btn7Copy, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn7Copy, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn7Copy, gt_color_hex(0x000000));
	gt_btn_set_radius(btn7Copy, 6);
	gt_btn_set_text(btn7Copy, "  %s", cb_data.settings->bot_name);
	gt_obj_add_event_cb(btn7Copy, disp_list_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
    gt_obj_set_fixed(btn7Copy, true);

	/** img9Copy */
	img9Copy = gt_img_create(btn7Copy);
	gt_obj_set_pos(img9Copy, 178, 364);
	gt_obj_set_size(img9Copy, 27, 20);
	gt_img_set_src(img9Copy, "f:img_down1_27x20.png");

	list1 = gt_listview_create(screen_setup);
	gt_obj_set_pos(list1, 19, 180);
	gt_obj_set_size(list1, 200, 80);
	gt_listview_set_font_color(list1, gt_color_hex(0xcadded));
	gt_listview_set_font_family(list1, gray_black_16);
	gt_listview_set_font_cjk(list1, 0);
	gt_listview_set_font_align(list1, GT_ALIGN_CENTER_MID);
	gt_listview_set_item_height(list1, 40);
	gt_listview_set_border_color(list1,gt_color_hex(0x454d5a));
	gt_listview_set_border_width(list1, 1);
	gt_listview_set_septal_line(list1, 0);
	gt_listview_set_highlight_mode(list1, 1);
	gt_listview_set_bg_color(list1, gt_color_hex(0x1d2026));
	gt_listview_set_item_reduce(list1, 2);
	gt_listview_set_item_radius(list1, 6);
	gt_listview_set_scale(list1, 25, 75);
	gt_listview_set_scale_triple(list1, 20, 60, 20);
	gt_listview_set_next_row_item_count(list1, 1);
    gt_obj_set_visible(list1, GT_INVISIBLE);
	gt_obj_add_event_cb(list1, list_item_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

	return screen_setup;
}
