/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_action_msgs__msg__GoalStatus
 *** Description:
 *** Version:
 ***     1.0: 2023-04-05/ -  -
 *************************************************************************/

#pragma once

#include "forte_struct.h"

#include <action_msgs/msg/GoalInfo/ROS2_action_msgs__msg__GoalInfo_dtp.h>
#include "forte_sint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class CIEC_ROS2_action_msgs__msg__GoalStatus final : public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_action_msgs__msg__GoalStatus)

  public:
    CIEC_ROS2_action_msgs__msg__GoalStatus();

    CIEC_ROS2_action_msgs__msg__GoalStatus(const CIEC_ROS2_action_msgs__msg__GoalInfo &pagoal_info, const CIEC_SINT &pastatus);

    CIEC_ROS2_action_msgs__msg__GoalInfo var_goal_info;
    CIEC_SINT var_status;

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


