/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage
 *** Description: 
 *** Version:
***     1.0: 2023-03-23/ -  - 
 *************************************************************************/

#include "ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage_gen.cpp"
#endif

DEFINE_FIRMWARE_DATATYPE(ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage, g_nStringIdROS2_turtlesim__action__RotateAbsolute__FeedbackMessage);

CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage::CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage() :
    CIEC_STRUCT(g_nStringIdROS2_turtlesim__action__RotateAbsolute__FeedbackMessage, 2, scmElementTypes, scmElementNames, e_APPLICATION + e_CONSTRUCTED + 1) {
}

const CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage::scmElementNames[] = {g_nStringIdgoal_id, g_nStringIdfeedback};
const CStringDictionary::TStringId CIEC_ROS2_turtlesim__action__RotateAbsolute__FeedbackMessage::scmElementTypes[] = {g_nStringIdROS2_unique_identifier_msgs__msg__UUID, g_nStringIdROS2_turtlesim__action__RotateAbsolute__Feedback};


