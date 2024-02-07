project(fastdds C CXX)
cmake_minimum_required(VERSION 3.20)

include(toolchain-utils)

set(BUILD_TESTING ON CACHE BOOL "")
set(COMPILE_TOOLS ON CACHE BOOL "")
set(THIRDPARTY_UPDATE OFF CACHE BOOL "")

set(Asio_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE STRING "" FORCE)

set(TINYXML2_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE STRING "" FORCE)
set(TINYXML2_LIBRARY "${CMAKE_INSTALL_PREFIX}/lib/libtinyxml2.a" CACHE STRING "" FORCE)

include(${CGET_CMAKE_ORIGINAL_SOURCE_FILE})

patch(src/cpp/rtps/reader/WriterProxy.cpp "#define SHOULD_DEBUG_LINUX" "")