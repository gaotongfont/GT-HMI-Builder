#include "gt_ui.h"


/** screen_home */
gt_obj_st * screen_home = NULL;
static gt_obj_st * img1 = NULL;

/** 按下加载到主界面 */
static void action0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_home(void)
{
	screen_home = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_home, gt_color_hex(0xFFFFFF));

	

	/** img1 */
	/** 启动界面背景 */
	img1 = gt_img_create(screen_home);
	gt_obj_set_pos(img1, 0, 0);
	gt_obj_set_size(img1, 1024, 600);
	gt_img_set_src(img1, "f:img_1024x600_10kk.png");
	gt_obj_add_event_cb(img1, action0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	return screen_home;
}

