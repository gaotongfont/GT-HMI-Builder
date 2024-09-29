
/* include --------------------------------------------------------------*/
#include "gt_port_vf.h"
#include "../gt.h"
#include "../src/others/gt_log.h"


/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static variables -----------------------------------------------------*/
static const gt_vfs_st virt_file_sys[] ={
	/* name, w, h, addr, size, is_alpha */
    {"f:img_160x41_sy_n_160x410x231.png", 160, 41, 108092, 13120, 0},
	{"f:img_160x41_sy_p_160x410x231.png", 160, 41, 121212, 19680, 1},
	{"f:img_160x41_xy.png", 160, 41, 140892, 19680, 1},
	{"f:img_160x41_xy_n_160x41160x231.png", 160, 41, 160572, 19680, 1},
	{"f:img_160x41_yyzx.png", 160, 41, 180252, 13120, 0},
	{"f:img_160x41_yyzx_p_160x41320x231.png", 160, 41, 193372, 19680, 1},
	{"f:img_480x272_hjzx1.png", 480, 272, 213052, 391680, 1},
	{"f:img_480x272_hjzx3.png", 480, 272, 604732, 391680, 1},
	{"f:img_480x272_hjzx4.png", 480, 272, 996412, 391680, 1},
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

