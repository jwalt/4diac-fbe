cmake_minimum_required(VERSION 3.13)
project(tulibs LANGUAGES C VERSION 0.2014.10.3)

find_package(libusb-1.0)
find_package(libusb-compat-0.1)
find_package(libftdi)
find_package(libudev)
find_package(bzip2 CONFIG)
find_package(zlib CONFIG)
find_package(gnu-gsl)

file(WRITE src/lib/execinfo.h
  "inline static size_t backtrace(void *x, int y) { return 0; }\n"
  "inline static void* backtrace_symbols(void *x, int y) { return NULL; }\n"
)

include(ReMake)
add_subdirectory(src)

target_link_libraries(tulibs-ftdi PUBLIC libusb::usb libudev::udev libftdi::ftdi pthread)
target_link_libraries(tulibs-file PUBLIC zlib::zlib bzip2::bz2)
target_link_libraries(tulibs-usb PUBLIC libusb::usb-1.0 libudev::udev pthread)
target_link_libraries(tulibs-spline PUBLIC gnu-gsl::gsl)
target_link_libraries(tulibs-transform PUBLIC gnu-gsl::gsl)

target_compile_options(tulibs-serial PRIVATE -include sys/select.h)

include(toolchain-utils)
install_export_config()
