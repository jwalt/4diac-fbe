cmake_minimum_required(VERSION 3.13)
project(libusb-compat-0.1 LANGUAGES C VERSION 0.1.7)

find_package(libusb-1.0)

add_library(usb libusb/core.c)
target_link_libraries(usb PUBLIC libusb::usb-1.0)

file(WRITE libusb/config.h "")
target_include_directories(usb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libusb)
target_compile_definitions(usb PRIVATE "API_EXPORTED=__attribute__((visibility(\"default\")))")

install(TARGETS usb EXPORT ${CMAKE_PROJECT_NAME} DESTINATION lib)
install(FILES libusb/usb.h DESTINATION include)

include(toolchain-utils)
install_export_config(libusb-compat-0.1 libusb)
