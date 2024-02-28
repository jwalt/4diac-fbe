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

PROJECT(tinyssh C)
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

add_custom_target(build-all ALL
  VERBATIM
  COMMAND ${CMAKE_COMMAND} -E env
  "LDFLAGS=${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_EXE_LINKER_FLAGS_RELEASE}"
  "CFLAGS=${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}"
  "CC=${CMAKE_C_COMPILER}"
  sh make-tinysshcc.sh
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin DESTINATION .)
