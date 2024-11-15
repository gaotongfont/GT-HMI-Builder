#ifndef _WIFI_H_
#define _WIFI_H_


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include <netdb.h>
#include "esp_log.h"
#include "gt_ui.h"

typedef struct _network_connet_info_t
{
    uint8_t         connet_state;    /* 网络连接状态 */
    char            ip_buf[100];     /* 分配的IP地址 */
    char            mac_buf[100];    /* 子网掩码 */
    void (*fun)(uint8_t x);          /* 函数指针 */
} network_connet_info;

typedef struct {
   char *name;
   char *password;
   bool isConnected;
}wifi_info_t;

extern wifi_info_t *scan_wifi_list;
extern uint16_t ap_count;
extern bool is_auto_connected_end;

wifi_config_t get_current_wifi_config();
int8_t get_current_rssi_level();

void wifi_event_init();
void wifi_init(void);
void wifi_scan(void);
void wifi_sta_connect(char *name, char *password);

void set_current_wifi_isConnected();
void reset_current_wifi_isConnected();
bool check_cur_wifi_is_in_wifi_list(char *name, char *password);
#endif // !_WIFI_H_
