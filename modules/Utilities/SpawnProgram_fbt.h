/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: SpawnProgram
 *** Description: Execute an external program
 *** Version:
 ***     1.0: 2020-10-13/jwalter -  -
 *************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_wstring.h"
#include "forte_bool.h"
#include "forte_dint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_SpawnProgram final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_SpawnProgram)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventREQID = 0;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const TEventID scmEventCNFID = 0;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

  public:
    FORTE_SpawnProgram(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_WSTRING var_EXECUTABLE;
    CIEC_WSTRING var_ARG;
    CIEC_BOOL var_WAIT;

    CIEC_WSTRING var_STATUS;
    CIEC_DINT var_RESULT;

    CIEC_WSTRING var_conn_STATUS;
    CIEC_DINT var_conn_RESULT;

    CEventConnection conn_CNF;

    CDataConnection *conn_EXECUTABLE;
    CDataConnection *conn_ARG;
    CDataConnection *conn_WAIT;

    CDataConnection conn_STATUS;
    CDataConnection conn_RESULT;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_REQ(const CIEC_WSTRING &paEXECUTABLE, const CIEC_WSTRING &paARG, const CIEC_BOOL &paWAIT, CIEC_WSTRING &paSTATUS, CIEC_DINT &paRESULT) {
      var_EXECUTABLE = paEXECUTABLE;
      var_ARG = paARG;
      var_WAIT = paWAIT;
      executeEvent(scmEventREQID, nullptr);
      paSTATUS = var_STATUS;
      paRESULT = var_RESULT;
    }

    void operator()(const CIEC_WSTRING &paEXECUTABLE, const CIEC_WSTRING &paARG, const CIEC_BOOL &paWAIT, CIEC_WSTRING &paSTATUS, CIEC_DINT &paRESULT) {
      evt_REQ(paEXECUTABLE, paARG, paWAIT, paSTATUS, paRESULT);
    }
};


