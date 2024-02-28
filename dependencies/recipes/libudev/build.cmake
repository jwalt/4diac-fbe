cmake_minimum_required(VERSION 3.13)
project(libudev LANGUAGES C VERSION 3.2.8)

if (WIN32)
  message(FATAL_ERROR "windows not supported")
elseif (APPLE)
  message(FATAL_ERROR "macOS not supported")
elseif (UNIX)
else()
  message(FATAL_ERROR "Target OS not known")
endif()

add_library(udev
  src/libudev/libudev.c
  src/libudev/libudev-list.c
  src/libudev/libudev-util.c
  src/libudev/libudev-device.c
  src/libudev/libudev-enumerate.c
  src/libudev/libudev-monitor.c
  src/libudev/libudev-queue.c
  src/libudev/libudev-hwdb.c

  src/shared/conf-files.c
  src/shared/device-nodes.c
  src/shared/dev-setup.c
  src/shared/fileio.c
  src/shared/hashmap.c
  src/shared/label.c
  src/shared/log.c
  src/shared/mempool.c
  src/shared/mkdir.c
  src/shared/mkdir-label.c
  src/shared/MurmurHash2.c
  src/shared/path-util.c
  src/shared/process-util.c
  src/shared/random-util.c
  src/shared/selinux-util.c
  src/shared/siphash24.c
  src/shared/smack-util.c
  src/shared/strbuf.c
  src/shared/strv.c
  src/shared/strxcpyx.c
  src/shared/sysctl-util.c
  src/shared/terminal-util.c
  src/shared/time-util.c
  src/shared/util.c
  src/shared/utf8.c
  src/shared/virt.c
  )

target_include_directories(udev PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/shared)
file(WRITE src/shared/config.h [=[
  #define HAVE_DECL_NAME_TO_HANDLE_AT 1
  #define HAVE_DECL_STRNDUPA 1
  #define HAVE_DECL_GETTID 1
]=])

target_compile_definitions(udev PRIVATE
  "UDEV_CONF_FILE=\"/dev/null\""
  "UDEV_ROOT_RUN=\"/dev/null\""
  "UDEV_HWDB_BIN=\"/dev/null\""
  _GNU_SOURCE
  "SIZEOF_TIME_T=4"
  "SIZEOF_PID_T=4"
  "SIZEOF_UID_T=4"
  "SIZEOF_GID_T=4"
  "SIZEOF_RLIM_T=4"
  "SIZEOF_DEV_T=8"
  "SIZEOF_INO_T=4"
  )


install(TARGETS udev EXPORT ${CMAKE_PROJECT_NAME} DESTINATION lib)
install(FILES src/libudev/libudev.h DESTINATION include)

include(toolchain-utils)
install_export_config()
