#include "gt_src.h"


const gt_src_st user_src_list[] = {
	{".:img_72x99_1.png", 72, 99, src_img_72x99_1, 21384, 1},
	{".:img_72x99_2.png", 72, 99, src_img_72x99_2, 21384, 1},
	{".:img_72x99_3.png", 72, 99, src_img_72x99_3, 21384, 1},
	{".:img_99x38_8.png", 99, 38, src_img_99x38_8, 11286, 1},
	{".:img_99x38_9.png", 99, 38, src_img_99x38_9, 11286, 1},
	{NULL, 0, 0, NULL, 0, 0},
};


void gt_user_src_init(void)
{
	gt_src_init(user_src_list, sizeof(user_src_list)/sizeof(gt_src_st));
}

