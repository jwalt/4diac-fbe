/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__action__RotateAbsolute__SendGoal__Response
 *** Description:
 *** Version:
 ***     1.0: 2023-03-23/ -  -
 *************************************************************************/

#pragma once

#include "forte_struct.h"

#include "forte_bool.h"
#include <builtin_interfaces/msg/Time/ROS2_builtin_interfaces__msg__Time_dtp.h>
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Response final : public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__SendGoal__Response)

  public:
    CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Response();

    CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Response(const CIEC_BOOL &paaccepted, const CIEC_ROS2_builtin_interfaces__msg__Time &pastamp);

    CIEC_BOOL var_accepted;
    CIEC_ROS2_builtin_interfaces__msg__Time var_stamp;

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


