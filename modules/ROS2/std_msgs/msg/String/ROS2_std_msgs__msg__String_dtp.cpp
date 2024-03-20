/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_std_msgs__msg__String
 *** Description: Primitive Type: String
 *** Version:
 *************************************************************************/

#include "ROS2_std_msgs__msg__String_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_std_msgs__msg__String_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_std_msgs__msg__String, g_nStringIdROS2_std_msgs__msg__String);

const CStringDictionary::TStringId CIEC_ROS2_std_msgs__msg__String::scmElementNames[] = {g_nStringIddata};

CIEC_ROS2_std_msgs__msg__String::CIEC_ROS2_std_msgs__msg__String() :
    CIEC_STRUCT() {
}

CIEC_ROS2_std_msgs__msg__String::CIEC_ROS2_std_msgs__msg__String(const CIEC_STRING &padata) :
    CIEC_STRUCT(),
    var_data(padata) {
}

CStringDictionary::TStringId CIEC_ROS2_std_msgs__msg__String::getStructTypeNameID() const {
  return g_nStringIdROS2_std_msgs__msg__String;
}

void CIEC_ROS2_std_msgs__msg__String::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_std_msgs__msg__String == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_std_msgs__msg__String &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_std_msgs__msg__String::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_data;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_std_msgs__msg__String::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_data;
  }
  return nullptr;
}

