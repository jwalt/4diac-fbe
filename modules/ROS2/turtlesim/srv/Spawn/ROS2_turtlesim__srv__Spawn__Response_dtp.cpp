/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__srv__Spawn__Response
 *** Description: turtlesim/srv/Spawn_Response
 *** Version:
 ***     1.0: 2023-03-14/ -  -
 *************************************************************************/

#include "ROS2_turtlesim__srv__Spawn__Response_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_turtlesim__srv__Spawn__Response_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_turtlesim__srv__Spawn__Response, g_nStringIdROS2_turtlesim__srv__Spawn__Response);

const CStringDictionary::TStringId CIEC_ROS2_turtlesim__srv__Spawn__Response::scmElementNames[] = {g_nStringIdname};

CIEC_ROS2_turtlesim__srv__Spawn__Response::CIEC_ROS2_turtlesim__srv__Spawn__Response() :
    CIEC_STRUCT() {
}

CIEC_ROS2_turtlesim__srv__Spawn__Response::CIEC_ROS2_turtlesim__srv__Spawn__Response(const CIEC_STRING &paname) :
    CIEC_STRUCT(),
    var_name(paname) {
}

CStringDictionary::TStringId CIEC_ROS2_turtlesim__srv__Spawn__Response::getStructTypeNameID() const {
  return g_nStringIdROS2_turtlesim__srv__Spawn__Response;
}

void CIEC_ROS2_turtlesim__srv__Spawn__Response::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_turtlesim__srv__Spawn__Response == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_turtlesim__srv__Spawn__Response &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_turtlesim__srv__Spawn__Response::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_name;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_turtlesim__srv__Spawn__Response::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_name;
  }
  return nullptr;
}

