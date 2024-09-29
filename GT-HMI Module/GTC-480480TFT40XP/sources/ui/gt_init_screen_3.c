#include "gt_ui.h"


/** screen_3 */
gt_obj_st * screen_3 = NULL;
static gt_obj_st * img18 = NULL;
static gt_obj_st * img19 = NULL;
static gt_obj_st * lab11 = NULL;
static gt_obj_st * img20 = NULL;
static gt_obj_st * img21 = NULL;
static gt_obj_st * img22 = NULL;
static gt_obj_st * img23 = NULL;

/** ���¼��������� */
static void img19_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_HOME, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** ���¼��ذ�ɫ�ƹ���� */
static void img21_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_4, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

/** ���¼��غ�ɫ�ƹ���� */
static void img22_0_cb(gt_event_st * e) {
	gt_disp_stack_load_scr_anim(GT_ID_SCREEN_5, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

gt_obj_st * gt_init_screen_3(void)
{
	screen_3 = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_3, gt_color_hex(0xFFFFFF));

	

	/** img18 */
	/** ����Ʊ���ͼ */
	img18 = gt_img_create(screen_3);
	gt_obj_set_pos(img18, 0, 0);
	gt_obj_set_size(img18, 480, 480);
	gt_img_set_src(img18, ".:img_480x480_1.png");

	

	/** img19 */
	/** ����ͼ�� */
	img19 = gt_img_create(screen_3);
	gt_obj_set_pos(img19, 19, 22);
	gt_obj_set_size(img19, 15, 26);
	gt_img_set_src(img19, ".:img_15x26_187.png");
	gt_obj_add_event_cb(img19, img19_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** lab11 */
	/** ��������֣�ʸ��24�ţ�4bit */
	lab11 = gt_label_create(screen_3);
	gt_obj_set_pos(lab11, 52, 19);
	gt_obj_set_size(lab11, 120, 32);
	gt_label_set_font_color(lab11, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab11, 24);
	gt_label_set_font_family_cn(lab11, 80);
	gt_label_set_font_family_en(lab11, 84);
	gt_label_set_font_gray(lab11, 4);
	gt_label_set_text(lab11, "�����");

	

	/** img20 */
	/** ��ɫѡ��Ч�� */
	img20 = gt_img_create(screen_3);
	gt_obj_set_pos(img20, 38, 368);
	gt_obj_set_size(img20, 104, 42);
	gt_img_set_src(img20, ".:img_104x42_616.png");

	

	/** img21 */
	/** ��ɫδѡ��Ч�� */
	img21 = gt_img_create(screen_3);
	gt_obj_set_pos(img21, 185, 366);
	gt_obj_set_size(img21, 104, 42);
	gt_img_set_src(img21, ".:img_104x42_618.png");
	gt_obj_add_event_cb(img21, img21_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img22 */
	/** ��ɫδѡ��Ч�� */
	img22 = gt_img_create(screen_3);
	gt_obj_set_pos(img22, 331, 366);
	gt_obj_set_size(img22, 104, 42);
	gt_img_set_src(img22, ".:img_104x42_614.png");
	gt_obj_add_event_cb(img22, img22_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
	

	/** img23 */
	/** ��ɫ��ͼƬ */
	img23 = gt_img_create(screen_3);
	gt_obj_set_pos(img23, 98, 0);
	gt_obj_set_size(img23, 289, 289);
	gt_img_set_src(img23, ".:img_289x289_403.png");


	return screen_3;
}

