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

#ifndef _ROS2_TURTLESIM__ACTION__ROTATEABSOLUTE__FEEDBACKMESSAGE_H_
#define _ROS2_TURTLESIM__ACTION__ROTATEABSOLUTE__FEEDBACKMESSAGE_H_

#include "forte_struct.h"

#include "ROS2_turtlesim__action__RotateAbsolute__Feedback_dtp.h"
#include <unique_identifier_msgs/msg/UUID/ROS2_unique_identifier_msgs__msg__UUID_dtp.h>
#include "forte_array_at.h"


class CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage: public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage)

  public:
      CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage();

      virtual ~CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage() {
      }

          CIEC_ROS2_unique_identifier_msgs__msg__UUID &goal_id() {
            return *static_cast<CIEC_ROS2_unique_identifier_msgs__msg__UUID*>(getMember(0));
          }
          
          CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback &feedback() {
            return *static_cast<CIEC_ROS2_turtlesim__action__RotateAbsolute__Feedback*>(getMember(1));
          }
          

  private:
    static const CStringDictionary::TStringId scmElementTypes[];
    static const CStringDictionary::TStringId scmElementNames[];

};

#endif // _ROS2_TURTLESIM__ACTION__ROTATEABSOLUTE__FEEDBACKMESSAGE_H_


