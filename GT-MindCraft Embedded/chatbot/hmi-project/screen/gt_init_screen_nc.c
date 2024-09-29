#include "gt_ui.h"
#include "gt_font_config.h"


/** screen_nc */
gt_obj_st * screen_nc = NULL;
static gt_obj_st * listvxg = NULL;

static void screen_setup_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

gt_obj_st * gt_init_screen_nc(void)
{
	screen_nc = gt_obj_create(NULL);
	gt_obj_add_event_cb(screen_nc, screen_setup_0_cb, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
	gt_screen_set_bgcolor(screen_nc, gt_color_hex(0x000000));


	

	/** listvxg */
	listvxg = gt_listview_create(screen_nc);
	gt_obj_set_pos(listvxg, 19, 57);
	gt_obj_set_size(listvxg, 200, 124);
	gt_listview_set_font_color(listvxg, gt_color_hex(0xcadded));
	gt_listview_set_font_family(listvxg, gray_black_16);
	gt_listview_set_font_cjk(listvxg, 0);
	gt_listview_set_font_align(listvxg, GT_ALIGN_CENTER_MID);
	gt_listview_set_item_height(listvxg, 40);
	gt_listview_set_border_color(listvxg,gt_color_hex(0x454d5a));
	gt_listview_set_border_width(listvxg, 1);
	gt_listview_set_septal_line(listvxg, 0);
	gt_listview_set_highlight_mode(listvxg, 1);
	gt_listview_set_bg_color(listvxg, gt_color_hex(0x1d2026));
	gt_listview_set_item_reduce(listvxg, 2);
	gt_listview_set_item_radius(listvxg, 10);
	gt_listview_set_scale(listvxg, 25, 75);
	gt_listview_set_scale_triple(listvxg, 20, 60, 20);
	gt_listview_set_next_row_item_count(listvxg, 1);
	gt_listview_add_item(listvxg, "智酱");
	gt_listview_add_item(listvxg, "聊天侠");
	gt_listview_add_item(listvxg, "老羞");



	return screen_nc;
}

