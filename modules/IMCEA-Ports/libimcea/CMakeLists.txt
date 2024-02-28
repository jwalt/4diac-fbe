set(IMCEA_DIR "" CACHE STRING "Base directory of extracted IMCEA driver installer")

if (IMCEA_DIR)
  add_library(imcea
	${IMCEA_DIR}/examples/imcealib.cpp
	${IMCEA_DIR}/examples/pcio.cpp
	${IMCEA_DIR}/examples/pcioPortWin32.cpp
	)
  target_compile_definitions(imcea PRIVATE PCIO_VERBOSE)

  if (MINGW)
	# MinGW workaround. Proper solution would be a one-line patch to imcdrv.h,
	# but copyright...
	forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
	target_include_directories(imcea PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
	target_compile_definitions(imcea PUBLIC IMCEA_IMCDRV_PATH="${IMCEA_DIR}/inc/imcdrv.h")
	target_compile_definitions(imcea PUBLIC IMCEA_IMCEALIB_PATH="${IMCEA_DIR}/inc/imcealib.h")
	target_compile_definitions(imcea PUBLIC IMCEA_PCIOPORTWIN32_PATH="${IMCEA_DIR}/inc/pcioPortWin32.h")
	target_compile_definitions(imcea PUBLIC IMCEA_PCIOPORT_PATH="${IMCEA_DIR}/inc/pcioPort.h")
	target_compile_definitions(imcea PUBLIC IMCEA_PCIO_PATH="${IMCEA_DIR}/inc/pcio.h")
	target_compile_definitions(imcea PUBLIC IMCEA_CIO_PATH="${IMCEA_DIR}/inc/cio.h")
	target_compile_options(imcea PRIVATE
	  -Wno-write-strings -Wno-unused-variable -Wno-unused-parameter -Wno-format
	  -Wno-type-limits -Wno-unused-but-set-variable -Wno-error -Wno-narrowing)
  else()
    target_include_directories(imcea PUBLIC ${IMCEA_DIR}/inc)
  endif()

endif()
