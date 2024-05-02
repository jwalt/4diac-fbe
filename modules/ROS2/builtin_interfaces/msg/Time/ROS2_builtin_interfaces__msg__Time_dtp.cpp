/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_builtin_interfaces__msg__Time
 *** Description:
 *** Version:
 ***     1.0: 2023-03-15/ -  -
 *************************************************************************/

#include "ROS2_builtin_interfaces__msg__Time_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_builtin_interfaces__msg__Time_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_builtin_interfaces__msg__Time, g_nStringIdROS2_builtin_interfaces__msg__Time);

const CStringDictionary::TStringId CIEC_ROS2_builtin_interfaces__msg__Time::scmElementNames[] = {g_nStringIdsec, g_nStringIdnanosec};

CIEC_ROS2_builtin_interfaces__msg__Time::CIEC_ROS2_builtin_interfaces__msg__Time() :
    CIEC_STRUCT() {
}

CIEC_ROS2_builtin_interfaces__msg__Time::CIEC_ROS2_builtin_interfaces__msg__Time(const CIEC_INT &pasec, const CIEC_UINT &pananosec) :
    CIEC_STRUCT(),
    var_sec(pasec),
    var_nanosec(pananosec) {
}

CStringDictionary::TStringId CIEC_ROS2_builtin_interfaces__msg__Time::getStructTypeNameID() const {
  return g_nStringIdROS2_builtin_interfaces__msg__Time;
}

void CIEC_ROS2_builtin_interfaces__msg__Time::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_builtin_interfaces__msg__Time == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_builtin_interfaces__msg__Time &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_builtin_interfaces__msg__Time::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_sec;
    case 1: return &var_nanosec;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_builtin_interfaces__msg__Time::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_sec;
    case 1: return &var_nanosec;
  }
  return nullptr;
}

