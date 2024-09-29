#include "gt_ui.h"


/** screen_home */
gt_obj_st * screen_home = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * clock1 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * img3 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab1_copy = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * img4 = NULL;
static gt_obj_st * img5 = NULL;

/** 按下后时钟控件数字显示为3分  */
static void img1_0_cb(gt_event_st * e) {
	gt_clock_set_time(clock1, 0, 3, 0);
}

/** 按下后时钟控件数字显示为5分 */
static void img2_0_cb(gt_event_st * e) {
	gt_clock_set_time(clock1, 0, 5, 0);
}

/** 按下后时钟控件数字显示为8分 */
static void img3_0_cb(gt_event_st * e) {
	gt_clock_set_time(clock1, 0, 8, 0);
}

/** 按下后时钟控件数字显示为10秒 */
static void lab1_0_cb(gt_event_st * e) {
	gt_clock_set_time(clock1, 0, 0, 10);
}

/** 按下后时钟控件数字显示为1分 */
static void lab1_copy_0_cb(gt_event_st * e) {
	gt_clock_set_time(clock1, 0, 1, 0);
}

/** 按下后时钟控件数字显示为5分 */
static void lab5_0_cb(gt_event_st * e) {
	gt_clock_set_time(clock1, 0, 5, 0);
}

/** 按下后暂停时间 */
static void img4_0_cb(gt_event_st * e) {
	gt_clock_stop(clock1);
}

/** 按下后启动时钟倒计时 */
static void img5_0_cb(gt_event_st * e) {
	gt_clock_start(clock1);
}

gt_obj_st * gt_init_screen_home(void)
{
	screen_home = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_home, gt_color_hex(0x000000));

	

	/** rect1 */
	/** 矩形框 */
	rect1 = gt_rect_create(screen_home);
	gt_obj_set_pos(rect1, 12, 12);
	gt_obj_set_size(rect1, 216, 60);
	gt_rect_set_radius(rect1, 0);
	gt_rect_set_bg_color(rect1, gt_color_hex(0x1b1b1b));
	gt_rect_set_color_border(rect1, gt_color_hex(0x1b1b1b));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 0);

	

	/** clock1 */
	/** 倒计时时间显示，工作模式设置为倒计时 */
	clock1 = gt_clock_create(screen_home);
	gt_obj_set_pos(clock1, 97, 25);
	gt_obj_set_size(clock1, 140, 40);
	gt_clock_set_font_color(clock1, gt_color_hex(0xff8000));
	gt_clock_set_font_size(clock1, 32);
	gt_clock_set_font_family_en(clock1, 42);
	gt_clock_set_font_family_numb(clock1, 114);
	gt_clock_set_space(clock1, 5, 0);
	gt_clock_set_time(clock1, 0, 0, 0);
	gt_clock_set_mode(clock1, GT_CLOCK_MODE_COUNTDOWN);
	gt_clock_set_format(clock1, "mm:ss");

	

	/** img1 */
	/** 牛奶/咖啡图标 */
	img1 = gt_img_create(screen_home);
	gt_obj_set_pos(img1, 10, 128);
	gt_obj_set_size(img1, 72, 99);
	gt_img_set_src(img1, ".:img_72x99_1.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img2 */
	/** 面包/馒头图标 */
	img2 = gt_img_create(screen_home);
	gt_obj_set_pos(img2, 82, 128);
	gt_obj_set_size(img2, 72, 99);
	gt_img_set_src(img2, ".:img_72x99_2.png");
	gt_obj_add_event_cb(img2, img2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img3 */
	/** 蒸水蛋图标 */
	img3 = gt_img_create(screen_home);
	gt_obj_set_pos(img3, 154, 128);
	gt_obj_set_size(img3, 72, 99);
	gt_img_set_src(img3, ".:img_72x99_3.png");
	gt_obj_add_event_cb(img3, img3_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab1 */
	/** 数字10 */
	lab1 = gt_label_create(screen_home);
	gt_obj_set_pos(lab1, 12, 78);
	gt_obj_set_size(lab1, 45, 40);
	gt_label_set_font_color(lab1, gt_color_hex(0xffa200));
	gt_label_set_font_size(lab1, 32);
	gt_label_set_font_family_cn(lab1, 16);
	gt_label_set_font_family_en(lab1, 42);
	gt_label_set_text(lab1, "10");
	gt_obj_add_event_cb(lab1, lab1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab2 */
	/** 文字秒 */
	lab2 = gt_label_create(screen_home);
	gt_obj_set_pos(lab2, 52, 88);
	gt_obj_set_size(lab2, 20, 24);
	gt_label_set_font_color(lab2, gt_color_hex(0xffa200));
	gt_label_set_font_size(lab2, 16);
	gt_label_set_font_family_cn(lab2, 14);
	gt_label_set_text(lab2, "秒 ");

	

	/** lab1_copy */
	/** 数字1 */
	lab1_copy = gt_label_create(screen_home);
	gt_obj_set_pos(lab1_copy, 108, 78);
	gt_obj_set_size(lab1_copy, 30, 40);
	gt_label_set_font_color(lab1_copy, gt_color_hex(0xffa200));
	gt_label_set_font_size(lab1_copy, 32);
	gt_label_set_font_family_cn(lab1_copy, 16);
	gt_label_set_font_family_en(lab1_copy, 42);
	gt_label_set_text(lab1_copy, "1");
	gt_obj_add_event_cb(lab1_copy, lab1_copy_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab4 */
	/** 文字分 */
	lab4 = gt_label_create(screen_home);
	gt_obj_set_pos(lab4, 126, 88);
	gt_obj_set_size(lab4, 20, 24);
	gt_label_set_font_color(lab4, gt_color_hex(0xffa200));
	gt_label_set_font_size(lab4, 16);
	gt_label_set_font_family_cn(lab4, 14);
	gt_label_set_text(lab4, "分 ");

	

	/** lab5 */
	/** 数字5 */
	lab5 = gt_label_create(screen_home);
	gt_obj_set_pos(lab5, 184, 78);
	gt_obj_set_size(lab5, 30, 40);
	gt_label_set_font_color(lab5, gt_color_hex(0xffa200));
	gt_label_set_font_size(lab5, 32);
	gt_label_set_font_family_en(lab5, 42);
	gt_label_set_text(lab5, "5");
	gt_obj_add_event_cb(lab5, lab5_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab6 */
	/** 文字分 */
	lab6 = gt_label_create(screen_home);
	gt_obj_set_pos(lab6, 207, 90);
	gt_obj_set_size(lab6, 20, 24);
	gt_label_set_font_color(lab6, gt_color_hex(0xffa200));
	gt_label_set_font_size(lab6, 16);
	gt_label_set_font_family_cn(lab6, 14);
	gt_label_set_text(lab6, "分 ");

	

	/** img4 */
	/** 暂停/取消图标 */
	img4 = gt_img_create(screen_home);
	gt_obj_set_pos(img4, 10, 260);
	gt_obj_set_size(img4, 99, 38);
	gt_img_set_src(img4, ".:img_99x38_8.png");
	gt_obj_add_event_cb(img4, img4_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img5 */
	/** 确定/开始图标 */
	img5 = gt_img_create(screen_home);
	gt_obj_set_pos(img5, 126, 260);
	gt_obj_set_size(img5, 99, 38);
	gt_img_set_src(img5, ".:img_99x38_9.png");
	gt_obj_add_event_cb(img5, img5_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	return screen_home;
}

