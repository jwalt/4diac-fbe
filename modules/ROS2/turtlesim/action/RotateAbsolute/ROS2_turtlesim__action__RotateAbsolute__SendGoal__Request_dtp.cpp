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

#include "ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request, g_nStringIdROS2_turtlesim__action__RotateAbsolute__SendGoal__Request);

const CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request::scmElementNames[] = {g_nStringIdgoal_id, g_nStringIdgoal};

CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request::CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request() :
    CIEC_STRUCT() {
}

CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request::CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request(const CIEC_ROS2_unique_identifier_msgs__msg__UUID &pagoal_id, const CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal &pagoal) :
    CIEC_STRUCT(),
    var_goal_id(pagoal_id),
    var_goal(pagoal) {
}

CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request::getStructTypeNameID() const {
  return g_nStringIdROS2_turtlesim__action__RotateAbsolute__SendGoal__Request;
}

void CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_turtlesim__action__RotateAbsolute__SendGoal__Request == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_goal_id;
    case 1: return &var_goal;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_goal_id;
    case 1: return &var_goal;
  }
  return nullptr;
}

