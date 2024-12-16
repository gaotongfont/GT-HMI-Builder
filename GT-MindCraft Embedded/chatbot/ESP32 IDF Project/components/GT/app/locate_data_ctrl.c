#include "locate_data_ctrl.h"


/**
 *  各数据段的数据长度
 */
static const uint8_t locate_data_len[] = {
    [LD_COB_ID] = 6,
#if USE_FUNC_CLOCK_LIST
    [LD_CLOCK_LIST] = CLOCK_LIST_DATA_MAX_LEN,
#endif //!USE_FUNC_CLOCK_LIST
};

//临时数组长度
#define TMP_BUFF_SIZE   10

/**
 * 加载数据保存区的值
 * @param idx   需要获取的数据
 * @param data  存储返回的数据
 * @return      获取的数据长度
 */
uint16_t locate_data_load(locate_data_idx idx, uint8_t *const data) {
    uint16_t i, offset = 0;
    uint16_t len = locate_data_len[idx];

    for (i=0; i<(uint16_t)idx; i++) {
        offset += locate_data_len[i];
    }

    // r_dat_bat(ADDRESS_LOCATE_DATA_START + offset, len, data);

    return len;
}

/**
 * 保存数据
 * @param idx   需要获取的数据
 * @param data  需要存储的数据
 * @param len   需要写入数据的长度
 */
GT_Status locate_data_save(locate_data_idx idx, const uint8_t *const data, uint16_t len) {
    uint16_t i, offset = 0;
    uint8_t tmp[TMP_BUFF_SIZE] = {0};
    uint8_t *dat_ptr = tmp;

    if (len > locate_data_len[idx]) {
        return GT_ERR;
    }

    for (i=0; i<(uint16_t)idx; i++) {
        offset += locate_data_len[i];
    }

#if USE_FUNC_CLOCK_LIST
    if (LD_CLOCK_LIST == idx) {
        dat_ptr = (uint8_t *)data;
    } else
#endif //!USE_FUNC_CLOCK_LIST
    {
    memcpy(tmp, data, len);
    }
#if 0
    r_dat_bat(ADDRESS_LOCATE_DATA_START, ZK_LOCATE_DATA_SIZE, ZK_BUFF_PTR);

    SPI_Write_Datas(ADDRESS_LOCATE_DATA_START, ZK_BUFF_PTR, ZK_LOCATE_DATA_SIZE);
#else
    // flash_write_data(ADDRESS_LOCATE_DATA_START + offset, locate_data_len[idx], dat_ptr);
#endif

    return GT_OK;
}

/**
 * 开机加载本地数据
 */
GT_Status locate_data_init(void)
{
#if USE_TMP_CODE_EN
    // locate_data_load(LD_SPLIT_WORD, &trans_ctrl.is_split_default_mode);
    locate_data_load(LD_LCD_DIR, &gt_psram_p->lcd_dir_ctrl.lcd_dir_mode);

#if USE_FUNC_CLOCK_LIST
    gt_get_clock_list();
#endif //!USE_FUNC_CLOCK_LIST
#endif //!USE_TMP_CODE_EN

    return GT_OK;
}
