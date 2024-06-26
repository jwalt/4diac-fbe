/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: EPOSGetDI
 *** Description: Get EPOS digital input values
 *** Version:
 ***     1.0: 2020-10-12/jwalter -  -
 *************************************************************************/

#include "EPOSGetDI_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EPOSGetDI_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_EPOSGetDI, g_nStringIdEPOSGetDI)

const CStringDictionary::TStringId FORTE_EPOSGetDI::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdNODE};
const CStringDictionary::TStringId FORTE_EPOSGetDI::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBYTE};
const CStringDictionary::TStringId FORTE_EPOSGetDI::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdNEG_LIMIT, g_nStringIdPOS_LIMIT};
const CStringDictionary::TStringId FORTE_EPOSGetDI::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdBOOL, g_nStringIdBOOL};
const TDataIOID FORTE_EPOSGetDI::scmEIWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_EPOSGetDI::scmEIWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_EPOSGetDI::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};
const TDataIOID FORTE_EPOSGetDI::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, 2, 3, scmWithListDelimiter};
const TForteInt16 FORTE_EPOSGetDI::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_EPOSGetDI::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};
const SFBInterfaceSpec FORTE_EPOSGetDI::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  4, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_EPOSGetDI::FORTE_EPOSGetDI(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, &scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    var_conn_NEG_LIMIT(var_NEG_LIMIT),
    var_conn_POS_LIMIT(var_POS_LIMIT),
    conn_INITO(this, 0),
    conn_CNF(this, 1),
    conn_QI(nullptr),
    conn_NODE(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS),
    conn_NEG_LIMIT(this, 2, &var_conn_NEG_LIMIT),
    conn_POS_LIMIT(this, 3, &var_conn_POS_LIMIT) {
};

void FORTE_EPOSGetDI::setInitialValues() {
	var_QI = 0_BOOL;
	var_NODE = 0_BYTE;
	var_QO = 0_BOOL;
	var_STATUS = u""_WSTRING;
	var_NEG_LIMIT = 0_BOOL;
	var_POS_LIMIT = 0_BOOL;
}

#include "EPOSCommon.h"

void FORTE_EPOSGetDI::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventINITID:
      handleINIT();
      break;
    case scmEventREQID:
      handleREQ([this](){
        var_NEG_LIMIT = CIEC_BOOL(!!isNegLimit(var_NODE));
        var_POS_LIMIT = CIEC_BOOL(!!isPosLimit(var_NODE));
        return nullptr;
      });
      break;
  }
}

void FORTE_EPOSGetDI::readInputData(const TEventID paEIID) {
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

void FORTE_EPOSGetDI::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    case scmEventCNFID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      writeData(2, var_NEG_LIMIT, conn_NEG_LIMIT);
      writeData(3, var_POS_LIMIT, conn_POS_LIMIT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_EPOSGetDI::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_NODE;
  }
  return nullptr;
}

CIEC_ANY *FORTE_EPOSGetDI::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
    case 2: return &var_NEG_LIMIT;
    case 3: return &var_POS_LIMIT;
  }
  return nullptr;
}

CEventConnection *FORTE_EPOSGetDI::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_EPOSGetDI::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_NODE;
  }
  return nullptr;
}

CDataConnection *FORTE_EPOSGetDI::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
    case 2: return &conn_NEG_LIMIT;
    case 3: return &conn_POS_LIMIT;
  }
  return nullptr;
}

