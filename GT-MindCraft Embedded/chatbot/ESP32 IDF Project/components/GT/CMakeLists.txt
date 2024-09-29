set(src_dirs
            GT_DRV
            GT_TOUCH
            SPI
            FLASH_SPI
            LCD
            ESPTIM
            screen
            CJSON
            GUI
            GUI/driver
            GUI/examples
            GUI/examples/widgets
            GUI/src
            GUI/src/core
            GUI/src/extra
            GUI/src/extra/draw
            GUI/src/extra/gif
            GUI/src/extra/jpeg
            GUI/src/extra/png
            GUI/src/font
            GUI/src/hal
            GUI/src/others
            GUI/src/utils
            GUI/src/widgets)

set(include_dirs
            GT_DRV
            GT_TOUCH
            SPI
            FLASH_SPI
            LCD
            ESPTIM
            screen
            CJSON
            GUI
            GUI/driver
            GUI/examples
            GUI/examples/widgets
            GUI/src
            GUI/src/core
            GUI/src/extra
            GUI/src/extra/draw
            GUI/src/extra/gif
            GUI/src/extra/jpeg
            GUI/src/extra/png
            GUI/src/font
            GUI/src/hal
            GUI/src/others
            GUI/src/utils
            GUI/src/widgets)

set(requires
            log
            esp_wifi
            esp_event
            wpa_supplicant
            audio_board
            audio_hal
            audio_mixer
            audio_stream
            audio_recorder
            audio_sal
            audio_stream
            esp_peripherals
            esp_common)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})

component_compile_options(-ffast-math -O3 -Wno-error=stringop-overflow -Wno-format -Wno-error=maybe-uninitialized)


# 设置静态库路径
set(FONT_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/GUI/driver)
# set(FONT_LIB_PATH ${CMAKE_SOURCE_DIR}/components/GT/GUI/driver)

# 链接静态库
target_link_libraries(${COMPONENT_LIB} ${FONT_LIB_PATH}/libgt_gui_driver.a)