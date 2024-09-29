#include "gt_ui.h"


/** screen_6 */
gt_obj_st * screen_6 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * imgbtn3 = NULL;

/** 按下加载到主界面 */
static void action0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_6(void)
{
	screen_6 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_6, gt_color_hex(0x090329));

	

	/** img1 */
	/** 返回图标 */
	img1 = gt_img_create(screen_6);
	gt_obj_set_pos(img1, 1, 6);
	gt_obj_set_size(img1, 84, 58);
	gt_img_set_src(img1, ".:img_84x58_14.png");
	gt_obj_add_event_cb(img1, action0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab5 */
	/** 图片按钮文字，宋体24x24 */
	lab5 = gt_label_create(screen_6);
	gt_obj_set_pos(lab5, 93, 24);
	gt_obj_set_size(lab5, 120, 40);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 5);
	gt_label_set_text(lab5, "图片按钮");

	

	/** imgbtn3 */
	/** 图片按钮，可设置按下后不同的图片效果 */
	imgbtn3 = gt_imgbtn_create(screen_6);
	gt_obj_set_pos(imgbtn3, 355, 188);
	gt_obj_set_size(imgbtn3, 320, 200);
	gt_imgbtn_set_src(imgbtn3, ".:img_320x200_img33.png");
	gt_imgbtn_set_src_press(imgbtn3, ".:img_320x200_img32.png");


	return screen_6;
}

