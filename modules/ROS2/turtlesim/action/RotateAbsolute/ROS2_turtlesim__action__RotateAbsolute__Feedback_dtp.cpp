/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__action__RotateAbsolute__Feedback
 *** Description:
 *** Version:
 ***     1.0: 2023-03-21/ -  -
 *************************************************************************/

#include "ROS2_turtlesim__action__RotateAbsolute__Feedback_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_turtlesim__action__RotateAbsolute__Feedback_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__Feedback, g_nStringIdROS2_turtlesim__action__RotateAbsolute__Feedback);

const CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback::scmElementNames[] = {g_nStringIdremaining};

CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback::CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback() :
    CIEC_STRUCT() {
}

CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback::CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback(const CIEC_REAL &paremaining) :
    CIEC_STRUCT(),
    var_remaining(paremaining) {
}

CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback::getStructTypeNameID() const {
  return g_nStringIdROS2_turtlesim__action__RotateAbsolute__Feedback;
}

void CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_turtlesim__action__RotateAbsolute__Feedback == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_remaining;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_remaining;
  }
  return nullptr;
}

