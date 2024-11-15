#include "gt_ui.h"

static const gt_scr_list_st gt_scr_list[] = {
    {GT_ID_SCREEN_HOME, gt_init_screen_home},
    {GT_ID_SCREEN_SETUP, gt_init_screen_setup},
    {GT_ID_SCREEN_SUBTITLE, gt_init_screen_subtitle},
	{GT_ID_MAIN_INTERFACE, gt_init_main_interface},
	{GT_ID_SETTING_LIST, gt_init_setting_list},
	{GT_ID_VOLUME_AND_BRIGHTNESS, gt_init_volume_and_brightness},
	{GT_ID_KEYBOARD, gt_init_keyboard},
	{GT_ID_FORGET_PASSWORD, gt_init_forget_password},
	{GT_ID_CONNECTION_FAILED, gt_init_connection_failed},
	{GT_ID_WIFI_LIST, gt_init_wifi_list},
};

static const char* age_items[] = {
    "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"
};
static const char* role_items[] = {"老师", "朋友", "密友", "心理咨询师"};
static const char* char_items[] = {"外向", "正经", "搞怪", "内向"};
static const char* ai_name_items[] = {"智酱","聊天侠","老羞"};
static const char* timbre_items[] = {"可爱男童","萌萌女童","卡通猪小琪","妩媚御姐","俏皮萌妹"};
static const char* voice_id_items[] = {"cute_boy", "lovely_girl", "peppa_pig", "wumei_yujie", "qiaopi_mengmei"};

void gt_ui_init(void) {


    gt_scr_stack_register_id_list(gt_scr_list, sizeof(gt_scr_list) / sizeof(gt_scr_list[0]), 20);
	gt_scr_stack_set_home_scr_id(GT_ID_MAIN_INTERFACE, false);
	gt_disp_stack_load_scr(GT_ID_MAIN_INTERFACE);
}

static void set_player_many_times(gt_obj_st * obj, void * item, uint16_t item_byte_size, uint16_t times) {
    for (uint16_t i = 0; i < times; i++) {
        gt_player_add_item(obj, item, item_byte_size);
    }
}

void set_emojis_in_player(gt_obj_st * obj, gt_ai_emojis_et emojis)
{
    gt_player_stop(obj);
    gt_player_remove_all_items(obj);
    switch (emojis) {
    case AI_EMOJIS_WAITING: {
        set_player_many_times(obj, "f:img_0_00_3_228x117.jpg", sizeof("f:img_0_00_3_228x117.jpg"), 3);
        gt_player_add_item(obj, "f:img_0_01_228x117.jpg", sizeof("f:img_0_01_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_02_228x117.jpg", sizeof("f:img_0_02_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_03_228x117.jpg", sizeof("f:img_0_03_228x117.jpg"));
        set_player_many_times(obj, "f:img_0_05_10_228x117.jpg", sizeof("f:img_0_05_10_228x117.jpg"), 10);
        gt_player_add_item(obj, "f:img_0_06_228x117.jpg", sizeof("f:img_0_06_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_07_228x117.jpg", sizeof("f:img_0_07_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_08_228x117.jpg", sizeof("f:img_0_08_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_09_228x117.jpg", sizeof("f:img_0_09_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_10_228x117.jpg", sizeof("f:img_0_10_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_11_228x117.jpg", sizeof("f:img_0_11_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_12_228x117.jpg", sizeof("f:img_0_12_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_13_228x117.jpg", sizeof("f:img_0_13_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_14_228x117.jpg", sizeof("f:img_0_14_228x117.jpg"));
        set_player_many_times(obj, "f:img_0_15_7_228x117.jpg", sizeof("f:img_0_15_7_228x117.jpg"), 7);
        gt_player_add_item(obj, "f:img_0_16_228x117.jpg", sizeof("f:img_0_16_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_17_228x117.jpg", sizeof("f:img_0_17_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_18_228x117.jpg", sizeof("f:img_0_18_228x117.jpg"));
        set_player_many_times(obj, "f:img_0_19_12_228x117.jpg", sizeof("f:img_0_19_12_228x117.jpg"), 12);
        gt_player_add_item(obj, "f:img_0_20_228x117.jpg", sizeof("f:img_0_20_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_21_228x117.jpg", sizeof("f:img_0_21_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_22_228x117.jpg", sizeof("f:img_0_22_228x117.jpg"));
        set_player_many_times(obj, "f:img_0_23_10_228x117.jpg", sizeof("f:img_0_23_10_228x117.jpg"), 10);
        gt_player_add_item(obj, "f:img_0_24_228x117.jpg", sizeof("f:img_0_24_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_25_228x117.jpg", sizeof("f:img_0_25_228x117.jpg"));
        set_player_many_times(obj, "f:img_0_26_9_228x117.jpg", sizeof("f:img_0_26_9_228x117.jpg"), 9);
        gt_player_add_item(obj, "f:img_0_27_228x117.jpg", sizeof("f:img_0_27_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_28_228x117.jpg", sizeof("f:img_0_28_228x117.jpg"));
        set_player_many_times(obj, "f:img_0_29_9_228x117.jpg", sizeof("f:img_0_29_9_228x117.jpg"), 9);
        gt_player_add_item(obj, "f:img_0_30_228x117.jpg", sizeof("f:img_0_30_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_31_228x117.jpg", sizeof("f:img_0_31_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_32_228x117.jpg", sizeof("f:img_0_32_228x117.jpg"));
        set_player_many_times(obj, "f:img_0_33_8_228x117.jpg", sizeof("f:img_0_33_8_228x117.jpg"), 8);
        gt_player_add_item(obj, "f:img_0_34_228x117.jpg", sizeof("f:img_0_34_228x117.jpg"));
        set_player_many_times(obj, "f:img_0_35_3_228x117.jpg", sizeof("f:img_0_35_3_228x117.jpg"), 3);
        gt_player_add_item(obj, "f:img_0_36_228x117.jpg", sizeof("f:img_0_36_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_37_228x117.jpg", sizeof("f:img_0_37_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_38_228x117.jpg", sizeof("f:img_0_38_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_39_228x117.jpg", sizeof("f:img_0_39_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_40_228x117.jpg", sizeof("f:img_0_40_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_41_228x117.jpg", sizeof("f:img_0_41_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_42_228x117.jpg", sizeof("f:img_0_42_228x117.jpg"));
        gt_player_add_item(obj, "f:img_0_43_228x117.jpg", sizeof("f:img_0_43_228x117.jpg"));
        break;
    }
    case AI_EMOJIS_RECORDING: {
        for (uint8_t i = 0; i < 2; i++)
        {
            set_player_many_times(obj, "f:img_01_01_2_222x112.jpg", sizeof("f:img_01_01_2_222x112.jpg"), 2);
            gt_player_add_item(obj, "f:img_01_02_222x112.jpg", sizeof("f:img_01_02_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_03_222x112.jpg", sizeof("f:img_01_03_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_04_222x112.jpg", sizeof("f:img_01_04_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_05_222x112.jpg", sizeof("f:img_01_05_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_06_222x112.jpg", sizeof("f:img_01_06_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_07_222x112.jpg", sizeof("f:img_01_07_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_08_222x112.jpg", sizeof("f:img_01_08_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_09_222x112.jpg", sizeof("f:img_01_09_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_10_222x112.jpg", sizeof("f:img_01_10_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_11_222x112.jpg", sizeof("f:img_01_11_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_12_222x112.jpg", sizeof("f:img_01_12_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_13_222x112.jpg", sizeof("f:img_01_13_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_14_222x112.jpg", sizeof("f:img_01_14_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_15_222x112.jpg", sizeof("f:img_01_15_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_16_222x112.jpg", sizeof("f:img_01_16_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_17_222x112.jpg", sizeof("f:img_01_17_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_18_222x112.jpg", sizeof("f:img_01_18_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_19_222x112.jpg", sizeof("f:img_01_19_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_20_222x112.jpg", sizeof("f:img_01_20_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_21_222x112.jpg", sizeof("f:img_01_21_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_22_222x112.jpg", sizeof("f:img_01_22_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_23_222x112.jpg", sizeof("f:img_01_23_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_24_222x112.jpg", sizeof("f:img_01_24_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_25_222x112.jpg", sizeof("f:img_01_25_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_26_222x112.jpg", sizeof("f:img_01_26_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_27_222x112.jpg", sizeof("f:img_01_27_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_28_222x112.jpg", sizeof("f:img_01_28_222x112.jpg"));
            gt_player_add_item(obj, "f:img_01_29_t2_222x112.jpg", sizeof("f:img_01_29_t2_222x112.jpg"));
        }
        gt_player_add_item(obj, "f:img_01_30_222x112.jpg", sizeof("f:img_01_30_222x112.jpg"));
        gt_player_add_item(obj, "f:img_01_31_222x112.jpg", sizeof("f:img_01_31_222x112.jpg"));
        gt_player_add_item(obj, "f:img_01_32_222x112.jpg", sizeof("f:img_01_32_222x112.jpg"));
        gt_player_add_item(obj, "f:img_01_33_222x112.jpg", sizeof("f:img_01_33_222x112.jpg"));
        gt_player_add_item(obj, "f:img_01_34_222x112.jpg", sizeof("f:img_01_34_222x112.jpg"));
        gt_player_add_item(obj, "f:img_01_35_222x112.jpg", sizeof("f:img_01_35_222x112.jpg"));
        gt_player_add_item(obj, "f:img_01_36_222x112.jpg", sizeof("f:img_01_36_222x112.jpg"));
        set_player_many_times(obj, "f:img_01_37_6_222x112.jpg", sizeof("f:img_01_37_6_222x112.jpg"), 6);
        gt_player_add_item(obj, "f:img_01_43_222x112.jpg", sizeof("f:img_01_43_222x112.jpg"));
        gt_player_add_item(obj, "f:img_01_44_222x112.jpg", sizeof("f:img_01_44_222x112.jpg"));
        gt_player_add_item(obj, "f:img_01_45_222x112.jpg", sizeof("f:img_01_45_222x112.jpg"));
        gt_player_add_item(obj, "f:img_01_46_222x112.jpg", sizeof("f:img_01_46_222x112.jpg"));
        gt_player_add_item(obj, "f:img_01_47_222x112.jpg", sizeof("f:img_01_47_222x112.jpg"));
        gt_player_add_item(obj, "f:img_01_48_222x112.jpg", sizeof("f:img_01_48_222x112.jpg"));
        break;
    }
    case AI_EMOJIS_SPEAKING: {
        for (uint8_t i = 0; i < 2; i++)
        {
            set_player_many_times(obj, "f:img_08_07_6_228x116.jpg", sizeof("f:img_08_07_6_228x116.jpg"), 6);
            gt_player_add_item(obj, "f:img_08_08_228x116.jpg", sizeof("f:img_08_08_228x116.jpg"));
            gt_player_add_item(obj, "f:img_08_09_228x116.jpg", sizeof("f:img_08_09_228x116.jpg"));
            gt_player_add_item(obj, "f:img_08_10_228x116.jpg", sizeof("f:img_08_10_228x116.jpg"));
            gt_player_add_item(obj, "f:img_08_11_228x116.jpg", sizeof("f:img_08_11_228x116.jpg"));
            gt_player_add_item(obj, "f:img_08_12_228x116.jpg", sizeof("f:img_08_12_228x116.jpg"));
            gt_player_add_item(obj, "f:img_08_13_228x116.jpg", sizeof("f:img_08_13_228x116.jpg"));
            gt_player_add_item(obj, "f:img_08_14_228x116.jpg", sizeof("f:img_08_14_228x116.jpg"));
            gt_player_add_item(obj, "f:img_08_15_228x116.jpg", sizeof("f:img_08_15_228x116.jpg"));
            gt_player_add_item(obj, "f:img_08_16_228x116.jpg", sizeof("f:img_08_16_228x116.jpg"));
            gt_player_add_item(obj, "f:img_08_17_228x116.jpg", sizeof("f:img_08_17_228x116.jpg"));
            gt_player_add_item(obj, "f:img_08_18_228x116.jpg", sizeof("f:img_08_18_228x116.jpg"));
            gt_player_add_item(obj, "f:img_08_19_228x116.jpg", sizeof("f:img_08_19_228x116.jpg"));
            gt_player_add_item(obj, "f:img_08_20_t02_228x116.jpg", sizeof("f:img_08_20_t02_228x116.jpg"));

        }
        gt_player_add_item(obj, "f:img_08_21_228x116.jpg", sizeof("f:img_08_21_228x116.jpg"));
        gt_player_add_item(obj, "f:img_08_22_228x116.jpg", sizeof("f:img_08_22_228x116.jpg"));
        gt_player_add_item(obj, "f:img_08_23_228x116.jpg", sizeof("f:img_08_23_228x116.jpg"));
        gt_player_add_item(obj, "f:img_08_24_228x116.jpg", sizeof("f:img_08_24_228x116.jpg"));
        gt_player_add_item(obj, "f:img_08_25_228x116.jpg", sizeof("f:img_08_25_228x116.jpg"));
        gt_player_add_item(obj, "f:img_08_26_228x116.jpg", sizeof("f:img_08_26_228x116.jpg"));
        gt_player_add_item(obj, "f:img_08_27_228x116.jpg", sizeof("f:img_08_27_228x116.jpg"));
        gt_player_add_item(obj, "f:img_08_28_228x116.jpg", sizeof("f:img_08_28_228x116.jpg"));
        gt_player_add_item(obj, "f:img_08_29_228x116.jpg", sizeof("f:img_08_29_228x116.jpg"));
        gt_player_add_item(obj, "f:img_08_30_228x116.jpg", sizeof("f:img_08_30_228x116.jpg"));
        gt_player_add_item(obj, "f:img_08_31_228x116.jpg", sizeof("f:img_08_31_228x116.jpg"));
        gt_player_add_item(obj, "f:img_08_32_228x116.jpg", sizeof("f:img_08_32_228x116.jpg"));
        gt_player_add_item(obj, "f:img_08_33_228x116.jpg", sizeof("f:img_08_33_228x116.jpg"));
        gt_player_add_item(obj, "f:img_08_34_228x116.jpg", sizeof("f:img_08_34_228x116.jpg"));
        gt_player_add_item(obj, "f:img_08_35_228x116.jpg", sizeof("f:img_08_35_228x116.jpg"));
        gt_player_add_item(obj, "f:img_08_36_228x116.jpg", sizeof("f:img_08_36_228x116.jpg"));
        break;
    }
    case AI_EMOJIS_SYMPATHY: {
        for (uint8_t i = 0; i < 2; i++)
        {
            gt_player_add_item(obj, "f:img_02_01_2_225x116.jpg", sizeof("f:img_02_01_2_225x116.jpg"));
            gt_player_add_item(obj, "f:img_02_02_225x116.jpg", sizeof("f:img_02_02_225x116.jpg"));
            gt_player_add_item(obj, "f:img_02_03_225x116.jpg", sizeof("f:img_02_03_225x116.jpg"));
            gt_player_add_item(obj, "f:img_02_04_225x116.jpg", sizeof("f:img_02_04_225x116.jpg"));
            gt_player_add_item(obj, "f:img_02_05_225x116.jpg", sizeof("f:img_02_05_225x116.jpg"));
            gt_player_add_item(obj, "f:img_02_06_225x116.jpg", sizeof("f:img_02_06_225x116.jpg"));
            gt_player_add_item(obj, "f:img_02_07_225x116.jpg", sizeof("f:img_02_07_225x116.jpg"));
            gt_player_add_item(obj, "f:img_02_08_225x116.jpg", sizeof("f:img_02_08_225x116.jpg"));
            gt_player_add_item(obj, "f:img_02_09_225x116.jpg", sizeof("f:img_02_09_225x116.jpg"));
            gt_player_add_item(obj, "f:img_02_10_225x116.jpg", sizeof("f:img_02_10_225x116.jpg"));
            gt_player_add_item(obj, "f:img_02_11_225x116.jpg", sizeof("f:img_02_11_225x116.jpg"));
            gt_player_add_item(obj, "f:img_02_12_225x116.jpg", sizeof("f:img_02_12_225x116.jpg"));
            gt_player_add_item(obj, "f:img_02_13_225x116.jpg", sizeof("f:img_02_13_225x116.jpg"));
            gt_player_add_item(obj, "f:img_02_14_225x116.jpg", sizeof("f:img_02_14_225x116.jpg"));
            gt_player_add_item(obj, "f:img_02_15_225x116.jpg", sizeof("f:img_02_15_225x116.jpg"));
            if (i == 0)
            {
                set_player_many_times(obj, "f:img_02_16_225x116.jpg", sizeof("f:img_02_16_225x116.jpg"), 3);
            }else {
                set_player_many_times(obj, "f:img_02_16_225x116.jpg", sizeof("f:img_02_16_225x116.jpg"), 10);
            }
        }
        break;
    }
    case AI_EMOJIS_ENCOURAGE: {
        for (uint8_t i = 0; i < 3; i++)
        {
            set_player_many_times(obj, "f:img_04_09_10_228x117.jpg", sizeof("f:img_04_09_10_228x117.jpg"), 10);
            gt_player_add_item(obj, "f:img_04_10_228x117.jpg", sizeof("f:img_04_10_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_11_228x117.jpg", sizeof("f:img_04_11_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_12_228x117.jpg", sizeof("f:img_04_12_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_13_228x117.jpg", sizeof("f:img_04_13_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_14_228x117.jpg", sizeof("f:img_04_14_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_15_228x117.jpg", sizeof("f:img_04_15_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_16_228x117.jpg", sizeof("f:img_04_16_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_17_228x117.jpg", sizeof("f:img_04_17_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_18_228x117.jpg", sizeof("f:img_04_18_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_19_228x117.jpg", sizeof("f:img_04_19_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_20_228x117.jpg", sizeof("f:img_04_20_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_21_228x117.jpg", sizeof("f:img_04_21_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_22_228x117.jpg", sizeof("f:img_04_22_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_23_228x117.jpg", sizeof("f:img_04_23_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_24_228x117.jpg", sizeof("f:img_04_24_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_25_228x117.jpg", sizeof("f:img_04_25_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_26_228x117.jpg", sizeof("f:img_04_26_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_27_228x117.jpg", sizeof("f:img_04_27_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_28_228x117.jpg", sizeof("f:img_04_28_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_29_228x117.jpg", sizeof("f:img_04_29_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_30_228x117.jpg", sizeof("f:img_04_30_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_31_228x117.jpg", sizeof("f:img_04_31_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_32_228x117.jpg", sizeof("f:img_04_32_228x117.jpg"));
            gt_player_add_item(obj, "f:img_04_33_228x117.jpg", sizeof("f:img_04_33_228x117.jpg"));
            set_player_many_times(obj, "f:img_04_34_4_228x117.jpg", sizeof("f:img_04_34_4_228x117.jpg"), 4);
            set_player_many_times(obj, "f:img_04_38_9_228x117.jpg", sizeof("f:img_04_38_9_228x117.jpg"), 9);

        }
        break;
    }
    case AI_EMOJIS_HAPPY: {
        for (uint8_t i = 0; i < 2; i++)
        {
            if (i == 0)
            {
                set_player_many_times(obj, "f:img_03_06_6_225x116.jpg", sizeof("f:img_03_06_6_225x116.jpg"), 6);
            }else {
                set_player_many_times(obj, "f:img_03_06_6_225x116.jpg", sizeof("f:img_03_06_6_225x116.jpg"), 4);
            }
            gt_player_add_item(obj, "f:img_03_07_225x116.jpg", sizeof("f:img_03_07_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_08_225x116.jpg", sizeof("f:img_03_08_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_09_225x116.jpg", sizeof("f:img_03_09_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_10_225x116.jpg", sizeof("f:img_03_10_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_11_225x116.jpg", sizeof("f:img_03_11_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_12_225x116.jpg", sizeof("f:img_03_12_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_13_225x116.jpg", sizeof("f:img_03_13_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_14_225x116.jpg", sizeof("f:img_03_14_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_15_225x116.jpg", sizeof("f:img_03_15_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_16_225x116.jpg", sizeof("f:img_03_16_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_17_225x116.jpg", sizeof("f:img_03_17_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_18_225x116.jpg", sizeof("f:img_03_18_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_19_225x116.jpg", sizeof("f:img_03_19_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_20_225x116.jpg", sizeof("f:img_03_20_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_21_225x116.jpg", sizeof("f:img_03_21_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_22_225x116.jpg", sizeof("f:img_03_22_225x116.jpg"));
            gt_player_add_item(obj, "f:img_03_23_225x116.jpg", sizeof("f:img_03_23_225x116.jpg"));
            if (i == 0)
            {
                set_player_many_times(obj, "f:img_03_24_7_225x116.jpg", sizeof("f:img_03_24_7_225x116.jpg"), 7);
            }else {
                set_player_many_times(obj, "f:img_03_24_7_225x116.jpg", sizeof("f:img_03_24_7_225x116.jpg"), 12);
            }
        }
        break;
    }
    case AI_ANIM_AUDIO: {
        gt_player_add_item(obj, "f:img_09_00_80x30.png", sizeof("f:img_09_00_80x30.png"));
        gt_player_add_item(obj, "f:img_09_01_80x30.png", sizeof("f:img_09_01_80x30.png"));
        gt_player_add_item(obj, "f:img_09_02_80x30.png", sizeof("f:img_09_02_80x30.png"));
        gt_player_add_item(obj, "f:img_09_03_80x30.png", sizeof("f:img_09_03_80x30.png"));
        gt_player_add_item(obj, "f:img_09_04_80x30.png", sizeof("f:img_09_04_80x30.png"));
        gt_player_add_item(obj, "f:img_09_05_80x30.png", sizeof("f:img_09_05_80x30.png"));
        gt_player_add_item(obj, "f:img_09_06_80x30.png", sizeof("f:img_09_06_80x30.png"));
        gt_player_add_item(obj, "f:img_09_07_80x30.png", sizeof("f:img_09_07_80x30.png"));
        gt_player_add_item(obj, "f:img_09_08_80x30.png", sizeof("f:img_09_08_80x30.png"));
        gt_player_add_item(obj, "f:img_09_09_80x30.png", sizeof("f:img_09_09_80x30.png"));
        gt_player_add_item(obj, "f:img_09_10_80x30.png", sizeof("f:img_09_10_80x30.png"));
        gt_player_add_item(obj, "f:img_09_11_80x30.png", sizeof("f:img_09_11_80x30.png"));
        gt_player_add_item(obj, "f:img_09_12_80x30.png", sizeof("f:img_09_12_80x30.png"));
        gt_player_add_item(obj, "f:img_09_13_80x30.png", sizeof("f:img_09_13_80x30.png"));
        gt_player_add_item(obj, "f:img_09_14_80x30.png", sizeof("f:img_09_14_80x30.png"));
        gt_player_add_item(obj, "f:img_09_15_80x30.png", sizeof("f:img_09_15_80x30.png"));
        gt_player_add_item(obj, "f:img_09_16_80x30.png", sizeof("f:img_09_16_80x30.png"));
        gt_player_add_item(obj, "f:img_09_17_80x30.png", sizeof("f:img_09_17_80x30.png"));
        gt_player_add_item(obj, "f:img_09_18_80x30.png", sizeof("f:img_09_18_80x30.png"));
        gt_player_add_item(obj, "f:img_09_19_80x30.png", sizeof("f:img_09_19_80x30.png"));
        break;
    }
    case AI_ANIM_SMILE: {
        gt_player_add_item(obj, "f:img_05_00_60x21.png", sizeof("f:img_05_00_60x21.png"));
        gt_player_add_item(obj, "f:img_05_01_60x21.png", sizeof("f:img_05_01_60x21.png"));
        gt_player_add_item(obj, "f:img_05_02_60x21.png", sizeof("f:img_05_02_60x21.png"));
        gt_player_add_item(obj, "f:img_05_03_60x21.png", sizeof("f:img_05_03_60x21.png"));
        gt_player_add_item(obj, "f:img_05_04_60x21.png", sizeof("f:img_05_04_60x21.png"));
        gt_player_add_item(obj, "f:img_05_05_60x21.png", sizeof("f:img_05_05_60x21.png"));
        gt_player_add_item(obj, "f:img_05_06_60x21.png", sizeof("f:img_05_06_60x21.png"));
        gt_player_add_item(obj, "f:img_05_07_60x21.png", sizeof("f:img_05_07_60x21.png"));
        gt_player_add_item(obj, "f:img_05_08_60x21.png", sizeof("f:img_05_08_60x21.png"));
        gt_player_add_item(obj, "f:img_05_09_60x21.png", sizeof("f:img_05_09_60x21.png"));
        gt_player_add_item(obj, "f:img_05_10_60x21.png", sizeof("f:img_05_10_60x21.png"));
        gt_player_add_item(obj, "f:img_05_11_60x21.png", sizeof("f:img_05_11_60x21.png"));
        gt_player_add_item(obj, "f:img_05_12_60x21.png", sizeof("f:img_05_12_60x21.png"));
        gt_player_add_item(obj, "f:img_05_13_60x21.png", sizeof("f:img_05_13_60x21.png"));
        gt_player_add_item(obj, "f:img_05_14_60x21.png", sizeof("f:img_05_14_60x21.png"));
        gt_player_add_item(obj, "f:img_05_15_60x21.png", sizeof("f:img_05_15_60x21.png"));
        gt_player_add_item(obj, "f:img_05_16_60x21.png", sizeof("f:img_05_16_60x21.png"));
        gt_player_add_item(obj, "f:img_05_17_60x21.png", sizeof("f:img_05_17_60x21.png"));
        gt_player_add_item(obj, "f:img_05_18_60x21.png", sizeof("f:img_05_18_60x21.png"));
        gt_player_add_item(obj, "f:img_05_19_60x21.png", sizeof("f:img_05_19_60x21.png"));
        gt_player_add_item(obj, "f:img_05_20_60x21.png", sizeof("f:img_05_20_60x21.png"));
        gt_player_add_item(obj, "f:img_05_21_60x21.png", sizeof("f:img_05_21_60x21.png"));
        gt_player_add_item(obj, "f:img_05_22_60x21.png", sizeof("f:img_05_22_60x21.png"));
        gt_player_add_item(obj, "f:img_05_23_60x21.png", sizeof("f:img_05_23_60x21.png"));
        break;
    }
    default:
        break;
    }
    gt_player_play(obj);
}

void add_items_to_listview(gt_obj_st * obj, const char* items[], size_t item_count) {
    for (size_t i = 0; i < item_count; i++) {
        gt_listview_add_item(obj, items[i]);
    }
}

void set_items_in_listview(gt_obj_st * obj, gt_ai_setting_et option) {
    gt_listview_clear_all_items(obj);
    switch (option) {
    case AI_SETTING_AGE: {
        add_items_to_listview(obj, age_items, sizeof(age_items) / sizeof(age_items[0]));
        break;
    }
    case AI_SETTING_ROLE: {
        add_items_to_listview(obj, role_items, sizeof(role_items) / sizeof(role_items[0]));
        break;
    }
    case AI_SETTING_CHAR: {
        add_items_to_listview(obj, char_items, sizeof(char_items) / sizeof(char_items[0]));
        break;
    }
    case AI_SETTING_TIMBRE: {
        add_items_to_listview(obj, timbre_items, sizeof(timbre_items) / sizeof(timbre_items[0]));
        break;
    }
    case AI_SETTING_AI_NAME: {
        add_items_to_listview(obj, ai_name_items, sizeof(ai_name_items) / sizeof(ai_name_items[0]));
        break;
    }
    default:
        break;
    }
}

char* gt_vocie_id_string_get(char *timbre)
{
    int i = 0, len = sizeof(timbre_items) / sizeof(timbre_items[0]);
    for(i = 0; i < len; i++) {
        if (strcmp(timbre, timbre_items[i]) == 0) {
            return (char*)voice_id_items[i];
        }
    }
    return (char*)voice_id_items[0];
}

char* gt_timber_string_get(char *voice_id)
{
    int i = 0, len = sizeof(voice_id_items) / sizeof(voice_id_items[0]);
    for(i = 0; i < len; i++) {
        if (strcmp(voice_id_items[i], voice_id) == 0) {
            return (char*)timbre_items[i];
        }
    }
    return (char*)timbre_items[0];

}

