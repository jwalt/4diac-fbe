forte_add_module(MAX6675 OFF "I/O support for MAX6675 temperature sensor on SPI 1")

if (FORTE_MODULE_MAX6675)
  forte_add_sourcefile_hcpp(MAX6675_fbt)
endif()
