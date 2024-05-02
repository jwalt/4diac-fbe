/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_action_msgs__msg__GoalInfo
 *** Description:
 *** Version:
 ***     1.0: 2023-03-15/ -  -
 *************************************************************************/

#include "ROS2_action_msgs__msg__GoalInfo_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_action_msgs__msg__GoalInfo_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_action_msgs__msg__GoalInfo, g_nStringIdROS2_action_msgs__msg__GoalInfo);

const CStringDictionary::TStringId CIEC_ROS2_action_msgs__msg__GoalInfo::scmElementNames[] = {g_nStringIdgoal_id, g_nStringIdstamp};

CIEC_ROS2_action_msgs__msg__GoalInfo::CIEC_ROS2_action_msgs__msg__GoalInfo() :
    CIEC_STRUCT() {
}

CIEC_ROS2_action_msgs__msg__GoalInfo::CIEC_ROS2_action_msgs__msg__GoalInfo(const CIEC_ROS2_unique_identifier_msgs__msg__UUID &pagoal_id, const CIEC_ROS2_builtin_interfaces__msg__Time &pastamp) :
    CIEC_STRUCT(),
    var_goal_id(pagoal_id),
    var_stamp(pastamp) {
}

CStringDictionary::TStringId CIEC_ROS2_action_msgs__msg__GoalInfo::getStructTypeNameID() const {
  return g_nStringIdROS2_action_msgs__msg__GoalInfo;
}

void CIEC_ROS2_action_msgs__msg__GoalInfo::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_action_msgs__msg__GoalInfo == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_action_msgs__msg__GoalInfo &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_action_msgs__msg__GoalInfo::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_goal_id;
    case 1: return &var_stamp;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_action_msgs__msg__GoalInfo::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_goal_id;
    case 1: return &var_stamp;
  }
  return nullptr;
}

