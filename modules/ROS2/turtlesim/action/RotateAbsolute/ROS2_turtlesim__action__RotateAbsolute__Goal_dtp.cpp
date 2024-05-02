/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__action__RotateAbsolute__Goal
 *** Description:
 *** Version:
 ***     1.0: 2023-03-21/ -  -
 *************************************************************************/

#include "ROS2_turtlesim__action__RotateAbsolute__Goal_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_turtlesim__action__RotateAbsolute__Goal_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__Goal, g_nStringIdROS2_turtlesim__action__RotateAbsolute__Goal);

const CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal::scmElementNames[] = {g_nStringIdtheta};

CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal::CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal() :
    CIEC_STRUCT() {
}

CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal::CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal(const CIEC_REAL &patheta) :
    CIEC_STRUCT(),
    var_theta(patheta) {
}

CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal::getStructTypeNameID() const {
  return g_nStringIdROS2_turtlesim__action__RotateAbsolute__Goal;
}

void CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_turtlesim__action__RotateAbsolute__Goal == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_theta;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_theta;
  }
  return nullptr;
}

