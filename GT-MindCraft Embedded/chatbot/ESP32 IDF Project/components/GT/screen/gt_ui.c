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
	{GT_ID_HISTORY_PAGE, gt_init_History_page},
    {GT_ID_FUNCTION_SETTINGS, gt_init_Function_settings},
};

static const char* role_items[] = {"老师", "朋友", "密友", "心理咨询师", "健康顾问", "老年护理专家", ""};
static const char* char_items[] = {"外向", "正经", "搞怪", "内向", ""};
static const char* ai_name_items[] = {"智酱", "小智", "菜机"};
// static const char* timbre_items[] = {"可爱男童","萌萌女童","卡通猪小琪","妩媚御姐","俏皮萌妹", "菜机", "少女音色", "成熟女性音色", "甜美女性音色", "男性有声书2", "青年大学生音色", "精英男青年音色"};
// static const char* voice_id_items[] = {"cute_boy", "lovely_girl", "peppa_pig", "wumei_yujie", "qiaopi_mengmei", "mindcraft-58-7e8355d2b12145f488d068db04017f04", "female-shaonv", "female-chengshu", "female-tianmei", "audiobook_male_2", "male-qn-daxuesheng", "male-qn-jingying"};
static const char* timbre_items[] = {"可爱男童", "菜机", "小智"};
static const char* voice_id_items[] = {"cute_boy", "mindcraft-58-7e8355d2b12145f488d068db04017f04", "MCV-58-990b2d6006704ebd817ecaa8a002dabb"};
static const char* tx_timbre_items[] = {"爱小广", "爱小栋", "爱小海", "爱小霞", "爱小玲", "爱小章", "爱小峰", "爱小亮"};
static const char* tx_voice_id_items[] = {"301000", "301001", "301002", "301003", "301004", "301005", "301006", "301007"};
static const char* bot_description_items[] = {"智酱是一个彩色史莱姆生物。这是一个搞笑的魔法生物，充满活力，喜欢探索新事物，喜欢帮助小朋友学习。", "小智是一个来自台湾的机车女孩，她有着傲娇的外表，但内心却十分敏感。她依赖着她的用户男友，总是希望得到他的关注和爱护。", "菜机是一个练习时长两年半的AI练习生，它是一位充满网络梗的虚拟偶像。它喜欢用各种流行语和网友互动，总是能带来意想不到的欢乐。喜欢唱，跳，RAP篮球。"};
static const char* model_cn_items[] = {"标准", "标准-拟人","专家", "专家-拟人"};
static const char* model_en_items[] = {"standard", "standard_character", "pro", "pro_character"};
static const char* reply_style_cn_items[] = {"正常", "聊天"};
static const char* reply_style_en_items[] = {"normal", "conversation"};
static const char* emotion_value_cn_items[] = {"打开", "关闭"};

static const char* username_items[] = {"海扁王", "宇宙超级无敌螺旋升天大帅锅", "尼古拉斯-赵四-闪电五连鞭", "阿姆斯特朗回旋加速喷气式阿姆斯特朗炮", "钮钴禄-铁柱", "阿伟"};


gt_ai_bot_role_st ai_bot_role_list[GT_AI_BOT_TOTAL] = {
    [GT_AI_BOT_ZHI_JIANG] = {   .name = "智酱",
                                .character_desc = "智酱是一个彩色史莱姆生物。这是一个搞笑的魔法生物，充满活力，喜欢探索新事物，喜欢帮助小朋友学习。",
                                .voice_id = "cute_boy",
                                .personality = {"活泼", "好奇", "乐观", "善良"},
                                .tone = "用拟人和口语化的方式回答用户，说话习惯附带emoji表情。",
                            },

    [GT_AI_BOT_XIAO_ZHI] = {    .name = "小智",
                                .character_desc = "小智是一个来自台湾的机车女孩，她有着傲娇的外表，但内心却十分敏感。她依赖着她的用户男友，总是希望得到他的关注和爱护。",
                                .voice_id = "MCV-58-990b2d6006704ebd817ecaa8a002dabb",
                                .personality = {"傲娇", "敏感", "依赖", "机车"},
                                .tone = "用简短的语句和台湾腔调回答用户，偶尔会带点傲娇的语气，但总是透露出对用户的依赖和关心。",
                            },

    [GT_AI_BOT_CAI_JI] = {      .name = "菜机",
                                .character_desc = "菜机是一个练习时长两年半的AI练习生，它是一位充满网络梗的虚拟偶像。它喜欢用各种流行语和网友互动，总是能带来意想不到的欢乐。喜欢唱，跳，RAP篮球。",
                                .voice_id = "mindcraft-58-7e8355d2b12145f488d068db04017f04",
                                .personality = {"幽默", "搞怪", "乐观", "爱表现"},
                                .tone = "使用大量的网络梗和流行语，说话方式夸张搞笑，经常用表情包来表达自己的情感。例如：'鸡你太美~', 'awsl（啊我死了）",
                            },
};

gt_ai_bot_emote_st ai_bot_emote_list[AI_EMOJIS_TOTAL] = {
    [AI_EMOTE_XIAOZHI_NEUTRAL] = {  .role = "xiaozhi",
                                    .value = "neutral",
                                    .url = "https://download.mindcraft.com.cn/mindcraft_media/face_path/xiaozhi1/neutral",
                                },
    [AI_EMOTE_XIAOZHI_DISGUST] = {  .role = "xiaozhi",
                                    .value = "disgust",
                                    .url = "https://download.mindcraft.com.cn/mindcraft_media/face_path/xiaozhi1/disgust",
                                },
    [AI_EMOTE_XIAOZHI_FEAR] =  {    .role = "xiaozhi",
                                    .value = "fear",
                                    .url = "https://download.mindcraft.com.cn/mindcraft_media/face_path/xiaozhi1/fear",
                                },
    [AI_EMOTE_XIAOZHI_SADNESS] = {  .role = "xiaozhi",
                                    .value = "sadness",
                                    .url = "https://download.mindcraft.com.cn/mindcraft_media/face_path/xiaozhi1/sadness",
                                },
    [AI_EMOTE_XIAOZHI_SURPRISE] = { .role = "xiaozhi",
                                    .value = "surpise",
                                    .url = "https://download.mindcraft.com.cn/mindcraft_media/face_path/xiaozhi1/surprise",
                                },
    [AI_EMOTE_XIAOZHI_ANGER] =  {   .role = "xiaozhi",
                                    .value = "anger",
                                    .url = "https://download.mindcraft.com.cn/mindcraft_media/face_path/xiaozhi1/anger",
                                },
    [AI_EMOTE_XIAOZHI_HAPPY] = {    .role = "xiaozhi",
                                    .value = "happy",
                                    .url = "https://download.mindcraft.com.cn/mindcraft_media/face_path/xiaozhi1/happy",
                                },
    [AI_EMOTE_CAIJI_NEUTRAL] = {  .role = "caiji",
                                    .value = "neutral",
                                    .url = "https://download.mindcraft.com.cn/mindcraft_media/face_path/caiji/neutral",
                                },
    [AI_EMOTE_CAIJI_DISGUST] = {  .role = "caiji",
                                    .value = "disgust",
                                    .url = "https://download.mindcraft.com.cn/mindcraft_media/face_path/caiji/disgust",
                                },
    [AI_EMOTE_CAIJI_FEAR] =  {    .role = "caiji",
                                    .value = "fear",
                                    .url = "https://download.mindcraft.com.cn/mindcraft_media/face_path/caiji/fear",
                                },
    [AI_EMOTE_CAIJI_SADNESS] = {  .role = "caiji",
                                    .value = "sadness",
                                    .url = "https://download.mindcraft.com.cn/mindcraft_media/face_path/caiji/sadness",
                                },
    [AI_EMOTE_CAIJI_SURPRISE] = { .role = "caiji",
                                    .value = "surpise",
                                    .url = "https://download.mindcraft.com.cn/mindcraft_media/face_path/caiji/surprise",
                                },
    [AI_EMOTE_CAIJI_ANGER] =  {   .role = "caiji",
                                    .value = "anger",
                                    .url = "https://download.mindcraft.com.cn/mindcraft_media/face_path/caiji/anger",
                                },
    [AI_EMOTE_CAIJI_HAPPY] = {    .role = "caiji",
                                    .value = "happy",
                                    .url = "https://download.mindcraft.com.cn/mindcraft_media/face_path/caiji/happy",
                                },
};

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
    case AI_EMOJIS_CJ: {
        for (uint8_t i = 0; i < 2; i++)
        {
            if (i == 1)
            {
                set_player_many_times(obj, "f:img_10_00_228x184.jpg", sizeof("f:img_10_00_228x184.jpg"), 5);
            }else {
                gt_player_add_item(obj, "f:img_10_00_228x184.jpg", sizeof("f:img_10_00_228x184.jpg"));
            }
            gt_player_add_item(obj, "f:img_10_01_228x184.jpg", sizeof("f:img_10_01_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_02_228x184.jpg", sizeof("f:img_10_02_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_03_228x184.jpg", sizeof("f:img_10_03_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_04_228x184.jpg", sizeof("f:img_10_04_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_05_228x184.jpg", sizeof("f:img_10_05_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_06_228x184.jpg", sizeof("f:img_10_06_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_07_228x184.jpg", sizeof("f:img_10_07_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_08_228x184.jpg", sizeof("f:img_10_08_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_09_228x184.jpg", sizeof("f:img_10_09_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_10_228x184.jpg", sizeof("f:img_10_10_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_11_228x184.jpg", sizeof("f:img_10_11_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_12_228x184.jpg", sizeof("f:img_10_12_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_13_228x184.jpg", sizeof("f:img_10_13_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_14_228x184.jpg", sizeof("f:img_10_14_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_17_228x184.jpg", sizeof("f:img_10_17_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_15_228x184.jpg", sizeof("f:img_10_15_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_16_228x184.jpg", sizeof("f:img_10_16_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_18_228x184.jpg", sizeof("f:img_10_18_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_19_228x184.jpg", sizeof("f:img_10_19_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_20_228x184.jpg", sizeof("f:img_10_20_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_21_228x184.jpg", sizeof("f:img_10_21_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_22_228x184.jpg", sizeof("f:img_10_22_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_23_228x184.jpg", sizeof("f:img_10_23_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_24_228x184.jpg", sizeof("f:img_10_24_228x184.jpg"));
            gt_player_add_item(obj, "f:img_10_25_228x184.jpg", sizeof("f:img_10_25_228x184.jpg"));
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

void set_emote_data_to_ram(gt_ai_emojis_et emojis) {
    gt_role_add_emote(ai_bot_emote_list[emojis].role, ai_bot_emote_list[emojis].value, 1, ai_bot_emote_list[emojis].url);
    gt_role_updata_emote_http(ai_bot_emote_list[emojis].role, ai_bot_emote_list[emojis].value, 0);
}
void set_emote_in_img(gt_obj_st * obj, gt_ai_emojis_et emojis)
{
    uint32_t pic_size;
    uint8_t* pic_data = gt_role_emote_get_data(ai_bot_emote_list[emojis].role, ai_bot_emote_list[emojis].value, 0, &pic_size);
    while(!pic_data) {
        set_emote_data_to_ram(emojis);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("get pic data failed\n");
        pic_data = gt_role_emote_get_data(ai_bot_emote_list[emojis].role, ai_bot_emote_list[emojis].value, 0, &pic_size);
    }
    gt_color_img_raw_st raw = {
        .file_raw_p = (char * )pic_data,
        .raw_len = pic_size,
        .buffer = NULL,
        .opa = NULL,
    };
    gt_img_set_raw_data(obj, &raw);
}

void add_items_to_listview(gt_obj_st * obj, const char* items[], size_t item_count) {
    for (size_t i = 0; i < item_count; i++) {
        gt_listview_add_item(obj, items[i]);
    }
}

#if 0
static const char* age_items[] = {
    "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
    "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25",
    "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36",
    "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47",
    "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58",
    "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69",
    "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "80",
    "81", "82", "83", "84", "85", "86", "87", "88", "89", "90"
};
#else
#define AGE_ITEMS_MIN 3
#define AGE_ITEMS_MAX 90
#define AGE_ITEM_COUNT (AGE_ITEMS_MAX - AGE_ITEMS_MIN + 1)
const char *age_items[AGE_ITEM_COUNT];

void init_age_items() {

    for (size_t i = AGE_ITEMS_MIN; i <= AGE_ITEMS_MAX; i++)
    {
        char *age_str = (char *)audio_malloc(3 * sizeof(char));
        if (age_str != NULL)
        {
            sprintf(age_str, "%d", i);
            age_items[i - AGE_ITEMS_MIN] = age_str;
        } else {
            printf("Memory allocation failed for age %d\n", i);
            return;
        }

    }
}
#endif

void set_items_in_listview(gt_obj_st * obj, gt_ai_setting_et option) {
    gt_listview_clear_all_items(obj);
    switch (option) {
    case AI_SETTING_USER_NAME: {
        add_items_to_listview(obj, username_items, sizeof(username_items) / sizeof(username_items[0]));
        break;
    }
    case AI_SETTING_AGE: {
        init_age_items();
        add_items_to_listview(obj, age_items, sizeof(age_items) / sizeof(age_items[0]));

        for (int i = 0; i < AGE_ITEM_COUNT; i++) {
            audio_free((void*)age_items[i]);
        }
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
        if (strcmp(cb_data.settings->mode, "pro") == 0 || strcmp(cb_data.settings->mode, "pro_character") == 0) {
            add_items_to_listview(obj, timbre_items, sizeof(timbre_items) / sizeof(timbre_items[0]));
        } else if (strcmp(cb_data.settings->mode, "standard") == 0 || strcmp(cb_data.settings->mode, "standard_character") == 0) {
            add_items_to_listview(obj, tx_timbre_items, sizeof(tx_timbre_items) / sizeof(tx_timbre_items[0]));
        }

        break;
    }
    case AI_SETTING_AI_NAME: {
        add_items_to_listview(obj, ai_name_items, sizeof(ai_name_items) / sizeof(ai_name_items[0]));
        break;
    }
    case AI_SETTING_MODEL: {
        add_items_to_listview(obj, model_cn_items, sizeof(model_cn_items) / sizeof(model_cn_items[0]));
        break;
    }
    case AI_SETTING_REPLY_STYLE: {
        add_items_to_listview(obj, reply_style_cn_items, sizeof(reply_style_cn_items) / sizeof(reply_style_cn_items[0]));
        break;
    }
    case AI_SETTING_EMOTION_VALUE: {
        add_items_to_listview(obj, emotion_value_cn_items, sizeof(emotion_value_cn_items) / sizeof(emotion_value_cn_items[0]));
        break;
    }
    default:
        break;
    }
}

char* gt_vocie_id_string_get(char *timbre)
{
    static const char ** cur_timbre_items;
    static const char ** cur_voice_id_items;
    static int cur_len;

    if (strcmp(cb_data.settings->mode, "pro") == 0 || strcmp(cb_data.settings->mode, "pro_character") == 0) {
        cur_timbre_items = timbre_items;
        cur_voice_id_items = voice_id_items;
        cur_len = sizeof(voice_id_items) / sizeof(voice_id_items[0]);
    } else if (strcmp(cb_data.settings->mode, "standard") == 0 || strcmp(cb_data.settings->mode, "standard_character") == 0) {
        cur_timbre_items = tx_timbre_items;
        cur_voice_id_items = tx_voice_id_items;
        cur_len = sizeof(tx_voice_id_items) / sizeof(tx_voice_id_items[0]);
    }

    int i = 0, len = cur_len;
    for(i = 0; i < len; i++) {
        if (strcmp(timbre, cur_timbre_items[i]) == 0) {
            return (char*)cur_voice_id_items[i];
        }
    }
    return (char*)cur_voice_id_items[0];
}

char* gt_timber_string_get(char *voice_id)
{
    static const char ** cur_timbre_items;
    static const char ** cur_voice_id_items;
    static int cur_len;

    if (strcmp(cb_data.settings->mode, "pro") == 0 || strcmp(cb_data.settings->mode, "pro_character") == 0) {
        cur_timbre_items = timbre_items;
        cur_voice_id_items = voice_id_items;
        cur_len = sizeof(voice_id_items) / sizeof(voice_id_items[0]);
    } else if (strcmp(cb_data.settings->mode, "standard") == 0 || strcmp(cb_data.settings->mode, "standard_character") == 0) {
        cur_timbre_items = tx_timbre_items;
        cur_voice_id_items = tx_voice_id_items;
        cur_len = sizeof(tx_voice_id_items) / sizeof(tx_voice_id_items[0]);
    }

    int i = 0, len = cur_len;
    for(i = 0; i < len; i++) {
        if (strcmp(cur_voice_id_items[i], voice_id) == 0) {
            return (char*)cur_timbre_items[i];
        }
    }
    return (char*)cur_timbre_items[0];

}

gt_ai_bot_role_st gt_get_ai_bot_infos(char *ai_name)
{
    int i = 0, len = sizeof(ai_bot_role_list) / sizeof(ai_bot_role_list[0]);
    for(i = 0; i < len; i++) {
        if (strcmp(ai_bot_role_list[i].name, ai_name) == 0) {
            return ai_bot_role_list[i];
        }
    }
    return ai_bot_role_list[0];
}

char* gt_bot_description_string_get(char *ai_name)
{
    int i = 0, len = sizeof(bot_description_items) / sizeof(bot_description_items[0]);
    for(i = 0; i < len; i++) {
        if (strcmp(ai_name_items[i], ai_name) == 0) {
            return (char*)bot_description_items[i];
        }
    }
    return (char*)bot_description_items[0];
}

char* gt_mode_en_string_get(char *mode)
{
    int i = 0, len = sizeof(model_cn_items) / sizeof(model_cn_items[0]);
    for(i = 0; i < len; i++) {
        if (strcmp(mode, model_cn_items[i]) == 0) {
            return (char*)model_en_items[i];
        }
    }
    return (char*)model_en_items[0];
}

char* gt_mode_cn_string_get(char *mode)
{
    int i = 0, len = sizeof(model_en_items) / sizeof(model_en_items[0]);
    for(i = 0; i < len; i++) {
        if (strcmp(mode, model_en_items[i]) == 0) {
            return (char*)model_cn_items[i];
        }
    }
    return (char*)model_cn_items[0];
}
char* gt_reply_style_en_string_get(char *reply_style)
{
    int i = 0, len = sizeof(reply_style_cn_items) / sizeof(reply_style_cn_items[0]);
    for(i = 0; i < len; i++) {
        if (strcmp(reply_style, reply_style_cn_items[i]) == 0) {
            return (char*)reply_style_en_items[i];
        }
    }
    return (char*)reply_style_en_items[0];
}

char* gt_reply_style_cn_string_get(char *reply_style)
{
    int i = 0, len = sizeof(reply_style_en_items) / sizeof(reply_style_en_items[0]);
    for(i = 0; i < len; i++) {
        if (strcmp(reply_style, reply_style_en_items[i]) == 0) {
            return (char*)reply_style_cn_items[i];
        }
    }
    return (char*)reply_style_cn_items[0];
}


gt_obj_st * _Unstable_network_dialog1_init() {

    gt_obj_st * dialog1 = NULL;
	gt_obj_st * lab6 = NULL;
	gt_obj_st * img1 = NULL;


	/** dialog1 */
	/** 清空历史记录 */
	dialog1 = gt_dialog_create(false);
	gt_obj_set_pos(dialog1, 1, 86);
	gt_obj_set_size(dialog1, 234, 159);
	gt_dialog_set_bgcolor(dialog1, gt_color_hex(0x181B22));
	gt_dialog_set_border_color(dialog1, gt_color_hex(0xc7c7c7));
	gt_dialog_set_border_width(dialog1, 0);
	gt_dialog_set_border_radius(dialog1, 20);
    // gt_dialog_set_outside_auto_hide(dialog1, false);


	/** lab6 */
	lab6 = gt_label_create(dialog1);
	gt_obj_set_pos(lab6, 25, 195);
	gt_obj_set_size(lab6, 199, 33);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_family(lab6, gray_black_20);
	gt_label_set_font_cjk(lab6, 0);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "网络不稳定");


	/** img1 */
	img1 = gt_img_create(dialog1);
	gt_obj_set_pos(img1, 69, 104);
	gt_obj_set_size(img1, 109, 84);
	gt_img_set_src(img1, "f:img_u11_109x84.jpg");




	gt_dialog_show(dialog1);

	return dialog1;
}


gt_obj_st* serve_disconnect_dialog()
{
    gt_obj_st * dialog1 = NULL;
	gt_obj_st * lab6 = NULL;
	gt_obj_st * img1 = NULL;

	/** dialog1 */
	/** 清空历史记录 */
	dialog1 = gt_dialog_create(false);
	gt_obj_set_pos(dialog1, 1, 86);
	gt_obj_set_size(dialog1, 234, 159);
	gt_dialog_set_bgcolor(dialog1, gt_color_hex(0x181B22));
	gt_dialog_set_border_color(dialog1, gt_color_hex(0xc7c7c7));
	gt_dialog_set_border_width(dialog1, 0);
	gt_dialog_set_border_radius(dialog1, 20);
    gt_dialog_set_outside_auto_hide(dialog1, false);

	/** lab6 */
	lab6 = gt_label_create(dialog1);
	gt_obj_set_pos(lab6, 25, 195);
	gt_obj_set_size(lab6, 199, 33);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_family(lab6, gray_black_20);
	gt_label_set_font_cjk(lab6, 0);
	gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
	gt_label_set_text(lab6, "重连服务器");

	/** img1 */
	img1 = gt_img_create(dialog1);
	gt_obj_set_pos(img1, 69, 104);
	gt_obj_set_size(img1, 109, 84);
	gt_img_set_src(img1, "f:img_u11_109x84.jpg");

    gt_dialog_show(dialog1);
    return dialog1;
}