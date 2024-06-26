/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: MCP23017
 *** Description: Service Interface Function Block Type
 *** Version:
 ***     1.0: 2021-04-29/markk -  -
 *************************************************************************/

#include "MCP23017_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "MCP23017_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_MCP23017, g_nStringIdMCP23017)

const CStringDictionary::TStringId FORTE_MCP23017::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdBUS_NUM, g_nStringIdI2C_ADDR, g_nStringIdOE_A, g_nStringIdOE_B, g_nStringIdSD_A, g_nStringIdSD_B};
const CStringDictionary::TStringId FORTE_MCP23017::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdUINT, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE, g_nStringIdBYTE};
const CStringDictionary::TStringId FORTE_MCP23017::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdRD_A, g_nStringIdRD_B};
const CStringDictionary::TStringId FORTE_MCP23017::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBYTE, g_nStringIdBYTE};
const TDataIOID FORTE_MCP23017::scmEIWith[] = {0, 1, 2, 3, 4, scmWithListDelimiter, 0, 5, 3, scmWithListDelimiter, 0, 6, 4, scmWithListDelimiter};
const TForteInt16 FORTE_MCP23017::scmEIWithIndexes[] = {0, 6, 10};
const CStringDictionary::TStringId FORTE_MCP23017::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ_A, g_nStringIdREQ_B};
const TDataIOID FORTE_MCP23017::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter, 0, 2, scmWithListDelimiter};
const TForteInt16 FORTE_MCP23017::scmEOWithIndexes[] = {0, 2, 5};
const CStringDictionary::TStringId FORTE_MCP23017::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF_A, g_nStringIdCNF_B};
const SFBInterfaceSpec FORTE_MCP23017::scmFBInterfaceSpec = {
  3, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  3, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  7, scmDataInputNames, scmDataInputTypeIds,
  3, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_MCP23017::FORTE_MCP23017(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, &scmFBInterfaceSpec, paInstanceNameId),
    var_conn_QO(var_QO),
    var_conn_RD_A(var_RD_A),
    var_conn_RD_B(var_RD_B),
    conn_INITO(this, 0),
    conn_CNF_A(this, 1),
    conn_CNF_B(this, 2),
    conn_QI(nullptr),
    conn_BUS_NUM(nullptr),
    conn_I2C_ADDR(nullptr),
    conn_OE_A(nullptr),
    conn_OE_B(nullptr),
    conn_SD_A(nullptr),
    conn_SD_B(nullptr),
    conn_QO(this, 0, &var_conn_QO),
    conn_RD_A(this, 1, &var_conn_RD_A),
    conn_RD_B(this, 2, &var_conn_RD_B) {
};

void FORTE_MCP23017::setInitialValues() {
	var_QI = 0_BOOL;
	var_BUS_NUM = 0_UINT;
	var_I2C_ADDR = 0_BYTE;
	var_OE_A = 0_BYTE;
	var_OE_B = 0_BYTE;
	var_SD_A = 0_BYTE;
	var_SD_B = 0_BYTE;
	var_QO = 0_BOOL;
	var_RD_A = 0_BYTE;
	var_RD_B = 0_BYTE;
}

void FORTE_MCP23017::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventINITID:
      if (auto event = executeINIT(); event) sendOutputEvent(*event, paECET);
      break;
    case scmEventREQ_AID:
      if (auto event = executeREQ_B(); event) sendOutputEvent(*event, paECET);
      break;
    case scmEventREQ_BID:
      if (auto event = executeREQ_A(); event) sendOutputEvent(*event, paECET);
      break;
  }
}

void FORTE_MCP23017::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_BUS_NUM, conn_BUS_NUM);
      readData(2, var_I2C_ADDR, conn_I2C_ADDR);
      readData(3, var_OE_A, conn_OE_A);
      readData(4, var_OE_B, conn_OE_B);
      break;
    }
    case scmEventREQ_AID: {
      readData(0, var_QI, conn_QI);
      readData(5, var_SD_A, conn_SD_A);
      readData(3, var_OE_A, conn_OE_A);
      break;
    }
    case scmEventREQ_BID: {
      readData(0, var_QI, conn_QI);
      readData(6, var_SD_B, conn_SD_B);
      readData(4, var_OE_B, conn_OE_B);
      break;
    }
    default:
      break;
  }
}

void FORTE_MCP23017::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      break;
    }
    case scmEventCNF_AID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_RD_A, conn_RD_A);
      break;
    }
    case scmEventCNF_BID: {
      writeData(0, var_QO, conn_QO);
      writeData(2, var_RD_B, conn_RD_B);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_MCP23017::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QI;
    case 1: return &var_BUS_NUM;
    case 2: return &var_I2C_ADDR;
    case 3: return &var_OE_A;
    case 4: return &var_OE_B;
    case 5: return &var_SD_A;
    case 6: return &var_SD_B;
  }
  return nullptr;
}

CIEC_ANY *FORTE_MCP23017::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_QO;
    case 1: return &var_RD_A;
    case 2: return &var_RD_B;
  }
  return nullptr;
}

CEventConnection *FORTE_MCP23017::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_CNF_A;
    case 2: return &conn_CNF_B;
  }
  return nullptr;
}

CDataConnection **FORTE_MCP23017::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_BUS_NUM;
    case 2: return &conn_I2C_ADDR;
    case 3: return &conn_OE_A;
    case 4: return &conn_OE_B;
    case 5: return &conn_SD_A;
    case 6: return &conn_SD_B;
  }
  return nullptr;
}

CDataConnection *FORTE_MCP23017::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_RD_A;
    case 2: return &conn_RD_B;
  }
  return nullptr;
}

