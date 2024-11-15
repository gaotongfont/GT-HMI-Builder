# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

include($ENV{ADF_PATH}/CMakeLists.txt)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

include_directories($ENV{IDF_PATH}/examples/common_components/protocol_examples_common/include)
include_directories($ENV{IDF_PATH}/components/esp_http_client/include)

include_directories($ENV{ADF_PATH}/components/input_key_service/include)
include_directories($ENV{ADF_PATH}/components/esp-adf-libs/esp_codec/include)

project(31_recoding)
