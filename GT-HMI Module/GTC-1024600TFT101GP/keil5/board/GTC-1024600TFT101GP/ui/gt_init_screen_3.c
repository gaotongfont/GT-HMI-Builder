#include "gt_ui.h"


/** screen_3 */
gt_obj_st * screen_3 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab1 = NULL;

/** 按下加载到主界面 */
static void action0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_3(void)
{
	screen_3 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_3, gt_color_hex(0x0e053d));

	

	/** img2 */
	/** 图片背景界面 */
	img2 = gt_img_create(screen_3);
	gt_obj_set_pos(img2, 0, 0);
	gt_obj_set_size(img2, 1024, 600);
	gt_img_set_src(img2, "f:img_1024x600_12.png");

	

	/** img1 */
	/** 返回图标 */
	img1 = gt_img_create(screen_3);
	gt_obj_set_pos(img1, 1, 6);
	gt_obj_set_size(img1, 84, 58);
	gt_img_set_src(img1, "f:img_84x58_14.png");
	gt_obj_add_event_cb(img1, action0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab1 */
	/** 图片文字，宋体24x24 */
	lab1 = gt_label_create(screen_3);
	gt_obj_set_pos(lab1, 93, 24);
	gt_obj_set_size(lab1, 60, 40);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 5);
	gt_label_set_text(lab1, "图片");


	return screen_3;
}

