#include "gt_src.h"


const gt_src_st user_src_list[] = {
	{".:img_28x28_7_ic.png", 28, 28, src_img_28x28_7_ic, 2352, 1},
	{".:img_30x30_70_wifi_medium.png", 30, 30, src_img_30x30_70_wifi_medium, 2700, 1},
	{".:img_36x36_45_next.png", 36, 36, src_img_36x36_45_next, 3888, 1},
	{".:img_36x36_54_previous.png", 36, 36, src_img_36x36_54_previous, 3888, 1},
	{".:img_68x68_2060.png", 68, 68, src_img_68x68_2060, 13872, 1},
	{".:img_68x68_2372.png", 68, 68, src_img_68x68_2372, 13872, 1},
	{".:img_84x84_0_c.png", 84, 84, src_img_84x84_0_c, 21168, 1},
	{".:img_84x84_1_c.png", 84, 84, src_img_84x84_1_c, 21168, 1},
	{".:img_84x84_2_c.png", 84, 84, src_img_84x84_2_c, 21168, 1},
	{".:img_20x20_v1_icon.png", 20, 20, src_img_20x20_v1_icon, 1200, 1},
	{".:img_20x20_v2_icon.png", 20, 20, src_img_20x20_v2_icon, 1200, 1},
	{".:img_20x20_v3_icon.png", 20, 20, src_img_20x20_v3_icon, 1200, 1},
	{".:img_20x20_v4_icon.png", 20, 20, src_img_20x20_v4_icon, 1200, 1},
	{".:img_20x20_v5_icon.png", 20, 20, src_img_20x20_v5_icon, 1200, 1},
	{".:img_20x20_v6_icon.png", 20, 20, src_img_20x20_v6_icon, 1200, 1},
	{".:img_21x19_9_c.png", 21, 19, src_img_21x19_9_c, 1197, 1},
	{".:img_21x21_8_c.png", 21, 21, src_img_21x21_8_c, 1323, 1},
	{".:img_24x24_85_volume_notice.png", 24, 24, src_img_24x24_85_volume_notice, 1728, 1},
	{".:img_26x26_2_battery_regular.png", 26, 26, src_img_26x26_2_battery_regular, 2028, 1},
	{".:img_101x94_6_c.png", 101, 94, src_img_101x94_6_c, 28482, 1},
	{".:img_12x20__images_arrow_right.png", 12, 20, src_img_12x20__images_arrow_right, 720, 1},
	{".:img_16x16_icon_left.png", 16, 16, src_img_16x16_icon_left, 768, 1},
	{".:img_17x17_s1_c.png", 17, 17, src_img_17x17_s1_c, 867, 1},
	{".:img_17x17_s2_c.png", 17, 17, src_img_17x17_s2_c, 867, 1},
	{".:img_18x15_4_c.png", 18, 15, src_img_18x15_4_c, 810, 1},
	{".:img_19x25_7_c.png", 19, 25, src_img_19x25_7_c, 1425, 1},
	{".:img_207x87_5_c.png", 207, 87, src_img_207x87_5_c, 54027, 1},
	{".:img_20x20_61_chevron_down.png", 20, 20, src_img_20x20_61_chevron_down, 1200, 1},
	{".:img_20x20_65_chevron.png", 20, 20, src_img_20x20_65_chevron, 1200, 1},
	{NULL, 0, 0, NULL, 0, 0},
};


void gt_user_src_init(void)
{
	gt_src_init(user_src_list, sizeof(user_src_list)/sizeof(gt_src_st));
}

