cmake_minimum_required(VERSION 3.12)
project(opencv_contrib-src)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/modules/ DESTINATION src/opencv_contrib/modules/)
