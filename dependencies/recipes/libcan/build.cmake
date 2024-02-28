cmake_minimum_required(VERSION 3.13)
project(can LANGUAGES C VERSION 0.2014.9.24)

find_package(tulibs)

include(ReMake)

add_subdirectory(src/can)
add_subdirectory(src/serial)
add_subdirectory(src/usb)

target_include_directories(can-serial PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/can)
target_link_libraries(can-serial PUBLIC tulibs::tulibs-serial)

target_include_directories(can-usb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/can)
target_link_libraries(can-usb PUBLIC tulibs::tulibs-ftdi)

include(toolchain-utils)
install_export_config()
