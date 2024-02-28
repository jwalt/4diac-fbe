/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: EPOSGetPosition
 *** Description: Get EPOS current position
 *** Version: 
 ***     1.0: 2020-10-12/jwalter - null - 
 *************************************************************************/

#include "EPOSGetPosition.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EPOSGetPosition_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_EPOSGetPosition, g_nStringIdEPOSGetPosition)

const CStringDictionary::TStringId FORTE_EPOSGetPosition::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdNODE};

const CStringDictionary::TStringId FORTE_EPOSGetPosition::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_EPOSGetPosition::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdPOSITION};

const CStringDictionary::TStringId FORTE_EPOSGetPosition::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdREAL};

const TForteInt16 FORTE_EPOSGetPosition::scm_anEIWithIndexes[] = {0, 3};
const TDataIOID FORTE_EPOSGetPosition::scm_anEIWith[] = {0, 1, 255, 0, 1, 255};
const CStringDictionary::TStringId FORTE_EPOSGetPosition::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_EPOSGetPosition::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 255};
const TForteInt16 FORTE_EPOSGetPosition::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_EPOSGetPosition::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_EPOSGetPosition::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  2,  scm_anDataInputNames, scm_anDataInputTypeIds,
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};

#include "EPOSCommon.h"

void FORTE_EPOSGetPosition::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventINITID:
      handleINIT();
      break;
    case scm_nEventREQID:
      handleREQ([this](){
        float val = NAN;
        auto err = getPosition(NODE(), val);
        POSITION() = CIEC_REAL(val);
        return err;
      });
      break;
  }
}
