/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: EPOSMove
 *** Description: Initiate movement of a Maxon EPOS motor controller connected via USB. FIXME: Units are not yet accurate and disregard gears.
 *** Version:
 ***     1.0: 2020-10-12/jwalter -  -
 *************************************************************************/

#include "EPOSMove_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "EPOSMove_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_EPOSMove, g_nStringIdEPOSMove)

const CStringDictionary::TStringId FORTE_EPOSMove::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdNODE, g_nStringIdTARGET, g_nStringIdMODE, g_nStringIdSPEED, g_nStringIdACCEL};
const CStringDictionary::TStringId FORTE_EPOSMove::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBYTE, g_nStringIdREAL, g_nStringIdBYTE, g_nStringIdREAL, g_nStringIdREAL};
const CStringDictionary::TStringId FORTE_EPOSMove::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};
const CStringDictionary::TStringId FORTE_EPOSMove::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};
const TDataIOID FORTE_EPOSMove::scmEIWith[] = {0, 1, scmWithListDelimiter, 0, 1, 2, 3, 4, 5, scmWithListDelimiter};
const TForteInt16 FORTE_EPOSMove::scmEIWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_EPOSMove::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};
const TDataIOID FORTE_EPOSMove::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_EPOSMove::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_EPOSMove::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};
const SFBInterfaceSpec FORTE_EPOSMove::scmFBInterfaceSpec = {
  2, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  2, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  6, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_EPOSMove::FORTE_EPOSMove(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, &scmFBInterfaceSpec, paInstanceNameId),
    var_NODE(0_BYTE),
    var_TARGET(100.0_REAL),
    var_MODE(1_BYTE),
    var_SPEED(100.0_REAL),
    var_ACCEL(100.0_REAL),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_INITO(this, 0),
    conn_CNF(this, 1),
    conn_QI(nullptr),
    conn_NODE(nullptr),
    conn_TARGET(nullptr),
    conn_MODE(nullptr),
    conn_SPEED(nullptr),
    conn_ACCEL(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_STATUS(this, 1, &var_conn_STATUS) {
};

void FORTE_EPOSMove::setInitialValues() {
	var_QI = 0_BOOL;
	var_NODE = 0_BYTE;
	var_TARGET = 100.0_REAL;
	var_MODE = 1_BYTE;
	var_SPEED = 100.0_REAL;
	var_ACCEL = 100.0_REAL;
	var_QO = 0_BOOL;
	var_STATUS = u""_WSTRING;
}

#include "EPOSCommon.h"

void FORTE_EPOSMove::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventINITID:
      handleINIT();
      break;
    case scmEventREQID:
      handleREQ([this](){
        if (var_MODE) {
          return moveToPosition(var_NODE, var_TARGET, var_MODE==1, var_SPEED, var_ACCEL);
        } else {
          return moveWithVelocity(var_NODE, var_SPEED, var_ACCEL, var_ACCEL);
        }
      });
      break;
  }
}

void FORTE_EPOSMove::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_NODE, conn_NODE);
      break;
    }
    case scmEventREQID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_NODE, conn_NODE);
      readData(2, var_TARGET, conn_TARGET);
      readData(3, var_MODE, conn_MODE);
      readData(4, var_SPEED, conn_SPEED);
      readData(5, var_ACCEL, conn_ACCEL);
      break;
    }
    default:
      break;
  }
}

void FORTE_EPOSMove::writeOutputData(const TEventID paEIID) {
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

CIEC_ANY *FORTE_EPOSMove::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_NODE;
    case 2: return &var_TARGET;
    case 3: return &var_MODE;
    case 4: return &var_SPEED;
    case 5: return &var_ACCEL;
  }
  return nullptr;
}

CIEC_ANY *FORTE_EPOSMove::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_EPOSMove::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_EPOSMove::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_NODE;
    case 2: return &conn_TARGET;
    case 3: return &conn_MODE;
    case 4: return &conn_SPEED;
    case 5: return &conn_ACCEL;
  }
  return nullptr;
}

CDataConnection *FORTE_EPOSMove::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

