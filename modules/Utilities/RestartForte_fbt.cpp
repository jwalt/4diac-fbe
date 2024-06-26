/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: RestartForte
 *** Description: Restart FORTE runtime. WARNING: This is buggy by design and cannot be fixed. Consider ExitForte with an external auto-restart mechanism instead (e.g. a wrapper script or systemd service).
 *** Version:
 ***     1.0: 2020-10-13/jwalter -  -
 *************************************************************************/

#include "RestartForte_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RestartForte_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_RestartForte, g_nStringIdRestartForte)

const TForteInt16 FORTE_RestartForte::scmEIWithIndexes[] = {-1};
const CStringDictionary::TStringId FORTE_RestartForte::scmEventInputNames[] = {g_nStringIdREQ};
const SFBInterfaceSpec FORTE_RestartForte::scmFBInterfaceSpec = {
  1, scmEventInputNames, nullptr, scmEIWithIndexes,
  0, nullptr, nullptr, nullptr,
  0, nullptr, nullptr,
  0, nullptr, nullptr,
  0, nullptr,
  0, nullptr
};

FORTE_RestartForte::FORTE_RestartForte(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, &scmFBInterfaceSpec, paInstanceNameId) {
};

#include <unistd.h>

void FORTE_RestartForte::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID:
      DEVLOG_WARNING("============================================================================\n");
      DEVLOG_WARNING("Issuing hard runtime restart. This is buggy by design.\n");
      DEVLOG_WARNING("In production settings, use ExitForte and an auto-restart mechanism instead.\n");
      DEVLOG_WARNING("============================================================================\n");
      for (int i = 3; i < 1024; i++) close(i);
      execl("/proc/self/exe", "/proc/self/exe", (char *)NULL);
      DEVLOG_ERROR("Could not execute /proc/self/exe\n");
      exit(1);
      break;
  }
}

void FORTE_RestartForte::readInputData(TEventID) {
  // nothing to do
}

void FORTE_RestartForte::writeOutputData(TEventID) {
  // nothing to do
}

CIEC_ANY *FORTE_RestartForte::getDI(size_t) {
  return nullptr;
}

CIEC_ANY *FORTE_RestartForte::getDO(size_t) {
  return nullptr;
}

CEventConnection *FORTE_RestartForte::getEOConUnchecked(TPortId) {
  return nullptr;
}

CDataConnection **FORTE_RestartForte::getDIConUnchecked(TPortId) {
  return nullptr;
}

CDataConnection *FORTE_RestartForte::getDOConUnchecked(TPortId) {
  return nullptr;
}

