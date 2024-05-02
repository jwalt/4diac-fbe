/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__srv__Spawn__Request
 *** Description: turtlesim/srv/Spawn_Request
 *** Version:
***     1.0: 2023-03-14/ -  - 
 *************************************************************************/

#include "ROS2_turtlesim__srv__Spawn__Request.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_turtlesim__srv__Spawn__Request_gen.cpp"
#endif

DEFINE_FIRMWARE_DATATYPE(ROS2_turtlesim__srv__Spawn__Request, g_nStringIdROS2_turtlesim__srv__Spawn__Request);

CIEC_ROS2_turtlesim__srv__Spawn__Request::CIEC_ROS2_turtlesim__srv__Spawn__Request() :
    CIEC_STRUCT(g_nStringIdROS2_turtlesim__srv__Spawn__Request, 4, scmElementTypes, scmElementNames, e_APPLICATION + e_CONSTRUCTED + 1) {
}

const CStringDictionary::TStringId CIEC_ROS2_turtlesim__srv__Spawn__Request::scmElementNames[] = {g_nStringIdx, g_nStringIdy, g_nStringIdtheta, g_nStringIdname};
const CStringDictionary::TStringId CIEC_ROS2_turtlesim__srv__Spawn__Request::scmElementTypes[] = {g_nStringIdREAL, g_nStringIdREAL, g_nStringIdREAL, g_nStringIdSTRING};


