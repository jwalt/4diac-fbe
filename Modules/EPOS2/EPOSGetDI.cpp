/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: EPOSGetDI
 *** Description: Get EPOS digital input values
 *** Version: 
 ***     1.0: 2020-10-12/jwalter - null - 
 *************************************************************************/

#include "EPOSGetDI.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EPOSGetDI_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_EPOSGetDI, g_nStringIdEPOSGetDI)

const CStringDictionary::TStringId FORTE_EPOSGetDI::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdNODE};

const CStringDictionary::TStringId FORTE_EPOSGetDI::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_EPOSGetDI::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdNEG_LIMIT, g_nStringIdPOS_LIMIT};

const CStringDictionary::TStringId FORTE_EPOSGetDI::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdBOOL, g_nStringIdBOOL};

const TForteInt16 FORTE_EPOSGetDI::scm_anEIWithIndexes[] = {0, 3};
const TDataIOID FORTE_EPOSGetDI::scm_anEIWith[] = {0, 1, 255, 0, 1, 255};
const CStringDictionary::TStringId FORTE_EPOSGetDI::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_EPOSGetDI::scm_anEOWith[] = {0, 1, 255, 0, 1, 2, 3, 255};
const TForteInt16 FORTE_EPOSGetDI::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_EPOSGetDI::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_EPOSGetDI::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  2,  scm_anDataInputNames, scm_anDataInputTypeIds,
  4,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};

#include "EPOSCommon.h"

void FORTE_EPOSGetDI::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventINITID:
      handleINIT();
      break;
      
    case scm_nEventREQID:
      handleREQ([this](){
        NEG_LIMIT() = CIEC_BOOL(!!isNegLimit(NODE()));
        POS_LIMIT() = CIEC_BOOL(!!isPosLimit(NODE()));
        return nullptr;
      });
      break;
  }
}



