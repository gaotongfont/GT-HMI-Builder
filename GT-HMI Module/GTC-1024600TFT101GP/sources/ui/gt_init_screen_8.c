#include "gt_ui.h"


/** screen_8 */
gt_obj_st * screen_8 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * cbox3 = NULL;
static gt_obj_st * cbox4 = NULL;
static gt_obj_st * cbox5 = NULL;
static gt_obj_st * cbox1 = NULL;
static gt_obj_st * cbox2 = NULL;

/** 按下加载到主界面 */
static void action0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_8(void)
{
	screen_8 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_8, gt_color_hex(0x000000));

	

	/** img1 */
	/** 返回图标 */
	img1 = gt_img_create(screen_8);
	gt_obj_set_pos(img1, 1, 5);
	gt_obj_set_size(img1, 84, 58);
	gt_img_set_src(img1, ".:img_84x58_14.png");
	gt_obj_add_event_cb(img1, action0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab5 */
	/** 复选框文字，宋体24x24 */
	lab5 = gt_label_create(screen_8);
	gt_obj_set_pos(lab5, 93, 24);
	gt_obj_set_size(lab5, 100, 40);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 5);
	gt_label_set_text(lab5, "复选框");

	

	/** img2 */
	/** 时钟图标 */
	img2 = gt_img_create(screen_8);
	gt_obj_set_pos(img2, 114, 188);
	gt_obj_set_size(img2, 408, 261);
	gt_img_set_src(img2, ".:img_408x261_18.png");

	

	/** cbox3 */
	/** 星期三文字，宋体24x24 */
	cbox3 = gt_checkbox_create(screen_8);
	gt_obj_set_pos(cbox3, 710, 280);
	gt_obj_set_size(cbox3, 120, 50);
	gt_checkbox_set_font_color(cbox3, gt_color_hex(0xffffff));
	gt_checkbox_set_font_size(cbox3, 24);
	gt_checkbox_set_font_family_cn(cbox3, 5);
	gt_checkbox_set_text(cbox3, "星期三");
	gt_obj_set_state(cbox3, 0);
	gt_checkbox_set_font_point_offset(cbox3, 0, 0);

	

	/** cbox4 */
	/** 星期四文字，宋体24x24 */
	cbox4 = gt_checkbox_create(screen_8);
	gt_obj_set_pos(cbox4, 710, 360);
	gt_obj_set_size(cbox4, 120, 50);
	gt_checkbox_set_font_color(cbox4, gt_color_hex(0xffffff));
	gt_checkbox_set_font_size(cbox4, 24);
	gt_checkbox_set_font_family_cn(cbox4, 5);
	gt_checkbox_set_text(cbox4, "星期四");
	gt_obj_set_state(cbox4, 0);
	gt_checkbox_set_font_point_offset(cbox4, 0, 0);

	

	/** cbox5 */
	/** 星期五文字，宋体24x24 */
	cbox5 = gt_checkbox_create(screen_8);
	gt_obj_set_pos(cbox5, 710, 440);
	gt_obj_set_size(cbox5, 120, 50);
	gt_checkbox_set_font_color(cbox5, gt_color_hex(0xffffff));
	gt_checkbox_set_font_size(cbox5, 24);
	gt_checkbox_set_font_family_cn(cbox5, 5);
	gt_checkbox_set_text(cbox5, "星期五");
	gt_obj_set_state(cbox5, 0);
	gt_checkbox_set_font_point_offset(cbox5, 0, 0);

	

	/** cbox1 */
	/** 星期一文字，宋体24x24 */
	cbox1 = gt_checkbox_create(screen_8);
	gt_obj_set_pos(cbox1, 710, 120);
	gt_obj_set_size(cbox1, 120, 50);
	gt_checkbox_set_font_color(cbox1, gt_color_hex(0xffffff));
	gt_checkbox_set_font_size(cbox1, 24);
	gt_checkbox_set_font_family_cn(cbox1, 5);
	gt_checkbox_set_text(cbox1, "星期一");
	gt_obj_set_state(cbox1, 0);
	gt_checkbox_set_font_point_offset(cbox1, 0, 0);

	

	/** cbox2 */
	/** 星期二文字，宋体24x24 */
	cbox2 = gt_checkbox_create(screen_8);
	gt_obj_set_pos(cbox2, 710, 200);
	gt_obj_set_size(cbox2, 120, 50);
	gt_checkbox_set_font_color(cbox2, gt_color_hex(0xffffff));
	gt_checkbox_set_font_size(cbox2, 24);
	gt_checkbox_set_font_family_cn(cbox2, 5);
	gt_checkbox_set_text(cbox2, "星期二");
	gt_obj_set_state(cbox2, 0);
	gt_checkbox_set_font_point_offset(cbox2, 0, 0);


	return screen_8;
}

