#include "gt_ui.h"


/** screen_7 */
gt_obj_st * screen_7 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * img4 = NULL;
static gt_obj_st * img5 = NULL;
static gt_obj_st * img6 = NULL;
static gt_obj_st * slider1 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;

/** 按下加载主界面 */
static void img2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载制冷界面 */
static void img3_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载制热界面 */
static void img4_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_2, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载送风界面 */
static void img5_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_6, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 滑动后温度显示获取对应的进度数值 */
static void slider1_0_cb(gt_event_st * e) {
	uint16_t value = (uint16_t)gt_slider_get_pos(slider1);
	gt_label_set_text(lab5, "%d", value);

}

gt_obj_st * gt_init_screen_7(void)
{
	screen_7 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_7, gt_color_hex(0xFFFFFF));

	

	/** img1 */
	/** 除湿背景图 */
	img1 = gt_img_create(screen_7);
	gt_obj_set_pos(img1, 0, 0);
	gt_obj_set_size(img1, 480, 480);
	gt_img_set_src(img1, ".:img_480x480_317.png");

	

	/** img2 */
	/** 返回图标 */
	img2 = gt_img_create(screen_7);
	gt_obj_set_pos(img2, 19, 22);
	gt_obj_set_size(img2, 15, 26);
	gt_img_set_src(img2, ".:img_15x26_187.png");
	gt_obj_add_event_cb(img2, img2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab1 */
	/** 空调文字，矢量24号，4bit */
	lab1 = gt_label_create(screen_7);
	gt_obj_set_pos(lab1, 52, 19);
	gt_obj_set_size(lab1, 60, 32);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 80);
	gt_label_set_font_family_en(lab1, 84);
	gt_label_set_font_gray(lab1, 4);
	gt_label_set_text(lab1, "空调");

	

	/** rect1 */
	/** 模式背景矩形框 */
	rect1 = gt_rect_create(screen_7);
	gt_obj_set_pos(rect1, 53, 378);
	gt_obj_set_size(rect1, 380, 40);
	gt_rect_set_radius(rect1, 20);
	gt_rect_set_bg_color(rect1, gt_color_hex(0x060606));
	gt_rect_set_color_border(rect1, gt_color_hex(0x060606));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 0);

	

	/** img3 */
	/** 制冷未选中图标 */
	img3 = gt_img_create(screen_7);
	gt_obj_set_pos(img3, 87, 367);
	gt_obj_set_size(img3, 60, 60);
	gt_img_set_src(img3, ".:img_60x60_609.png");
	gt_obj_add_event_cb(img3, img3_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img4 */
	/** 制热未选中图标 */
	img4 = gt_img_create(screen_7);
	gt_obj_set_pos(img4, 172, 365);
	gt_obj_set_size(img4, 60, 60);
	gt_img_set_src(img4, ".:img_60x60_610.png");
	gt_obj_add_event_cb(img4, img4_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img5 */
	/** 送风未选中图标 */
	img5 = gt_img_create(screen_7);
	gt_obj_set_pos(img5, 263, 367);
	gt_obj_set_size(img5, 60, 60);
	gt_img_set_src(img5, ".:img_60x60_611.png");
	gt_obj_add_event_cb(img5, img5_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img6 */
	/** 除湿选中图标 */
	img6 = gt_img_create(screen_7);
	gt_obj_set_pos(img6, 345, 367);
	gt_obj_set_size(img6, 60, 60);
	gt_img_set_src(img6, ".:img_60x60_312.png");

	

	/** slider1 */
	/** 温度调整滑动条 */
	slider1 = gt_slider_create(screen_7);
	gt_obj_set_pos(slider1, 93, 120);
	gt_obj_set_size(slider1, 50, 170);
	gt_slider_set_start_end(slider1, 16, 30);
	gt_slider_set_pos(slider1, 20);
	gt_slider_set_color_act(slider1, gt_color_hex(0x1bc183));
	gt_slider_set_color_ina(slider1, gt_color_hex(0x232323));
	gt_slider_set_tag_visible(slider1, 1);
	gt_slider_set_dir(slider1, GT_BAR_DIR_VER_D2U);
	gt_obj_add_event_cb(slider1, slider1_0_cb, GT_EVENT_TYPE_INPUT_SCROLL, NULL);
	

	/** rect2 */
	/** 模式底部矩形框 */
	rect2 = gt_rect_create(screen_7);
	gt_obj_set_pos(rect2, 300, 114);
	gt_obj_set_size(rect2, 80, 36);
	gt_rect_set_radius(rect2, 20);
	gt_rect_set_bg_color(rect2, gt_color_hex(0x1bc183));
	gt_rect_set_color_border(rect2, gt_color_hex(0x1bc183));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);

	

	/** lab2 */
	/** 除湿 */
	lab2 = gt_label_create(screen_7);
	gt_obj_set_pos(lab2, 315, 112);
	gt_obj_set_size(lab2, 60, 32);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 80);
	gt_label_set_font_family_en(lab2, 84);
	gt_label_set_font_gray(lab2, 4);
	gt_label_set_text(lab2, "除湿");

	

	/** lab4 */
	/** 当前室内温度文字，矢量16号，4bit */
	lab4 = gt_label_create(screen_7);
	gt_obj_set_pos(lab4, 274, 269);
	gt_obj_set_size(lab4, 160, 24);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 16);
	gt_label_set_font_family_cn(lab4, 80);
	gt_label_set_font_family_en(lab4, 84);
	gt_label_set_font_gray(lab4, 4);
	gt_label_set_text(lab4, "当前室内温度5℃");

	

	/** lab5 */
	lab5 = gt_label_create(screen_7);
	gt_obj_set_pos(lab5, 255, 164);
	gt_obj_set_size(lab5, 120, 80);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 72);
	gt_label_set_font_family_cn(lab5, 80);
	gt_label_set_font_family_en(lab5, 84);
	gt_label_set_font_gray(lab5, 2);
	gt_label_set_text(lab5, "20");

	

	/** lab6 */
	/** ℃文字，矢量72号，2bit */
	lab6 = gt_label_create(screen_7);
	gt_obj_set_pos(lab6, 339, 164);
	gt_obj_set_size(lab6, 100, 80);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 72);
	gt_label_set_font_family_cn(lab6, 80);
	gt_label_set_font_family_en(lab6, 84);
	gt_label_set_font_gray(lab6, 2);
	gt_label_set_text(lab6, "℃");


	return screen_7;
}

