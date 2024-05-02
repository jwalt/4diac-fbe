/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_action_msgs__srv__CancelGoal__Request
 *** Description:
 *** Version:
 ***     1.0: 2023-03-15/ -  -
 *************************************************************************/

#pragma once

#include "forte_struct.h"

#include <action_msgs/msg/GoalInfo/ROS2_action_msgs__msg__GoalInfo_dtp.h>
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class CIEC_ROS2_action_msgs__srv__CancelGoal__Request final : public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_action_msgs__srv__CancelGoal__Request)

  public:
    CIEC_ROS2_action_msgs__srv__CancelGoal__Request();

    CIEC_ROS2_action_msgs__srv__CancelGoal__Request(const CIEC_ROS2_action_msgs__msg__GoalInfo &pagoal_info);

    CIEC_ROS2_action_msgs__msg__GoalInfo var_goal_info;

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


