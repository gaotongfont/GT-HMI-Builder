#include "gt_src.h"


const gt_src_st user_src_list[] = {
	{".:img_15x14_4.png", 15, 14, src_img_15x14_4, 630, 1},
	{".:img_15x14_5.png", 15, 14, src_img_15x14_5, 630, 1},
	{".:img_320x61_1.png", 320, 61, src_img_320x61_1, 58560, 1},
	{NULL, 0, 0, NULL, 0, 0},
};


void gt_user_src_init(void)
{
	gt_src_init(user_src_list, sizeof(user_src_list)/sizeof(gt_src_st));
}

