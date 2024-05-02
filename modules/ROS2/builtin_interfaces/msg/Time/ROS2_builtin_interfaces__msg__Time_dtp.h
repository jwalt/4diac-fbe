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

#pragma once

#include "forte_struct.h"

#include "forte_int.h"
#include "forte_uint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class CIEC_ROS2_builtin_interfaces__msg__Time final : public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_builtin_interfaces__msg__Time)

  public:
    CIEC_ROS2_builtin_interfaces__msg__Time();

    CIEC_ROS2_builtin_interfaces__msg__Time(const CIEC_INT &pasec, const CIEC_UINT &pananosec);

    CIEC_INT var_sec;
    CIEC_UINT var_nanosec;

    size_t getStructSize() const override {
      return 2;
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


