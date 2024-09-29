#include "gt_ui.h"
#include "gt_font_config.h"


/** screen_ys */
gt_obj_st * screen_ys = NULL;
static gt_obj_st * listv1 = NULL;

static void screen_setup_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

gt_obj_st * gt_init_screen_ys(void)
{
	screen_ys = gt_obj_create(NULL);
	gt_obj_add_event_cb(screen_ys, screen_setup_0_cb, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
	gt_screen_set_bgcolor(screen_ys, gt_color_hex(0x000000));


	

	/** listv1 */
	listv1 = gt_listview_create(screen_ys);
	gt_obj_set_pos(listv1, 19, 54);
	gt_obj_set_size(listv1, 200, 200);
	gt_listview_set_font_color(listv1, gt_color_hex(0xcadded));
	gt_listview_set_font_family(listv1, gray_black_16);
	gt_listview_set_font_cjk(listv1, 0);
	gt_listview_set_font_align(listv1, GT_ALIGN_CENTER_MID);
	gt_listview_set_item_height(listv1, 40);
	gt_listview_set_border_color(listv1,gt_color_hex(0x454d5a));
	gt_listview_set_border_width(listv1, 1);
	gt_listview_set_septal_line(listv1, 0);
	gt_listview_set_highlight_mode(listv1, 1);
	gt_listview_set_bg_color(listv1, gt_color_hex(0x1d2026));
	gt_listview_set_item_reduce(listv1, 2);
	gt_listview_set_item_radius(listv1, 6);
	gt_listview_set_scale(listv1, 25, 75);
	gt_listview_set_scale_triple(listv1, 20, 60, 20);
	gt_listview_set_next_row_item_count(listv1, 1);
	gt_listview_add_item(listv1, "青涩青年音色");
	gt_listview_add_item(listv1, "精英青年音色");
	gt_listview_add_item(listv1, "霸道青年音色");
	gt_listview_add_item(listv1, "青年大学生音色");
	gt_listview_add_item(listv1, "少女音色");
	gt_listview_add_item(listv1, "御姐音色");
	gt_listview_add_item(listv1, "成熟女性音色");
	gt_listview_add_item(listv1, "甜美女性音色");
	gt_listview_add_item(listv1, "成熟女性音色");
	gt_listview_add_item(listv1, "甜美女性音色");
	gt_listview_add_item(listv1, "男性主持人");
	gt_listview_add_item(listv1, "女性主持人");
	gt_listview_add_item(listv1, "男性有声书1");
	gt_listview_add_item(listv1, "男性有声书2");
	gt_listview_add_item(listv1, "女性有声书1");
	gt_listview_add_item(listv1, "女性有声书2");
	gt_listview_add_item(listv1, "青涩青年音色-beta");
	gt_listview_add_item(listv1, "精英青年音色-beta");
	gt_listview_add_item(listv1, "霸道青年音色-beta");
	gt_listview_add_item(listv1, "青年大学生音色-beta");
	gt_listview_add_item(listv1, "少女音色-beta");
	gt_listview_add_item(listv1, "御姐音色-beta");
	gt_listview_add_item(listv1, "成熟女性音色-beta");
	gt_listview_add_item(listv1, "甜美女性音色-beta");



	return screen_ys;
}

