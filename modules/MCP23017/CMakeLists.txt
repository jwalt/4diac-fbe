forte_add_module(MCP23017 OFF "MCP23017 16-bit I²C GPIO extender")

if (FORTE_MODULE_MCP23017)
  forte_add_sourcefile_hcpp(I2CDevice)
  forte_add_sourcefile_hcpp(MCP23017_fbt)
endif()
