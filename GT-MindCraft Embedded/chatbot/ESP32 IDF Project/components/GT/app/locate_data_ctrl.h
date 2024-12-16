#ifndef _LOCATE_DATA_H_
#define _LOCATE_DATA_H_

#include "zk_config.h"

/**
 * 数组索引下标
 */
typedef enum {
    LD_COB_ID,          //COB id 6个字节
#if USE_FUNC_CLOCK_LIST
    LD_CLOCK_LIST,      //@ref CLOCK_LIST_DATA_MAX_LEN
#endif //!USE_FUNC_CLOCK_LIST
}locate_data_idx;

#if USE_FUNC_CLOCK_LIST
#define CLOCK_LIST_DATA_MAX_LEN     (160) //byte
#endif //!USE_FUNC_CLOCK_LIST

GT_Status locate_data_init(void);
uint16_t locate_data_load(locate_data_idx idx, uint8_t *const data);
GT_Status locate_data_save(locate_data_idx idx, const uint8_t *const data, uint16_t len);

#endif //!_LOCATE_DATA_H_
