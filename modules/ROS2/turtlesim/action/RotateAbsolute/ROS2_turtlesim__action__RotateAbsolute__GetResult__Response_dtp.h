/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__action__RotateAbsolute__GetResult__Response
 *** Description:
 *** Version:
 ***     1.0: 2023-03-23/ -  -
 *************************************************************************/

#pragma once

#include "forte_struct.h"

#include "forte_sint.h"
#include "ROS2_turtlesim__action__RotateAbsolute__Result_dtp.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response final : public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__GetResult__Response)

  public:
    CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response();

    CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response(const CIEC_SINT &pastatus, const CIEC_ROS2_turtlesim__action__RotateAbsolute__Result &paresult);

    CIEC_SINT var_status;
    CIEC_ROS2_turtlesim__action__RotateAbsolute__Result var_result;

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


