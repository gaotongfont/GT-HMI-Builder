#include "gt_ui.h"
#include "gt_font_config.h"


/** screen_js */
gt_obj_st * screen_js = NULL;
static gt_obj_st * listvxgCopy = NULL;

static void screen_setup_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

gt_obj_st * gt_init_screen_js(void)
{
	screen_js = gt_obj_create(NULL);
	gt_obj_add_event_cb(screen_js, screen_setup_0_cb, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
	gt_screen_set_bgcolor(screen_js, gt_color_hex(0x000000));


	

	/** listvxgCopy */
	listvxgCopy = gt_listview_create(screen_js);
	gt_obj_set_pos(listvxgCopy, 19, 57);
	gt_obj_set_size(listvxgCopy, 200, 166);
	gt_listview_set_font_color(listvxgCopy, gt_color_hex(0xcadded));
	gt_listview_set_font_family(listvxgCopy, gray_black_16);
	gt_listview_set_font_cjk(listvxgCopy, 0);
	gt_listview_set_font_align(listvxgCopy, GT_ALIGN_CENTER_MID);
	gt_listview_set_item_height(listvxgCopy, 40);
	gt_listview_set_border_color(listvxgCopy,gt_color_hex(0x454d5a));
	gt_listview_set_border_width(listvxgCopy, 1);
	gt_listview_set_septal_line(listvxgCopy, 0);
	gt_listview_set_highlight_mode(listvxgCopy, 1);
	gt_listview_set_bg_color(listvxgCopy, gt_color_hex(0x1d2026));
	gt_listview_set_item_reduce(listvxgCopy, 2);
	gt_listview_set_item_radius(listvxgCopy, 6);
	gt_listview_set_scale(listvxgCopy, 25, 75);
	gt_listview_set_scale_triple(listvxgCopy, 20, 60, 20);
	gt_listview_set_next_row_item_count(listvxgCopy, 1);
	gt_listview_add_item(listvxgCopy, "老师");
	gt_listview_add_item(listvxgCopy, "朋友");
	gt_listview_add_item(listvxgCopy, "密友");
	gt_listview_add_item(listvxgCopy, "心理咨询师");



	return screen_js;
}

