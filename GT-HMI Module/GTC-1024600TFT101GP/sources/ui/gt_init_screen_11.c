#include "gt_ui.h"


/** screen_11 */
gt_obj_st * screen_11 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * group1 = NULL;
static gt_obj_st * radio4 = NULL;
static gt_obj_st * radio3 = NULL;
static gt_obj_st * radio2 = NULL;
static gt_obj_st * radio1 = NULL;

/** 按下加载到主界面 */
static void action0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_2, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_11(void)
{
	screen_11 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_11, gt_color_hex(0x000000));

	

	/** img1 */
	/** 返回图标 */
	img1 = gt_img_create(screen_11);
	gt_obj_set_pos(img1, 1, 6);
	gt_obj_set_size(img1, 84, 58);
	gt_img_set_src(img1, ".:img_84x58_14.png");
	gt_obj_add_event_cb(img1, action0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab5 */
	/** 单选框、成组文字，宋体24x24 */
	lab5 = gt_label_create(screen_11);
	gt_obj_set_pos(lab5, 93, 24);
	gt_obj_set_size(lab5, 170, 50);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 5);
	gt_label_set_text(lab5, "单选框、成组");

	

	/** img2 */
	/** 单选框、成组图标 */
	img2 = gt_img_create(screen_11);
	gt_obj_set_pos(img2, 192, 103);
	gt_obj_set_size(img2, 604, 272);
	gt_img_set_src(img2, ".:img_604x272_19.png");

	

	/** group1 */
	group1 = gt_group_create(screen_11);
	gt_obj_set_pos(group1, 158, 286);
	gt_obj_set_size(group1, 3, 2);

	

	/** radio4 */
	/** 文字特大，宋体24x24 */
	radio4 = gt_radio_create(group1);
	gt_obj_set_pos(radio4, 747, 456);
	gt_obj_set_size(radio4, 100, 50);
	gt_radio_set_font_color(radio4, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio4, 24);
	gt_radio_set_font_family_cn(radio4, 5);
	gt_radio_set_text(radio4, "特大");
	gt_radio_set_font_point_offset(radio4, 0, 0);

	

	/** radio3 */
	/** 文字大，宋体24x24 */
	radio3 = gt_radio_create(group1);
	gt_obj_set_pos(radio3, 555, 458);
	gt_obj_set_size(radio3, 60, 50);
	gt_radio_set_font_color(radio3, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio3, 24);
	gt_radio_set_font_family_cn(radio3, 5);
	gt_radio_set_text(radio3, "大");
	gt_radio_set_font_point_offset(radio3, 0, 0);

	

	/** radio2 */
	/** 文字标准，宋体24x24 */
	radio2 = gt_radio_create(group1);
	gt_obj_set_pos(radio2, 343, 456);
	gt_obj_set_size(radio2, 100, 50);
	gt_radio_set_font_color(radio2, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio2, 24);
	gt_radio_set_font_family_cn(radio2, 5);
	gt_radio_set_text(radio2, "标准");
	gt_radio_set_font_point_offset(radio2, 0, 0);

	

	/** radio1 */
	/** 文字小，宋体24x24 */
	radio1 = gt_radio_create(group1);
	gt_obj_set_pos(radio1, 164, 458);
	gt_obj_set_size(radio1, 60, 50);
	gt_radio_set_font_color(radio1, gt_color_hex(0xffffff));
	gt_radio_set_font_size(radio1, 24);
	gt_radio_set_font_family_cn(radio1, 5);
	gt_radio_set_text(radio1, "小");
	gt_radio_set_selected(radio1);
	gt_radio_set_font_point_offset(radio1, 0, 0);


	return screen_11;
}

