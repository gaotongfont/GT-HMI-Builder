#include "gt_ui.h"


/** screen_5 */
gt_obj_st * screen_5 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * img4 = NULL;
static gt_obj_st * img5 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;

/** 按下加载到主界面 */
static void action0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void action1_cb(gt_event_st * e) {
	gt_label_set_font_color(lab2, gt_color_hex(0x00ffff));
}

static void action2_cb(gt_event_st * e) {
	gt_label_set_font_color(lab1, gt_color_hex(0x00ffff));
}

static void action3_cb(gt_event_st * e) {
	gt_label_set_font_color(lab3, gt_color_hex(0x00ffff));
}

static void action4_cb(gt_event_st * e) {
	gt_label_set_font_color(lab4, gt_color_hex(0x00ffff));
}

gt_obj_st * gt_init_screen_5(void)
{
	screen_5 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_5, gt_color_hex(0x090329));

	

	/** img1 */
	/** 返回图标 */
	img1 = gt_img_create(screen_5);
	gt_obj_set_pos(img1, 1, 6);
	gt_obj_set_size(img1, 84, 58);
	gt_img_set_src(img1, ".:img_84x58_14.png");
	gt_obj_add_event_cb(img1, action0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab5 */
	/** 标签文字，宋体24x24 */
	lab5 = gt_label_create(screen_5);
	gt_obj_set_pos(lab5, 93, 24);
	gt_obj_set_size(lab5, 80, 40);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 5);
	gt_label_set_text(lab5, "标签");

	

	/** img2 */
	/** 蓝牙设置图标 */
	img2 = gt_img_create(screen_5);
	gt_obj_set_pos(img2, 83, 111);
	gt_obj_set_size(img2, 869, 76);
	gt_img_set_src(img2, ".:img_869x76_21.png");

	

	/** img3 */
	/** 音量设置图标 */
	img3 = gt_img_create(screen_5);
	gt_obj_set_pos(img3, 81, 214);
	gt_obj_set_size(img3, 869, 77);
	gt_img_set_src(img3, ".:img_869x77_22.png");

	

	/** img4 */
	/** 亮度设置图标 */
	img4 = gt_img_create(screen_5);
	gt_obj_set_pos(img4, 81, 320);
	gt_obj_set_size(img4, 869, 77);
	gt_img_set_src(img4, ".:img_869x77_23.png");

	

	/** img5 */
	/** 系统设置图标 */
	img5 = gt_img_create(screen_5);
	gt_obj_set_pos(img5, 82, 427);
	gt_obj_set_size(img5, 869, 76);
	gt_img_set_src(img5, ".:img_869x76_24.png");

	

	/** lab2 */
	/** 蓝牙设置文字，宋体24x24 */
	lab2 = gt_label_create(screen_5);
	gt_obj_set_pos(lab2, 178, 128);
	gt_obj_set_size(lab2, 120, 40);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 5);
	gt_label_set_text(lab2, "蓝牙设置");
	gt_obj_add_event_cb(lab2, action1_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab1 */
	/** 音量设置文字，宋体24x24 */
	lab1 = gt_label_create(screen_5);
	gt_obj_set_pos(lab1, 180, 234);
	gt_obj_set_size(lab1, 120, 40);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 5);
	gt_label_set_text(lab1, "音量设置");
	gt_obj_add_event_cb(lab1, action2_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab3 */
	/** 亮度设置文字，宋体24x24 */
	lab3 = gt_label_create(screen_5);
	gt_obj_set_pos(lab3, 181, 339);
	gt_obj_set_size(lab3, 120, 40);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 5);
	gt_label_set_text(lab3, "亮度设置");
	gt_obj_add_event_cb(lab3, action3_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab4 */
	/** 系统设置文字，宋体24x24 */
	lab4 = gt_label_create(screen_5);
	gt_obj_set_pos(lab4, 182, 449);
	gt_obj_set_size(lab4, 120, 40);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 5);
	gt_label_set_text(lab4, "系统设置");
	gt_obj_add_event_cb(lab4, action4_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	return screen_5;
}

