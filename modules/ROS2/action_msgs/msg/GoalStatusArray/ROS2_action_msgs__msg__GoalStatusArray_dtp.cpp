/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_action_msgs__msg__GoalStatusArray
 *** Description:
 *** Version:
 ***     1.0: 2023-04-05/ -  -
 *************************************************************************/

#include "ROS2_action_msgs__msg__GoalStatusArray_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_action_msgs__msg__GoalStatusArray_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_action_msgs__msg__GoalStatusArray, g_nStringIdROS2_action_msgs__msg__GoalStatusArray);

const CStringDictionary::TStringId CIEC_ROS2_action_msgs__msg__GoalStatusArray::scmElementNames[] = {g_nStringIdstatus_list};

CIEC_ROS2_action_msgs__msg__GoalStatusArray::CIEC_ROS2_action_msgs__msg__GoalStatusArray() :
    CIEC_STRUCT() {
}

CIEC_ROS2_action_msgs__msg__GoalStatusArray::CIEC_ROS2_action_msgs__msg__GoalStatusArray(const CIEC_ARRAY_COMMON<CIEC_ROS2_action_msgs__msg__GoalStatus> &pastatus_list) :
    CIEC_STRUCT(),
    var_status_list(pastatus_list) {
}

CStringDictionary::TStringId CIEC_ROS2_action_msgs__msg__GoalStatusArray::getStructTypeNameID() const {
  return g_nStringIdROS2_action_msgs__msg__GoalStatusArray;
}

void CIEC_ROS2_action_msgs__msg__GoalStatusArray::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_action_msgs__msg__GoalStatusArray == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_action_msgs__msg__GoalStatusArray &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_action_msgs__msg__GoalStatusArray::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_status_list;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_action_msgs__msg__GoalStatusArray::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_status_list;
  }
  return nullptr;
}

