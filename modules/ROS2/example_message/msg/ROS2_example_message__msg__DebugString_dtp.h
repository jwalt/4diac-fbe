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

#pragma once

#include "forte_struct.h"

#include "forte_string.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class CIEC_ROS2_example_message__msg__DebugString final : public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_example_message__msg__DebugString)

  public:
    CIEC_ROS2_example_message__msg__DebugString();

    CIEC_ROS2_example_message__msg__DebugString(const CIEC_STRING &padata);

    CIEC_STRING var_data;

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


