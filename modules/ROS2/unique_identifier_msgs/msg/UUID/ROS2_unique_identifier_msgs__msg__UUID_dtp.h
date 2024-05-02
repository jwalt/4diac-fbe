/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_unique_identifier_msgs__msg__UUID
 *** Description:
 *** Version:
 ***     1.0: 2023-03-15/ -  -
 *************************************************************************/

#pragma once

#include "forte_struct.h"

#include "forte_usint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class CIEC_ROS2_unique_identifier_msgs__msg__UUID final : public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_unique_identifier_msgs__msg__UUID)

  public:
    CIEC_ROS2_unique_identifier_msgs__msg__UUID();

    CIEC_ROS2_unique_identifier_msgs__msg__UUID(const CIEC_ARRAY_COMMON<CIEC_USINT> &pauuid);

    CIEC_ARRAY_FIXED<CIEC_USINT, 0, 15> var_uuid;

    size_t getStructSize() const override {
      return 1;
    }

    const CStringDictionary::TStringId* elementNames() const override {
      return scmElementNames;
    }

    CStringDictionary::TStringId getStructTypeNameID() const override;

    void setValue(const CIEC_ANY &paValue) override;

    CIEC_ANY *getMember(size_t) override;
    const CIEC_ANY *getMember(size_t) const override;

  private:
    static const CStringDictionary::TStringId scmElementNames[];

};


