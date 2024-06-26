/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: LMS1xxNearest
 *** Description: Get distance to nearest object in front of a LMS1xx LIDAR sensor
 *** Version:
 ***     1.0: 2020-10-13/jwalter -  -
 *************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_wstring.h"
#include "forte_uint.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

#define FBT_INCLUDES
#include "LMS1xxNearest.h"
#undef FBT_INCLUDES


class FORTE_LMS1xxNearest final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_LMS1xxNearest)

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

#include "LMS1xxNearest.h"

  public:
    FORTE_LMS1xxNearest(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_BOOL var_QI;

    CIEC_BOOL var_QO;
    CIEC_WSTRING var_STATUS;
    CIEC_UINT var_DISTANCE;

    CIEC_BOOL var_conn_QO;
    CIEC_WSTRING var_conn_STATUS;
    CIEC_UINT var_conn_DISTANCE;

    CEventConnection conn_INITO;
    CEventConnection conn_CNF;

    CDataConnection *conn_QI;

    CDataConnection conn_QO;
    CDataConnection conn_STATUS;
    CDataConnection conn_DISTANCE;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_INIT(const CIEC_BOOL &paQI, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS, CIEC_UINT &paDISTANCE) {
      var_QI = paQI;
      executeEvent(scmEventINITID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
      paDISTANCE = var_DISTANCE;
    }

    void evt_REQ(const CIEC_BOOL &paQI, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS, CIEC_UINT &paDISTANCE) {
      var_QI = paQI;
      executeEvent(scmEventREQID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
      paDISTANCE = var_DISTANCE;
    }

    void operator()(const CIEC_BOOL &paQI, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS, CIEC_UINT &paDISTANCE) {
      evt_INIT(paQI, paQO, paSTATUS, paDISTANCE);
    }
};


