/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ExitForte
 *** Description: Exit FORTE runtime
 *** Version:
 ***     1.0: 2020-10-13/jwalter -  -
 *************************************************************************/

#include "ExitForte_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ExitForte_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_ExitForte, g_nStringIdExitForte)

const CStringDictionary::TStringId FORTE_ExitForte::scmDataInputNames[] = {g_nStringIdSTATUS};
const CStringDictionary::TStringId FORTE_ExitForte::scmDataInputTypeIds[] = {g_nStringIdDINT};
const TForteInt16 FORTE_ExitForte::scmEIWithIndexes[] = {-1};
const CStringDictionary::TStringId FORTE_ExitForte::scmEventInputNames[] = {g_nStringIdREQ};
const SFBInterfaceSpec FORTE_ExitForte::scmFBInterfaceSpec = {
  1, scmEventInputNames, nullptr, scmEIWithIndexes,
  0, nullptr, nullptr, nullptr,
  1, scmDataInputNames, scmDataInputTypeIds,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

FORTE_ExitForte::FORTE_ExitForte(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, &scmFBInterfaceSpec, paInstanceNameId),
    var_STATUS(0_DINT),
    conn_STATUS(nullptr) {
};

void FORTE_ExitForte::setInitialValues() {
	var_STATUS = 0_DINT;
}

void FORTE_ExitForte::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      exit(int32_t(var_STATUS));
      break;
  }
}

void FORTE_ExitForte::readInputData(TEventID) {
  // nothing to do
}

void FORTE_ExitForte::writeOutputData(TEventID) {
  // nothing to do
}

CIEC_ANY *FORTE_ExitForte::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_STATUS;
  }
  return nullptr;
}

CIEC_ANY *FORTE_ExitForte::getDO(size_t) {
  return nullptr;
}

CEventConnection *FORTE_ExitForte::getEOConUnchecked(TPortId) {
  return nullptr;
}

CDataConnection **FORTE_ExitForte::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_STATUS;
  }
  return nullptr;
}

CDataConnection *FORTE_ExitForte::getDOConUnchecked(TPortId) {
  return nullptr;
}

