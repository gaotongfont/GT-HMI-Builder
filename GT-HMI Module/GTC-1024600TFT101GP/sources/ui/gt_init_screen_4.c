#include "gt_ui.h"


/** screen_4 */
gt_obj_st * screen_4 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * btn2 = NULL;

/** 按下加载到主界面 */
static void action0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下背景颜色改变 */
static void action9_cb(gt_event_st * e) {
	gt_btn_set_color_background(btn1, gt_color_hex(0x0080ff));
}

/** 按下背景颜色改变 */
static void action1_cb(gt_event_st * e) {
	gt_btn_set_color_background(btn2, gt_color_hex(0x0080ff));
}

gt_obj_st * gt_init_screen_4(void)
{
	screen_4 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_4, gt_color_hex(0x090329));

	

	/** img1 */
	/** 返回图标 */
	img1 = gt_img_create(screen_4);
	gt_obj_set_pos(img1, 1, 6);
	gt_obj_set_size(img1, 84, 58);
	gt_img_set_src(img1, ".:img_84x58_14.png");
	gt_obj_add_event_cb(img1, action0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab1 */
	/** 按钮文字，宋体24x24 */
	lab1 = gt_label_create(screen_4);
	gt_obj_set_pos(lab1, 93, 24);
	gt_obj_set_size(lab1, 60, 40);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 5);
	gt_label_set_text(lab1, "按钮");

	

	/** img2 */
	/** 头像图标 */
	img2 = gt_img_create(screen_4);
	gt_obj_set_pos(img2, 390, 59);
	gt_obj_set_size(img2, 269, 269);
	gt_img_set_src(img2, ".:img_269x269_Group_2.png");

	

	/** img3 */
	/** 文字图标 */
	img3 = gt_img_create(screen_4);
	gt_obj_set_pos(img3, 440, 365);
	gt_obj_set_size(img3, 171, 37);
	gt_img_set_src(img3, ".:img_171x37_40.png");

	

	/** btn1 */
	/** 挂断按钮 */
	btn1 = gt_btn_create(screen_4);
	gt_obj_set_pos(btn1, 233, 448);
	gt_obj_set_size(btn1, 200, 60);
	gt_btn_set_font_color(btn1, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn1, 24);
	gt_btn_set_font_family_cn(btn1, 5);
	gt_btn_set_text(btn1, "挂断");
	gt_btn_set_color_background(btn1, gt_color_hex(0xff0080));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn1, gt_color_hex(0x000000));
	gt_btn_set_radius(btn1, 40);
	gt_obj_add_event_cb(btn1, action9_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** btn2 */
	/** 接听按钮 */
	btn2 = gt_btn_create(screen_4);
	gt_obj_set_pos(btn2, 605, 448);
	gt_obj_set_size(btn2, 200, 60);
	gt_btn_set_font_color(btn2, gt_color_hex(0xffffff));
	gt_btn_set_font_size(btn2, 24);
	gt_btn_set_font_family_cn(btn2, 5);
	gt_btn_set_text(btn2, "接听");
	gt_btn_set_color_background(btn2, gt_color_hex(0x8000ff));
	gt_btn_set_color_pressed(btn2, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn2, gt_color_hex(0x000000));
	gt_btn_set_radius(btn2, 40);
	gt_obj_add_event_cb(btn2, action1_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	return screen_4;
}

