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

#pragma once

#include "funcbloc.h"
#include "forte_wstring.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

#define FBT_INCLUDES
#include "WatchTextFile.h"
#undef FBT_INCLUDES

class FORTE_WatchTextFile final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_WatchTextFile)

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

#include "WatchTextFile.h"

  public:
    FORTE_WatchTextFile(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_WSTRING var_FILE;

    CIEC_WSTRING var_STATUS;
    CIEC_BOOL var_CHANGED;
    CIEC_WSTRING var_CONTENT;

    CIEC_WSTRING var_conn_STATUS;
    CIEC_BOOL var_conn_CHANGED;
    CIEC_WSTRING var_conn_CONTENT;

    CEventConnection conn_CNF;

    CDataConnection *conn_FILE;

    CDataConnection conn_STATUS;
    CDataConnection conn_CHANGED;
    CDataConnection conn_CONTENT;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_REQ(const CIEC_WSTRING &paFILE, CIEC_WSTRING &paSTATUS, CIEC_BOOL &paCHANGED, CIEC_WSTRING &paCONTENT) {
      var_FILE = paFILE;
      executeEvent(scmEventREQID, nullptr);
      paSTATUS = var_STATUS;
      paCHANGED = var_CHANGED;
      paCONTENT = var_CONTENT;
    }

    void operator()(const CIEC_WSTRING &paFILE, CIEC_WSTRING &paSTATUS, CIEC_BOOL &paCHANGED, CIEC_WSTRING &paCONTENT) {
      evt_REQ(paFILE, paSTATUS, paCHANGED, paCONTENT);
    }
};


