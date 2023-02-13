project(tinyxml2)
cmake_minimum_required(VERSION 2.6)

add_library(tinyxml2 STATIC tinyxml2.cpp tinyxml2.h)
install(TARGETS tinyxml2 ARCHIVE DESTINATION lib)
install(FILES tinyxml2.h DESTINATION include)
