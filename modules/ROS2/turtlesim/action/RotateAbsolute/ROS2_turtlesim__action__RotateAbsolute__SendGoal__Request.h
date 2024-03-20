/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request
 *** Description: 
 *** Version:
***     1.0: 2023-03-23/Tim Hesse -  - 
 *************************************************************************/

#ifndef _ROS2_TURTLESIM__ACTION__ROTATEABSOLUTE__SENDGOAL__REQUEST_H_
#define _ROS2_TURTLESIM__ACTION__ROTATEABSOLUTE__SENDGOAL__REQUEST_H_

#include "forte_struct.h"

#include "modules/ros2/turtlesim/action/RotateAbsolute/ROS2_turtlesim__action__RotateAbsolute__Goal.h"
#include "modules/ros2/unique_identifier_msgs/msg/UUID/ROS2_unique_identifier_msgs__msg__UUID.h"
#include "forte_array_at.h"


class CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request: public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request)

  public:
      CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request();

      virtual ~CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Request() {
      }

          CIEC_ROS2_unique_identifier_msgs__msg__UUID &goal_id() {
            return *static_cast<CIEC_ROS2_unique_identifier_msgs__msg__UUID*>(getMember(0));
          }
          
          CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal &goal() {
            return *static_cast<CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal*>(getMember(1));
          }
          

  private:
    static const CStringDictionary::TStringId scmElementTypes[];
    static const CStringDictionary::TStringId scmElementNames[];

};

#endif // _ROS2_TURTLESIM__ACTION__ROTATEABSOLUTE__SENDGOAL__REQUEST_H_


