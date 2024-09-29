#include "gt_ui.h"


/** screen_home */
gt_obj_st * screen_home = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * rect2 = NULL;
static gt_obj_st * rect3 = NULL;
static gt_obj_st * rect4 = NULL;
static gt_obj_st * rect5 = NULL;
static gt_obj_st * rect6 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * lab10 = NULL;
static gt_obj_st * lab12 = NULL;
static gt_obj_st * lab13 = NULL;
static gt_obj_st * lab15 = NULL;
static gt_obj_st * inputNum1 = NULL;
static gt_obj_st * lab14 = NULL;
static gt_obj_st * rect7 = NULL;
static gt_obj_st * lab13_copy = NULL;
static gt_obj_st * rect7_copy = NULL;
static gt_obj_st * lab14_copy = NULL;
static gt_obj_st * rect9 = NULL;
static gt_obj_st * rect9_copy = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * img3 = NULL;

static void rect9_0_cb(gt_event_st * e) {
	gt_input_number_increase(inputNum1);
}

static void rect9_copy_0_cb(gt_event_st * e) {
	gt_input_number_decrease(inputNum1);
}

/** 按下温度递减 */
static void img2_0_cb(gt_event_st * e) {
	gt_input_number_decrease(inputNum1);
}

/** 按下温度递增 */
static void img3_0_cb(gt_event_st * e) {
	gt_input_number_increase(inputNum1);
}

gt_obj_st * gt_init_screen_home(void)
{
	screen_home = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_home, gt_color_hex(0x1b2234));

	

	/** img1 */
	/** banner背景 */
	img1 = gt_img_create(screen_home);
	gt_obj_set_pos(img1, 0, 0);
	gt_obj_set_size(img1, 320, 61);
	gt_img_set_src(img1, "f:img_320x61_1.png");

	

	/** rect1 */
	/** 排气温度矩形框 */
	rect1 = gt_rect_create(screen_home);
	gt_obj_set_pos(rect1, 4, 75);
	gt_obj_set_size(rect1, 306, 45);
	gt_rect_set_radius(rect1, 0);
	gt_rect_set_bg_color(rect1, gt_color_hex(0x263248));
	gt_rect_set_color_border(rect1, gt_color_hex(0x263248));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 0);

	

	/** rect2 */
	/** 供气压力矩形框 */
	rect2 = gt_rect_create(screen_home);
	gt_obj_set_pos(rect2, 4, 127);
	gt_obj_set_size(rect2, 306, 45);
	gt_rect_set_radius(rect2, 0);
	gt_rect_set_bg_color(rect2, gt_color_hex(0x263248));
	gt_rect_set_color_border(rect2, gt_color_hex(0x263248));
	gt_rect_set_fill(rect2, 1);
	gt_rect_set_border(rect2, 0);

	

	/** rect3 */
	/** 风机矩形框 */
	rect3 = gt_rect_create(screen_home);
	gt_obj_set_pos(rect3, 6, 179);
	gt_obj_set_size(rect3, 306, 45);
	gt_rect_set_radius(rect3, 0);
	gt_rect_set_bg_color(rect3, gt_color_hex(0x263248));
	gt_rect_set_color_border(rect3, gt_color_hex(0x263248));
	gt_rect_set_fill(rect3, 1);
	gt_rect_set_border(rect3, 0);

	

	/** rect4 */
	/** 变频矩形框 */
	rect4 = gt_rect_create(screen_home);
	gt_obj_set_pos(rect4, 4, 231);
	gt_obj_set_size(rect4, 306, 45);
	gt_rect_set_radius(rect4, 0);
	gt_rect_set_bg_color(rect4, gt_color_hex(0x263248));
	gt_rect_set_color_border(rect4, gt_color_hex(0x263248));
	gt_rect_set_fill(rect4, 1);
	gt_rect_set_border(rect4, 0);

	

	/** rect5 */
	/** 工作电压矩形框 */
	rect5 = gt_rect_create(screen_home);
	gt_obj_set_pos(rect5, 4, 283);
	gt_obj_set_size(rect5, 306, 45);
	gt_rect_set_radius(rect5, 0);
	gt_rect_set_bg_color(rect5, gt_color_hex(0x263248));
	gt_rect_set_color_border(rect5, gt_color_hex(0x263248));
	gt_rect_set_fill(rect5, 1);
	gt_rect_set_border(rect5, 0);

	

	/** rect6 */
	/** 故障矩形框 */
	rect6 = gt_rect_create(screen_home);
	gt_obj_set_pos(rect6, 3, 335);
	gt_obj_set_size(rect6, 306, 45);
	gt_rect_set_radius(rect6, 0);
	gt_rect_set_bg_color(rect6, gt_color_hex(0x263248));
	gt_rect_set_color_border(rect6, gt_color_hex(0x263248));
	gt_rect_set_fill(rect6, 1);
	gt_rect_set_border(rect6, 0);

	

	/** lab1 */
	/** 设备详情文字 */
	lab1 = gt_label_create(screen_home);
	gt_obj_set_pos(lab1, 113, 16);
	gt_obj_set_size(lab1, 110, 35);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 16);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT);
	gt_label_set_text(lab1, "设备详情");

	

	/** lab2 */
	/** 排气温度文字 */
	lab2 = gt_label_create(screen_home);
	gt_obj_set_pos(lab2, 17, 86);
	gt_obj_set_size(lab2, 120, 40);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 24);
	gt_label_set_font_family_cn(lab2, 15);
	gt_label_set_font_family_en(lab2, 33);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT);
	gt_label_set_text(lab2, "排气温度：");

	

	/** lab3 */
	/** 供气压力文字 */
	lab3 = gt_label_create(screen_home);
	gt_obj_set_pos(lab3, 17, 136);
	gt_obj_set_size(lab3, 130, 40);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 24);
	gt_label_set_font_family_cn(lab3, 15);
	gt_label_set_font_family_en(lab3, 33);
	gt_label_set_font_align(lab3, GT_ALIGN_LEFT);
	gt_label_set_text(lab3, "供气压力：");

	

	/** lab4 */
	/** 风机文字 */
	lab4 = gt_label_create(screen_home);
	gt_obj_set_pos(lab4, 17, 186);
	gt_obj_set_size(lab4, 72, 40);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 24);
	gt_label_set_font_family_cn(lab4, 15);
	gt_label_set_font_family_en(lab4, 33);
	gt_label_set_font_align(lab4, GT_ALIGN_LEFT);
	gt_label_set_text(lab4, "风机：");

	

	/** lab5 */
	/** 变频文字 */
	lab5 = gt_label_create(screen_home);
	gt_obj_set_pos(lab5, 17, 240);
	gt_obj_set_size(lab5, 80, 40);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 24);
	gt_label_set_font_family_cn(lab5, 15);
	gt_label_set_font_family_en(lab5, 33);
	gt_label_set_font_align(lab5, GT_ALIGN_LEFT);
	gt_label_set_text(lab5, "变频：");

	

	/** lab6 */
	/** 工作电压文字 */
	lab6 = gt_label_create(screen_home);
	gt_obj_set_pos(lab6, 17, 291);
	gt_obj_set_size(lab6, 130, 40);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 24);
	gt_label_set_font_family_cn(lab6, 15);
	gt_label_set_font_family_en(lab6, 33);
	gt_label_set_font_align(lab6, GT_ALIGN_LEFT);
	gt_label_set_text(lab6, "工作电压：");

	

	/** lab7 */
	/** 故障文字 */
	lab7 = gt_label_create(screen_home);
	gt_obj_set_pos(lab7, 17, 343);
	gt_obj_set_size(lab7, 72, 40);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 24);
	gt_label_set_font_family_cn(lab7, 15);
	gt_label_set_font_family_en(lab7, 33);
	gt_label_set_font_align(lab7, GT_ALIGN_LEFT);
	gt_label_set_text(lab7, "故障：");

	

	/** lab9 */
	/** 供气压力状态 */
	lab9 = gt_label_create(screen_home);
	gt_obj_set_pos(lab9, 199, 136);
	gt_obj_set_size(lab9, 80, 40);
	gt_label_set_font_color(lab9, gt_color_hex(0x72b1ff));
	gt_label_set_font_size(lab9, 20);
	gt_label_set_font_family_cn(lab9, 15);
	gt_label_set_font_align(lab9, GT_ALIGN_LEFT);
	gt_label_set_text(lab9, "断线");

	

	/** lab10 */
	/** 风机状态 */
	lab10 = gt_label_create(screen_home);
	gt_obj_set_pos(lab10, 161, 184);
	gt_obj_set_size(lab10, 140, 40);
	gt_label_set_font_color(lab10, gt_color_hex(0x72b1ff));
	gt_label_set_font_size(lab10, 24);
	gt_label_set_font_family_en(lab10, 41);
	gt_label_set_font_align(lab10, GT_ALIGN_LEFT);
	gt_label_set_text(lab10, "0.0  0.0");

	

	/** lab12 */
	/** 变频数据 */
	lab12 = gt_label_create(screen_home);
	gt_obj_set_pos(lab12, 146, 241);
	gt_obj_set_size(lab12, 167, 40);
	gt_label_set_font_color(lab12, gt_color_hex(0x72b1ff));
	gt_label_set_font_size(lab12, 24);
	gt_label_set_font_family_en(lab12, 41);
	gt_label_set_font_align(lab12, GT_ALIGN_LEFT);
	gt_label_set_text(lab12, "0RPM 0.0KW");

	

	/** lab13 */
	/** 工作电压数据 */
	lab13 = gt_label_create(screen_home);
	gt_obj_set_pos(lab13, 164, 291);
	gt_obj_set_size(lab13, 150, 40);
	gt_label_set_font_color(lab13, gt_color_hex(0x72b1ff));
	gt_label_set_font_size(lab13, 24);
	gt_label_set_font_family_en(lab13, 41);
	gt_label_set_font_align(lab13, GT_ALIGN_LEFT);
	gt_label_set_text(lab13, "0V 0.0H");

	

	/** lab15 */
	/** 故障数据 */
	lab15 = gt_label_create(screen_home);
	gt_obj_set_pos(lab15, 198, 343);
	gt_obj_set_size(lab15, 60, 40);
	gt_label_set_font_color(lab15, gt_color_hex(0x72b1ff));
	gt_label_set_font_size(lab15, 24);
	gt_label_set_font_family_en(lab15, 41);
	gt_label_set_font_align(lab15, GT_ALIGN_LEFT);
	gt_label_set_text(lab15, "E10");

	

	/** inputNum1 */
	/** 温度数值，可设置递增和递减数值范围等 */
	inputNum1 = gt_input_number_create(screen_home);
	gt_obj_set_pos(inputNum1, 195, 82);
	gt_obj_set_size(inputNum1, 64, 40);
	gt_input_number_set_font_color(inputNum1, gt_color_hex(0x72b1ff));
	gt_input_number_set_font_size(inputNum1, 24);
	gt_input_number_set_font_family_en(inputNum1, 41);
	gt_input_number_set_font_align(inputNum1, GT_ALIGN_CENTER_MID);
	gt_input_number_set_value(inputNum1, 50);
	gt_input_number_set_step(inputNum1, 5);
	gt_input_number_set_min(inputNum1, 10);
	gt_input_number_set_max(inputNum1, 100);
	gt_input_number_set_fill_zero_front(inputNum1, false);
	gt_input_number_set_display_integer_length(inputNum1, 2);
	gt_input_number_set_display_decimal_length(inputNum1, 0);

	

	/** lab14 */
	/** TX */
	lab14 = gt_label_create(screen_home);
	gt_obj_set_pos(lab14, 190, 417);
	gt_obj_set_size(lab14, 50, 40);
	gt_label_set_font_color(lab14, gt_color_hex(0x72b1ff));
	gt_label_set_font_size(lab14, 24);
	gt_label_set_font_family_en(lab14, 41);
	gt_label_set_font_align(lab14, GT_ALIGN_LEFT);
	gt_label_set_text(lab14, "TX ");

	

	/** rect7 */
	rect7 = gt_rect_create(screen_home);
	gt_obj_set_pos(rect7, 228, 422);
	gt_obj_set_size(rect7, 20, 20);
	gt_rect_set_radius(rect7, 20);
	gt_rect_set_bg_color(rect7, gt_color_hex(0xd70207));
	gt_rect_set_color_border(rect7, gt_color_hex(0xd70207));
	gt_rect_set_fill(rect7, 1);
	gt_rect_set_border(rect7, 0);

	

	/** lab13_copy */
	/** RX */
	lab13_copy = gt_label_create(screen_home);
	gt_obj_set_pos(lab13_copy, 250, 417);
	gt_obj_set_size(lab13_copy, 50, 40);
	gt_label_set_font_color(lab13_copy, gt_color_hex(0x72b1ff));
	gt_label_set_font_size(lab13_copy, 24);
	gt_label_set_font_family_en(lab13_copy, 41);
	gt_label_set_font_align(lab13_copy, GT_ALIGN_LEFT);
	gt_label_set_text(lab13_copy, "RX ");

	

	/** rect7_copy */
	rect7_copy = gt_rect_create(screen_home);
	gt_obj_set_pos(rect7_copy, 287, 422);
	gt_obj_set_size(rect7_copy, 20, 20);
	gt_rect_set_radius(rect7_copy, 20);
	gt_rect_set_bg_color(rect7_copy, gt_color_hex(0xd70207));
	gt_rect_set_color_border(rect7_copy, gt_color_hex(0xd70207));
	gt_rect_set_fill(rect7_copy, 1);
	gt_rect_set_border(rect7_copy, 0);

	

	/** lab14_copy */
	/** 停止文字 */
	lab14_copy = gt_label_create(screen_home);
	gt_obj_set_pos(lab14_copy, 19, 417);
	gt_obj_set_size(lab14_copy, 70, 40);
	gt_label_set_font_color(lab14_copy, gt_color_hex(0x72b1ff));
	gt_label_set_font_size(lab14_copy, 24);
	gt_label_set_font_family_cn(lab14_copy, 16);
	gt_label_set_font_family_en(lab14_copy, 41);
	gt_label_set_font_align(lab14_copy, GT_ALIGN_LEFT);
	gt_label_set_text(lab14_copy, "停止");

	

	/** rect9 */
	rect9 = gt_rect_create(screen_home);
	gt_obj_set_pos(rect9, 150, 76);
	gt_obj_set_size(rect9, 40, 40);
	gt_rect_set_radius(rect9, 0);
	gt_rect_set_bg_color(rect9, gt_color_hex(0x263248));
	gt_rect_set_color_border(rect9, gt_color_hex(0x263248));
	gt_rect_set_fill(rect9, 1);
	gt_rect_set_border(rect9, 0);
	gt_obj_add_event_cb(rect9, rect9_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** rect9_copy */
	rect9_copy = gt_rect_create(screen_home);
	gt_obj_set_pos(rect9_copy, 266, 77);
	gt_obj_set_size(rect9_copy, 40, 40);
	gt_rect_set_radius(rect9_copy, 0);
	gt_rect_set_bg_color(rect9_copy, gt_color_hex(0x263248));
	gt_rect_set_color_border(rect9_copy, gt_color_hex(0x263248));
	gt_rect_set_fill(rect9_copy, 1);
	gt_rect_set_border(rect9_copy, 0);
	gt_obj_add_event_cb(rect9_copy, rect9_copy_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img2 */
	/** 减少箭头 */
	img2 = gt_img_create(screen_home);
	gt_obj_set_pos(img2, 276, 91);
	gt_obj_set_size(img2, 15, 14);
	gt_img_set_src(img2, "f:img_15x14_5.png");
	gt_obj_add_event_cb(img2, img2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img3 */
	/** 增加箭头 */
	img3 = gt_img_create(screen_home);
	gt_obj_set_pos(img3, 162, 91);
	gt_obj_set_size(img3, 15, 14);
	gt_img_set_src(img3, "f:img_15x14_4.png");
	gt_obj_add_event_cb(img3, img3_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	return screen_home;
}

