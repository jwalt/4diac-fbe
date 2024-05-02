/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request
 *** Description: 
 *** Version:
***     1.0: 2023-03-23/ -  - 
 *************************************************************************/

#include "ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request_gen.cpp"
#endif

DEFINE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request, g_nStringIdROS2_turtlesim__action__RotateAbsolute__SendGoal__Request);

CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request::CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request() :
    CIEC_STRUCT(g_nStringIdROS2_turtlesim__action__RotateAbsolute__SendGoal__Request, 2, scmElementTypes, scmElementNames, e_APPLICATION + e_CONSTRUCTED + 1) {
}

const CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request::scmElementNames[] = {g_nStringIdgoal_id, g_nStringIdgoal};
const CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request::scmElementTypes[] = {g_nStringIdROS2_unique_identifier_msgs__msg__UUID, g_nStringIdROS2_turtlesim__action__RotateAbsolute__Goal};


