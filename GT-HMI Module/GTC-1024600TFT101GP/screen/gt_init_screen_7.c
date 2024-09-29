#include "gt_ui.h"


/** screen_7 */
gt_obj_st * screen_7 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * switch1 = NULL;
static gt_obj_st * switch2 = NULL;
static gt_obj_st * switch3 = NULL;

/** 按下加载到主界面 */
static void action0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_7(void)
{
	screen_7 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_7, gt_color_hex(0x000000));

	

	/** img1 */
	/** 返回图标 */
	img1 = gt_img_create(screen_7);
	gt_obj_set_pos(img1, 1, 6);
	gt_obj_set_size(img1, 84, 58);
	gt_img_set_src(img1, "f:img_84x58_14.png");
	gt_obj_add_event_cb(img1, action0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab5 */
	/** 开关文字，宋体24x24 */
	lab5 = gt_label_create(screen_7);
	gt_obj_set_pos(lab5, 93, 24);
	gt_obj_set_size(lab5, 100, 40);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 5);
	gt_label_set_text(lab5, "开关");

	

	/** img2 */
	/** 开关背景图标 */
	img2 = gt_img_create(screen_7);
	gt_obj_set_pos(img2, 71, 131);
	gt_obj_set_size(img2, 890, 324);
	gt_img_set_src(img2, "f:img_890x324_17.png");

	

	/** switch1 */
	/** 飞行模式开关 */
	switch1 = gt_switch_create(screen_7);
	gt_obj_set_pos(switch1, 806, 146);
	gt_obj_set_size(switch1, 130, 52);
	gt_switch_set_color_act(switch1, gt_color_hex(0x0080ff));
	gt_switch_set_color_ina(switch1, gt_color_hex(0x00ffff));
	gt_switch_set_color_point(switch1, gt_color_hex(0xFFFFFF));
	gt_obj_set_state(switch1, 1);

	

	/** switch2 */
	/** wifi开关 */
	switch2 = gt_switch_create(screen_7);
	gt_obj_set_pos(switch2, 806, 267);
	gt_obj_set_size(switch2, 130, 52);
	gt_switch_set_color_act(switch2, gt_color_hex(0x0080ff));
	gt_switch_set_color_ina(switch2, gt_color_hex(0x00ffff));
	gt_switch_set_color_point(switch2, gt_color_hex(0xFFFFFF));
	gt_obj_set_state(switch2, 1);

	

	/** switch3 */
	/** 蓝牙开关 */
	switch3 = gt_switch_create(screen_7);
	gt_obj_set_pos(switch3, 805, 382);
	gt_obj_set_size(switch3, 130, 52);
	gt_switch_set_color_act(switch3, gt_color_hex(0x0080ff));
	gt_switch_set_color_ina(switch3, gt_color_hex(0x00ffff));
	gt_switch_set_color_point(switch3, gt_color_hex(0xFFFFFF));
	gt_obj_set_state(switch3, 1);


	return screen_7;
}

