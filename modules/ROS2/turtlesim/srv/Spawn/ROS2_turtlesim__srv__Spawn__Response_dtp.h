/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__srv__Spawn__Response
 *** Description: turtlesim/srv/Spawn_Response
 *** Version:
 ***     1.0: 2023-03-14/ -  -
 *************************************************************************/

#pragma once

#include "forte_struct.h"

#include "forte_string.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class CIEC_ROS2_turtlesim__srv__Spawn__Response final : public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_turtlesim__srv__Spawn__Response)

  public:
    CIEC_ROS2_turtlesim__srv__Spawn__Response();

    CIEC_ROS2_turtlesim__srv__Spawn__Response(const CIEC_STRING &paname);

    CIEC_STRING var_name;

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


