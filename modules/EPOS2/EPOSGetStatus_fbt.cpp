/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: EPOSGetStatus
 *** Description: Get EPOS status flags
 *** Version:
 ***     1.0: 2020-10-12/jwalter -  -
 *************************************************************************/

#include "EPOSGetStatus_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EPOSGetStatus_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_EPOSGetStatus, g_nStringIdEPOSGetStatus)

const CStringDictionary::TStringId FORTE_EPOSGetStatus::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdNODE};
const CStringDictionary::TStringId FORTE_EPOSGetStatus::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBYTE};
const CStringDictionary::TStringId FORTE_EPOSGetStatus::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdENABLED, g_nStringIdMOVING, g_nStringIdQUICKSTOP, g_nStringIdDONE, g_nStringIdFAULT, g_nStringIdERROR};
const CStringDictionary::TStringId FORTE_EPOSGetStatus::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBYTE};
const TDataIOID FORTE_EPOSGetStatus::scmEIWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_EPOSGetStatus::scmEIWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_EPOSGetStatus::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};
const TDataIOID FORTE_EPOSGetStatus::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, 3, 4, 2, 5, 6, 7, scmWithListDelimiter};
const TForteInt16 FORTE_EPOSGetStatus::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_EPOSGetStatus::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};
const SFBInterfaceSpec FORTE_EPOSGetStatus::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  8, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_EPOSGetStatus::FORTE_EPOSGetStatus(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, &scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    var_conn_ENABLED(var_ENABLED),
    var_conn_MOVING(var_MOVING),
    var_conn_QUICKSTOP(var_QUICKSTOP),
    var_conn_DONE(var_DONE),
    var_conn_FAULT(var_FAULT),
    var_conn_ERROR(var_ERROR),
    conn_INITO(this, 0),
    conn_CNF(this, 1),
    conn_QI(nullptr),
    conn_NODE(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS),
    conn_ENABLED(this, 2, &var_conn_ENABLED),
    conn_MOVING(this, 3, &var_conn_MOVING),
    conn_QUICKSTOP(this, 4, &var_conn_QUICKSTOP),
    conn_DONE(this, 5, &var_conn_DONE),
    conn_FAULT(this, 6, &var_conn_FAULT),
    conn_ERROR(this, 7, &var_conn_ERROR) {
};

void FORTE_EPOSGetStatus::setInitialValues() {
	var_QI = 0_BOOL;
	var_NODE = 0_BYTE;
	var_QO = 0_BOOL;
	var_STATUS = u""_WSTRING;
	var_ENABLED = 0_BOOL;
	var_MOVING = 0_BOOL;
	var_QUICKSTOP = 0_BOOL;
	var_DONE = 0_BOOL;
	var_FAULT = 0_BOOL;
	var_ERROR = 0_BYTE;
}

#include "EPOSCommon.h"

void FORTE_EPOSGetStatus::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventINITID:
      handleINIT();
      break;
    case scmEventREQID:
      handleREQ([this](){
        auto node = var_NODE;
        var_MOVING = CIEC_BOOL(!isMovementComplete(node));
        var_ERROR = CIEC_BYTE(getError(node));
        auto st = getStatus(node);
        var_ENABLED = CIEC_BOOL(!!(st&(1<<2)));
        var_QUICKSTOP = CIEC_BOOL(!(st&(1<<5)));
        var_DONE = CIEC_BOOL(!!(st&(1<<10)));
        var_FAULT = CIEC_BOOL(!!(st&(1<<3)));
        return nullptr;
      });
      break;
  }
}

void FORTE_EPOSGetStatus::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_NODE, conn_NODE);
      break;
    }
    case scmEventREQID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_NODE, conn_NODE);
      break;
    }
    default:
      break;
  }
}

void FORTE_EPOSGetStatus::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    case scmEventCNFID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      writeData(3, var_MOVING, conn_MOVING);
      writeData(4, var_QUICKSTOP, conn_QUICKSTOP);
      writeData(2, var_ENABLED, conn_ENABLED);
      writeData(5, var_DONE, conn_DONE);
      writeData(6, var_FAULT, conn_FAULT);
      writeData(7, var_ERROR, conn_ERROR);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_EPOSGetStatus::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_NODE;
  }
  return nullptr;
}

CIEC_ANY *FORTE_EPOSGetStatus::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
    case 2: return &var_ENABLED;
    case 3: return &var_MOVING;
    case 4: return &var_QUICKSTOP;
    case 5: return &var_DONE;
    case 6: return &var_FAULT;
    case 7: return &var_ERROR;
  }
  return nullptr;
}

CEventConnection *FORTE_EPOSGetStatus::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_EPOSGetStatus::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_NODE;
  }
  return nullptr;
}

CDataConnection *FORTE_EPOSGetStatus::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
    case 2: return &conn_ENABLED;
    case 3: return &conn_MOVING;
    case 4: return &conn_QUICKSTOP;
    case 5: return &conn_DONE;
    case 6: return &conn_FAULT;
    case 7: return &conn_ERROR;
  }
  return nullptr;
}

