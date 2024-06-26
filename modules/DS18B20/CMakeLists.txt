forte_add_module(DS18B20 OFF "I/O support for DS18B20 temperature sensor on P9.12")

if (FORTE_MODULE_DS18B20)
  forte_add_sourcefile_hcpp(DS18B20_fbt)
  forte_add_link_library(stdc++fs)
endif()
