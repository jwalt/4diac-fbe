/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__action__RotateAbsolute__GetResult__Response
 *** Description:
 *** Version:
 ***     1.0: 2023-03-23/ -  -
 *************************************************************************/

#include "ROS2_turtlesim__action__RotateAbsolute__GetResult__Response_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_turtlesim__action__RotateAbsolute__GetResult__Response_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__GetResult__Response, g_nStringIdROS2_turtlesim__action__RotateAbsolute__GetResult__Response);

const CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response::scmElementNames[] = {g_nStringIdstatus, g_nStringIdresult};

CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response::CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response() :
    CIEC_STRUCT() {
}

CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response::CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response(const CIEC_SINT &pastatus, const CIEC_ROS2_turtlesim__action__RotateAbsolute__Result &paresult) :
    CIEC_STRUCT(),
    var_status(pastatus),
    var_result(paresult) {
}

CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response::getStructTypeNameID() const {
  return g_nStringIdROS2_turtlesim__action__RotateAbsolute__GetResult__Response;
}

void CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_turtlesim__action__RotateAbsolute__GetResult__Response == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_status;
    case 1: return &var_result;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_status;
    case 1: return &var_result;
  }
  return nullptr;
}

