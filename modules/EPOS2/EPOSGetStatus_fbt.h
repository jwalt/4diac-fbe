/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: EPOSGetStatus
 *** Description: Get EPOS status flags
 *** Version:
 ***     1.0: 2020-10-12/jwalter -  -
 *************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_byte.h"
#include "forte_wstring.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_EPOSGetStatus final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_EPOSGetStatus)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventINITID = 0;
    static const TEventID scmEventREQID = 1;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const TEventID scmEventINITOID = 0;
    static const TEventID scmEventCNFID = 1;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

  public:
    FORTE_EPOSGetStatus(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_BOOL var_QI;
    CIEC_BYTE var_NODE;

    CIEC_BOOL var_QO;
    CIEC_WSTRING var_STATUS;
    CIEC_BOOL var_ENABLED;
    CIEC_BOOL var_MOVING;
    CIEC_BOOL var_QUICKSTOP;
    CIEC_BOOL var_DONE;
    CIEC_BOOL var_FAULT;
    CIEC_BYTE var_ERROR;

    CIEC_BOOL var_conn_QO;
    CIEC_WSTRING var_conn_STATUS;
    CIEC_BOOL var_conn_ENABLED;
    CIEC_BOOL var_conn_MOVING;
    CIEC_BOOL var_conn_QUICKSTOP;
    CIEC_BOOL var_conn_DONE;
    CIEC_BOOL var_conn_FAULT;
    CIEC_BYTE var_conn_ERROR;

    CEventConnection conn_INITO;
    CEventConnection conn_CNF;

    CDataConnection *conn_QI;
    CDataConnection *conn_NODE;

    CDataConnection conn_QO;
    CDataConnection conn_STATUS;
    CDataConnection conn_ENABLED;
    CDataConnection conn_MOVING;
    CDataConnection conn_QUICKSTOP;
    CDataConnection conn_DONE;
    CDataConnection conn_FAULT;
    CDataConnection conn_ERROR;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_INIT(const CIEC_BOOL &paQI, const CIEC_BYTE &paNODE, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS, CIEC_BOOL &paENABLED, CIEC_BOOL &paMOVING, CIEC_BOOL &paQUICKSTOP, CIEC_BOOL &paDONE, CIEC_BOOL &paFAULT, CIEC_BYTE &paERROR) {
      var_QI = paQI;
      var_NODE = paNODE;
      executeEvent(scmEventINITID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
      paENABLED = var_ENABLED;
      paMOVING = var_MOVING;
      paQUICKSTOP = var_QUICKSTOP;
      paDONE = var_DONE;
      paFAULT = var_FAULT;
      paERROR = var_ERROR;
    }

    void evt_REQ(const CIEC_BOOL &paQI, const CIEC_BYTE &paNODE, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS, CIEC_BOOL &paENABLED, CIEC_BOOL &paMOVING, CIEC_BOOL &paQUICKSTOP, CIEC_BOOL &paDONE, CIEC_BOOL &paFAULT, CIEC_BYTE &paERROR) {
      var_QI = paQI;
      var_NODE = paNODE;
      executeEvent(scmEventREQID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
      paENABLED = var_ENABLED;
      paMOVING = var_MOVING;
      paQUICKSTOP = var_QUICKSTOP;
      paDONE = var_DONE;
      paFAULT = var_FAULT;
      paERROR = var_ERROR;
    }

    void operator()(const CIEC_BOOL &paQI, const CIEC_BYTE &paNODE, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS, CIEC_BOOL &paENABLED, CIEC_BOOL &paMOVING, CIEC_BOOL &paQUICKSTOP, CIEC_BOOL &paDONE, CIEC_BOOL &paFAULT, CIEC_BYTE &paERROR) {
      evt_INIT(paQI, paNODE, paQO, paSTATUS, paENABLED, paMOVING, paQUICKSTOP, paDONE, paFAULT, paERROR);
    }
};


