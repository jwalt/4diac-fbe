/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_action_msgs__msg__GoalStatus
 *** Description:
 *** Version:
 ***     1.0: 2023-04-05/ -  -
 *************************************************************************/

#include "ROS2_action_msgs__msg__GoalStatus_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_action_msgs__msg__GoalStatus_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_action_msgs__msg__GoalStatus, g_nStringIdROS2_action_msgs__msg__GoalStatus);

const CStringDictionary::TStringId CIEC_ROS2_action_msgs__msg__GoalStatus::scmElementNames[] = {g_nStringIdgoal_info, g_nStringIdstatus};

CIEC_ROS2_action_msgs__msg__GoalStatus::CIEC_ROS2_action_msgs__msg__GoalStatus() :
    CIEC_STRUCT() {
}

CIEC_ROS2_action_msgs__msg__GoalStatus::CIEC_ROS2_action_msgs__msg__GoalStatus(const CIEC_ROS2_action_msgs__msg__GoalInfo &pagoal_info, const CIEC_SINT &pastatus) :
    CIEC_STRUCT(),
    var_goal_info(pagoal_info),
    var_status(pastatus) {
}

CStringDictionary::TStringId CIEC_ROS2_action_msgs__msg__GoalStatus::getStructTypeNameID() const {
  return g_nStringIdROS2_action_msgs__msg__GoalStatus;
}

void CIEC_ROS2_action_msgs__msg__GoalStatus::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_action_msgs__msg__GoalStatus == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_action_msgs__msg__GoalStatus &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_action_msgs__msg__GoalStatus::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_goal_info;
    case 1: return &var_status;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_action_msgs__msg__GoalStatus::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_goal_info;
    case 1: return &var_status;
  }
  return nullptr;
}

