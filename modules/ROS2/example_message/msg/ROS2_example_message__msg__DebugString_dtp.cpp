/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_example_message__msg__DebugString
 *** Description: A Template for a Data Type
 *** Version:
 ***     1.0: 2024-04-18/ -  -
 *************************************************************************/

#include "ROS2_example_message__msg__DebugString_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_example_message__msg__DebugString_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_example_message__msg__DebugString, g_nStringIdROS2_example_message__msg__DebugString);

const CStringDictionary::TStringId CIEC_ROS2_example_message__msg__DebugString::scmElementNames[] = {g_nStringIddata};

CIEC_ROS2_example_message__msg__DebugString::CIEC_ROS2_example_message__msg__DebugString() :
    CIEC_STRUCT() {
}

CIEC_ROS2_example_message__msg__DebugString::CIEC_ROS2_example_message__msg__DebugString(const CIEC_STRING &padata) :
    CIEC_STRUCT(),
    var_data(padata) {
}

CStringDictionary::TStringId CIEC_ROS2_example_message__msg__DebugString::getStructTypeNameID() const {
  return g_nStringIdROS2_example_message__msg__DebugString;
}

void CIEC_ROS2_example_message__msg__DebugString::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_example_message__msg__DebugString == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_example_message__msg__DebugString &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_example_message__msg__DebugString::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_data;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_example_message__msg__DebugString::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_data;
  }
  return nullptr;
}

