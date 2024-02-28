cmake_minimum_required(VERSION 3.13)
project(epos LANGUAGES C VERSION 0.2014.9.25)

find_package(tulibs)
find_package(can)

include(ReMake)

add_subdirectory(src)

target_link_libraries(epos-epos PUBLIC tulibs::tulibs-timer can::can-serial tulibs::tulibs-config m)
target_link_libraries(epos-interpolated_position_eval PUBLIC tulibs::tulibs-spline)
target_link_libraries(epos-spline_to_interpolated_position PUBLIC tulibs::tulibs-spline)

include(toolchain-utils)
install_export_config()
