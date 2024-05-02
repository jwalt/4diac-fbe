/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__action__RotateAbsolute__Feedback
 *** Description:
 *** Version:
 ***     1.0: 2023-03-21/ -  -
 *************************************************************************/

#pragma once

#include "forte_struct.h"

#include "forte_real.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback final : public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__Feedback)

  public:
    CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback();

    CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback(const CIEC_REAL &paremaining);

    CIEC_REAL var_remaining;

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


