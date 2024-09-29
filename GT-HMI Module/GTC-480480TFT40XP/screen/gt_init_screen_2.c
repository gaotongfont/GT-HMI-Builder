#include "gt_ui.h"


/** screen_2 */
gt_obj_st * screen_2 = NULL;
static gt_obj_st * img12 = NULL;
static gt_obj_st * img13 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * img14 = NULL;
static gt_obj_st * img15 = NULL;
static gt_obj_st * img16 = NULL;
static gt_obj_st * img17 = NULL;
static gt_obj_st * slider2 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab6 = NULL;

/** 按下加载主界面 */
static void img2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载制冷界面 */
static void img3_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载送风界面 */
static void img16_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_6, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载除湿界面 */
static void img17_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_7, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 滑动后温度显示获取对应的进度数值 */
static void slider2_0_cb(gt_event_st * e) {
	uint16_t value = (uint16_t)gt_slider_get_pos(slider2);
	gt_label_set_text(lab6, "%d", value);

}

gt_obj_st * gt_init_screen_2(void)
{
	screen_2 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_2, gt_color_hex(0xFFFFFF));

	

	/** img12 */
	/** 制热背景图 */
	img12 = gt_img_create(screen_2);
	gt_obj_set_pos(img12, 0, 0);
	gt_obj_set_size(img12, 480, 480);
	gt_img_set_src(img12, "f:img_480x480_567.png");

	

	/** img13 */
	/** 返回图标 */
	img13 = gt_img_create(screen_2);
	gt_obj_set_pos(img13, 19, 22);
	gt_obj_set_size(img13, 15, 26);
	gt_img_set_src(img13, "f:img_15x26_187.png");
	gt_obj_add_event_cb(img13, img2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab7 */
	/** 空调文字，矢量24号，4bit */
	lab7 = gt_label_create(screen_2);
	gt_obj_set_pos(lab7, 52, 19);
	gt_obj_set_size(lab7, 60, 32);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_cn(lab7, 80);
	gt_label_set_font_family_en(lab7, 84);
	gt_label_set_font_gray(lab7, 4);
	gt_label_set_text(lab7, "空调");

	

	/** rect3 */
	/** 模式背景矩形框 */
	rect3 = gt_rect_create(screen_2);
	gt_obj_set_pos(rect3, 53, 378);
	gt_obj_set_size(rect3, 380, 40);
	gt_rect_set_radius(rect3, 20);
	gt_rect_set_bg_color(rect3, gt_color_hex(0x060606));
	gt_rect_set_color_border(rect3, gt_color_hex(0x060606));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 0);

	

	/** img14 */
	/** 制冷未选中图标 */
	img14 = gt_img_create(screen_2);
	gt_obj_set_pos(img14, 87, 367);
	gt_obj_set_size(img14, 60, 60);
	gt_img_set_src(img14, "f:img_60x60_609.png");
	gt_obj_add_event_cb(img14, img3_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img15 */
	/** 制热选中图标 */
	img15 = gt_img_create(screen_2);
	gt_obj_set_pos(img15, 174, 367);
	gt_obj_set_size(img15, 60, 60);
	gt_img_set_src(img15, "f:img_60x60_310.png");

	

	/** img16 */
	/** 送风未选中图标 */
	img16 = gt_img_create(screen_2);
	gt_obj_set_pos(img16, 263, 367);
	gt_obj_set_size(img16, 60, 60);
	gt_img_set_src(img16, "f:img_60x60_611.png");
	gt_obj_add_event_cb(img16, img16_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img17 */
	/** 除湿未选中图标 */
	img17 = gt_img_create(screen_2);
	gt_obj_set_pos(img17, 343, 365);
	gt_obj_set_size(img17, 60, 60);
	gt_img_set_src(img17, "f:img_60x60_612.png");
	gt_obj_add_event_cb(img17, img17_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** slider2 */
	/** 温度调整滑动条 */
	slider2 = gt_slider_create(screen_2);
	gt_obj_set_pos(slider2, 94, 120);
	gt_obj_set_size(slider2, 50, 170);
	gt_slider_set_start_end(slider2, 16, 30);
	gt_slider_set_pos(slider2, 18);
	gt_slider_set_color_act(slider2, gt_color_hex(0xf8a809));
	gt_slider_set_color_ina(slider2, gt_color_hex(0x232323));
	gt_slider_set_tag_visible(slider2, 1);
	gt_slider_set_dir(slider2, GT_BAR_DIR_VER_D2U);
	gt_obj_add_event_cb(slider2, slider2_0_cb, GT_EVENT_TYPE_INPUT_SCROLL, NULL);
	

	/** rect4 */
	/** 模式底部矩形框 */
	rect4 = gt_rect_create(screen_2);
	gt_obj_set_pos(rect4, 300, 114);
	gt_obj_set_size(rect4, 80, 36);
	gt_rect_set_radius(rect4, 20);
	gt_rect_set_bg_color(rect4, gt_color_hex(0xf8a809));
	gt_rect_set_color_border(rect4, gt_color_hex(0xf8a809));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);

	

	/** lab8 */
	/** 制热文字，24号，4Bit */
	lab8 = gt_label_create(screen_2);
	gt_obj_set_pos(lab8, 317, 113);
	gt_obj_set_size(lab8, 60, 32);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 24);
	gt_label_set_font_family_cn(lab8, 80);
	gt_label_set_font_family_en(lab8, 84);
	gt_label_set_font_gray(lab8, 4);
	gt_label_set_text(lab8, "制热");

	

	/** lab10 */
	/** 当前室内温度文字，矢量16号，4bit */
	lab10 = gt_label_create(screen_2);
	gt_obj_set_pos(lab10, 274, 269);
	gt_obj_set_size(lab10, 160, 24);
	gt_label_set_font_color(lab10, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab10, 16);
	gt_label_set_font_family_cn(lab10, 80);
	gt_label_set_font_family_en(lab10, 84);
	gt_label_set_font_gray(lab10, 4);
	gt_label_set_text(lab10, "当前室内温度5℃");

	

	/** lab4 */
	/** ℃文字，矢量72号，2bit */
	lab4 = gt_label_create(screen_2);
	gt_obj_set_pos(lab4, 352, 163);
	gt_obj_set_size(lab4, 100, 80);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 72);
	gt_label_set_font_family_cn(lab4, 80);
	gt_label_set_font_family_en(lab4, 84);
	gt_label_set_font_gray(lab4, 2);
	gt_label_set_text(lab4, "℃");

	

	/** lab6 */
	lab6 = gt_label_create(screen_2);
	gt_obj_set_pos(lab6, 245, 163);
	gt_obj_set_size(lab6, 120, 80);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 72);
	gt_label_set_font_family_cn(lab6, 80);
	gt_label_set_font_family_en(lab6, 84);
	gt_label_set_font_gray(lab6, 2);
	gt_label_set_text(lab6, "18");


	return screen_2;
}

