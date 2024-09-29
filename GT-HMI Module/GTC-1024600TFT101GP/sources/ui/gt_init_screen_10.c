#include "gt_ui.h"


/** screen_10 */
gt_obj_st * screen_10 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * rect2 = NULL;

/** 按下加载到主界面 */
static void action0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_2, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_10(void)
{
	screen_10 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_10, gt_color_hex(0x000000));

	

	/** img1 */
	/** 返回图标 */
	img1 = gt_img_create(screen_10);
	gt_obj_set_pos(img1, 1, 6);
	gt_obj_set_size(img1, 84, 58);
	gt_img_set_src(img1, ".:img_84x58_14.png");
	gt_obj_add_event_cb(img1, action0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab5 */
	/** 矩形文字，宋体24x24 */
	lab5 = gt_label_create(screen_10);
	gt_obj_set_pos(lab5, 93, 24);
	gt_obj_set_size(lab5, 100, 50);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 5);
	gt_label_set_text(lab5, "矩形");

	

	/** rect1 */
	/** 矩形 */
	rect1 = gt_rect_create(screen_10);
	gt_obj_set_pos(rect1, 169, 209);
	gt_obj_set_size(rect1, 200, 200);
	gt_rect_set_radius(rect1, 0);
	gt_rect_set_bg_color(rect1, gt_color_hex(0x8000ff));
	gt_rect_set_color_border(rect1, gt_color_hex(0x8000ff));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 0);

	

	/** rect2 */
	/** 矩形，边框宽度10 */
	rect2 = gt_rect_create(screen_10);
	gt_obj_set_pos(rect2, 513, 159);
	gt_obj_set_size(rect2, 300, 300);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0x0080ff));
	gt_rect_set_color_border(rect2, gt_color_hex(0x0080ff));
	gt_rect_set_fill(rect2, 0);
	gt_rect_set_border(rect2, 10);


	return screen_10;
}

