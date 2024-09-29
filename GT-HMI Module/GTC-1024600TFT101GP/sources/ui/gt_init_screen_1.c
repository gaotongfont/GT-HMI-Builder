#include "gt_ui.h"


/** screen_1 */
gt_obj_st * screen_1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * img4 = NULL;
static gt_obj_st * img5 = NULL;
static gt_obj_st * img6 = NULL;
static gt_obj_st * img7 = NULL;

/** 按下加载到图片界面 */
static void action0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_3, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到按钮界面 */
static void action1_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_4, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到标签界面 */
static void action2_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_5, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void action6_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_2, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到图片按钮界面 */
static void action3_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_6, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到开关界面 */
static void action4_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_7, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载到复选框界面 */
static void action5_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_8, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_1(void)
{
	screen_1 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_1, gt_color_hex(0x090329));

	

	/** img1 */
	/** 图片图标 */
	img1 = gt_img_create(screen_1);
	gt_obj_set_pos(img1, 148, 54);
	gt_obj_set_size(img1, 184, 208);
	gt_img_set_src(img1, ".:img_184x208_1.png");
	gt_obj_add_event_cb(img1, action0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img2 */
	/** 按钮图标 */
	img2 = gt_img_create(screen_1);
	gt_obj_set_pos(img2, 423, 54);
	gt_obj_set_size(img2, 184, 208);
	gt_img_set_src(img2, ".:img_184x208_2.png");
	gt_obj_add_event_cb(img2, action1_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img3 */
	/** 标签图标 */
	img3 = gt_img_create(screen_1);
	gt_obj_set_pos(img3, 694, 54);
	gt_obj_set_size(img3, 184, 208);
	gt_img_set_src(img3, ".:img_184x208_3.png");
	gt_obj_add_event_cb(img3, action2_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img4 */
	img4 = gt_img_create(screen_1);
	gt_obj_set_pos(img4, 944, 262);
	gt_obj_set_size(img4, 44, 63);
	gt_img_set_src(img4, ".:img_44x63_10.png");
	gt_obj_add_event_cb(img4, action6_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img5 */
	/** 图片按钮图标 */
	img5 = gt_img_create(screen_1);
	gt_obj_set_pos(img5, 148, 334);
	gt_obj_set_size(img5, 184, 208);
	gt_img_set_src(img5, ".:img_184x208_4.png");
	gt_obj_add_event_cb(img5, action3_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img6 */
	/** 开关图标 */
	img6 = gt_img_create(screen_1);
	gt_obj_set_pos(img6, 423, 334);
	gt_obj_set_size(img6, 184, 208);
	gt_img_set_src(img6, ".:img_184x208_5.png");
	gt_obj_add_event_cb(img6, action4_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img7 */
	/** 复选框图标 */
	img7 = gt_img_create(screen_1);
	gt_obj_set_pos(img7, 694, 334);
	gt_obj_set_size(img7, 184, 208);
	gt_img_set_src(img7, ".:img_184x208_6.png");
	gt_obj_add_event_cb(img7, action5_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	return screen_1;
}

