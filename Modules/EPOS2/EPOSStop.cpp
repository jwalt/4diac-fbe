/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: EPOSStop
 *** Description: Stop EPOS movement prematurely
 *** Version: 
 ***     1.0: 2020-10-12/jwalter -  - 
 *************************************************************************/

#include "EPOSStop.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EPOSStop_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_EPOSStop, g_nStringIdEPOSStop)

const CStringDictionary::TStringId FORTE_EPOSStop::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdNODE};

const CStringDictionary::TStringId FORTE_EPOSStop::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_EPOSStop::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};

const CStringDictionary::TStringId FORTE_EPOSStop::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};

const TForteInt16 FORTE_EPOSStop::scm_anEIWithIndexes[] = {0, 3};
const TDataIOID FORTE_EPOSStop::scm_anEIWith[] = {0, 1, 255, 0, 1, 255};
const CStringDictionary::TStringId FORTE_EPOSStop::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_EPOSStop::scm_anEOWith[] = {0, 1, 255, 0, 1, 255};
const TForteInt16 FORTE_EPOSStop::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_EPOSStop::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_EPOSStop::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  2,  scm_anDataInputNames, scm_anDataInputTypeIds,
  2,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_EPOSStop::setInitialValues(){
  NODE() = CIEC_BYTE(0);
}

#include "EPOSCommon.h"

void FORTE_EPOSStop::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventINITID:
      handleINIT();
      break;
    case scm_nEventREQID:
      handleREQ([this](){
        return stopMovement(NODE());
      });
      break;
  }
}
