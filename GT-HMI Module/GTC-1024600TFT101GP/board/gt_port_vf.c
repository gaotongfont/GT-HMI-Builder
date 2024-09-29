
/* include --------------------------------------------------------------*/
#include "gt_port_vf.h"
#include "../gt.h"
#include "../src/others/gt_log.h"


/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static variables -----------------------------------------------------*/
static const gt_vfs_st virt_file_sys[] ={
	/* name, w, h, addr, size, is_alpha */
    {"f:img_1024x600_10kk.png", 1024, 600, 643820, 1843200, 1},
	{"f:img_1024x600_12.png", 1024, 600, 2487020, 1228800, 0},
	{"f:img_171x37_40.png", 171, 37, 3715820, 18981, 1},
	{"f:img_184x208_1.png", 184, 208, 3734801, 114816, 1},
	{"f:img_184x208_2.png", 184, 208, 3849617, 114816, 1},
	{"f:img_184x208_3.png", 184, 208, 3964433, 114816, 1},
	{"f:img_184x208_4.png", 184, 208, 4079249, 114816, 1},
	{"f:img_184x208_5.png", 184, 208, 4194065, 114816, 1},
	{"f:img_184x208_6.png", 184, 208, 4308881, 114816, 1},
	{"f:img_184x208_7.png", 184, 208, 4423697, 114816, 1},
	{"f:img_184x208_8.png", 184, 208, 4538513, 114816, 1},
	{"f:img_184x208_9.png", 184, 208, 4653329, 114816, 1},
	{"f:img_269x269_Group_2.png", 269, 269, 4768145, 217083, 1},
	{"f:img_320x200_img32.png", 320, 200, 4985228, 192000, 1},
	{"f:img_320x200_img33.png", 320, 200, 5177228, 192000, 1},
	{"f:img_408x261_18.png", 408, 261, 5369228, 319464, 1},
	{"f:img_44x63_10.png", 44, 63, 5688692, 8316, 1},
	{"f:img_44x63_11.png", 44, 63, 5697008, 8316, 1},
	{"f:img_604x272_19.png", 604, 272, 5705324, 492864, 1},
	{"f:img_84x58_14.png", 84, 58, 6198188, 14616, 1},
	{"f:img_869x76_21.png", 869, 76, 6212804, 198132, 1},
	{"f:img_869x76_24.png", 869, 76, 6410936, 198132, 1},
	{"f:img_869x77_22.png", 869, 77, 6609068, 200739, 1},
	{"f:img_869x77_23.png", 869, 77, 6809807, 200739, 1},
	{"f:img_890x324_17.png", 890, 324, 7010546, 865080, 1},
	{"f:img_977x363_20.png", 977, 363, 7875626, 1063953, 1},
	{"f:img_99x67_30.png", 99, 67, 8939579, 19899, 1},
	{"f:img_99x67_31.png", 99, 67, 8959478, 19899, 1},
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

