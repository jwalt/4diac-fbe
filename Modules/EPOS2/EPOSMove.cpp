/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: EPOSMove
 *** Description: Initiate movement of a Maxon EPOS motor controller connected via USB. FIXME: Units are not yet accurate and disregard gears.
 *** Version: 
 ***     1.0: 2020-10-12/jwalter -  - 
 *************************************************************************/

#include "EPOSMove.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EPOSMove_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_EPOSMove, g_nStringIdEPOSMove)

const CStringDictionary::TStringId FORTE_EPOSMove::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdNODE, g_nStringIdTARGET, g_nStringIdMODE, g_nStringIdSPEED, g_nStringIdACCEL};

const CStringDictionary::TStringId FORTE_EPOSMove::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBYTE, g_nStringIdREAL, g_nStringIdBYTE, g_nStringIdREAL, g_nStringIdREAL};

const CStringDictionary::TStringId FORTE_EPOSMove::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};

const CStringDictionary::TStringId FORTE_EPOSMove::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};

const TForteInt16 FORTE_EPOSMove::scm_anEIWithIndexes[] = {0, 3};
const TDataIOID FORTE_EPOSMove::scm_anEIWith[] = {0, 1, 255, 0, 1, 2, 3, 4, 5, 255};
const CStringDictionary::TStringId FORTE_EPOSMove::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_EPOSMove::scm_anEOWith[] = {0, 1, 255, 0, 1, 255};
const TForteInt16 FORTE_EPOSMove::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_EPOSMove::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_EPOSMove::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  6,  scm_anDataInputNames, scm_anDataInputTypeIds,
  2,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_EPOSMove::setInitialValues(){
  NODE() = CIEC_BYTE(0);
  TARGET() = CIEC_REAL(100);
  MODE() = CIEC_BYTE(1);
  SPEED() = CIEC_REAL(100);
  ACCEL() = CIEC_REAL(100);
}


#include "EPOSCommon.h"

void FORTE_EPOSMove::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventINITID:
      handleINIT();
      break;
    case scm_nEventREQID:
      handleREQ([this](){
        if (MODE()) {
          return moveToPosition(NODE(), TARGET(), MODE()==1, SPEED(), ACCEL());
        } else {
          return moveWithVelocity(NODE(), SPEED(), ACCEL(), ACCEL());
        }
      });
      break;
  }
}
