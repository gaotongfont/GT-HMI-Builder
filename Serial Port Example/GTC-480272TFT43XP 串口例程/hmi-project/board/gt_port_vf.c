
/* include --------------------------------------------------------------*/
#include "gt_port_vf.h"
#include "../gt.h"
#include "../src/others/gt_log.h"


/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static variables -----------------------------------------------------*/
static const gt_vfs_st virt_file_sys[] ={
	/* name, w, h, addr, size, is_alpha */
    {"f:img_20x17_1.png", 20, 17, 3877212, 1020, 1},
	{"f:img_20x17_2.png", 20, 17, 3878232, 1020, 1},
    {NULL,0,0,0,0},
};
static gt_fs_drv_st drv_vf;

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
    gt_vf_init(virt_file_sys);
#if GT_USE_MODE_FLASH
	drv_vf.rw_cb = spi_wr;
#else
	drv_vf.rw_cb = NULL;
#endif
    gt_vf_drv_register(&drv_vf);
}



/* end ------------------------------------------------------------------*/

