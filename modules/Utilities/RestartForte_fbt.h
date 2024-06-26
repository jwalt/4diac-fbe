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

#pragma once

#include "funcbloc.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_RestartForte final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_RestartForte)

  private:
    static const TEventID scmEventREQID = 0;
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;

  public:
    FORTE_RestartForte(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_REQ() {
      executeEvent(scmEventREQID, nullptr);
    }

    void operator()() {
      evt_REQ();
    }
};


