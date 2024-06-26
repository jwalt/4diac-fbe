/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: MAX6675
 *** Description: Read temperature from a MAX6675 Type K converter on /dev/spidev0.0
 *** Version:
 ***     1.0: 2020-10-01/jwalter -  -
 *************************************************************************/

#include "MAX6675_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "MAX6675_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_MAX6675, g_nStringIdMAX6675)

const CStringDictionary::TStringId FORTE_MAX6675::scmDataInputNames[] = {g_nStringIdQI};
const CStringDictionary::TStringId FORTE_MAX6675::scmDataInputTypeIds[] = {g_nStringIdBOOL};
const CStringDictionary::TStringId FORTE_MAX6675::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdTEMP};
const CStringDictionary::TStringId FORTE_MAX6675::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdWORD};
const TDataIOID FORTE_MAX6675::scmEIWith[] = {0, scmWithListDelimiter, 0, scmWithListDelimiter};
const TForteInt16 FORTE_MAX6675::scmEIWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_MAX6675::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};
const TDataIOID FORTE_MAX6675::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_MAX6675::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_MAX6675::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};
const SFBInterfaceSpec FORTE_MAX6675::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  3, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_MAX6675::FORTE_MAX6675(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, &scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    var_conn_TEMP(var_TEMP),
    conn_INITO(this, 0),
    conn_CNF(this, 1),
    conn_QI(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS),
    conn_TEMP(this, 2, &var_conn_TEMP) {
};

void FORTE_MAX6675::setInitialValues() {
	var_QI = 0_BOOL;
	var_QO = 0_BOOL;
	var_STATUS = u""_WSTRING;
	var_TEMP = 0_WORD;
}


void FORTE_MAX6675::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventINITID:
      if (auto event = executeINIT(); event) sendOutputEvent(*event, paECET);
      break;
    case scmEventREQID:
      if (auto event = executeREQ(); event) sendOutputEvent(*event, paECET);
      break;
  }
}

void FORTE_MAX6675::readInputData(const TEventID paEIID) {
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

void FORTE_MAX6675::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    case scmEventCNFID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      writeData(2, var_TEMP, conn_TEMP);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_MAX6675::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
  }
  return nullptr;
}

CIEC_ANY *FORTE_MAX6675::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
    case 2: return &var_TEMP;
  }
  return nullptr;
}

CEventConnection *FORTE_MAX6675::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_MAX6675::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
  }
  return nullptr;
}

CDataConnection *FORTE_MAX6675::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
    case 2: return &conn_TEMP;
  }
  return nullptr;
}

