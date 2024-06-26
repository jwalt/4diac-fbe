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

#pragma once

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_uint.h"
#include "forte_byte.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

#define FBT_INCLUDES
#include "MCP23017.h"
#undef FBT_INCLUDES

class FORTE_MCP23017 final : public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_MCP23017)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventINITID = 0;
    static const TEventID scmEventREQ_AID = 1;
    static const TEventID scmEventREQ_BID = 2;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const TEventID scmEventINITOID = 0;
    static const TEventID scmEventCNF_AID = 1;
    static const TEventID scmEventCNF_BID = 2;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

#include "MCP23017.h"

  public:
    FORTE_MCP23017(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_BOOL var_QI;
    CIEC_UINT var_BUS_NUM;
    CIEC_BYTE var_I2C_ADDR;
    CIEC_BYTE var_OE_A;
    CIEC_BYTE var_OE_B;
    CIEC_BYTE var_SD_A;
    CIEC_BYTE var_SD_B;

    CIEC_BOOL var_QO;
    CIEC_BYTE var_RD_A;
    CIEC_BYTE var_RD_B;

    CIEC_BOOL var_conn_QO;
    CIEC_BYTE var_conn_RD_A;
    CIEC_BYTE var_conn_RD_B;

    CEventConnection conn_INITO;
    CEventConnection conn_CNF_A;
    CEventConnection conn_CNF_B;

    CDataConnection *conn_QI;
    CDataConnection *conn_BUS_NUM;
    CDataConnection *conn_I2C_ADDR;
    CDataConnection *conn_OE_A;
    CDataConnection *conn_OE_B;
    CDataConnection *conn_SD_A;
    CDataConnection *conn_SD_B;

    CDataConnection conn_QO;
    CDataConnection conn_RD_A;
    CDataConnection conn_RD_B;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_INIT(const CIEC_BOOL &paQI, const CIEC_UINT &paBUS_NUM, const CIEC_BYTE &paI2C_ADDR, const CIEC_BYTE &paOE_A, const CIEC_BYTE &paOE_B, const CIEC_BYTE &paSD_A, const CIEC_BYTE &paSD_B, CIEC_BOOL &paQO, CIEC_BYTE &paRD_A, CIEC_BYTE &paRD_B) {
      var_QI = paQI;
      var_BUS_NUM = paBUS_NUM;
      var_I2C_ADDR = paI2C_ADDR;
      var_OE_A = paOE_A;
      var_OE_B = paOE_B;
      var_SD_A = paSD_A;
      var_SD_B = paSD_B;
      executeEvent(scmEventINITID, nullptr);
      paQO = var_QO;
      paRD_A = var_RD_A;
      paRD_B = var_RD_B;
    }

    void evt_REQ_A(const CIEC_BOOL &paQI, const CIEC_UINT &paBUS_NUM, const CIEC_BYTE &paI2C_ADDR, const CIEC_BYTE &paOE_A, const CIEC_BYTE &paOE_B, const CIEC_BYTE &paSD_A, const CIEC_BYTE &paSD_B, CIEC_BOOL &paQO, CIEC_BYTE &paRD_A, CIEC_BYTE &paRD_B) {
      var_QI = paQI;
      var_BUS_NUM = paBUS_NUM;
      var_I2C_ADDR = paI2C_ADDR;
      var_OE_A = paOE_A;
      var_OE_B = paOE_B;
      var_SD_A = paSD_A;
      var_SD_B = paSD_B;
      executeEvent(scmEventREQ_AID, nullptr);
      paQO = var_QO;
      paRD_A = var_RD_A;
      paRD_B = var_RD_B;
    }

    void evt_REQ_B(const CIEC_BOOL &paQI, const CIEC_UINT &paBUS_NUM, const CIEC_BYTE &paI2C_ADDR, const CIEC_BYTE &paOE_A, const CIEC_BYTE &paOE_B, const CIEC_BYTE &paSD_A, const CIEC_BYTE &paSD_B, CIEC_BOOL &paQO, CIEC_BYTE &paRD_A, CIEC_BYTE &paRD_B) {
      var_QI = paQI;
      var_BUS_NUM = paBUS_NUM;
      var_I2C_ADDR = paI2C_ADDR;
      var_OE_A = paOE_A;
      var_OE_B = paOE_B;
      var_SD_A = paSD_A;
      var_SD_B = paSD_B;
      executeEvent(scmEventREQ_BID, nullptr);
      paQO = var_QO;
      paRD_A = var_RD_A;
      paRD_B = var_RD_B;
    }

    void operator()(const CIEC_BOOL &paQI, const CIEC_UINT &paBUS_NUM, const CIEC_BYTE &paI2C_ADDR, const CIEC_BYTE &paOE_A, const CIEC_BYTE &paOE_B, const CIEC_BYTE &paSD_A, const CIEC_BYTE &paSD_B, CIEC_BOOL &paQO, CIEC_BYTE &paRD_A, CIEC_BYTE &paRD_B) {
      evt_INIT(paQI, paBUS_NUM, paI2C_ADDR, paOE_A, paOE_B, paSD_A, paSD_B, paQO, paRD_A, paRD_B);
    }
};


