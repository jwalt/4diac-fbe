/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: EPOSGetSpeed
 *** Description: Get EPOS current movement speed
 *** Version: 
 ***     1.0: 2020-10-12/jwalter - null - 
 *************************************************************************/

#include "EPOSGetSpeed.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EPOSGetSpeed_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_EPOSGetSpeed, g_nStringIdEPOSGetSpeed)

const CStringDictionary::TStringId FORTE_EPOSGetSpeed::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdNODE};

const CStringDictionary::TStringId FORTE_EPOSGetSpeed::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_EPOSGetSpeed::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdSPEED};

const CStringDictionary::TStringId FORTE_EPOSGetSpeed::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdREAL};

const TForteInt16 FORTE_EPOSGetSpeed::scm_anEIWithIndexes[] = {0, 3};
const TDataIOID FORTE_EPOSGetSpeed::scm_anEIWith[] = {0, 1, 255, 0, 1, 255};
const CStringDictionary::TStringId FORTE_EPOSGetSpeed::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_EPOSGetSpeed::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 255};
const TForteInt16 FORTE_EPOSGetSpeed::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_EPOSGetSpeed::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_EPOSGetSpeed::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  2,  scm_anDataInputNames, scm_anDataInputTypeIds,
  3,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};

#include "EPOSCommon.h"

void FORTE_EPOSGetSpeed::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventINITID:
      handleINIT();
      break;
    case scm_nEventREQID:
      handleREQ([this](){
        float val = NAN;
        auto err = getVelocity(NODE(), val);
        SPEED() = CIEC_REAL(val);
        return err;
      });
      break;
  }
}



