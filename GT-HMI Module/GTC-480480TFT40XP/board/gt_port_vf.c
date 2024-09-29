
/* include --------------------------------------------------------------*/
#include "gt_port_vf.h"
#include "../gt.h"
#include "../src/others/gt_log.h"


/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static variables -----------------------------------------------------*/
static const gt_vfs_st virt_file_sys[] ={
	/* name, w, h, addr, size, is_alpha */
    {"f:img_104x42_614.png", 104, 42, 1404676, 13104, 1},
	{"f:img_104x42_615.png", 104, 42, 1417780, 13104, 1},
	{"f:img_104x42_616.png", 104, 42, 1430884, 13104, 1},
	{"f:img_104x42_617.png", 104, 42, 1443988, 13104, 1},
	{"f:img_104x42_618.png", 104, 42, 1457092, 13104, 1},
	{"f:img_104x42_619.png", 104, 42, 1470196, 13104, 1},
	{"f:img_15x26_187.png", 15, 26, 1483300, 1170, 1},
	{"f:img_204x112_267.png", 204, 112, 1484470, 68544, 1},
	{"f:img_204x112_268.png", 204, 112, 1553014, 68544, 1},
	{"f:img_204x112_269.png", 204, 112, 1621558, 68544, 1},
	{"f:img_204x112_270.png", 204, 112, 1690102, 68544, 1},
	{"f:img_289x289_400.png", 289, 289, 1758646, 250563, 1},
	{"f:img_289x289_403.png", 289, 289, 2009209, 250563, 1},
	{"f:img_289x289_404.png", 289, 289, 2259772, 250563, 1},
	{"f:img_480x480_1.png", 480, 480, 2510335, 691200, 1},
	{"f:img_480x480_317.png", 480, 480, 3201535, 691200, 1},
	{"f:img_480x480_318.png", 480, 480, 3892735, 691200, 1},
	{"f:img_480x480_566.png", 480, 480, 4583935, 691200, 1},
	{"f:img_480x480_567.png", 480, 480, 5275135, 691200, 1},
	{"f:img_480x480_bj.png", 480, 480, 5966335, 691200, 1},
	{"f:img_60x60_304.png", 60, 60, 6657535, 10800, 1},
	{"f:img_60x60_310.png", 60, 60, 6668335, 10800, 1},
	{"f:img_60x60_311.png", 60, 60, 6679135, 10800, 1},
	{"f:img_60x60_312.png", 60, 60, 6689935, 10800, 1},
	{"f:img_60x60_609.png", 60, 60, 6700735, 10800, 1},
	{"f:img_60x60_610.png", 60, 60, 6711535, 10800, 1},
	{"f:img_60x60_611.png", 60, 60, 6722335, 10800, 1},
	{"f:img_60x60_612.png", 60, 60, 6733135, 10800, 1},
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

