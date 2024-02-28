forte_add_module(UPDATER OFF "Eclipse hawkBit-based updater")

if (FORTE_MODULE_UPDATER)
  add_executable(updater updater.cpp)
  install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/scripts/ DESTINATION updater USE_SOURCE_PERMISSIONS)
  install(TARGETS updater DESTINATION updater)
  target_link_libraries(updater jsoncpp amqpcpp)
endif()
