#include "gt_src.h"


const gt_src_st user_src_list[] = {
	{".:img_160x41_sy_n_160x410x231.png", 160, 41, src_img_160x41_sy_n_160x410x231, 13120, 0},
	{".:img_160x41_sy_p_160x410x231.png", 160, 41, src_img_160x41_sy_p_160x410x231, 19680, 1},
	{".:img_160x41_xy.png", 160, 41, src_img_160x41_xy, 19680, 1},
	{".:img_160x41_xy_n_160x41160x231.png", 160, 41, src_img_160x41_xy_n_160x41160x231, 19680, 1},
	{".:img_160x41_yyzx.png", 160, 41, src_img_160x41_yyzx, 13120, 0},
	{".:img_160x41_yyzx_p_160x41320x231.png", 160, 41, src_img_160x41_yyzx_p_160x41320x231, 19680, 1},
	{".:img_480x272_hjzx1.png", 480, 272, src_img_480x272_hjzx1, 391680, 1},
	{".:img_480x272_hjzx3.png", 480, 272, src_img_480x272_hjzx3, 391680, 1},
	{".:img_480x272_hjzx4.png", 480, 272, src_img_480x272_hjzx4, 391680, 1},
	{NULL, 0, 0, NULL, 0, 0},
};


void gt_user_src_init(void)
{
	gt_src_init(user_src_list, sizeof(user_src_list)/sizeof(gt_src_st));
}

