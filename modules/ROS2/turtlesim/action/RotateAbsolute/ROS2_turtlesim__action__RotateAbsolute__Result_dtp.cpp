/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__action__RotateAbsolute__Result
 *** Description:
 *** Version:
 ***     1.0: 2023-03-21/ -  -
 *************************************************************************/

#include "ROS2_turtlesim__action__RotateAbsolute__Result_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_turtlesim__action__RotateAbsolute__Result_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__Result, g_nStringIdROS2_turtlesim__action__RotateAbsolute__Result);

const CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__Result::scmElementNames[] = {g_nStringIddelta};

CIEC_ROS2_turtlesim__action__RotateAbsolute__Result::CIEC_ROS2_turtlesim__action__RotateAbsolute__Result() :
    CIEC_STRUCT() {
}

CIEC_ROS2_turtlesim__action__RotateAbsolute__Result::CIEC_ROS2_turtlesim__action__RotateAbsolute__Result(const CIEC_REAL &padelta) :
    CIEC_STRUCT(),
    var_delta(padelta) {
}

CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__Result::getStructTypeNameID() const {
  return g_nStringIdROS2_turtlesim__action__RotateAbsolute__Result;
}

void CIEC_ROS2_turtlesim__action__RotateAbsolute__Result::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_turtlesim__action__RotateAbsolute__Result == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_turtlesim__action__RotateAbsolute__Result &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_turtlesim__action__RotateAbsolute__Result::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_delta;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_turtlesim__action__RotateAbsolute__Result::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_delta;
  }
  return nullptr;
}

