/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__action__RotateAbsolute__Goal
 *** Description: 
 *** Version:
***     1.0: 2023-03-21/Tim Hesse -  - 
 *************************************************************************/

#ifndef _ROS2_TURTLESIM__ACTION__ROTATEABSOLUTE__GOAL_H_
#define _ROS2_TURTLESIM__ACTION__ROTATEABSOLUTE__GOAL_H_

#include "forte_struct.h"

#include "forte_real.h"
#include "forte_array_at.h"


class CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal: public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__Goal)

  public:
      CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal();

      virtual ~CIEC_ROS2_turtlesim__action__RotateAbsolute__Goal() {
      }

          CIEC_REAL &theta() {
            return *static_cast<CIEC_REAL*>(getMember(0));
          }
          

  private:
    static const CStringDictionary::TStringId scmElementTypes[];
    static const CStringDictionary::TStringId scmElementNames[];

};

#endif // _ROS2_TURTLESIM__ACTION__ROTATEABSOLUTE__GOAL_H_


