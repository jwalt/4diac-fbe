/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage
 *** Description:
 *** Version:
 ***     1.0: 2023-03-23/ -  -
 *************************************************************************/

#include "ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage, g_nStringIdROS2_turtlesim__action__RotateAbsolute__FeedbackMessage);

const CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage::scmElementNames[] = {g_nStringIdgoal_id, g_nStringIdfeedback};

CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage::CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage() :
    CIEC_STRUCT() {
}

CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage::CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage(const CIEC_ROS2_unique_identifier_msgs__msg__UUID &pagoal_id, const CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback &pafeedback) :
    CIEC_STRUCT(),
    var_goal_id(pagoal_id),
    var_feedback(pafeedback) {
}

CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage::getStructTypeNameID() const {
  return g_nStringIdROS2_turtlesim__action__RotateAbsolute__FeedbackMessage;
}

void CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_turtlesim__action__RotateAbsolute__FeedbackMessage == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_goal_id;
    case 1: return &var_feedback;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_goal_id;
    case 1: return &var_feedback;
  }
  return nullptr;
}

