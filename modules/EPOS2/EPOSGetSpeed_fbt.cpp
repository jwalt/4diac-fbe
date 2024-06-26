/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: EPOSGetSpeed
 *** Description: Get EPOS current movement speed
 *** Version:
 ***     1.0: 2020-10-12/jwalter -  -
 *************************************************************************/

#include "EPOSGetSpeed_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EPOSGetSpeed_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_EPOSGetSpeed, g_nStringIdEPOSGetSpeed)

const CStringDictionary::TStringId FORTE_EPOSGetSpeed::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdNODE};
const CStringDictionary::TStringId FORTE_EPOSGetSpeed::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBYTE};
const CStringDictionary::TStringId FORTE_EPOSGetSpeed::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdSPEED};
const CStringDictionary::TStringId FORTE_EPOSGetSpeed::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdREAL};
const TDataIOID FORTE_EPOSGetSpeed::scmEIWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_EPOSGetSpeed::scmEIWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_EPOSGetSpeed::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};
const TDataIOID FORTE_EPOSGetSpeed::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_EPOSGetSpeed::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_EPOSGetSpeed::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};
const SFBInterfaceSpec FORTE_EPOSGetSpeed::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  2, scmDataInputNames, scmDataInputTypeIds,
  3, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_EPOSGetSpeed::FORTE_EPOSGetSpeed(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, &scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    var_conn_SPEED(var_SPEED),
    conn_INITO(this, 0),
    conn_CNF(this, 1),
    conn_QI(nullptr),
    conn_NODE(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS),
    conn_SPEED(this, 2, &var_conn_SPEED) {
};

void FORTE_EPOSGetSpeed::setInitialValues() {
	var_QI = 0_BOOL;
	var_NODE = 0_BYTE;
	var_QO = 0_BOOL;
	var_STATUS = u""_WSTRING;
	var_SPEED = 0_REAL;
}

#include "EPOSCommon.h"

void FORTE_EPOSGetSpeed::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventINITID:
      handleINIT();
      break;
    case scmEventREQID:
      handleREQ([this](){
        float val = NAN;
        auto err = getVelocity(var_NODE, val);
        var_SPEED = CIEC_REAL(val);
        return err;
      });
      break;
  }
}

void FORTE_EPOSGetSpeed::readInputData(const TEventID paEIID) {
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

void FORTE_EPOSGetSpeed::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    case scmEventCNFID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      writeData(2, var_SPEED, conn_SPEED);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_EPOSGetSpeed::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_NODE;
  }
  return nullptr;
}

CIEC_ANY *FORTE_EPOSGetSpeed::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
    case 2: return &var_SPEED;
  }
  return nullptr;
}

CEventConnection *FORTE_EPOSGetSpeed::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_EPOSGetSpeed::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_NODE;
  }
  return nullptr;
}

CDataConnection *FORTE_EPOSGetSpeed::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
    case 2: return &conn_SPEED;
  }
  return nullptr;
}

