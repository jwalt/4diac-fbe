/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__action__RotateAbsolute__SendGoal__Response
 *** Description: 
 *** Version:
***     1.0: 2023-03-23/Tim Hesse -  - 
 *************************************************************************/

#ifndef _ROS2_TURTLESIM__ACTION__ROTATEABSOLUTE__SENDGOAL__RESPONSE_H_
#define _ROS2_TURTLESIM__ACTION__ROTATEABSOLUTE__SENDGOAL__RESPONSE_H_

#include "forte_struct.h"

#include "forte_bool.h"
#include "modules/ros2/builtin_interfaces/msg/Time/ROS2_builtin_interfaces__msg__Time.h"
#include "forte_array_at.h"


class CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Response: public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__SendGoal__Response)

  public:
      CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Response();

      virtual ~CIEC_ROS2_turtlesim__action__RotateAbsolute__SendGoal__Response() {
      }

          CIEC_BOOL &accepted() {
            return *static_cast<CIEC_BOOL*>(getMember(0));
          }
          
          CIEC_ROS2_builtin_interfaces__msg__Time &stamp() {
            return *static_cast<CIEC_ROS2_builtin_interfaces__msg__Time*>(getMember(1));
          }
          

  private:
    static const CStringDictionary::TStringId scmElementTypes[];
    static const CStringDictionary::TStringId scmElementNames[];

};

#endif // _ROS2_TURTLESIM__ACTION__ROTATEABSOLUTE__SENDGOAL__RESPONSE_H_


