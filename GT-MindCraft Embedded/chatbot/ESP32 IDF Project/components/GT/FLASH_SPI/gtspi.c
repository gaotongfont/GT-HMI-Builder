#include "gtspi.h"


#define PIN_NUM_MISO GPIO_NUM_47
#define PIN_NUM_MOSI GPIO_NUM_12
#define PIN_NUM_CLK  GPIO_NUM_21
#define PIN_NUM_CS   GPIO_NUM_13
#define IO11 GPIO_NUM_11

static const char *TAG = "SPI_DEBUG";

spi_device_handle_t spi;

void spi_init() {

    // 配置IO11引脚为输出并设置为高电平
    gpio_config_t io11_conf = {
        .intr_type = GPIO_INTR_DISABLE,       //禁用中断
        .mode = GPIO_MODE_OUTPUT,             //设置为输出模式
        .pin_bit_mask = (1ULL << IO11),       //设置IO11引脚
        .pull_down_en = GPIO_PULLDOWN_DISABLE,  //禁用下拉
        .pull_up_en = GPIO_PULLUP_DISABLE,   //禁用上拉
    };
    gpio_config(&io11_conf);
    gpio_set_level(IO11, 1);  //将IO11引脚设置为高电平

    // 配置CS引脚为输出并设置为高电平
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << PIN_NUM_CS),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
    };
    gpio_config(&io_conf);
    gpio_set_level(PIN_NUM_CS, 1);  //手动拉高CS

    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4096,
    };

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 10 * 1000 * 1000,  //10MHz
        .mode = 0,                           //SPI模式0
        .spics_io_num = -1,//PIN_NUM_CS,     //CS引脚
        .queue_size = 7,                     //事务队列大小
        //.flags = SPI_DEVICE_HALFDUPLEX,
    };
    // 初始化SPI总线
    esp_err_t ret = spi_bus_initialize(SPI3_HOST, &buscfg, SPI_DMA_CH_AUTO);
    // if (ret == ESP_OK) {
    //     ESP_LOGI(TAG, "SPI bus initialized successfully");
    // } else {
    //     ESP_LOGE(TAG, "SPI bus initialization failed with error: %d", ret);
    // }
    assert(ret == ESP_OK);
    // 添加SPI设备
    ret = spi_bus_add_device(SPI3_HOST, &devcfg, &spi);
    // if (ret == ESP_OK) {
    //     ESP_LOGI(TAG, "SPI device added successfully");
    // } else {
    //     ESP_LOGE(TAG, "Failed to add SPI device with error: %d", ret);
    // }
    assert(ret == ESP_OK);
    //gpio_set_level(PIN_NUM_CS, 1);  // 手动拉高CS，结束传输
}

// 读取OTP区域数据的函数

// 传输时要确保正确配置
void spi_transmit(const uint8_t* data_to_send, size_t length_of_data_to_send) {
    spi_transaction_t trans = {
        .flags = SPI_TRANS_USE_TXDATA,
        .length = 8 * length_of_data_to_send, //数据长度，单位为位
        .tx_buffer = data_to_send,
        .rx_buffer = NULL,  //禁用MISO读取
    };
    gpio_set_level(PIN_NUM_CS, 0);
    esp_err_t ret = spi_device_transmit(spi, &trans);
    gpio_set_level(PIN_NUM_CS, 1);
    assert(ret == ESP_OK);
}


//发送一个字节
void Send_Byte(uint8_t data) {
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &data;
    esp_err_t ret = spi_device_transmit(spi, &t);//esp_err_t ret = spi_device_polling_transmit(spi, &t);
    // if (ret == ESP_OK) {
    //     ESP_LOGI(TAG, "Byte sent successfully");
    // } else {
    //     ESP_LOGE(TAG, "Failed to send byte with error: %d", ret);
    // }

}


//接收一个字节
uint8_t Get_Byte() {
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8;
    uint8_t recv_data = 0;
    t.rx_buffer = &recv_data;
    esp_err_t ret = spi_device_transmit(spi, &t); //esp_err_t ret = spi_device_polling_transmit(spi, &t);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to receive byte with error: %d", ret);
    }
    return recv_data;
}


//读取OTP区域数据的函数
unsigned char gt_read_data(unsigned char* sendbuf, unsigned char sendlen, unsigned char* receivebuf, unsigned int receivelen) {
    unsigned int i;
    gpio_set_level(PIN_NUM_CS, 0);
    esp_rom_delay_us(10);
    for(i = 0; i < sendlen; i++) {
        Send_Byte(sendbuf[i]);
    }
    for(i = 0; i < receivelen; i++) {
        receivebuf[i] = Get_Byte();
    }
    gpio_set_level(PIN_NUM_CS, 1);
    esp_rom_delay_us(10);
    return 1;
}
