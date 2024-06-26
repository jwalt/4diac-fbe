/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: EPOSGetPosition
 *** Description: Get EPOS current position
 *** Version:
 ***     1.0: 2020-10-12/jwalter -  -
 *************************************************************************/

#include "EPOSGetPosition_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EPOSGetPosition_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_EPOSGetPosition, g_nStringIdEPOSGetPosition)

const CStringDictionary::TStringId FORTE_EPOSGetPosition::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdNODE};
const CStringDictionary::TStringId FORTE_EPOSGetPosition::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBYTE};
const CStringDictionary::TStringId FORTE_EPOSGetPosition::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdPOSITION};
const CStringDictionary::TStringId FORTE_EPOSGetPosition::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdREAL};
const TDataIOID FORTE_EPOSGetPosition::scmEIWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_EPOSGetPosition::scmEIWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_EPOSGetPosition::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};
const TDataIOID FORTE_EPOSGetPosition::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_EPOSGetPosition::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_EPOSGetPosition::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};
const SFBInterfaceSpec FORTE_EPOSGetPosition::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  3, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_EPOSGetPosition::FORTE_EPOSGetPosition(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, &scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    var_conn_POSITION(var_POSITION),
    conn_INITO(this, 0),
    conn_CNF(this, 1),
    conn_QI(nullptr),
    conn_NODE(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS),
    conn_POSITION(this, 2, &var_conn_POSITION) {
};

void FORTE_EPOSGetPosition::setInitialValues() {
	var_QI = 0_BOOL;
	var_NODE = 0_BYTE;
	var_QO = 0_BOOL;
	var_STATUS = u""_WSTRING;
	var_POSITION = 0_REAL;
}

#include "EPOSCommon.h"

void FORTE_EPOSGetPosition::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventINITID:
      handleINIT();
      break;
    case scmEventREQID:
      handleREQ([this](){
        float val = NAN;
        auto err = getPosition(var_NODE, val);
        var_POSITION = CIEC_REAL(val);
        return err;
      });
      break;
  }
}

void FORTE_EPOSGetPosition::readInputData(const TEventID paEIID) {
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

void FORTE_EPOSGetPosition::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    case scmEventCNFID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      writeData(2, var_POSITION, conn_POSITION);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_EPOSGetPosition::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_NODE;
  }
  return nullptr;
}

CIEC_ANY *FORTE_EPOSGetPosition::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
    case 2: return &var_POSITION;
  }
  return nullptr;
}

CEventConnection *FORTE_EPOSGetPosition::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_EPOSGetPosition::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_NODE;
  }
  return nullptr;
}

CDataConnection *FORTE_EPOSGetPosition::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
    case 2: return &conn_POSITION;
  }
  return nullptr;
}

