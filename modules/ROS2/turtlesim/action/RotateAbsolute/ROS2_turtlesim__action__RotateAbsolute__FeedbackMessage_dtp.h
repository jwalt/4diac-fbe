/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage
 *** Description:
 *** Version:
 ***     1.0: 2023-03-23/Tim Hesse -  -
 *************************************************************************/

#pragma once

#include "forte_struct.h"

#include <unique_identifier_msgs/msg/UUID/ROS2_unique_identifier_msgs__msg__UUID_dtp.h>
#include "ROS2_turtlesim__action__RotateAbsolute__Feedback_dtp.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage final : public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage)

  public:
    CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage();

    CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage(const CIEC_ROS2_unique_identifier_msgs__msg__UUID &pagoal_id, const CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback &pafeedback);

    CIEC_ROS2_unique_identifier_msgs__msg__UUID var_goal_id;
    CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback var_feedback;

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


