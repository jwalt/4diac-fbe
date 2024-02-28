/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: EPOSGetStatus
 *** Description: Get EPOS status flags
 *** Version: 
 ***     1.0: 2020-10-12/jwalter -  - 
 *************************************************************************/

#ifndef _EPOSGETSTATUS_H_
#define _EPOSGETSTATUS_H_

#include <funcbloc.h>
#include <forte_bool.h>
#include <forte_byte.h>
#include <forte_wstring.h>

class FORTE_EPOSGetStatus: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_EPOSGetStatus)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_BOOL &QI() {
    return *static_cast<CIEC_BOOL*>(getDI(0));
  };

  CIEC_BYTE &NODE() {
    return *static_cast<CIEC_BYTE*>(getDI(1));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_BOOL &QO() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  };

  CIEC_WSTRING &STATUS() {
    return *static_cast<CIEC_WSTRING*>(getDO(1));
  };

  CIEC_BOOL &ENABLED() {
    return *static_cast<CIEC_BOOL*>(getDO(2));
  };

  CIEC_BOOL &MOVING() {
    return *static_cast<CIEC_BOOL*>(getDO(3));
  };

  CIEC_BOOL &QUICKSTOP() {
    return *static_cast<CIEC_BOOL*>(getDO(4));
  };

  CIEC_BOOL &DONE() {
    return *static_cast<CIEC_BOOL*>(getDO(5));
  };

  CIEC_BOOL &FAULT() {
    return *static_cast<CIEC_BOOL*>(getDO(6));
  };

  CIEC_BYTE &ERROR() {
    return *static_cast<CIEC_BYTE*>(getDO(7));
  };

  static const TEventID scm_nEventINITID = 0;
  static const TEventID scm_nEventREQID = 1;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventINITOID = 0;
  static const TEventID scm_nEventCNFID = 1;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

   FORTE_FB_DATA_ARRAY(2, 2, 8, 0);

  void executeEvent(int pa_nEIID);

public:
  FUNCTION_BLOCK_CTOR(FORTE_EPOSGetStatus){
  };

  virtual ~FORTE_EPOSGetStatus(){};

};

#endif //close the ifdef sequence from the beginning of the file

