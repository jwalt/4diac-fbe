/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__srv__Spawn__Request
 *** Description: turtlesim/srv/Spawn_Request
 *** Version:
 ***     1.0: 2023-03-14/ -  -
 *************************************************************************/

#include "ROS2_turtlesim__srv__Spawn__Request_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_turtlesim__srv__Spawn__Request_dtp_gen.cpp"
#endif

#include "forte_string.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_turtlesim__srv__Spawn__Request, g_nStringIdROS2_turtlesim__srv__Spawn__Request);

const CStringDictionary::TStringId CIEC_ROS2_turtlesim__srv__Spawn__Request::scmElementNames[] = {g_nStringIdx, g_nStringIdy, g_nStringIdtheta, g_nStringIdname};

CIEC_ROS2_turtlesim__srv__Spawn__Request::CIEC_ROS2_turtlesim__srv__Spawn__Request() :
    CIEC_STRUCT(),
    var_name(""_STRING) {
}

CIEC_ROS2_turtlesim__srv__Spawn__Request::CIEC_ROS2_turtlesim__srv__Spawn__Request(const CIEC_REAL &pax, const CIEC_REAL &pay, const CIEC_REAL &patheta, const CIEC_STRING &paname) :
    CIEC_STRUCT(),
    var_x(pax),
    var_y(pay),
    var_theta(patheta),
    var_name(paname) {
}

CStringDictionary::TStringId CIEC_ROS2_turtlesim__srv__Spawn__Request::getStructTypeNameID() const {
  return g_nStringIdROS2_turtlesim__srv__Spawn__Request;
}

void CIEC_ROS2_turtlesim__srv__Spawn__Request::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_turtlesim__srv__Spawn__Request == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_turtlesim__srv__Spawn__Request &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_turtlesim__srv__Spawn__Request::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_x;
    case 1: return &var_y;
    case 2: return &var_theta;
    case 3: return &var_name;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_turtlesim__srv__Spawn__Request::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_x;
    case 1: return &var_y;
    case 2: return &var_theta;
    case 3: return &var_name;
  }
  return nullptr;
}

