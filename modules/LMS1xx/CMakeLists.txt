forte_add_module(LMS1xx OFF "I/O support for SICK LMS1xx laser scanners")

if (FORTE_MODULE_LMS1xx)
  add_subdirectory(liblms1xx)
  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/liblms1xx)
  forte_add_sourcefile_hcpp(LMS1xxNearest_fbt)
  forte_add_sourcefile_hcpp(LMS1xxCommon)
  forte_add_link_library(lms1xx)

  add_executable(lms1xx-test test.cpp)
  target_link_libraries(lms1xx-test lms1xx)
endif()
