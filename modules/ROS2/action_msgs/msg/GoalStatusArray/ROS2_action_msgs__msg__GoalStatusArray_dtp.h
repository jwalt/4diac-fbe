/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_action_msgs__msg__GoalStatusArray
 *** Description:
 *** Version:
 ***     1.0: 2023-04-05/ -  -
 *************************************************************************/

#pragma once

#include "forte_struct.h"

#include <action_msgs/msg/GoalInfo/ROS2_action_msgs__msg__GoalInfo_dtp.h>
#include <action_msgs/msg/GoalStatus/ROS2_action_msgs__msg__GoalStatus_dtp.h>
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class CIEC_ROS2_action_msgs__msg__GoalStatusArray final : public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_action_msgs__msg__GoalStatusArray)

  public:
    CIEC_ROS2_action_msgs__msg__GoalStatusArray();

    CIEC_ROS2_action_msgs__msg__GoalStatusArray(const CIEC_ARRAY_COMMON<CIEC_ROS2_action_msgs__msg__GoalStatus> &pastatus_list);

    CIEC_ARRAY_FIXED<CIEC_ROS2_action_msgs__msg__GoalStatus, 0, 15> var_status_list;

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


