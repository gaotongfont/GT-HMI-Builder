#include "gt_ui.h"


/** screen_13 */
gt_obj_st * screen_13 = NULL;
static gt_obj_st * img7 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * img2 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;

/** 按下加载回翻译界面 */
static void img7_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_1, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** 按下加载回古诗词界面 */
static void img2_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_7, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_13(void)
{
	screen_13 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_13, gt_color_hex(0x000000));

	

	/** img7 */
	/** 返回图标 */
	img7 = gt_img_create(screen_13);
	gt_obj_set_pos(img7, 8, 14);
	gt_obj_set_size(img7, 16, 16);
	gt_img_set_src(img7, "f:img_16x16_icon_left.png");
	gt_obj_add_event_cb(img7, img7_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab1 */
	/** 中文句子，优黑16x16 */
	lab1 = gt_label_create(screen_13);
	gt_obj_set_pos(lab1, 34, 13);
	gt_obj_set_size(lab1, 280, 25);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 16);
	gt_label_set_font_family_cn(lab1, 24);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT);
	gt_label_set_space(lab1, 1, 0);
	gt_label_set_text(lab1, "牧童骑在黄牛背上，嘹亮的歌声在林");

	

	/** img2 */
	img2 = gt_img_create(screen_13);
	gt_obj_set_pos(img2, 293, 143);
	gt_obj_set_size(img2, 20, 20);
	gt_img_set_src(img2, "f:img_20x20_65_chevron.png");
	gt_obj_add_event_cb(img2, img2_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab2 */
	/** 中文句子，优黑16x16 */
	lab2 = gt_label_create(screen_13);
	gt_obj_set_pos(lab2, 30, 41);
	gt_obj_set_size(lab2, 280, 24);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 16);
	gt_label_set_font_family_cn(lab2, 24);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT);
	gt_label_set_space(lab2, 1, 0);
	gt_label_set_text(lab2, "中回荡。忽然想要捕捉树上鸣叫的知");

	

	/** lab3 */
	/** 中文句子，优黑16x16 */
	lab3 = gt_label_create(screen_13);
	gt_obj_set_pos(lab3, 29, 71);
	gt_obj_set_size(lab3, 280, 24);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 16);
	gt_label_set_font_family_cn(lab3, 24);
	gt_label_set_font_align(lab3, GT_ALIGN_LEFT);
	gt_label_set_space(lab3, 1, 0);
	gt_label_set_text(lab3, "了，就马上停止唱歌，一声不响地站");

	

	/** lab4 */
	/** 中文句子，优黑16x16 */
	lab4 = gt_label_create(screen_13);
	gt_obj_set_pos(lab4, 29, 100);
	gt_obj_set_size(lab4, 280, 24);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 16);
	gt_label_set_font_family_cn(lab4, 24);
	gt_label_set_font_align(lab4, GT_ALIGN_LEFT);
	gt_label_set_space(lab4, 1, 0);
	gt_label_set_text(lab4, "立在了树旁边。");


	return screen_13;
}

