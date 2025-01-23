#include "gt_pipeline_play.h"
#include "audio_mem.h"


#define RINGBUFF 2048

static const char *TAG = "GT_PIPELINE_PLAY";


typedef struct gt_pipeline{
    audio_pipeline_handle_t pipeline;
    audio_element_handle_t http_stream_reader;
    audio_element_handle_t i2s_stream_writer;
    audio_element_handle_t mp3_decoder;
    audio_event_iface_msg_t* msg;
    audio_event_iface_handle_t evt;
    ringbuf_handle_t ringbuf;
    esp_audio_handle_t player;
    bool isStartListen;
};

extern audio_board_handle_t gt_board_handle;
static GTPIPELINE* gt_pipeline_obj = NULL;

void gt_pipeline_init(GTPIPELINE* gt_pipeline_obj)
{
    esp_audio_cfg_t cfg = DEFAULT_ESP_AUDIO_CONFIG();
    cfg.vol_handle = gt_board_handle->audio_hal;
    cfg.vol_set = (audio_volume_set)audio_hal_set_volume;
    cfg.vol_get = (audio_volume_get)audio_hal_get_volume;
    cfg.resample_rate = 16000;//48000;
    cfg.prefer_type = ESP_AUDIO_PREFER_MEM;
    gt_pipeline_obj->player = esp_audio_create(&cfg);
    
    // audio_pipeline_handle_t pipeline;
    // audio_element_handle_t http_stream_reader, i2s_stream_writer, mp3_decoder;

    // esp_log_level_set("*", ESP_LOG_WARN);
    // esp_log_level_set(TAG, ESP_LOG_DEBUG);

    ESP_LOGI(TAG, "[2.0] Create audio pipeline for playback");
    audio_pipeline_cfg_t pipeline_cfg = DEFAULT_AUDIO_PIPELINE_CONFIG();
    gt_pipeline_obj->pipeline = audio_pipeline_init(&pipeline_cfg);
    // audio_pipeline_cfg_t pipeline_cfg = DEFAULT_AUDIO_PIPELINE_CONFIG();
    // pipeline = audio_pipeline_init(&pipeline_cfg);
    // mem_assert(pipeline);

    ESP_LOGI(TAG, "[2.1] Create http stream to read data");
    http_stream_cfg_t http_cfg = HTTP_STREAM_CFG_DEFAULT();
    gt_pipeline_obj->http_stream_reader =  http_stream_init(&http_cfg);
    // http_stream_cfg_t http_cfg = HTTP_STREAM_CFG_DEFAULT();
    // http_stream_reader = http_stream_init(&http_cfg);

    ESP_LOGI(TAG, "[2.2] Create i2s stream to write data to codec chip");
    i2s_stream_cfg_t i2s_cfg = I2S_STREAM_CFG_DEFAULT_WITH_PARA(0, 16000, 16, 2);//I2S_STREAM_CFG_DEFAULT();
    i2s_cfg.type = AUDIO_STREAM_WRITER;
    i2s_cfg.std_cfg.slot_cfg.slot_mode = I2S_SLOT_MODE_MONO; 
    i2s_cfg.std_cfg.slot_cfg.slot_mask = I2S_STD_SLOT_LEFT;
    i2s_cfg.use_alc = true;
    i2s_cfg.uninstall_drv = false;
    i2s_cfg.stack_in_ext = true;
    // i2s_cfg.volume = 100;
    gt_pipeline_obj->i2s_stream_writer = i2s_stream_init(&i2s_cfg);
    // i2s_stream_cfg_t i2s_cfg = I2S_STREAM_CFG_DEFAULT();
    // i2s_cfg.type = AUDIO_STREAM_WRITER;
    // i2s_stream_writer = i2s_stream_init(&i2s_cfg);

    ESP_LOGI(TAG, "[2.3] Create mp3 decoder to decode mp3 file");
    mp3_decoder_cfg_t mp3_cfg = DEFAULT_MP3_DECODER_CONFIG();
    gt_pipeline_obj->mp3_decoder = mp3_decoder_init(&mp3_cfg);
    // mp3_decoder_cfg_t mp3_cfg = DEFAULT_MP3_DECODER_CONFIG();
    // mp3_decoder = mp3_decoder_init(&mp3_cfg);

    gt_pipeline_obj->ringbuf = rb_create(RINGBUFF, 12);
    audio_element_set_output_ringbuf(gt_pipeline_obj->http_stream_reader, gt_pipeline_obj->ringbuf);
    audio_element_set_input_ringbuf(gt_pipeline_obj->i2s_stream_writer, gt_pipeline_obj->ringbuf);


    ESP_LOGI(TAG, "[2.4] Register all elements to audio pipeline");
    audio_pipeline_register(gt_pipeline_obj->pipeline, gt_pipeline_obj->http_stream_reader, "http");
    audio_pipeline_register(gt_pipeline_obj->pipeline, gt_pipeline_obj->mp3_decoder,        "mp3");
    audio_pipeline_register(gt_pipeline_obj->pipeline, gt_pipeline_obj->i2s_stream_writer,  "i2s");
    // audio_pipeline_register(pipeline, http_stream_reader, "http");
    // audio_pipeline_register(pipeline, mp3_decoder,        "mp3");
    // audio_pipeline_register(pipeline, i2s_stream_writer,  "i2s");

    ESP_LOGI(TAG, "[2.5] Link it together http_stream-->mp3_decoder-->i2s_stream-->[codec_chip]");
    const char *link_tag[3] = {"http", "mp3", "i2s"};
    audio_pipeline_link(gt_pipeline_obj->pipeline, &link_tag[0], 3);
    // audio_pipeline_link(pipeline, &link_tag[0], 3);

    // ESP_LOGI(TAG, "[2.6] Set up  uri (http as http_stream, mp3 as mp3 decoder, and default output is i2s)");
    // audio_element_set_uri(http_stream_reader, "https://dl.espressif.com/dl/audio/ff-16b-2c-44100hz.mp3");
    
    // Example of using an audio event -- START
    ESP_LOGI(TAG, "[ 4 ] Set up  event listener");
    audio_event_iface_cfg_t evt_cfg = AUDIO_EVENT_IFACE_DEFAULT_CFG();
    evt_cfg.external_queue_size = 32;
    evt_cfg.queue_set_size = 12;
    gt_pipeline_obj->evt = audio_event_iface_init(&evt_cfg);
    // audio_event_iface_handle_t evt = audio_event_iface_init(&evt_cfg);

    ESP_LOGI(TAG, "[4.1] Listening event from all elements of pipeline");
    audio_pipeline_set_listener(gt_pipeline_obj->pipeline, gt_pipeline_obj->evt);
    // audio_pipeline_set_listener(pipeline, evt);

    // ESP_LOGI(TAG, "[4.2] Listening event from peripherals");
    // audio_event_iface_set_listener(esp_periph_set_get_event_iface(set), evt);

    // ESP_LOGI(TAG, "[ 5 ] Start audio_pipeline");
    // audio_pipeline_run(pipeline);

    // // Example of using an audio event -- END

    // ESP_LOGI(TAG, "[ 6 ] Stop audio_pipeline");
    // audio_pipeline_stop(pipeline);
    // audio_pipeline_wait_for_stop(pipeline);
    // audio_pipeline_terminate(pipeline);

    // /* Terminate the pipeline before removing the listener */
    // audio_pipeline_unregister(pipeline, http_stream_reader);
    // audio_pipeline_unregister(pipeline, i2s_stream_writer);
    // audio_pipeline_unregister(pipeline, mp3_decoder);

    // audio_pipeline_remove_listener(pipeline);

    // /* Stop all peripherals before removing the listener */
    // esp_periph_set_stop_all(set);
    // audio_event_iface_remove_listener(esp_periph_set_get_event_iface(set), evt);

    // /* Make sure audio_pipeline_remove_listener & audio_event_iface_remove_listener are called before destroying event_iface */
    // audio_event_iface_destroy(evt);

    // /* Release all resources */
    // audio_pipeline_deinit(pipeline);
    // audio_element_deinit(http_stream_reader);
    // audio_element_deinit(i2s_stream_writer);
    // audio_element_deinit(mp3_decoder);
    // esp_periph_set_destroy(set);
    esp_audio_vol_set(gt_pipeline_obj->player, 100);
    AUDIO_MEM_SHOW(TAG);
}

static GTPIPELINE* gt_create_audio_pipeline()
{
    GTPIPELINE* gt_pipeline_obj = (GTPIPELINE*)audio_malloc(sizeof(GTPIPELINE));
    gt_pipeline_obj->msg = (audio_event_iface_msg_t*)audio_malloc(sizeof(audio_event_iface_msg_t));
    gt_pipeline_obj->isStartListen = false;
    return gt_pipeline_obj;
}

GTPIPELINE* gt_pipeline_single()
{
    if(gt_pipeline_obj == NULL)
    {
        gt_pipeline_obj = gt_create_audio_pipeline();
    }
    return gt_pipeline_obj;
}

int gt_audio_pipeline_run(GTPIPELINE* gt_pipeline_obj, const char* uri)
{
    if(!gt_pipeline_obj)
    {
        return ESP_FAIL;
    }

    // audio_element_reset_state(gt_pipeline_obj->http_stream_reader);
    // audio_element_reset_state(gt_pipeline_obj->mp3_decoder);
    // audio_element_reset_state(gt_pipeline_obj->i2s_stream_writer);
    // audio_pipeline_reset_elements(gt_pipeline_obj->pipeline);
    // audio_pipeline_reset_ringbuffer(gt_pipeline_obj->pipeline);

    audio_element_set_uri(gt_pipeline_obj->http_stream_reader, uri);
    
    audio_pipeline_run(gt_pipeline_obj->pipeline);
    return ESP_OK;
}

audio_event_iface_msg_t* get_iface_msg(GTPIPELINE* gt_pipeline_obj)
{
    if(!gt_pipeline_obj)
    {
        return NULL;
    }
    return gt_pipeline_obj->msg;
}

audio_event_iface_handle_t get_evt(GTPIPELINE* gt_pipeline_obj)
{
    return gt_pipeline_obj->evt;
}

audio_element_handle_t get_mp3_decoder(GTPIPELINE* gt_pipeline_obj)
{
    return gt_pipeline_obj->mp3_decoder;
}

audio_element_handle_t get_i2s_stream_writer(GTPIPELINE* gt_pipeline_obj)
{
    return gt_pipeline_obj->i2s_stream_writer;
}

audio_element_handle_t get_http_stream_reader(GTPIPELINE* gt_pipeline_obj)
{
    return gt_pipeline_obj->http_stream_reader;
}

int gt_audio_pipeline_stop(GTPIPELINE* gt_pipeline_obj)
{
    if(!gt_pipeline_obj)
    {
        return ESP_FAIL;
    }
    audio_pipeline_stop(gt_pipeline_obj->pipeline);
    audio_pipeline_wait_for_stop(gt_pipeline_obj->pipeline);

    // 丢弃所有未处理的事件
    audio_event_iface_discard(gt_pipeline_obj->evt);
    
    audio_element_reset_input_ringbuf(gt_pipeline_obj->http_stream_reader);
    audio_element_reset_input_ringbuf(gt_pipeline_obj->mp3_decoder);
    audio_element_reset_input_ringbuf(gt_pipeline_obj->i2s_stream_writer);

    audio_pipeline_reset_elements(gt_pipeline_obj->pipeline);
    audio_pipeline_reset_ringbuffer(gt_pipeline_obj->pipeline);

    // 将所有元素的状态重置到 AEL_STATE_INIT
    audio_element_reset_state(gt_pipeline_obj->http_stream_reader);
    audio_element_reset_state(gt_pipeline_obj->mp3_decoder);
    audio_element_reset_state(gt_pipeline_obj->i2s_stream_writer);

    // audio_event_iface_discard(gt_pipeline_obj->evt);
    return ESP_OK;
}


int gt_audio_pipeline_resume(GTPIPELINE* gt_pipeline_obj)
{
    if(!gt_pipeline_obj)
    {
        return ESP_FAIL;
    }
    audio_pipeline_resume(gt_pipeline_obj->pipeline);
    return ESP_OK;
}

int gt_audio_pipeline_reset_items_state(GTPIPELINE* gt_pipeline_obj)
{
    if(!gt_pipeline_obj)
    {
        return ESP_FAIL;
    }
    audio_pipeline_reset_elements(gt_pipeline_obj->pipeline);
    // audio_pipeline_reset_items_state(gt_pipeline_obj->pipeline);
    
    return ESP_OK;
}

int gt_audio_event_iface_discard (GTPIPELINE* gt_pipeline_obj)
{
    if(!gt_pipeline_obj)
    {
        return ESP_FAIL;
    }
    audio_event_iface_discard(gt_pipeline_obj->evt);
    return ESP_OK;
}


void set_startListen(GTPIPELINE* gt_pipeline_obj, bool value)
{
    if(!gt_pipeline_obj)
    {
        return;
    }
    gt_pipeline_obj->isStartListen = value;
}

bool get_startListen()
{
    return gt_pipeline_obj->isStartListen;
}