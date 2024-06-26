/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: WatchTextFile
 *** Description: Check text file for changes and return last line of content (maximum 256 bytes).
 *** Version:
 ***     1.0: 2020-10-13/jwalter -  -
 *************************************************************************/

#include "WatchTextFile_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "WatchTextFile_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_WatchTextFile, g_nStringIdWatchTextFile)

const CStringDictionary::TStringId FORTE_WatchTextFile::scmDataInputNames[] = {g_nStringIdFILE};
const CStringDictionary::TStringId FORTE_WatchTextFile::scmDataInputTypeIds[] = {g_nStringIdWSTRING};
const CStringDictionary::TStringId FORTE_WatchTextFile::scmDataOutputNames[] = {g_nStringIdSTATUS, g_nStringIdCHANGED, g_nStringIdCONTENT};
const CStringDictionary::TStringId FORTE_WatchTextFile::scmDataOutputTypeIds[] = {g_nStringIdWSTRING, g_nStringIdBOOL, g_nStringIdWSTRING};
const TDataIOID FORTE_WatchTextFile::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_WatchTextFile::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_WatchTextFile::scmEventInputNames[] = {g_nStringIdREQ};
const TDataIOID FORTE_WatchTextFile::scmEOWith[] = {0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_WatchTextFile::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_WatchTextFile::scmEventOutputNames[] = {g_nStringIdCNF};
const SFBInterfaceSpec FORTE_WatchTextFile::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  3, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_WatchTextFile::FORTE_WatchTextFile(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, &scmFBInterfaceSpec, paInstanceNameId),
    var_conn_STATUS(var_STATUS),
    var_conn_CHANGED(var_CHANGED),
    var_conn_CONTENT(var_CONTENT),
    conn_CNF(this, 0),
    conn_FILE(nullptr),
    conn_STATUS(this, 0, &var_conn_STATUS),
    conn_CHANGED(this, 1, &var_conn_CHANGED),
    conn_CONTENT(this, 2, &var_conn_CONTENT) {
};

void FORTE_WatchTextFile::setInitialValues() {
	var_FILE = u""_WSTRING;
	var_STATUS = u""_WSTRING;
	var_CHANGED = 0_BOOL;
	var_CONTENT = u""_WSTRING;
}

void FORTE_WatchTextFile::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      if (auto event = executeREQ(); event) sendOutputEvent(*event, paECET);
      break;
  }
}

void FORTE_WatchTextFile::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_FILE, conn_FILE);
      break;
    }
    default:
      break;
  }
}

void FORTE_WatchTextFile::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_STATUS, conn_STATUS);
      writeData(1, var_CHANGED, conn_CHANGED);
      writeData(2, var_CONTENT, conn_CONTENT);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_WatchTextFile::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_FILE;
  }
  return nullptr;
}

CIEC_ANY *FORTE_WatchTextFile::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_STATUS;
    case 1: return &var_CHANGED;
    case 2: return &var_CONTENT;
  }
  return nullptr;
}

CEventConnection *FORTE_WatchTextFile::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_WatchTextFile::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_FILE;
  }
  return nullptr;
}

CDataConnection *FORTE_WatchTextFile::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_STATUS;
    case 1: return &conn_CHANGED;
    case 2: return &conn_CONTENT;
  }
  return nullptr;
}

