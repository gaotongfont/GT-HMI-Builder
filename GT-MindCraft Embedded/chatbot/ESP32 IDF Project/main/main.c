/* Play an MP3 file from HTTP and save it to SD card

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "audio_element.h"
#include "audio_pipeline.h"
#include "audio_event_iface.h"
#include "audio_common.h"
#include "http_stream.h"
#include "i2s_stream.h"
#include "mp3_decoder.h"
#include "fatfs_stream.h"
#include "raw_stream.h"
#include "esp_peripherals.h"
#include "periph_wifi.h"
#include "periph_sdcard.h"
#include "board.h"
#include "audio_idf_version.h"
#include "esp_lcd_panel_ops.h"
#include "tca9554.h"
#include "audio_mem.h"
#include "audio_thread.h"

#if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 1, 0))
#include "esp_netif.h"
#else
#include "tcpip_adapter.h"
#endif

#include "gtspi.h"
#include "gt_recording.h"
#include "gt_audio_play.h"
#include "gt_touch.h"
#include "spi.h"
#include "lcd.h"
#include "esptim.h"
#include "gt.h"
#include "gt_ui.h"
#include "http_send.h"
#include "wifi_config.h"
#include "freertos/queue.h"
#include "audio_thread.h"
/* ------------------------------------------------------------------------ */
static const char *TAG = "APP_MAIN";
static esp_periph_set_handle_t set = NULL;
audio_board_handle_t gt_board_handle = NULL;
static esp_lcd_panel_handle_t lcd_handle = NULL;
static tp_dev_t* gt_tp_dev = NULL;

static portMUX_TYPE my_spinlock = portMUX_INITIALIZER_UNLOCKED;

ChatbotData cb_data;

QueueHandle_t mYxQueue;
QueueHandle_t mYxQueue2;


void print_memory_info(void) {
    // 获取总的空闲堆内存
    size_t free_heap_size = esp_get_free_heap_size();
    // 获取内部 RAM 的空闲内存
    size_t free_internal_heap_size = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);
    // 获取外部 SPIRAM 的空闲内存
    size_t free_spiram_heap_size = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);

    ESP_LOGW(">>> ","Total free heap size: %zu bytes", free_heap_size);
    ESP_LOGW(">>> ","Free internal heap size: %zu bytes", free_internal_heap_size);
    ESP_LOGW(">>> ","Free SPIRAM heap size: %zu bytes\n", free_spiram_heap_size);
}

/* ------------------------------------------------------------------------ */
/**
 * @brief lcd批量写入数据
 *
 * @param data    数据buff
 * @param length  数据长度
 */
static void batch_write_data(uint8_t *data, uint32_t length)
{
    size_t lcd_buffer_size = 0;
    esp_err_t ret = spi_bus_get_max_transaction_len(SPI2_HOST, &lcd_buffer_size);   //spi一次最大传输的字节 32k DMA

    lcd_buffer_size = lcd_buffer_size >> 2;                                         //分次传输的字节 8k

    uint32_t count = length / lcd_buffer_size;                                      //完整传输的次数
    uint32_t mod = length % lcd_buffer_size;                                        //剩余的字节数
    uint32_t i = 0;
    for(i = 0; i < count; i++){
        lcd_write_data(data + i * lcd_buffer_size, lcd_buffer_size);
    }
    if(mod != 0){
        lcd_write_data(data + i * lcd_buffer_size, mod);
    }
}

/**
 * @brief 刷屏函数
 *
 * @param drv   不需要配置
 * @param area  area->x绘制区域的起始x坐标
 *              area->y绘制区域的起始y坐标
 *              area->w绘制区域的宽度
 *              area->h绘制区域的高度
 * @param color 颜色数组
 */
void _flush_cb(struct _gt_disp_drv_s * drv, gt_area_st * area, gt_color_t * color)
{
    uint32_t start_x = area->x, start_y = area->y;
    uint16_t width = area->w;
    uint16_t height = area->h;
    uint32_t end_x = start_x + width - 1, end_y = start_y + height - 1;

    uint8_t *data = (uint8_t *)color;

    lcd_set_window(start_x, start_y, end_x, end_y);
    batch_write_data(data, width * height * sizeof(gt_color_t));
}

/**
 * @brief 触摸函数
 *
 * @param indev_drv 不需要配置
 * @param data      data->state 触摸状态
 *                  data->point.x 触摸点x坐标
 *                  data->point.y 触摸点y坐标
 */
void read_cb(struct _gt_indev_drv_s * indev_drv, gt_indev_data_st * data)
{
    if(!gt_tp_dev->read_point()){
		data->state = GT_INDEV_STATE_RELEASED;
        // data->point.x = gt_tp_dev->point.x;
        // data->point.y = gt_tp_dev->point.y;
		return;
	}
    data->point.x = gt_tp_dev->point.x;
	data->point.y = gt_tp_dev->point.y;
	data->state = gt_tp_dev->point.status == TP_STATE_RELEASED ? GT_INDEV_STATE_RELEASED : GT_INDEV_STATE_PRESSED;
}

/**
 * @brief spi读写
 *
 * @param data_write    写入数据
 * @param len_write     写入数据长度
 * @param data_read     读取数据
 * @param len_read      读取数据长度
 * @return uint32_t
 */
uint32_t spi_wr(uint8_t * data_write, uint32_t len_write, uint8_t * data_read, uint32_t len_read)
{
    uint32_t ReadAddr;
	ReadAddr = *(data_write + 1) << 16;					//高八位地址
	ReadAddr += *(data_write + 2) << 8;				    //中八位地址
	ReadAddr += *(data_write + 3);						//低八位地址

    r_dat_bat(ReadAddr, len_read, data_read);
    return 1;
}

unsigned long r_dat_bat(unsigned long address, unsigned long DataLen, unsigned char* pBuff)
{
    // 查找指定的分区
    const esp_partition_t *partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_FAT, "resource");
    if (partition == NULL) {
        // 分区未找到，返回错误
        ESP_LOGE("FLASH", "Flash partition not found.");
        return 0;
    }
    // 从分区中读取数据
    esp_err_t err = esp_partition_read(partition, address, pBuff, DataLen);
    if (err != ESP_OK) {
        // 读取失败，返回错误
        ESP_LOGE("FLASH", "Flash read failure");
        return 0;
    }

    return 1;
}

void gt_gui_task(void *pvParameters)
{
    ESP_LOGI(TAG, "--------------------------gt_gui_task\n");
    int received_msg;
    while(1){
        if (xQueueReceive(mYxQueue2, &received_msg, 1) == pdPASS) {
            ESP_LOGI(TAG, "2-------------------received_msg = %d\n", received_msg);
            if (ESP_OK == received_msg) {
                //启动音频播放器
                gt_audio_player_start(cb_data.answer->tts_audio);
                //跳转到字幕界面
                gt_disp_stack_load_scr_anim(GT_ID_SCREEN_SUBTITLE, GT_SCR_ANIM_TYPE_NONE, 50, 0, true);
            } else {
                //切换语音识别失败时的ui
                identification_failed_ui();
            }
        }
        gt_task_handler();
        // vTaskDelay(1);
    }
}
/* ------------------------------------------------------------------------ */


void app_main(void)
{
    esp_xl9555_config_t pca_cfg = {0};

    mYxQueue = xQueueCreate(3, sizeof(int));
    if (mYxQueue == NULL) {
        // 队列创建失败处理
        ESP_LOGE(TAG, "Failed to create queue");
    }
    mYxQueue2 = xQueueCreate(3, sizeof(int));
    if (mYxQueue2 == NULL) {
        // 队列创建失败处理
        ESP_LOGE(TAG, "Failed to create queue");
    }
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
#if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 1, 0))
    ESP_ERROR_CHECK(esp_netif_init());
#else
    tcpip_adapter_init();
#endif
    // init audio board
    gt_board_handle = audio_board_init();
    audio_hal_ctrl_codec(gt_board_handle->audio_hal, AUDIO_HAL_CODEC_MODE_BOTH, AUDIO_HAL_CTRL_START);
    audio_hal_set_volume(gt_board_handle->adc_hal, 100);
    // peripheral init
    esp_periph_config_t set_periph_cfg = DEFAULT_ESP_PERIPH_SET_CONFIG();
    set_periph_cfg.extern_stack = true;
    set = esp_periph_set_init(&set_periph_cfg);
    // sdcard init
#ifdef CONFIG_ESP32_S3_GT_BOARD
    audio_board_sdcard_init(set, SD_MODE_SPI);
#else
    audio_board_sdcard_init(set, SD_MODE_1_LINE);
#endif


    xl955_config(&pca_cfg);             /* 初始化扩展IO */
    xl9555_init(&pca_cfg);
    xl9555_set_io_config(LCD_NUM_PWR, 0);
    LCD_PWR(0);

    int font_res = -1;
    spi_init();
    font_res = GT_Font_Init();          /* 初始化字库 */
    // printf("==========font_res=========%d\r\n",font_res);

    spi2_init();
    lcd_init();                         /* 初始化LCD */

    gt_init();                             /* gui初始化 */
    gt_ui_init();                          /* 界面初始化 */
    esptim_int_init(1000);              /* 定时器初始化，定时1ms */

    gt_tp_dev = gt_touch_init();        /* 初始化触摸屏 */

    gt_audio_player_init();             /* 初始化播放器 */
    gt_audio_player_vol_set(100);
    gt_recording_init();                /* 初始化录音 */

    LCD_PWR(1);

    /* 设置界面参数 */
    cb_data.settings = (SendSettingsData*)audio_malloc(sizeof(SendSettingsData));
    memset(cb_data.settings, 0, sizeof(SendSettingsData));

    sprintf(cb_data.settings->emotion_output,"%s","true");
    cb_data.settings->user_age = 6;
    sprintf(cb_data.settings->bot_character,"%s","朋友");
    sprintf(cb_data.settings->bot_personality,"%s","外向");
    sprintf(cb_data.settings->voice_id,"%s","cute_boy");
    sprintf(cb_data.settings->bot_name,"%s","智酱");
    sprintf(cb_data.settings->output_format,"%s","mp3");

    cb_data.answer = (ReceivedAnswerData*)audio_malloc(sizeof(ReceivedAnswerData));
    memset(cb_data.answer, 0, sizeof(ReceivedAnswerData));

    taskENTER_CRITICAL(&my_spinlock);

    xTaskCreate(gt_gui_task, "gt_gui_task", 4096, NULL, 3, NULL);
    xTaskCreate(&http_test_task, "http_test_task", 8*1024, &cb_data, 3, NULL);

    taskEXIT_CRITICAL(&my_spinlock);
    print_memory_info();

    wifi_sta_init();                    /* 网络配置 */

}
