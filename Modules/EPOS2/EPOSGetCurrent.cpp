/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: EPOSGetCurrent
 *** Description: Get EPOS current current
 *** Version: 
 ***     1.0: 2020-10-12/jwalter - null - 
 *************************************************************************/

#include "EPOSGetCurrent.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EPOSGetCurrent_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_EPOSGetCurrent, g_nStringIdEPOSGetCurrent)

const CStringDictionary::TStringId FORTE_EPOSGetCurrent::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdNODE};

const CStringDictionary::TStringId FORTE_EPOSGetCurrent::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_EPOSGetCurrent::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdCURRENT};

const CStringDictionary::TStringId FORTE_EPOSGetCurrent::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdREAL};

const TForteInt16 FORTE_EPOSGetCurrent::scm_anEIWithIndexes[] = {0, 3};
const TDataIOID FORTE_EPOSGetCurrent::scm_anEIWith[] = {0, 1, 255, 0, 1, 255};
const CStringDictionary::TStringId FORTE_EPOSGetCurrent::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_EPOSGetCurrent::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 255};
const TForteInt16 FORTE_EPOSGetCurrent::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_EPOSGetCurrent::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_EPOSGetCurrent::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  2,  scm_anDataInputNames, scm_anDataInputTypeIds,
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};

#include "EPOSCommon.h"

void FORTE_EPOSGetCurrent::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventINITID:
      handleINIT();
      break;
    case scm_nEventREQID:
      handleREQ([this](){
        float val = NAN;
        auto err = getCurrent(NODE(), val);
        CURRENT() = CIEC_REAL(val);
        return err;
      });
      break;
  }
}
