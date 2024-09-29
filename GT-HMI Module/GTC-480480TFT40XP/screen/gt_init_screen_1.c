#include "gt_ui.h"


/** screen_1 */
gt_obj_st * screen_1 = NULL;
static gt_obj_st * img6 = NULL;
static gt_obj_st * img7 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * slider1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * img8 = NULL;
static gt_obj_st * img9 = NULL;
static gt_obj_st * img10 = NULL;
static gt_obj_st * img11 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab7 = NULL;

/** 按下加载主界面 */
static void img2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 滑动后温度显示获取对应的进度数值 */
static void slider1_0_cb(gt_event_st * e) {
	uint16_t value = (uint16_t)gt_slider_get_pos(slider1);
	gt_label_set_text(lab7, "%d", value);

}

/** 按下加载制热界面 */
static void img4_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_2, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载送风界面 */
static void img10_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_6, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载除湿界面 */
static void img11_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_7, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_1(void)
{
	screen_1 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_1, gt_color_hex(0xFFFFFF));

	

	/** img6 */
	/** 制冷背景图 */
	img6 = gt_img_create(screen_1);
	gt_obj_set_pos(img6, 0, 0);
	gt_obj_set_size(img6, 480, 480);
	gt_img_set_src(img6, "f:img_480x480_566.png");

	

	/** img7 */
	/** 返回图标 */
	img7 = gt_img_create(screen_1);
	gt_obj_set_pos(img7, 17, 20);
	gt_obj_set_size(img7, 15, 26);
	gt_img_set_src(img7, "f:img_15x26_187.png");
	gt_obj_add_event_cb(img7, img2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab3 */
	/** 空调文字，矢量24号，4bit */
	lab3 = gt_label_create(screen_1);
	gt_obj_set_pos(lab3, 52, 19);
	gt_obj_set_size(lab3, 60, 32);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 80);
	gt_label_set_font_family_en(lab3, 84);
	gt_label_set_font_gray(lab3, 4);
	gt_label_set_text(lab3, "空调");

	

	/** slider1 */
	/** 温度调整滑动条 */
	slider1 = gt_slider_create(screen_1);
	gt_obj_set_pos(slider1, 91, 118);
	gt_obj_set_size(slider1, 50, 170);
	gt_slider_set_start_end(slider1, 16, 30);
	gt_slider_set_pos(slider1, 26);
	gt_slider_set_color_act(slider1, gt_color_hex(0x0ac6f6));
	gt_slider_set_color_ina(slider1, gt_color_hex(0x232323));
	gt_slider_set_tag_visible(slider1, 1);
	gt_slider_set_dir(slider1, GT_BAR_DIR_VER_D2U);
	gt_obj_add_event_cb(slider1, slider1_0_cb, GT_EVENT_TYPE_INPUT_SCROLL, NULL);
	

	/** rect1 */
	/** 模式背景矩形框 */
	rect1 = gt_rect_create(screen_1);
	gt_obj_set_pos(rect1, 53, 378);
	gt_obj_set_size(rect1, 380, 40);
	gt_rect_set_radius(rect1, 20);
	gt_rect_set_bg_color(rect1, gt_color_hex(0x060606));
	gt_rect_set_color_border(rect1, gt_color_hex(0x060606));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 0);

	

	/** img8 */
	/** 制冷选中图标 */
	img8 = gt_img_create(screen_1);
	gt_obj_set_pos(img8, 85, 365);
	gt_obj_set_size(img8, 60, 60);
	gt_img_set_src(img8, "f:img_60x60_304.png");

	

	/** img9 */
	/** 制热未选中图标 */
	img9 = gt_img_create(screen_1);
	gt_obj_set_pos(img9, 174, 367);
	gt_obj_set_size(img9, 60, 60);
	gt_img_set_src(img9, "f:img_60x60_610.png");
	gt_obj_add_event_cb(img9, img4_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img10 */
	/** 送风未选中图标 */
	img10 = gt_img_create(screen_1);
	gt_obj_set_pos(img10, 261, 365);
	gt_obj_set_size(img10, 60, 60);
	gt_img_set_src(img10, "f:img_60x60_611.png");
	gt_obj_add_event_cb(img10, img10_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img11 */
	/** 除湿未选中图标 */
	img11 = gt_img_create(screen_1);
	gt_obj_set_pos(img11, 343, 365);
	gt_obj_set_size(img11, 60, 60);
	gt_img_set_src(img11, "f:img_60x60_612.png");
	gt_obj_add_event_cb(img11, img11_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** rect2 */
	/** 模式底部矩形框 */
	rect2 = gt_rect_create(screen_1);
	gt_obj_set_pos(rect2, 300, 114);
	gt_obj_set_size(rect2, 80, 36);
	gt_rect_set_radius(rect2, 20);
	gt_rect_set_bg_color(rect2, gt_color_hex(0x00c6f6));
	gt_rect_set_color_border(rect2, gt_color_hex(0x00c6f6));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);

	

	/** lab4 */
	/** 制冷文字，24号，4Bit */
	lab4 = gt_label_create(screen_1);
	gt_obj_set_pos(lab4, 316, 113);
	gt_obj_set_size(lab4, 60, 32);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 80);
	gt_label_set_font_family_en(lab4, 84);
	gt_label_set_font_gray(lab4, 4);
	gt_label_set_text(lab4, "制冷");

	

	/** lab6 */
	/** 当前室内温度文字，矢量16号，4bit */
	lab6 = gt_label_create(screen_1);
	gt_obj_set_pos(lab6, 274, 269);
	gt_obj_set_size(lab6, 160, 24);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 16);
	gt_label_set_font_family_cn(lab6, 80);
	gt_label_set_font_family_en(lab6, 84);
	gt_label_set_font_gray(lab6, 4);
	gt_label_set_text(lab6, "当前室内温度33℃");

	

	/** lab5 */
	/** ℃文字，矢量72号，2bit */
	lab5 = gt_label_create(screen_1);
	gt_obj_set_pos(lab5, 352, 163);
	gt_obj_set_size(lab5, 90, 80);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 72);
	gt_label_set_font_family_cn(lab5, 80);
	gt_label_set_font_family_en(lab5, 84);
	gt_label_set_font_gray(lab5, 2);
	gt_label_set_text(lab5, "℃");

	

	/** lab7 */
	lab7 = gt_label_create(screen_1);
	gt_obj_set_pos(lab7, 244, 161);
	gt_obj_set_size(lab7, 120, 80);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 72);
	gt_label_set_font_family_cn(lab7, 80);
	gt_label_set_font_family_en(lab7, 84);
	gt_label_set_font_gray(lab7, 2);
	gt_label_set_text(lab7, "26");


	return screen_1;
}

