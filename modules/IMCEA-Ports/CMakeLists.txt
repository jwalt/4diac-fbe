add_subdirectory(libimcea)

forte_add_module(SIEMENS_IMCEA OFF "I/O support for Siemens Microboxes using the IMCEA driver")

if (FORTE_MODULE_SIEMENS_IMCEA)
  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

  forte_add_sourcefile_hcpp(../../org.eclipse.4diac.forte/src/stdfblib/io/IX)
  forte_add_sourcefile_hcpp(../../org.eclipse.4diac.forte/src/stdfblib/io/QX)
  forte_add_sourcefile_hcpp(processinterface)

  forte_add_link_library(imcea)
endif()
