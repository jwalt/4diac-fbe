project(asio C CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

include(toolchain-utils)
patch(src/Makefile.in "HAVE_CXX" "noHAVE_CXX")

set(AUTOTOOLS_CONFIGURE_OPTIONS
  "--without-boost"
  "--enable-separate-compilation")

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/src/tests/libasio.a DESTINATION lib)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/asio.hpp DESTINATION include)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/asio DESTINATION include)

include(autotools-build)
