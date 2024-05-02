/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_action_msgs__srv__CancelGoal__Request
 *** Description:
 *** Version:
 ***     1.0: 2023-03-15/ -  -
 *************************************************************************/

#include "ROS2_action_msgs__srv__CancelGoal__Request_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_action_msgs__srv__CancelGoal__Request_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_action_msgs__srv__CancelGoal__Request, g_nStringIdROS2_action_msgs__srv__CancelGoal__Request);

const CStringDictionary::TStringId CIEC_ROS2_action_msgs__srv__CancelGoal__Request::scmElementNames[] = {g_nStringIdgoal_info};

CIEC_ROS2_action_msgs__srv__CancelGoal__Request::CIEC_ROS2_action_msgs__srv__CancelGoal__Request() :
    CIEC_STRUCT() {
}

CIEC_ROS2_action_msgs__srv__CancelGoal__Request::CIEC_ROS2_action_msgs__srv__CancelGoal__Request(const CIEC_ROS2_action_msgs__msg__GoalInfo &pagoal_info) :
    CIEC_STRUCT(),
    var_goal_info(pagoal_info) {
}

CStringDictionary::TStringId CIEC_ROS2_action_msgs__srv__CancelGoal__Request::getStructTypeNameID() const {
  return g_nStringIdROS2_action_msgs__srv__CancelGoal__Request;
}

void CIEC_ROS2_action_msgs__srv__CancelGoal__Request::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_action_msgs__srv__CancelGoal__Request == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_action_msgs__srv__CancelGoal__Request &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_action_msgs__srv__CancelGoal__Request::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_goal_info;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_action_msgs__srv__CancelGoal__Request::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_goal_info;
  }
  return nullptr;
}

