/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: EPOSStop
 *** Description: Stop EPOS movement prematurely
 *** Version:
 ***     1.0: 2020-10-12/jwalter -  -
 *************************************************************************/

#include "EPOSStop_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EPOSStop_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_EPOSStop, g_nStringIdEPOSStop)

const CStringDictionary::TStringId FORTE_EPOSStop::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdNODE};
const CStringDictionary::TStringId FORTE_EPOSStop::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBYTE};
const CStringDictionary::TStringId FORTE_EPOSStop::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};
const CStringDictionary::TStringId FORTE_EPOSStop::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};
const TDataIOID FORTE_EPOSStop::scmEIWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_EPOSStop::scmEIWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_EPOSStop::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};
const TDataIOID FORTE_EPOSStop::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_EPOSStop::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_EPOSStop::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};
const SFBInterfaceSpec FORTE_EPOSStop::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_EPOSStop::FORTE_EPOSStop(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, &scmFBInterfaceSpec, paInstanceNameId),
    var_NODE(0_BYTE),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_INITO(this, 0),
    conn_CNF(this, 1),
    conn_QI(nullptr),
    conn_NODE(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS) {
};

void FORTE_EPOSStop::setInitialValues() {
	var_QI = 0_BOOL;
	var_NODE = 0_BYTE;
	var_QO = 0_BOOL;
	var_STATUS = u""_WSTRING;
}

#include "EPOSCommon.h"

void FORTE_EPOSStop::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventINITID:
      handleINIT();
      break;
    case scmEventREQID:
      handleREQ([this](){
        return stopMovement(var_NODE);
      });
      break;
  }
}

void FORTE_EPOSStop::readInputData(const TEventID paEIID) {
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

void FORTE_EPOSStop::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    case scmEventCNFID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_EPOSStop::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_NODE;
  }
  return nullptr;
}

CIEC_ANY *FORTE_EPOSStop::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_EPOSStop::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_EPOSStop::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_NODE;
  }
  return nullptr;
}

CDataConnection *FORTE_EPOSStop::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

