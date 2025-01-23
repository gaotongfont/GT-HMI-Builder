#include "wifi.h"

#if 01
// 定义事件标志组和标志位
EventGroupHandle_t wifi_event_group;
#define WIFI_SCAN_DONE_BIT  BIT0  // 扫描完成标志
#define WIFI_CONNECTED_BIT  BIT1  // 连接成功标志
#define WIFI_FAIL_BIT       BIT2  // 连接失败标志

#define DEFAULT_SCAN_LIST_SIZE 8

network_connet_info network_connet;
static const char *TAG = "scan_connect";

wifi_info_t *scan_wifi_list;
uint16_t ap_count = 0;
bool allow_reconnect = true;

/**
 * @brief Get the current wifi config
 *
 * @return wifi_config_t
 */
wifi_config_t get_current_wifi_config() {
    wifi_config_t wifi_config = {0};  // 初始化 wifi_config 结构体

    // 获取当前的 WiFi 配置
    esp_err_t err = esp_wifi_get_config(ESP_IF_WIFI_STA, &wifi_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, ">>Failed to get WiFi configuration: %s", esp_err_to_name(err));
        return (wifi_config_t){0};  // 返回一个初始化的结构体
    }

    // 打印当前的 WiFi 配置
    ESP_LOGI(TAG, ">>Current WiFi SSID: %s", wifi_config.sta.ssid);
    ESP_LOGI(TAG, ">>Current WiFi Password: %s", wifi_config.sta.password);

    return wifi_config;
}

/**
 * @brief Get the current rssi level
 *
 * @return int8_t
 */
int8_t get_current_rssi_level() {
    wifi_ap_record_t ap_info;

    int8_t rssi;
    gt_wifi_icon_status_et rssi_level = WIFI_NO_CONNECTED;
    esp_err_t err = esp_wifi_sta_get_ap_info(&ap_info);
    if (err == ESP_OK) {
        rssi = ap_info.rssi;
        ESP_LOGI(TAG, "RSSI: %d dBm", rssi);
    } else {
        rssi = 0;
        ESP_LOGE(TAG, "Failed to get RSSI: %s", esp_err_to_name(err));
    }
    if (rssi == 0)
    {
        rssi_level = WIFI_NO_CONNECTED;
    } else if (rssi < -70) {
        rssi_level = WIFI_SIGNAL_1;
    } else if (rssi >= -70 && rssi <= -67) {
        rssi_level = WIFI_SIGNAL_2;
    } else if (rssi >= -67 && rssi <= -50) {
        rssi_level = WIFI_SIGNAL_3;
    } else if (rssi >= -50) {
        rssi_level = WIFI_SIGNAL_4;
    }

    return rssi_level;
}

void set_current_wifi_isConnected()
{
    for (size_t i = 0; i < ap_count; i++) {
        if (i != selected_idx)
        {
            scan_wifi_list[i].isConnected = false;
        }else {
            scan_wifi_list[i].isConnected = true;
        }
    }
}

void reset_current_wifi_isConnected()
{
    for (size_t i = 0; i < ap_count; i++) {
        scan_wifi_list[i].isConnected = false;
    }
}

bool check_cur_wifi_is_in_wifi_list(char *name, char *password) {
    bool wifi_is_found = false;
    for (size_t i = 0; i < ap_count; i++) {
        if (strcmp(name, scan_wifi_list[i].name) == 0)
        {
            wifi_is_found = true;
            selected_idx = i;
            ESP_LOGI(TAG,"--------selected_idx = %d\n", selected_idx);
            if (scan_wifi_list[selected_idx].password != NULL) {
                audio_free(scan_wifi_list[selected_idx].password);
            }
            scan_wifi_list[selected_idx].password = (char *)audio_malloc(strlen(password) + 1);
            if (scan_wifi_list[selected_idx].password == NULL) {
                ESP_LOGE(TAG, "Failed to allocate memory for password");
                return false;
            }
            strcpy(scan_wifi_list[selected_idx].password, (const char *)password);
            break;
        }
    }
    return wifi_is_found;
}
/**
 * @brief       链接显示
 * @param       flag:2->链接;1->链接失败;0->再链接中
 * @retval      无
 */
void connet_display(uint8_t flag)
{
    ESP_LOGI(TAG,"--------flag = 0x%x\n", flag);

    if((flag & 0x80) == 0x80)
    {
        // ESP_LOGI(TAG,"--------ssid:%s",DEFAULT_SSID);
        // ESP_LOGI(TAG,"--------psw:%s",DEFAULT_PWD);
        ESP_LOGI(TAG,"11111111111111111111\n");

    }
    else if ((flag & 0x04) == 0x04)
    {
        // wifi_connecting_ui();
        // change_wifi_connect_tip(flag);
        ESP_LOGI(TAG,">>>>>>>>>>>>>>--------wifi connecting......\n");
    }
    else if ((flag & 0x02) == 0x02)
    {
        // wifi_connected_fail_ui();
        gt_scr_id_t screen_id = gt_scr_stack_get_current_id();
        ESP_LOGI(TAG,">>---------------screen_id: %d\n",screen_id);
        if (screen_id == GT_ID_MAIN_INTERFACE)
        {
            update_wifi_icon();
        } else if (screen_id == GT_ID_WIFI_LIST){
            vTaskDelay(300);
            gt_disp_stack_load_scr_anim(GT_ID_CONNECTION_FAILED, GT_SCR_ANIM_TYPE_NONE, 200, 0, true);
        }
        is_auto_connected_end = true;
        ESP_LOGI(TAG,"--------wifi connecting fail\n");
    }
    else if ((flag & 0x01) == 0x01)
    {
        ESP_LOGI(TAG,"--------%s\n",network_connet.ip_buf);
        // waiting_rec_ui();
        ESP_LOGE(TAG, "---------------selected_idx: %u\n", selected_idx);
        set_current_wifi_isConnected();
        change_wifi_connect_tip(flag);
        is_auto_connected_end = true;
        ESP_LOGI(TAG,"--------wifi connecting success\n");
    }

    network_connet.connet_state &= 0x00;
}


static void wifi_scan_done_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    if (event_id == WIFI_EVENT_SCAN_DONE) {
        // 设置扫描完成的标志位
        xEventGroupSetBits(wifi_event_group, WIFI_SCAN_DONE_BIT);
        ESP_LOGI(TAG, "WiFi scan completed.");
    }
}


void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {

     static int s_retry_num = 0;

    ESP_LOGI(TAG, "Event received: event_base = %s, event_id = %d", event_base, event_id);

    /* 扫描到要连接的WIFI事件 */
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        network_connet.connet_state |= 0x04;
        network_connet.fun(network_connet.connet_state);
        // esp_wifi_connect();
        ESP_LOGI(TAG, "------------------------aaaaaaaaaaaaaaaaaa");

    }
    /* 连接WIFI事件 */
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_CONNECTED)
    {
        network_connet.connet_state |= 0x80;
        network_connet.fun(network_connet.connet_state);
    }
    /* 连接WIFI失败事件 */
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        wifi_event_sta_disconnected_t* disconnection_info = (wifi_event_sta_disconnected_t*) event_data;
        ESP_LOGE(TAG, "Disconnected from AP, reason: %d", disconnection_info->reason);
        if (allow_reconnect)
        {
            network_connet.connet_state |= 0x02;
            /* 尝试连接 */
            if (s_retry_num < 5)
            {
                esp_wifi_connect();
                s_retry_num ++;
                ESP_LOGI(TAG, "retry to connect to the AP");
            }
            else
            {
                xEventGroupSetBits(wifi_event_group, WIFI_FAIL_BIT);
                network_connet.fun(network_connet.connet_state);
            }
            ESP_LOGI(TAG,"connect to the AP fail");
        }

    }
    /* 工作站从连接的AP获得IP */
    else if(event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        network_connet.connet_state |= 0x01;
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "static ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        sprintf(network_connet.ip_buf, "static ip:" IPSTR, IP2STR(&event->ip_info.ip));
        network_connet.fun(network_connet.connet_state);
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}


void wifi_event_init() {
    // 创建事件标志组
    wifi_event_group = xEventGroupCreate();
    // 注册 WiFi 事件处理程序
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_SCAN_DONE, &wifi_scan_done_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_CONNECTED, &wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL) );
}

void wifi_init(void) {
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    // 初始化 WiFi
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void wifi_scan(void) {

    // 清除之前的 AP 列表
    ESP_ERROR_CHECK(esp_wifi_clear_ap_list());
    // 开始扫描
    ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, false));  // 异步扫描
    // 等待扫描完成事件
    xEventGroupWaitBits(wifi_event_group, WIFI_SCAN_DONE_BIT, pdTRUE, pdFALSE, portMAX_DELAY);
    // 获取扫描结果
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    ESP_LOGI(TAG, "----------------ap_count = %d\n", ap_count);
    ap_count = ap_count > DEFAULT_SCAN_LIST_SIZE ? DEFAULT_SCAN_LIST_SIZE : ap_count;
    ESP_LOGI(TAG, "----------------ap_count = %d\n", ap_count);
    wifi_ap_record_t ap_info[ap_count];
    memset(ap_info, 0, sizeof(ap_info));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_count, ap_info));
    // 打印扫描结果
    // for (int i = 0; i < ap_count; i++) {
    //     ESP_LOGI(TAG, "SSID: %s, RSSI: %d, Channel: %d", ap_info[i].ssid, ap_info[i].rssi, ap_info[i].primary);
    // }
    scan_wifi_list = (wifi_info_t *) audio_malloc(ap_count * sizeof(wifi_info_t));
    if (scan_wifi_list == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for wifi_info_array");
        return; // 处理内存分配失败的情况
    }
    for (size_t i = 0; i < ap_count; i++)
    {
        scan_wifi_list[i].name = (char *)audio_malloc(strlen((const char *)ap_info[i].ssid) + 1);
        if (scan_wifi_list[i].name == NULL) {
            ESP_LOGE(TAG, "Failed to allocate memory for SSID");
            continue;
        }
        strcpy(scan_wifi_list[i].name, (const char *)ap_info[i].ssid);

        // scan_wifi_list[i].password = NULL;
        scan_wifi_list[i].password = (char *)audio_malloc(1);
        if (scan_wifi_list[i].password == NULL) {
            ESP_LOGE(TAG, "Failed to allocate memory for password");
            continue;
        }
        scan_wifi_list[i].password[0] = '\0'; // 初始化为空字符串
        scan_wifi_list[i].isConnected = false;
        ESP_LOGI(TAG,"----------------scan_wifi_list[i].name = %s\n", scan_wifi_list[i].name);
    }
}

void wifi_sta_connect(char *name, char *password) {
    if (name == NULL || password == NULL) {
        ESP_LOGE(TAG, "Invalid SSID or password");
        return;
    }

    network_connet.connet_state = 0x00;
    network_connet.fun = connet_display;

    allow_reconnect = false;
    esp_err_t ret = esp_wifi_disconnect();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to disconnect from AP: %s", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, ">>>>Disconnected from AP");
    }
    vTaskDelay(pdMS_TO_TICKS(300));
    allow_reconnect = true;

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = {0},  // 替换为目标 WiFi SSID
            .password = {0},  // 替换为目标 WiFi 密码
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
        },
    };

    // 将 name 和 password 复制到 wifi_config 中
    strncpy((char *)wifi_config.sta.ssid, (char *)name, sizeof(wifi_config.sta.ssid) - 1);
    strncpy((char *)wifi_config.sta.password, (char *)password, sizeof(wifi_config.sta.password) - 1);

    ESP_LOGI(TAG,"----------------wifi_config.sta.ssid = %s\n", wifi_config.sta.ssid);
    ESP_LOGI(TAG,"----------------wifi_config.sta.password = %s\n", wifi_config.sta.password);


    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));

    // 开始连接
    ESP_ERROR_CHECK(esp_wifi_connect());
    // 等待连接成功或失败
    EventBits_t bits = xEventGroupWaitBits(
        wifi_event_group,
        WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
        pdFALSE,
        pdFALSE,
        portMAX_DELAY);
    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "Successfully connected to WiFi.");
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGE(TAG, "Failed to connect to WiFi.");
    } else {
        ESP_LOGE(TAG, "Unexpected event occurred.");
    }
}
#endif