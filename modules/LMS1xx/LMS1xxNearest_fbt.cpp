/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: LMS1xxNearest
 *** Description: Get distance to nearest object in front of a LMS1xx LIDAR sensor
 *** Version:
 ***     1.0: 2020-10-13/jwalter -  -
 *************************************************************************/

#include "LMS1xxNearest_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "LMS1xxNearest_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_LMS1xxNearest, g_nStringIdLMS1xxNearest)

const CStringDictionary::TStringId FORTE_LMS1xxNearest::scmDataInputNames[] = {g_nStringIdQI};
const CStringDictionary::TStringId FORTE_LMS1xxNearest::scmDataInputTypeIds[] = {g_nStringIdBOOL};
const CStringDictionary::TStringId FORTE_LMS1xxNearest::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdDISTANCE};
const CStringDictionary::TStringId FORTE_LMS1xxNearest::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdUINT};
const TDataIOID FORTE_LMS1xxNearest::scmEIWith[] = {0, scmWithListDelimiter, 0, scmWithListDelimiter};
const TForteInt16 FORTE_LMS1xxNearest::scmEIWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_LMS1xxNearest::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};
const TDataIOID FORTE_LMS1xxNearest::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_LMS1xxNearest::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_LMS1xxNearest::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};
const SFBInterfaceSpec FORTE_LMS1xxNearest::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  3, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_LMS1xxNearest::FORTE_LMS1xxNearest(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, &scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    var_conn_DISTANCE(var_DISTANCE),
    conn_INITO(this, 0),
    conn_CNF(this, 1),
    conn_QI(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS),
    conn_DISTANCE(this, 2, &var_conn_DISTANCE) {
};

void FORTE_LMS1xxNearest::setInitialValues() {
	var_QI = 0_BOOL;
	var_QO = 0_BOOL;
	var_STATUS = u""_WSTRING;
	var_DISTANCE = 0_UINT;
}

void FORTE_LMS1xxNearest::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventINITID:
      if (auto event = executeINIT(); event) sendOutputEvent(*event, paECET);
      break;
    case scmEventREQID:
      if (auto event = executeREQ(); event) sendOutputEvent(*event, paECET);
      break;
  }
}

void FORTE_LMS1xxNearest::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      break;
    }
    case scmEventREQID: {
      readData(0, var_QI, conn_QI);
      break;
    }
    default:
      break;
  }
}

void FORTE_LMS1xxNearest::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    case scmEventCNFID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      writeData(2, var_DISTANCE, conn_DISTANCE);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_LMS1xxNearest::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
  }
  return nullptr;
}

CIEC_ANY *FORTE_LMS1xxNearest::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
    case 2: return &var_DISTANCE;
  }
  return nullptr;
}

CEventConnection *FORTE_LMS1xxNearest::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_LMS1xxNearest::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
  }
  return nullptr;
}

CDataConnection *FORTE_LMS1xxNearest::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
    case 2: return &conn_DISTANCE;
  }
  return nullptr;
}

