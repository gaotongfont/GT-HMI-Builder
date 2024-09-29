#include "gt_ui.h"


/** screen_home_cp */
gt_obj_st * screen_home_cp = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * gif1 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * lab1 = NULL;

gt_obj_st * gt_init_screen_home_cp(void)
{
	screen_home_cp = gt_obj_create(NULL);

	gt_screen_set_bgcolor(screen_home_cp, gt_color_hex(0x000000));


	

	/** img1 */
	img1 = gt_img_create(screen_home_cp);
	gt_obj_set_pos(img1, 17, 154);
	gt_obj_set_size(img1, 207, 139);
	gt_obj_set_opa(img1, GT_OPA_10);
	gt_img_set_src(img1, "f:img_1111_207x139.png");

	

	/** gif1 */
	gif1 = gt_gif_create(screen_home_cp);
	gt_obj_set_pos(gif1, 0, 56);
	gt_obj_set_size(gif1, 240, 140);
	gt_gif_set_src(gif1, "f:img_1723603037071_240x140.gif");
	gt_gif_play(gif1);

	

	/** imgbtn1 */
	imgbtn1 = gt_imgbtn_create(screen_home_cp);
	gt_obj_set_pos(imgbtn1, 36, 250);
	gt_obj_set_size(imgbtn1, 170, 44);
	gt_imgbtn_set_src(imgbtn1, "f:img_1_170x44.png");
	gt_imgbtn_add_state_item(imgbtn1, "f:img_1_170x44.png");

	

	/** lab1 */
	lab1 = gt_label_create(screen_home_cp);
	gt_obj_set_pos(lab1, 56, 256);
	gt_obj_set_size(lab1, 125, 30);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_family(lab1, 1);
	gt_label_set_font_cjk(lab1, 0);
	gt_label_set_font_align(lab1, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab1, "请长按说话");



	return screen_home_cp;
}

