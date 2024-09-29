#include "gt_ui.h"


/** screen_9 */
gt_obj_st * screen_9 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * img4 = NULL;
static gt_obj_st * img5 = NULL;
static gt_obj_st * slider1 = NULL;

/** 按下加载到主界面 */
static void action0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_2, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下滑动条向左滑动 */
static void img3_0_cb(gt_event_st * e) {
	gt_obj_st * target = (gt_obj_st * )e->user_data;
	gt_event_send(target, GT_EVENT_TYPE_INPUT_SCROLL_LEFT, NULL);
}

/** 按下滑动条向右滑动 */
static void img4_0_cb(gt_event_st * e) {
	gt_obj_st * target = (gt_obj_st * )e->user_data;
	gt_event_send(target, GT_EVENT_TYPE_INPUT_SCROLL_RIGHT, NULL);
}

gt_obj_st * gt_init_screen_9(void)
{
	screen_9 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_9, gt_color_hex(0x000000));

	

	/** img1 */
	/** 返回图标 */
	img1 = gt_img_create(screen_9);
	gt_obj_set_pos(img1, 1, 6);
	gt_obj_set_size(img1, 84, 58);
	gt_img_set_src(img1, ".:img_84x58_14.png");
	gt_obj_add_event_cb(img1, action0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab5 */
	/** 滑动条文字，宋体24x24 */
	lab5 = gt_label_create(screen_9);
	gt_obj_set_pos(lab5, 93, 24);
	gt_obj_set_size(lab5, 100, 50);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 5);
	gt_label_set_text(lab5, "滑动条");

	

	/** img3 */
	/** 音量减图标 */
	img3 = gt_img_create(screen_9);
	gt_obj_set_pos(img3, 87, 450);
	gt_obj_set_size(img3, 99, 67);
	gt_img_set_src(img3, ".:img_99x67_30.png");

	

	/** img4 */
	/** 音量加图标 */
	img4 = gt_img_create(screen_9);
	gt_obj_set_pos(img4, 805, 448);
	gt_obj_set_size(img4, 99, 67);
	gt_img_set_src(img4, ".:img_99x67_31.png");

	

	/** img5 */
	/** 滑动条背景图 */
	img5 = gt_img_create(screen_9);
	gt_obj_set_pos(img5, 47, 59);
	gt_obj_set_size(img5, 977, 363);
	gt_img_set_src(img5, ".:img_977x363_20.png");

	

	/** slider1 */
	/** 音量滑动条 */
	slider1 = gt_slider_create(screen_9);
	gt_obj_set_pos(slider1, 246, 432);
	gt_obj_set_size(slider1, 500, 100);
	gt_slider_set_start_end(slider1, 0, 100);
	gt_slider_set_pos(slider1, 50);
	gt_slider_set_color_act(slider1, gt_color_hex(0x409eff));
	gt_slider_set_color_ina(slider1, gt_color_hex(0xebeef5));
	gt_slider_set_tag_visible(slider1, 1);
	gt_slider_set_dir(slider1, GT_BAR_DIR_HOR_L2R);

	gt_obj_add_event_cb(img3, img3_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, slider1);
	gt_obj_add_event_cb(img4, img4_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, slider1);
	return screen_9;
}

