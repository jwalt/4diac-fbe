#********************************************************************************
# Copyright (c) 2018, 2024 OFFIS e.V.
#
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#    Jörg Walter - initial implementation
# *******************************************************************************/
#

PROJECT(ucspi-tcp C)
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

file(WRITE headers.h "
#include <memory.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
")
file(WRITE conf-cc "\"${CMAKE_C_COMPILER}\" ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE} -include headers.h -Wno-implicit-int")
file(WRITE conf-ld "\"${CMAKE_C_COMPILER}\" ${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
file(WRITE conf-home "${CMAKE_INSTALL_PREFIX}")

add_custom_target(build-all ALL
  VERBATIM
  COMMAND make
  COMMAND make setup check
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
