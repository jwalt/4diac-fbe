cmake_minimum_required(VERSION 3.13)
project(libusb-1.0 LANGUAGES C VERSION 1.0.22)

if (WIN32)
  add_compile_definitions(OS_WINDOWS=1 "POLL_NFDS_TYPE=unsigned int")
  set(srcs
	libusb/os/poll_windows.c
	libusb/os/threads_windows.c
	libusb/os/windows_nt_common.c
	libusb/os/windows_usbdk.c
	libusb/os/windows_winusb.c
	)
elseif (APPLE)
  message(FATAL_ERROR "macOS not yet functional")
  add_compile_definitions(OS_DARWIN=1 POLL_NFDS_TYPE=nfds_t THREADS_POSIX=1 HAVE_POLL_H=1)
  set(srcs
	libusb/os/poll_posix.c
	libusb/os/threads_posix.c
	libusb/os/darwin_usb.c
	)
elseif (UNIX)
  add_compile_definitions(OS_LINUX=1 POLL_NFDS_TYPE=nfds_t THREADS_POSIX=1 HAVE_POLL_H=1)
  set(srcs
	libusb/os/poll_posix.c
	libusb/os/threads_posix.c
	libusb/os/linux_usbfs.c
	libusb/os/linux_netlink.c
	)
else()
  message(FATAL_ERROR "Target OS not known")
endif()

add_compile_definitions("DEFAULT_VISIBILITY=__attribute__((visibility(\"default\")))")
add_compile_definitions(_GNU_SOURCE=1 HAVE_SYS_TIME_H=1 HAVE_SYS_TYPES_H=1)

add_library(usb-1.0
  ${srcs}

  libusb/core.c
  libusb/descriptor.c
  libusb/hotplug.c
  libusb/io.c
  libusb/strerror.c
  libusb/sync.c
  )

target_include_directories(usb-1.0 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libusb)
target_include_directories(usb-1.0 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libusb/os)

file(WRITE libusb/config.h "")

install(TARGETS usb-1.0 EXPORT ${CMAKE_PROJECT_NAME} DESTINATION lib)
install(FILES libusb/libusb.h DESTINATION include)


include(toolchain-utils)
install_export_config(libusb-1.0 libusb)
