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


static void add_event_cb_for_imgbtn();


/**
 * @brief 等待录音时的ui
 *
 */
void waiting_rec_ui() {
    gt_obj_set_visible(lab1, GT_VISIBLE);
    gt_obj_set_visible(lab2, GT_INVISIBLE);
    gt_obj_set_visible(player_audio, GT_INVISIBLE);
    gt_player_stop(player_audio);
    set_emojis_in_player(player_emojis, AI_EMOJIS_WAITING);

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
	gt_label_set_font_color(lab2, gt_color_hex(0x5b8ad9));
	gt_obj_set_pos(player_audio, 85, 261);
    set_emojis_in_player(player_audio, AI_ANIM_AUDIO);
    gt_obj_set_visible(player_audio, GT_VISIBLE);
    gt_player_play(player_audio);
    set_emojis_in_player(player_emojis, AI_EMOJIS_RECORDING);
}

/**
 * @brief 等待回复时的ui
 *
 */
static void waiting_answer_ui() {
    gt_obj_set_visible(lab1, GT_INVISIBLE);
    gt_label_set_text(lab2, blue_tip[1]);
	gt_label_set_font_color(lab2, gt_color_hex(0x5b8ad9));
	gt_obj_set_pos(player_audio, 90, 264);
    set_emojis_in_player(player_audio, AI_ANIM_SMILE);
    set_emojis_in_player(player_emojis, AI_EMOJIS_HAPPY);

    gt_obj_remove_all_event_cb(imgbtn1);
}

/**
 * @brief 语音识别失败时的ui
 *
 */
void identification_failed_ui() {
    gt_obj_set_visible(lab1, GT_VISIBLE);
    gt_label_set_text(lab2, blue_tip[2]);
    gt_label_set_font_color(lab2, gt_color_hex(0xFF7859));
    gt_obj_set_visible(player_audio, GT_INVISIBLE);
    gt_player_stop(player_audio);
    set_emojis_in_player(player_emojis, AI_EMOJIS_SYMPATHY);

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
    gt_audio_player_stop();

    //step2:开始录音
#if USE_HTTP_STREAM
    get_pipe_send_api_key();
    gt_pipe_send_start();
#else //!USE_HTTP_STREAM
    gt_recording_path_set("/sdcard/rec.wav");
    gt_recording_start();
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
#if USE_HTTP_STREAM
    gt_pipe_send_stop();
    set_ringbuf_done();
#else //!USE_HTTP_STREAM
    gt_recording_stop();
#endif //!USE_HTTP_STREAM

    print_memory_info();
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
    send_information_exe_func();
}

//焦点移开当前控件
static void cancel_recording_cb(gt_event_st * e) {
    //step1:切换等待录音时的ui
    waiting_rec_ui();

#if USE_HTTP_STREAM
    gt_pipe_send_stop();
    set_ringbuf_done();
#else //!USE_HTTP_STREAM
    //step2:结束录音，并删除SD卡中的录音文件
    gt_recording_stop();

    //删除SD卡中录音文件
    f_unlink("0:rec.wav");
#endif //!USE_HTTP_STREAM


    ESP_LOGI(TAG, "-----------------------焦点移开当前控件\n");

}

static void add_event_cb_for_imgbtn() {
    gt_obj_add_event_cb(imgbtn1, recording_cb, GT_EVENT_TYPE_INPUT_PRESSED, NULL);
    gt_obj_add_event_cb(imgbtn1, send_information_cb, GT_EVENT_TYPE_INPUT_RELEASED, NULL);
    gt_obj_add_event_cb(imgbtn1, cancel_recording_cb, GT_EVENT_TYPE_INPUT_PRESS_LOST, NULL);
}

static void screen_home_0_cb(gt_event_st * e) {
	gt_disp_stack_go_back(1);
    update_wifi_icon();
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
    set_emojis_in_player(player_emojis, AI_EMOJIS_WAITING);

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


    return screen_home;
}

