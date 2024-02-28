/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: EPOSGetDI
 *** Description: Get EPOS digital input values
 *** Version: 
 ***     1.0: 2020-10-12/jwalter - null - 
 *************************************************************************/

#ifndef _EPOSGETDI_H_
#define _EPOSGETDI_H_

#include <funcbloc.h>
#include <forte_bool.h>
#include <forte_byte.h>
#include <forte_wstring.h>

class FORTE_EPOSGetDI: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_EPOSGetDI)

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

  CIEC_BOOL &NEG_LIMIT() {
    return *static_cast<CIEC_BOOL*>(getDO(2));
  };

  CIEC_BOOL &POS_LIMIT() {
    return *static_cast<CIEC_BOOL*>(getDO(3));
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

   FORTE_FB_DATA_ARRAY(2, 2, 4, 0);

  void executeEvent(int pa_nEIID);

public:
  FUNCTION_BLOCK_CTOR(FORTE_EPOSGetDI){
  };

  virtual ~FORTE_EPOSGetDI(){};

};

#endif //close the ifdef sequence from the beginning of the file

