#include "gt_src.h"


const gt_src_st user_src_list[] = {
	{".:img_869x76_21.png", 869, 76, src_img_869x76_21, 198132, 1},
	{".:img_869x76_24.png", 869, 76, src_img_869x76_24, 198132, 1},
	{".:img_869x77_22.png", 869, 77, src_img_869x77_22, 200739, 1},
	{".:img_869x77_23.png", 869, 77, src_img_869x77_23, 200739, 1},
	{".:img_890x324_17.png", 890, 324, src_img_890x324_17, 865080, 1},
	{".:img_977x363_20.png", 977, 363, src_img_977x363_20, 1063953, 1},
	{".:img_99x67_30.png", 99, 67, src_img_99x67_30, 19899, 1},
	{".:img_99x67_31.png", 99, 67, src_img_99x67_31, 19899, 1},
	{".:img_1024x600_10kk.png", 1024, 600, src_img_1024x600_10kk, 1843200, 1},
	{".:img_1024x600_12.png", 1024, 600, src_img_1024x600_12, 1228800, 0},
	{".:img_171x37_40.png", 171, 37, src_img_171x37_40, 18981, 1},
	{".:img_184x208_1.png", 184, 208, src_img_184x208_1, 114816, 1},
	{".:img_184x208_2.png", 184, 208, src_img_184x208_2, 114816, 1},
	{".:img_184x208_3.png", 184, 208, src_img_184x208_3, 114816, 1},
	{".:img_184x208_4.png", 184, 208, src_img_184x208_4, 114816, 1},
	{".:img_184x208_5.png", 184, 208, src_img_184x208_5, 114816, 1},
	{".:img_184x208_6.png", 184, 208, src_img_184x208_6, 114816, 1},
	{".:img_184x208_7.png", 184, 208, src_img_184x208_7, 114816, 1},
	{".:img_184x208_8.png", 184, 208, src_img_184x208_8, 114816, 1},
	{".:img_184x208_9.png", 184, 208, src_img_184x208_9, 114816, 1},
	{".:img_269x269_Group_2.png", 269, 269, src_img_269x269_Group_2, 217083, 1},
	{".:img_320x200_img32.png", 320, 200, src_img_320x200_img32, 192000, 1},
	{".:img_320x200_img33.png", 320, 200, src_img_320x200_img33, 192000, 1},
	{".:img_408x261_18.png", 408, 261, src_img_408x261_18, 319464, 1},
	{".:img_44x63_10.png", 44, 63, src_img_44x63_10, 8316, 1},
	{".:img_44x63_11.png", 44, 63, src_img_44x63_11, 8316, 1},
	{".:img_604x272_19.png", 604, 272, src_img_604x272_19, 492864, 1},
	{".:img_84x58_14.png", 84, 58, src_img_84x58_14, 14616, 1},
	{NULL, 0, 0, NULL, 0, 0},
};


void gt_user_src_init(void)
{
	gt_src_init(user_src_list, sizeof(user_src_list)/sizeof(gt_src_st));
}

