/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: EPOSSetPosZero
 *** Description: Set EPOS position counter to zero
 *** Version: 
 ***     1.0: 2020-10-12/jwalter - null - 
 *************************************************************************/

#include "EPOSSetPosZero.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EPOSSetPosZero_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_EPOSSetPosZero, g_nStringIdEPOSSetPosZero)

const CStringDictionary::TStringId FORTE_EPOSSetPosZero::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdNODE};

const CStringDictionary::TStringId FORTE_EPOSSetPosZero::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBYTE};

const CStringDictionary::TStringId FORTE_EPOSSetPosZero::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};

const CStringDictionary::TStringId FORTE_EPOSSetPosZero::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};

const TForteInt16 FORTE_EPOSSetPosZero::scm_anEIWithIndexes[] = {0, 3};
const TDataIOID FORTE_EPOSSetPosZero::scm_anEIWith[] = {0, 1, 255, 0, 1, 255};
const CStringDictionary::TStringId FORTE_EPOSSetPosZero::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};

const TDataIOID FORTE_EPOSSetPosZero::scm_anEOWith[] = {0, 1, 255, 0, 1, 255};
const TForteInt16 FORTE_EPOSSetPosZero::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId FORTE_EPOSSetPosZero::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};

const SFBInterfaceSpec FORTE_EPOSSetPosZero::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  2,  scm_anDataInputNames, scm_anDataInputTypeIds,
  2,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void FORTE_EPOSSetPosZero::setInitialValues(){
  NODE() = CIEC_BYTE(0);
}

#include "EPOSCommon.h"

void FORTE_EPOSSetPosZero::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case scm_nEventINITID:
      handleINIT();
      break;
    case scm_nEventREQID:
      handleREQ([this](){
        return setZero(NODE());
      });
      break;
  }
}
