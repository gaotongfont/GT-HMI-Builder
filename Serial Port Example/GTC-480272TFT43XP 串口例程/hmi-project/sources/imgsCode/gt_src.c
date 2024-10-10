#include "gt_src.h"


const gt_src_st user_src_list[] = {
	{".:img_1_20x17.png", 20, 17, src_img_1_20x17, 1020, 1},
	{".:img_2_20x17.png", 20, 17, src_img_2_20x17, 1020, 1},
	{NULL, 0, 0, NULL, 0, 0},
};


void gt_user_src_init(void)
{
	gt_src_init(user_src_list, sizeof(user_src_list)/sizeof(gt_src_st));
}

