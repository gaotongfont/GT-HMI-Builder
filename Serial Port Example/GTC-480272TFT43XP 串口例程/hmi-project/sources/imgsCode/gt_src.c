#include "gt_src.h"


const gt_src_st user_src_list[] = {
	{".:img_20x17_2.png", 20, 17, src_img_20x17_2, 1020, 1},
	{".:img_20x17_1.png", 20, 17, src_img_20x17_1, 1020, 1},
	{NULL, 0, 0, NULL, 0, 0},
};


void gt_user_src_init(void)
{
	gt_src_init(user_src_list, sizeof(user_src_list)/sizeof(gt_src_st));
}

