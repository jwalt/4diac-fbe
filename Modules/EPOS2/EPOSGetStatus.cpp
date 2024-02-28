/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: EPOSGetStatus
 *** Description: Get EPOS status flags
 *** Version: 
 ***     1.0: 2020-10-12/jwalter -  - 
 *************************************************************************/

#include "EPOSGetStatus.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EPOSGetStatus_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_EPOSGetStatus, g_nStringIdEPOSGetStatus)

const CStringDictionary::TStringId FORTE_EPOSGetStatus::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdNODE};

const CStringDictionary::TStringId FORTE_EPOSGetStatus::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_EPOSGetStatus::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdENABLED, g_nStringIdMOVING, g_nStringIdQUICKSTOP, g_nStringIdDONE, g_nStringIdFAULT, g_nStringIdERROR};

const CStringDictionary::TStringId FORTE_EPOSGetStatus::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBYTE};

const TForteInt16 FORTE_EPOSGetStatus::scm_anEIWithIndexes[] = {0, 3};
const TDataIOID FORTE_EPOSGetStatus::scm_anEIWith[] = {0, 1, 255, 0, 1, 255};
const CStringDictionary::TStringId FORTE_EPOSGetStatus::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_EPOSGetStatus::scm_anEOWith[] = {0, 1, 255, 0, 1, 3, 4, 2, 5, 6, 7, 255};
const TForteInt16 FORTE_EPOSGetStatus::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_EPOSGetStatus::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_EPOSGetStatus::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  2,  scm_anDataInputNames, scm_anDataInputTypeIds,
  8,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


#include "EPOSCommon.h"

void FORTE_EPOSGetStatus::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventINITID:
      handleINIT();
      break;

    case scm_nEventREQID:
      handleREQ([this](){
        auto node = NODE();
        MOVING() = CIEC_BOOL(!isMovementComplete(node));
        ERROR() = CIEC_BYTE(getError(node));
        auto st = getStatus(node);
        ENABLED() = CIEC_BOOL(!!(st&(1<<2)));
        QUICKSTOP() = CIEC_BOOL(!(st&(1<<5)));
        DONE() = CIEC_BOOL(!!(st&(1<<10)));
        FAULT() = CIEC_BOOL(!!(st&(1<<3)));
        return nullptr;
      });
      break;
  }
}
