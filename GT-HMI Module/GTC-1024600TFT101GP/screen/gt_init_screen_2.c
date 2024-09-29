#include "gt_ui.h"


/** screen_2 */
gt_obj_st * screen_2 = NULL;
static gt_obj_st * img8 = NULL;
static gt_obj_st * img9 = NULL;
static gt_obj_st * img10 = NULL;
static gt_obj_st * img4 = NULL;

/** 按下加载到滑动条界面 */
static void action1_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_9, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到矩形界面 */
static void action2_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_10, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到单选框、成组界面 */
static void action3_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_11, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void action0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_2(void)
{
	screen_2 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_2, gt_color_hex(0x090329));

	

	/** img8 */
	/** 滑动条图标 */
	img8 = gt_img_create(screen_2);
	gt_obj_set_pos(img8, 148, 54);
	gt_obj_set_size(img8, 184, 208);
	gt_img_set_src(img8, "f:img_184x208_7.png");
	gt_obj_add_event_cb(img8, action1_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img9 */
	/** 矩形图标 */
	img9 = gt_img_create(screen_2);
	gt_obj_set_pos(img9, 423, 54);
	gt_obj_set_size(img9, 184, 208);
	gt_img_set_src(img9, "f:img_184x208_8.png");
	gt_obj_add_event_cb(img9, action2_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img10 */
	/** 单选框图标 */
	img10 = gt_img_create(screen_2);
	gt_obj_set_pos(img10, 694, 54);
	gt_obj_set_size(img10, 184, 208);
	gt_img_set_src(img10, "f:img_184x208_9.png");
	gt_obj_add_event_cb(img10, action3_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img4 */
	img4 = gt_img_create(screen_2);
	gt_obj_set_pos(img4, 44, 262);
	gt_obj_set_size(img4, 44, 63);
	gt_img_set_src(img4, "f:img_44x63_11.png");
	gt_obj_add_event_cb(img4, action0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	return screen_2;
}

