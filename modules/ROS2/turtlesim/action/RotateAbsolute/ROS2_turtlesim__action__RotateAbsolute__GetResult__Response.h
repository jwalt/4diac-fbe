/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__action__RotateAbsolute__GetResult__Response
 *** Description: 
 *** Version:
***     1.0: 2023-03-23/Tim Hesse -  - 
 *************************************************************************/

#ifndef _ROS2_TURTLESIM__ACTION__ROTATEABSOLUTE__GETRESULT__RESPONSE_H_
#define _ROS2_TURTLESIM__ACTION__ROTATEABSOLUTE__GETRESULT__RESPONSE_H_

#include "forte_struct.h"

#include "modules/ros2/turtlesim/action/RotateAbsolute/ROS2_turtlesim__action__RotateAbsolute__Result.h"
#include "forte_sint.h"
#include "forte_array_at.h"


class CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response: public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__GetResult__Response)

  public:
      CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response();

      virtual ~CIEC_ROS2_turtlesim__action__RotateAbsolute__GetResult__Response() {
      }

          CIEC_SINT &status() {
            return *static_cast<CIEC_SINT*>(getMember(0));
          }
          
          CIEC_ROS2_turtlesim__action__RotateAbsolute__Result &result() {
            return *static_cast<CIEC_ROS2_turtlesim__action__RotateAbsolute__Result*>(getMember(1));
          }
          

  private:
    static const CStringDictionary::TStringId scmElementTypes[];
    static const CStringDictionary::TStringId scmElementNames[];

};

#endif // _ROS2_TURTLESIM__ACTION__ROTATEABSOLUTE__GETRESULT__RESPONSE_H_


