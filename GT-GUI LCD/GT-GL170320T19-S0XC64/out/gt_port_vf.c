
/* include --------------------------------------------------------------*/
#include "gt_port_vf.h"
#include "../gt.h"
#include "../src/others/gt_log.h"


/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static variables -----------------------------------------------------*/
static const gt_vfs_st virt_file_sys[] ={
	/* name, w, h, addr, size, is_alpha */
    {"f:img_101x94_6_c.png", 101, 94, 805060, 28482, 1},
	{"f:img_12x20__images_arrow_right.png", 12, 20, 833542, 720, 1},
	{"f:img_16x16_icon_left.png", 16, 16, 834262, 768, 1},
	{"f:img_17x17_s1_c.png", 17, 17, 835030, 867, 1},
	{"f:img_17x17_s2_c.png", 17, 17, 835897, 867, 1},
	{"f:img_18x15_4_c.png", 18, 15, 836764, 810, 1},
	{"f:img_19x25_7_c.png", 19, 25, 837574, 1425, 1},
	{"f:img_207x87_5_c.png", 207, 87, 838999, 54027, 1},
	{"f:img_20x20_61_chevron_down.png", 20, 20, 893026, 1200, 1},
	{"f:img_20x20_65_chevron.png", 20, 20, 894226, 1200, 1},
	{"f:img_20x20_v1_icon.png", 20, 20, 895426, 1200, 1},
	{"f:img_20x20_v2_icon.png", 20, 20, 896626, 1200, 1},
	{"f:img_20x20_v3_icon.png", 20, 20, 897826, 1200, 1},
	{"f:img_20x20_v4_icon.png", 20, 20, 899026, 1200, 1},
	{"f:img_20x20_v5_icon.png", 20, 20, 900226, 1200, 1},
	{"f:img_20x20_v6_icon.png", 20, 20, 901426, 1200, 1},
	{"f:img_21x19_9_c.png", 21, 19, 902626, 1197, 1},
	{"f:img_21x21_8_c.png", 21, 21, 903823, 1323, 1},
	{"f:img_24x24_85_volume_notice.png", 24, 24, 905146, 1728, 1},
	{"f:img_26x26_2_battery_regular.png", 26, 26, 906874, 2028, 1},
	{"f:img_28x28_7_ic.png", 28, 28, 908902, 2352, 1},
	{"f:img_30x30_70_wifi_medium.png", 30, 30, 911254, 2700, 1},
	{"f:img_36x36_45_next.png", 36, 36, 913954, 3888, 1},
	{"f:img_36x36_54_previous.png", 36, 36, 917842, 3888, 1},
	{"f:img_68x68_2060.png", 68, 68, 921730, 13872, 1},
	{"f:img_68x68_2372.png", 68, 68, 935602, 13872, 1},
	{"f:img_84x84_0_c.png", 84, 84, 949474, 21168, 1},
	{"f:img_84x84_1_c.png", 84, 84, 970642, 21168, 1},
	{"f:img_84x84_2_c.png", 84, 84, 991810, 21168, 1},
    {NULL,0,0,0,0},
};

/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/


/* global functions / API interface -------------------------------------*/

#if GT_USE_MODE_FLASH
/**
 * @brief [flash] write or read data from flash
 *
 * @param data_write the data to be written
 * @param len_write the length of the data to be written
 * @param data_read the data to be read from flash
 * @param len_read the length need to read from flash
 *
 * @return uint32_t The number of bytes data read back preferentially,
 *      otherwise the number of bytes written successfully.
 */
extern uint32_t spi_wr(uint8_t * data_write, uint32_t len_write, uint8_t * data_read, uint32_t len_read);

#endif

void gt_port_vf_init(void)
{
#if GT_USE_MODE_FLASH
    gt_vf_init(virt_file_sys);

	gt_vf_drv_register(spi_wr);
#endif
}

/* end ------------------------------------------------------------------*/

