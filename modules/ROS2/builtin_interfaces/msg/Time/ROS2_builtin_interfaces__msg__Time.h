/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_builtin_interfaces__msg__Time
 *** Description: 
 *** Version:
***     1.0: 2023-03-15/Tim Hesse -  - 
 *************************************************************************/

#ifndef _ROS2_BUILTIN_INTERFACES__MSG__TIME_H_
#define _ROS2_BUILTIN_INTERFACES__MSG__TIME_H_

#include "forte_struct.h"

#include "forte_int.h"
#include "forte_uint.h"


class CIEC_ROS2_builtin_interfaces__msg__Time: public CIEC_STRUCT {
  DECLARE_FIRMWARE_DATATYPE(ROS2_builtin_interfaces__msg__Time)

  public:
      CIEC_ROS2_builtin_interfaces__msg__Time();

      virtual ~CIEC_ROS2_builtin_interfaces__msg__Time() {
      }

          CIEC_INT &sec() {
            return *static_cast<CIEC_INT*>(getMember(0));
          }
          
          CIEC_UINT &nanosec() {
            return *static_cast<CIEC_UINT*>(getMember(1));
          }
          

  private:
    static const CStringDictionary::TStringId scmElementTypes[];
    static const CStringDictionary::TStringId scmElementNames[];

};

#endif // _ROS2_BUILTIN_INTERFACES__MSG__TIME_H_


