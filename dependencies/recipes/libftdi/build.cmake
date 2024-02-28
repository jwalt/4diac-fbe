cmake_minimum_required(VERSION 3.13)
project(libftdi LANGUAGES C VERSION 0.20)

find_package(libusb-compat-0.1)

add_library(ftdi src/ftdi.c)
target_link_libraries(ftdi PUBLIC libusb::usb)
install(TARGETS ftdi EXPORT ${CMAKE_PROJECT_NAME} DESTINATION lib)
install(FILES src/ftdi.h DESTINATION include)

include(toolchain-utils)
install_export_config()
