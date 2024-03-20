/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__srv__Spawn__Request
 *** Description: turtlesim/srv/Spawn_Request
 *** Version:
***     1.0: 2023-03-14/Tim Hesse -  - 
 *************************************************************************/

#ifndef _ROS2_TURTLESIM__SRV__SPAWN__REQUEST_H_
#define _ROS2_TURTLESIM__SRV__SPAWN__REQUEST_H_

#include "forte_struct.h"

#include "forte_real.h"
#include "forte_string.h"
#include "forte_array_at.h"


class CIEC_ROS2_turtlesim__srv__Spawn__Request: public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_turtlesim__srv__Spawn__Request)

  public:
      CIEC_ROS2_turtlesim__srv__Spawn__Request();

      virtual ~CIEC_ROS2_turtlesim__srv__Spawn__Request() {
      }

          CIEC_REAL &x() {
            return *static_cast<CIEC_REAL*>(getMember(0));
          }
          
          CIEC_REAL &y() {
            return *static_cast<CIEC_REAL*>(getMember(1));
          }
          
          CIEC_REAL &theta() {
            return *static_cast<CIEC_REAL*>(getMember(2));
          }
          
          CIEC_STRING &name() {
            return *static_cast<CIEC_STRING*>(getMember(3));
          }
          

  private:
    static const CStringDictionary::TStringId scmElementTypes[];
    static const CStringDictionary::TStringId scmElementNames[];

};

#endif // _ROS2_TURTLESIM__SRV__SPAWN__REQUEST_H_


