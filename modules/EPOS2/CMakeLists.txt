# This is a generated build-system-configuration file for 4diac forte
#
# To use the current directory-name as basis for the module-name use

forte_add_module(EPOS OFF "I/O support for EPOS2 motor controllers")

if (FORTE_MODULE_EPOS)
  forte_add_all_sourcefiles_recursive()
  find_package(epos)
  forte_add_link_library(epos::epos-epos)
  forte_add_link_library(can::can-usb)
  forte_add_link_library(tulibs::tulibs-usb)

  add_executable(EPOS-test test.cpp)
  target_compile_definitions(EPOS-test PRIVATE TEST_STANDALONE)
  target_link_libraries(EPOS-test epos::epos-epos tulibs::tulibs-usb can::can-usb)
  install(TARGETS EPOS-test DESTINATION bin)
endif()
