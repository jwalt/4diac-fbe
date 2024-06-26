if (NOT WIN32)
  add_library(lms1xx LMS1xx.cpp)
  target_include_directories(lms1xx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif()
