# *******************************************************************************
# *******************************************************************************
# Copyright (c) 2024 OFFIS e.V.
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#     Malte Grave - initial implementation
# *******************************************************************************/
# *******************************************************************************/

forte_add_module(ROS2 ON "ROS2 data types for the FastDDS layer")
if (FORTE_MODULE_ROS2)
  add_subdirectory("action_msgs")
  add_subdirectory("builtin_interfaces")
  add_subdirectory("example_interfaces")
  add_subdirectory("example_message")
  add_subdirectory("turtlesim")
  add_subdirectory("unique_identifier_msgs")
  
  forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
endif()
