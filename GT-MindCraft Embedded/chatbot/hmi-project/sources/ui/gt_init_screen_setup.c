#include "gt_ui.h"
#include "gt_font_config.h"


/** screen_setup */
gt_obj_st * screen_setup = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * btn1Copy = NULL;
static gt_obj_st * lab2Copy = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * btn1 = NULL;
static gt_obj_st * imgbtn3 = NULL;
static gt_obj_st * btn5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * btn7 = NULL;
static gt_obj_st * imgbtn7 = NULL;
static gt_obj_st * imgbtn8 = NULL;
static gt_obj_st * imgbtn9 = NULL;
static gt_obj_st * lab7Copy = NULL;
static gt_obj_st * btn7Copy = NULL;
static gt_obj_st * imgbtn9Copy = NULL;

static void screen_setup_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
}

static void img1_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void imgbtn3_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_JS, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void imgbtn7_0_cb(gt_event_st * e) {
	
}

static void imgbtn8_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_XG, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void imgbtn9_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_YS, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

static void imgbtn9Copy_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_YS, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_setup(void)
{
	screen_setup = gt_obj_create(NULL);
	gt_obj_add_event_cb(screen_setup, screen_setup_0_cb, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
	gt_screen_set_bgcolor(screen_setup, gt_color_hex(0x000000));


	

	/** img1 */
	img1 = gt_img_create(screen_setup);
	gt_obj_set_pos(img1, 13, 10);
	gt_obj_set_size(img1, 16, 16);
	gt_img_set_src(img1, ".:img_fh_16x16.png");
	gt_obj_add_event_cb(img1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab3 */
	lab3 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab3, 39, 5);
	gt_obj_set_size(lab3, 55, 26);
	gt_label_set_font_color(lab3, gt_color_hex(0x94a5b3));
	gt_label_set_font_align(lab3, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab3, "设置");

	

	/** btn1Copy */
	btn1Copy = gt_btn_create(screen_setup);
	gt_obj_set_pos(btn1Copy, 21, 70);
	gt_obj_set_size(btn1Copy, 200, 36);
	gt_btn_set_font_color(btn1Copy, gt_color_hex(0x4193fb));
	gt_btn_set_font_align(btn1Copy, GT_ALIGN_LEFT_MID);
	gt_btn_set_text(btn1Copy, "   3");
	gt_btn_set_color_background(btn1Copy, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn1Copy, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn1Copy, gt_color_hex(0x000000));
	gt_btn_set_radius(btn1Copy, 8);

	

	/** lab2Copy */
	lab2Copy = gt_label_create(screen_setup);
	gt_obj_set_pos(lab2Copy, 19, 35);
	gt_obj_set_size(lab2Copy, 83, 23);
	gt_label_set_font_color(lab2Copy, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab2Copy, gray_black_16);
	gt_label_set_font_cjk(lab2Copy, 0);
	gt_label_set_font_align(lab2Copy, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab2Copy, "用户年龄：");

	

	/** lab5 */
	lab5 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab5, 17, 113);
	gt_obj_set_size(lab5, 84, 22);
	gt_label_set_font_color(lab5, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab5, gray_black_16);
	gt_label_set_font_cjk(lab5, 0);
	gt_label_set_font_align(lab5, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab5, "角色设定：");

	

	/** btn1 */
	btn1 = gt_btn_create(screen_setup);
	gt_obj_set_pos(btn1, 19, 141);
	gt_obj_set_size(btn1, 200, 36);
	gt_btn_set_font_color(btn1, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn1, gray_black_16);
	gt_btn_set_font_cjk(btn1, 0);
	gt_btn_set_font_align(btn1, GT_ALIGN_LEFT_MID);
	gt_btn_set_text(btn1, "  朋友");
	gt_btn_set_color_background(btn1, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn1, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn1, gt_color_hex(0x000000));
	gt_btn_set_radius(btn1, 6);

	

	/** imgbtn3 */
	imgbtn3 = gt_imgbtn_create(screen_setup);
	gt_obj_set_pos(imgbtn3, 184, 150);
	gt_obj_set_size(imgbtn3, 27, 20);
	gt_imgbtn_set_src(imgbtn3, ".:img_down1_27x20.png");
	gt_imgbtn_add_state_item(imgbtn3, ".:img_up1_27x20.png");
	gt_obj_add_event_cb(imgbtn3, imgbtn3_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	/** btn5 */
	btn5 = gt_btn_create(screen_setup);
	gt_obj_set_pos(btn5, 19, 213);
	gt_obj_set_size(btn5, 200, 36);
	gt_btn_set_font_color(btn5, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn5, gray_black_16);
	gt_btn_set_font_cjk(btn5, 0);
	gt_btn_set_font_align(btn5, GT_ALIGN_LEFT_MID);
	gt_btn_set_text(btn5, "  正经");
	gt_btn_set_color_background(btn5, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn5, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn5, gt_color_hex(0x000000));
	gt_btn_set_radius(btn5, 6);

	

	/** lab6 */
	lab6 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab6, 18, 185);
	gt_obj_set_size(lab6, 84, 21);
	gt_label_set_font_color(lab6, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab6, gray_black_16);
	gt_label_set_font_cjk(lab6, 0);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "性格设定：");

	

	/** lab7 */
	lab7 = gt_label_create(screen_setup);
	gt_obj_set_pos(lab7, 20, 254);
	gt_obj_set_size(lab7, 84, 23);
	gt_label_set_font_color(lab7, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab7, gray_black_16);
	gt_label_set_font_cjk(lab7, 0);
	gt_label_set_font_align(lab7, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab7, "音色设定：");

	

	/** btn7 */
	btn7 = gt_btn_create(screen_setup);
	gt_obj_set_pos(btn7, 19, 282);
	gt_obj_set_size(btn7, 200, 36);
	gt_btn_set_font_color(btn7, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn7, gray_black_16);
	gt_btn_set_font_cjk(btn7, 0);
	gt_btn_set_font_align(btn7, GT_ALIGN_LEFT_MID);
	gt_btn_set_text(btn7, "  精英青年音色");
	gt_btn_set_color_background(btn7, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn7, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn7, gt_color_hex(0x000000));
	gt_btn_set_radius(btn7, 6);

	

	/** imgbtn7 */
	imgbtn7 = gt_imgbtn_create(screen_setup);
	gt_obj_set_pos(imgbtn7, 185, 78);
	gt_obj_set_size(imgbtn7, 27, 20);
	gt_imgbtn_set_src(imgbtn7, ".:img_down1_27x20.png");
	gt_imgbtn_add_state_item(imgbtn7, ".:img_down1_27x20.png");

	

	/** imgbtn8 */
	imgbtn8 = gt_imgbtn_create(screen_setup);
	gt_obj_set_pos(imgbtn8, 184, 221);
	gt_obj_set_size(imgbtn8, 27, 20);
	gt_imgbtn_set_src(imgbtn8, ".:img_down1_27x20.png");
	gt_imgbtn_add_state_item(imgbtn8, ".:img_up1_27x20.png");
	gt_obj_add_event_cb(imgbtn8, imgbtn8_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
	

	/** imgbtn9 */
	imgbtn9 = gt_imgbtn_create(screen_setup);
	gt_obj_set_pos(imgbtn9, 184, 292);
	gt_obj_set_size(imgbtn9, 27, 20);
	gt_imgbtn_set_src(imgbtn9, ".:img_down1_27x20.png");
	gt_imgbtn_add_state_item(imgbtn9, ".:img_up1_27x20.png");
	gt_obj_add_event_cb(imgbtn9, imgbtn9_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab7Copy */
	lab7Copy = gt_label_create(screen_setup);
	gt_obj_set_pos(lab7Copy, 19, 325);
	gt_obj_set_size(lab7Copy, 84, 23);
	gt_label_set_font_color(lab7Copy, gt_color_hex(0x94a5b3));
	gt_label_set_font_family(lab7Copy, gray_black_16);
	gt_label_set_font_cjk(lab7Copy, 0);
	gt_label_set_font_align(lab7Copy, GT_ALIGN_LEFT_MID);
	gt_label_set_text(lab7Copy, "AI昵称：");

	

	/** btn7Copy */
	btn7Copy = gt_btn_create(screen_setup);
	gt_obj_set_pos(btn7Copy, 17, 353);
	gt_obj_set_size(btn7Copy, 200, 36);
	gt_btn_set_font_color(btn7Copy, gt_color_hex(0x4193fb));
	gt_btn_set_font_family(btn7Copy, gray_black_16);
	gt_btn_set_font_cjk(btn7Copy, 0);
	gt_btn_set_font_align(btn7Copy, GT_ALIGN_LEFT_MID);
	gt_btn_set_text(btn7Copy, "  智酱");
	gt_btn_set_color_background(btn7Copy, gt_color_hex(0x181b22));
	gt_btn_set_color_pressed(btn7Copy, gt_color_hex(0x00a8ff));
	gt_btn_set_font_color_pressed(btn7Copy, gt_color_hex(0x000000));
	gt_btn_set_radius(btn7Copy, 6);

	

	/** imgbtn9Copy */
	imgbtn9Copy = gt_imgbtn_create(screen_setup);
	gt_obj_set_pos(imgbtn9Copy, 178, 364);
	gt_obj_set_size(imgbtn9Copy, 27, 20);
	gt_imgbtn_set_src(imgbtn9Copy, ".:img_down1_27x20.png");
	gt_imgbtn_add_state_item(imgbtn9Copy, ".:img_up1_27x20.png");
	gt_obj_add_event_cb(imgbtn9Copy, imgbtn9Copy_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	return screen_setup;
}

