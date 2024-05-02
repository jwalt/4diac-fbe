/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_action_msgs__srv__CancelGoal__Response
 *** Description:
 *** Version:
 ***     1.0: 2023-03-15/ -  -
 *************************************************************************/

#include "ROS2_action_msgs__srv__CancelGoal__Response_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_action_msgs__srv__CancelGoal__Response_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_action_msgs__srv__CancelGoal__Response, g_nStringIdROS2_action_msgs__srv__CancelGoal__Response);

const CStringDictionary::TStringId CIEC_ROS2_action_msgs__srv__CancelGoal__Response::scmElementNames[] = {g_nStringIdreturn_code, g_nStringIdgoals_canceling};

CIEC_ROS2_action_msgs__srv__CancelGoal__Response::CIEC_ROS2_action_msgs__srv__CancelGoal__Response() :
    CIEC_STRUCT() {
}

CIEC_ROS2_action_msgs__srv__CancelGoal__Response::CIEC_ROS2_action_msgs__srv__CancelGoal__Response(const CIEC_SINT &pareturn_code, const CIEC_ARRAY_COMMON<CIEC_ROS2_action_msgs__msg__GoalInfo> &pagoals_canceling) :
    CIEC_STRUCT(),
    var_return_code(pareturn_code),
    var_goals_canceling(pagoals_canceling) {
}

CStringDictionary::TStringId CIEC_ROS2_action_msgs__srv__CancelGoal__Response::getStructTypeNameID() const {
  return g_nStringIdROS2_action_msgs__srv__CancelGoal__Response;
}

void CIEC_ROS2_action_msgs__srv__CancelGoal__Response::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_action_msgs__srv__CancelGoal__Response == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_action_msgs__srv__CancelGoal__Response &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_action_msgs__srv__CancelGoal__Response::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_return_code;
    case 1: return &var_goals_canceling;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_action_msgs__srv__CancelGoal__Response::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_return_code;
    case 1: return &var_goals_canceling;
  }
  return nullptr;
}

