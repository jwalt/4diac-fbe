/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_unique_identifier_msgs__msg__UUID
 *** Description:
 *** Version:
 *************************************************************************/

#include "ROS2_unique_identifier_msgs__msg__UUID_dtp.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_unique_identifier_msgs__msg__UUID_dtp_gen.cpp"
#endif

#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_DATATYPE(ROS2_unique_identifier_msgs__msg__UUID, g_nStringIdROS2_unique_identifier_msgs__msg__UUID);

const CStringDictionary::TStringId CIEC_ROS2_unique_identifier_msgs__msg__UUID::scmElementNames[] = {g_nStringIduuid};

CIEC_ROS2_unique_identifier_msgs__msg__UUID::CIEC_ROS2_unique_identifier_msgs__msg__UUID() :
    CIEC_STRUCT() {
}

CIEC_ROS2_unique_identifier_msgs__msg__UUID::CIEC_ROS2_unique_identifier_msgs__msg__UUID(const CIEC_ARRAY_COMMON<CIEC_USINT> &pauuid) :
    CIEC_STRUCT(),
    var_uuid(pauuid) {
}

CStringDictionary::TStringId CIEC_ROS2_unique_identifier_msgs__msg__UUID::getStructTypeNameID() const {
  return g_nStringIdROS2_unique_identifier_msgs__msg__UUID;
}

void CIEC_ROS2_unique_identifier_msgs__msg__UUID::setValue(const CIEC_ANY &paValue) {
  if (paValue.getDataTypeID() == e_STRUCT) {
    auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
    if (g_nStringIdROS2_unique_identifier_msgs__msg__UUID == otherStruct.getStructTypeNameID()) {
      operator=(static_cast<const CIEC_ROS2_unique_identifier_msgs__msg__UUID &>(paValue));
    }
  }
}

CIEC_ANY *CIEC_ROS2_unique_identifier_msgs__msg__UUID::getMember(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_uuid;
  }
  return nullptr;
}

const CIEC_ANY *CIEC_ROS2_unique_identifier_msgs__msg__UUID::getMember(const size_t paIndex) const {
  switch(paIndex) {
    case 0: return &var_uuid;
  }
  return nullptr;
}

