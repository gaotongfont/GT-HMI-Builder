
/* include --------------------------------------------------------------*/
#include "gt_port_vf.h"
#include "../gt.h"
#include "../src/others/gt_log.h"


/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static variables -----------------------------------------------------*/
static const gt_vfs_st virt_file_sys[] ={
	/* name, w, h, addr, size, is_alpha */
    {"f:img_104x42_614.png", 104, 42, 0, 13104, 1},
	{"f:img_104x42_615.png", 104, 42, 13104, 13104, 1},
	{"f:img_104x42_616.png", 104, 42, 26208, 13104, 1},
	{"f:img_104x42_617.png", 104, 42, 39312, 13104, 1},
	{"f:img_104x42_618.png", 104, 42, 52416, 13104, 1},
	{"f:img_104x42_619.png", 104, 42, 65520, 13104, 1},
	{"f:img_15x26_187.png", 15, 26, 78624, 1170, 1},
	{"f:img_204x112_267.png", 204, 112, 79794, 68544, 1},
	{"f:img_204x112_268.png", 204, 112, 148338, 68544, 1},
	{"f:img_204x112_269.png", 204, 112, 216882, 68544, 1},
	{"f:img_204x112_270.png", 204, 112, 285426, 68544, 1},
	{"f:img_289x289_400.png", 289, 289, 353970, 250563, 1},
	{"f:img_289x289_403.png", 289, 289, 604533, 250563, 1},
	{"f:img_289x289_404.png", 289, 289, 855096, 250563, 1},
	{"f:img_480x480_1.png", 480, 480, 1105659, 691200, 1},
	{"f:img_480x480_317.png", 480, 480, 1796859, 691200, 1},
	{"f:img_480x480_318.png", 480, 480, 2488059, 691200, 1},
	{"f:img_480x480_566.png", 480, 480, 3179259, 691200, 1},
	{"f:img_480x480_567.png", 480, 480, 3870459, 691200, 1},
	{"f:img_480x480_bj.png", 480, 480, 4561659, 691200, 1},
	{"f:img_60x60_304.png", 60, 60, 5252859, 10800, 1},
	{"f:img_60x60_310.png", 60, 60, 5263659, 10800, 1},
	{"f:img_60x60_311.png", 60, 60, 5274459, 10800, 1},
	{"f:img_60x60_312.png", 60, 60, 5285259, 10800, 1},
	{"f:img_60x60_609.png", 60, 60, 5296059, 10800, 1},
	{"f:img_60x60_610.png", 60, 60, 5306859, 10800, 1},
	{"f:img_60x60_611.png", 60, 60, 5317659, 10800, 1},
	{"f:img_60x60_612.png", 60, 60, 5328459, 10800, 1},
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

