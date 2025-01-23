#include "gt_ui.h"

static const char *TAG = "SCREEN_HOME";

static char *blue_tip[5] = {"松手发送，上移取消", "正在思考，请稍等", "识别失败，请重试", "WIFI连接中，请稍等", "WIFI连接失败"};

/** screen_home */
gt_obj_st * screen_home = NULL;
static gt_obj_st * stupbt = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * player_emojis = NULL;
static gt_obj_st * player_audio = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * Historybt = NULL;
static gt_obj_st * emptybt = NULL;

static gt_obj_st * dialog1 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * img1 = NULL;
static gt_obj_st * Cancel = NULL;
static gt_obj_st * Sure = NULL;
static gt_obj_st * img_emote = NULL;
static gt_obj_st * rect_b = NULL;


static void add_event_cb_for_imgbtn();

void set_role_emote(gt_obj_st * player, gt_obj_st * img, gt_ai_emojis_et zhijiang_emojis, gt_ai_emojis_et xiaozhi_emojis, gt_ai_emojis_et caiji_emojis) {
    if (strcmp(cb_data.settings->bot_name, "智酱") == 0)
    {
        gt_player_play(player);
        gt_obj_set_visible(img, GT_INVISIBLE);
        // set_emojis_in_player(player, AI_EMOJIS_RECORDING);
        set_emojis_in_player(player, zhijiang_emojis);
        gt_obj_set_visible(player, GT_VISIBLE);
        printf("11111111111111111111\n");
    } else if (strcmp(cb_data.settings->bot_name, "小智") == 0) {
        gt_player_stop(player);
        gt_obj_set_visible(player, GT_INVISIBLE);
        gt_obj_set_visible(img, GT_VISIBLE);
        // set_emote_in_img(img, AI_EMOTE_XIAOZHI_NEUTRAL);
        set_emote_in_img(img, xiaozhi_emojis);
    } else if (strcmp(cb_data.settings->bot_name, "菜机") == 0)
    {
        gt_player_stop(player);
        gt_obj_set_visible(player, GT_INVISIBLE);
        gt_obj_set_visible(img, GT_VISIBLE);
        // set_emote_in_img(img, AI_EMOTE_CAIJI_NEUTRAL);
        set_emote_in_img(img, caiji_emojis);
    }
}
/**
 * @brief 等待录音时的ui
 *
 */
void waiting_rec_ui() {
    gt_obj_set_visible(lab1, GT_VISIBLE);
    gt_obj_set_visible(lab2, GT_INVISIBLE);
    gt_obj_set_visible(rect_b, GT_INVISIBLE);
    gt_obj_set_visible(player_audio, GT_INVISIBLE);
    gt_player_stop(player_audio);
    set_role_emote(player_emojis, img_emote, AI_EMOJIS_WAITING, AI_EMOTE_XIAOZHI_NEUTRAL, AI_EMOTE_CAIJI_NEUTRAL);

    add_event_cb_for_imgbtn();
    gt_disp_invalid_area(screen_home);
    ESP_LOGI(TAG, "-----------------------等待录音UI\n");
}

/**
 * @brief 正在录音时的ui
 *
 */
static void recording_ui() {
    gt_obj_set_visible(lab1, GT_INVISIBLE);
    gt_obj_set_visible(lab2, GT_VISIBLE);
    gt_label_set_text(lab2, blue_tip[0]);
    gt_obj_set_visible(rect_b, GT_VISIBLE);
	gt_label_set_font_color(lab2, gt_color_hex(0x5b8ad9));
	gt_obj_set_pos(player_audio, 85, 261);
    set_emojis_in_player(player_audio, AI_ANIM_AUDIO);
    gt_obj_set_visible(player_audio, GT_VISIBLE);
    gt_player_play(player_audio);
    set_role_emote(player_emojis, img_emote, AI_EMOJIS_RECORDING, AI_EMOTE_XIAOZHI_NEUTRAL, AI_EMOTE_CAIJI_NEUTRAL);
}

/**
 * @brief 等待回复时的ui
 *
 */
static void waiting_answer_ui() {
    gt_obj_set_visible(lab1, GT_INVISIBLE);
    gt_label_set_text(lab2, blue_tip[1]);
    gt_obj_set_visible(rect_b, GT_VISIBLE);
	gt_label_set_font_color(lab2, gt_color_hex(0x5b8ad9));
	gt_obj_set_pos(player_audio, 90, 264);
    set_emojis_in_player(player_audio, AI_ANIM_SMILE);
    set_role_emote(player_emojis, img_emote, AI_EMOJIS_HAPPY, AI_EMOTE_XIAOZHI_NEUTRAL, AI_EMOTE_CAIJI_NEUTRAL);

    gt_obj_remove_all_event_cb(imgbtn1);
}

/**
 * @brief 语音识别失败时的ui
 *
 */
void identification_failed_ui() {
    gt_obj_set_visible(lab1, GT_VISIBLE);
    gt_label_set_text(lab2, blue_tip[2]);
    gt_obj_set_visible(rect_b, GT_VISIBLE);
    gt_label_set_font_color(lab2, gt_color_hex(0xFF7859));
    gt_obj_set_visible(player_audio, GT_INVISIBLE);
    gt_player_stop(player_audio);
    set_role_emote(player_emojis, img_emote, AI_EMOJIS_SYMPATHY, AI_EMOTE_XIAOZHI_SADNESS, AI_EMOTE_CAIJI_SADNESS);

    add_event_cb_for_imgbtn();
}

/**
 * @brief wifi连接时的ui
 *
 */
void wifi_connecting_ui() {
    gt_obj_set_visible(lab1, GT_INVISIBLE);
    gt_obj_set_visible(lab2, GT_VISIBLE);
    gt_label_set_text(lab2, blue_tip[3]);
    gt_obj_set_visible(rect_b, GT_VISIBLE);
	gt_label_set_font_color(lab2, gt_color_hex(0x5b8ad9));
	gt_obj_set_pos(player_audio, 90, 264);
    set_emojis_in_player(player_audio, AI_ANIM_SMILE);
    gt_obj_set_visible(player_audio, GT_VISIBLE);
    set_emojis_in_player(player_emojis, AI_EMOJIS_HAPPY);

    gt_obj_remove_all_event_cb(imgbtn1);
    ESP_LOGI(TAG, "-----------------------wifi连接时的ui\n");

}

/**
 * @brief wifi链接失败时的ui
 *
 */
void wifi_connected_fail_ui() {
    gt_obj_set_visible(lab1, GT_VISIBLE);
    gt_obj_set_visible(lab2, GT_VISIBLE);
    gt_label_set_text(lab2, blue_tip[4]);
    gt_obj_set_visible(rect_b, GT_VISIBLE);
    gt_label_set_font_color(lab2, gt_color_hex(0xFF7859));
    gt_obj_set_visible(player_audio, GT_INVISIBLE);
    gt_player_stop(player_audio);
    set_emojis_in_player(player_emojis, AI_EMOJIS_SYMPATHY);

    gt_obj_remove_all_event_cb(imgbtn1);
    gt_disp_invalid_area(screen_home);
    ESP_LOGI(TAG, "-----------------------wifi链接失败时的ui\n");

}

static void img1_0_cb(gt_event_st * e) {
    gt_disp_stack_load_scr_anim(GT_ID_SCREEN_SETUP, GT_SCR_ANIM_TYPE_NONE, 500, 0, true);
}

void recording_exe_func(void) {
    // 停止播放器
    // gt_audio_player_stop();

    //step2:开始录音
#if (WEBSOCKET_HTTP_SWITCH == 0)//USE_HTTP_STREAM
    printf("get_pipe_send_api_key\r\n");
    get_pipe_send_api_key();
    gt_pipe_send_start();
#elif (WEBSOCKET_HTTP_SWITCH == 1)//!USE_HTTP_STREAM
    gt_recording_path_set("/sdcard/rec.wav");
    gt_recording_start();
#elif (WEBSOCKET_HTTP_SWITCH == 2)
    if(get_startListen() == true)
    {
        set_startListen(gt_pipeline_single(), false);
        free_chatbot_audio_uri();
        // gt_audio_pipeline_stop(gt_pipeline_single());
        ESP_LOGI(TAG, "gt_audio_player_stop !!!!!!!!!!!!!!!!!");
        gt_websocket_client_stop_receive_data();
    }
    gt_audio_pipeline_stop(gt_pipeline_single());

    set_isFirstAudiouri(true);
    gt_websocket_client_create_task();
    gt_audio_storage_start();
    // get_pcm_data(void);
    xTaskCreate(get_pcm_data, "get_pcm_data", 3*1024, NULL, 2, NULL);
#endif //!USE_HTTP_STREAM

    ESP_LOGI(TAG, "-----------------------按下执行结束\n");
}

//按下
static void recording_cb(gt_event_st * e) {
    //step1:切换正在录音时的ui
    recording_ui();
    recording_exe_func();
}
void send_information_exe_func(void) {
    //step2:结束录音
#if (WEBSOCKET_HTTP_SWITCH == 0)//USE_HTTP_STREAM
    gt_pipe_send_stop();
    set_ringbuf_done();
#elif (WEBSOCKET_HTTP_SWITCH == 1)//!USE_HTTP_STREAM
    gt_recording_stop();
#elif (WEBSOCKET_HTTP_SWITCH == 2)
    gt_websocket_client_stop_send_audio_data();
    // gt_record_pcm_stop();
    gt_audio_storage_stop();
#endif //!USE_HTTP_STREAM
    //step3:获取设置界面的参数以及语音数据，并发送请求到服务器
    //这里采用消息队列mYxQueue向http_test_task任务发送消息
    int msg = 1; // 发送一个整数作为信号
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xQueueSendFromISR(mYxQueue, &msg, &xHigherPriorityTaskWoken);

    ESP_LOGI(TAG, "-----------------------抬起执行结束\n");
}

//抬起
static void send_information_cb(gt_event_st * e) {
    //step1:切换等待回复时的ui
    waiting_answer_ui();
    // waiting_rec_ui();
    send_information_exe_func();
}

//焦点移开当前控件
static void cancel_recording_cb(gt_event_st * e) {
    //step1:切换等待录音时的ui
    waiting_rec_ui();

#if (WEBSOCKET_HTTP_SWITCH == 0)//USE_HTTP_STREAM
    gt_pipe_send_stop();
    set_ringbuf_done();
#elif (WEBSOCKET_HTTP_SWITCH == 1)//!USE_HTTP_STREAM
    //step2:结束录音，并删除SD卡中的录音文件
    gt_recording_stop();
    //删除SD卡中录音文件
    f_unlink("0:rec.wav");
#elif (WEBSOCKET_HTTP_SWITCH == 2)
    gt_websocket_client_stop_send_audio_data();
    gt_audio_storage_stop();
#endif //!USE_HTTP_STREAM

    ESP_LOGI(TAG, "-----------------------焦点移开当前控件\n");

}

static void add_event_cb_for_imgbtn() {
    gt_obj_add_event_cb(imgbtn1, recording_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
    gt_obj_add_event_cb(imgbtn1, send_information_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
    gt_obj_add_event_cb(imgbtn1, cancel_recording_cb, GT_EVENT_TYPE_INPUT_PRESS_LOST, NULL);
}

static void screen_home_0_cb(gt_event_st * e) {
    if(dialog1 != NULL)
    {
        gt_dialog_close(dialog1);
        dialog1 = NULL;
    }
	gt_disp_stack_go_back(1);
    update_wifi_icon();
}

static void Sure_0_cb(gt_event_st * e) {
    ESP_LOGI(TAG,"--------is_auto_connected_end = %d\n", is_auto_connected_end);
    if (!is_auto_connected_end)
    {
        ESP_LOGI(TAG,"wifi auto connection is not end\n");
        return;
    }

    if(dialog1 != NULL)
    {
        gt_dialog_close(dialog1);
        dialog1 = NULL;
    }

    wifi_scan();
	gt_disp_stack_load_scr_anim(GT_ID_WIFI_LIST, GT_SCR_ANIM_TYPE_NONE, 0, 0, true);

    wifi_ap_record_t ap_info;
    esp_err_t ret;
    ret = esp_wifi_sta_get_ap_info(&ap_info);
    if (ret == ESP_OK) {
        // primary：AP的主要信道号，1.primary=0:未连接到 AP; 2.primary!=0:已连接到 AP，信道号有效。通过检查 primary 字段判断是否已连接
        if (ap_info.primary != 0) {
            wifi_config_t last_wifi_config = get_current_wifi_config();
            if (check_cur_wifi_is_in_wifi_list((char *)last_wifi_config.sta.ssid, (char *)last_wifi_config.sta.password))
            {
                set_current_wifi_isConnected();
                redraw_wifi_list();
            }else {
                //TODO:如果在扫描列表中没有找到这个已经自动连接的wifi，就把它加到列表的第一个。这个未实现
            }

        }
    }
}

static void Historybt_0_cb(gt_event_st * e) {
    set_history_in_chat();
}

static void emptybt_0_cb(gt_event_st * e) {
    // clear_chat_history();
    _Clear_page_dialog1_init();
}

gt_obj_st * gt_init_screen_home(void)
{
    screen_home = gt_obj_create(NULL);
	gt_obj_add_event_cb(screen_home, screen_home_0_cb, GT_EVENT_TYPE_INPUT_HOME_GESTURE_LEFT, NULL);
    gt_screen_set_bgcolor(screen_home, gt_color_hex(0x000000));


    /** rect1 */
	gt_obj_st* rect1 = gt_rect_create(screen_home);
	gt_obj_set_pos(rect1, 180, 0);
	gt_obj_set_size(rect1, 60, 40);
	gt_obj_set_opa(rect1, GT_OPA_TRANSP);
	gt_obj_add_event_cb(rect1, img1_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);

	/** stupbt */
	/** 设置 */
	stupbt = gt_img_create(rect1);
	gt_obj_set_pos(stupbt, 183, 16);
	gt_obj_set_size(stupbt, 24, 24);
	gt_img_set_src(stupbt, "f:img_Set_up_24x24.png");
    gt_obj_set_touch_parent(stupbt, true);

	/** Historybt */
	/** 历史记录 */
	Historybt = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(Historybt, 64, 18);
	gt_obj_set_size(Historybt, 22, 19);
	gt_imgbtn_set_src(Historybt, "f:img_History_22x19.png");
    gt_imgbtn_set_src_press(Historybt, "f:img_History2_22x19.png");
	gt_obj_add_event_cb(Historybt, Historybt_0_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);


	/** emptybt */
	/** 清空 */
	emptybt = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(emptybt, 125, 19);
	gt_obj_set_size(emptybt, 18, 18);
	gt_imgbtn_set_src(emptybt, "f:img_empty_18x18.png");
	gt_imgbtn_set_src_press(emptybt, "f:img_empty2_18x18.png");
	gt_obj_add_event_cb(emptybt, emptybt_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);

    /** imgbtn1 */
    imgbtn1 = gt_imgbtn_create(screen_home);
    gt_obj_set_pos(imgbtn1, 38, 253);
    gt_obj_set_size(imgbtn1, 170, 44);
    gt_imgbtn_set_src(imgbtn1, "f:img_aj_170x44.png");
    gt_obj_set_touch_expand_area(imgbtn1, 40, 20);
    gt_obj_set_fixed(imgbtn1, false);
    add_event_cb_for_imgbtn();

    /** lab1 */
    lab1 = gt_label_create(imgbtn1);
	gt_obj_set_pos(lab1, 46, 257);
	gt_obj_set_size(lab1, 154, 37);
    gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_family(lab1, gray_black_16);
    gt_label_set_font_cjk(lab1, 0);
    gt_label_set_font_align(lab1, GT_ALIGN_CENTER_MID);
    gt_label_set_text(lab1, "请长按说话");
    gt_obj_set_touch_parent(lab1, true);


    /** player_emojis */
    /** 表情 */
    player_emojis = gt_player_create(screen_home);
    gt_obj_set_pos(player_emojis, 4, 78);
    gt_obj_set_size(player_emojis, 228, 117);
    gt_player_set_type(player_emojis, GT_PLAYER_TYPE_IMG);
    gt_player_set_mode(player_emojis, GT_PLAYER_MODE_LOOP);
    gt_player_set_auto_play_period(player_emojis, 35);

    img_emote = gt_img_create(screen_home);
    gt_obj_set_pos(img_emote, 35, 38);
	gt_obj_set_size(img_emote, 169, 204);

    if (strcmp(cb_data.settings->bot_name, "智酱") == 0)
    {
        gt_obj_set_visible(img_emote, GT_INVISIBLE);
        set_emojis_in_player(player_emojis, AI_EMOJIS_WAITING);
        gt_obj_set_visible(player_emojis, GT_VISIBLE);
    } else if (strcmp(cb_data.settings->bot_name, "小智") == 0) {
        gt_obj_set_visible(player_emojis, GT_INVISIBLE);
        gt_obj_set_visible(img_emote, GT_VISIBLE);
        set_emote_in_img(img_emote, AI_EMOTE_XIAOZHI_NEUTRAL);

    } else if (strcmp(cb_data.settings->bot_name, "菜机") == 0)
    {
        gt_obj_set_visible(player_emojis, GT_INVISIBLE);
        gt_obj_set_visible(img_emote, GT_VISIBLE);
        set_emote_in_img(img_emote, AI_EMOTE_CAIJI_NEUTRAL);
    }

    /** rect1 */
	rect_b = gt_rect_create(screen_home);
	gt_obj_set_pos(rect_b, 35, 215);
	gt_obj_set_size(rect_b, 228, 40);
    gt_rect_set_bg_color(rect_b, gt_color_hex(0x000000));
    gt_obj_set_visible(rect_b, GT_INVISIBLE);

	/** lab2 */
	lab2 = gt_label_create(screen_home);
	gt_obj_set_pos(lab2, 25, 215);
	gt_obj_set_size(lab2, 187, 30);
	gt_label_set_font_color(lab2, gt_color_hex(0x5b8ad9));
	gt_label_set_font_family(lab2, gray_black_16);
	gt_label_set_font_cjk(lab2, 0);
	gt_label_set_font_align(lab2, GT_ALIGN_CENTER_MID);
    gt_obj_set_visible(lab2, GT_INVISIBLE);

    /** player_audio */
    /** 音频动画 */
	player_audio = gt_player_create(imgbtn1);
	gt_obj_set_pos(player_audio, 85, 261);
	gt_obj_set_size(player_audio, 80, 30);
	gt_player_set_type(player_audio, GT_PLAYER_TYPE_IMG);
	gt_player_set_mode(player_audio, GT_PLAYER_MODE_LOOP);
	gt_player_set_auto_play_period(player_audio, 30);
    gt_obj_set_visible(player_audio, GT_INVISIBLE);
    gt_obj_set_touch_parent(player_audio, true);



    int level = 0;
    gt_obj_st * dialog = NULL;

    level = get_current_rssi_level();
    printf("wifi_scan_anytime level   ======== %d\r\n",level);
    if (level == WIFI_NO_CONNECTED && dialog == NULL) {

        /** dialog1 */
        /** 清空历史记录 */
        dialog1 = gt_dialog_create(false);
        gt_obj_set_pos(dialog1, 0, 40);
        gt_obj_set_size(dialog1, 240, 240);
        gt_dialog_set_bgcolor(dialog1, gt_color_hex(0x181B22));
        gt_dialog_set_border_color(dialog1, gt_color_hex(0xc7c7c7));
        gt_dialog_set_border_width(dialog1, 0);
        gt_dialog_set_border_radius(dialog1, 20);
        gt_dialog_set_outside_auto_hide(dialog1, false);



        /** lab6 */
        lab6 = gt_label_create(dialog1);
        gt_obj_set_pos(lab6, 25, 155);
        gt_obj_set_size(lab6, 199, 66);
        gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
        gt_label_set_font_family(lab6, gray_black_20);
        gt_label_set_font_cjk(lab6, 0);
        gt_label_set_font_align(lab6, GT_ALIGN_CENTER_MID);
        gt_label_set_text(lab6, "网络未连接,是否去连接网络");


        /** img1 */
        img1 = gt_img_create(dialog1);
        gt_obj_set_pos(img1, 69, 64);
        gt_obj_set_size(img1, 109, 84);
        gt_img_set_src(img1, "f:img_u11_109x84.jpg");



        /** Cancel */
        /** 取消键 */
        Cancel = gt_btn_create(dialog1);
        gt_obj_set_pos(Cancel, 27, 228);
        gt_obj_set_size(Cancel, 80, 40);
        gt_btn_set_font_color(Cancel, gt_color_hex(0xffffff));
        gt_btn_set_font_family(Cancel, gray_black_16);
        gt_btn_set_font_cjk(Cancel, 0);
        gt_btn_set_font_align(Cancel, GT_ALIGN_CENTER_MID);
        gt_btn_set_text(Cancel, "取消");
        gt_btn_set_color_background(Cancel, gt_color_hex(0x0075FD));
        gt_btn_set_color_pressed(Cancel, gt_color_hex(0x00a8ff));
        gt_btn_set_font_color_pressed(Cancel, gt_color_hex(0x000000));
        gt_btn_set_radius(Cancel, 8);
        gt_obj_add_event_cb(Cancel, screen_home_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);




        /** Sure */
        /** 确认键 */
        Sure = gt_btn_create(dialog1);
        gt_obj_set_pos(Sure, 132, 228);
        gt_obj_set_size(Sure, 80, 40);
        gt_btn_set_font_color(Sure, gt_color_hex(0xffffff));
        gt_btn_set_font_family(Sure, gray_black_16);
        gt_btn_set_font_cjk(Sure, 0);
        gt_btn_set_font_align(Sure, GT_ALIGN_CENTER_MID);
        gt_btn_set_text(Sure, "确定");
        gt_btn_set_color_background(Sure, gt_color_hex(0xEB4558));
        gt_btn_set_color_pressed(Sure, gt_color_hex(0x00a8ff));
        gt_btn_set_font_color_pressed(Sure, gt_color_hex(0x000000));
        gt_btn_set_radius(Sure, 8);
        gt_obj_add_event_cb(Sure, Sure_0_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);


        gt_dialog_show(dialog1);

        ESP_LOGI(TAG,"11-------------------dialog----------------%p\r\n",dialog);
        ESP_LOGI(TAG,"11111111111111111111111\n");
    }


    return screen_home;
}

