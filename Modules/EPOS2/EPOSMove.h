/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: EPOSMove
 *** Description: Initiate movement of a Maxon EPOS motor controller connected via USB. FIXME: Units are not yet accurate and disregard gears.
 *** Version: 
 ***     1.0: 2020-10-12/jwalter -  - 
 *************************************************************************/

#ifndef _EPOSMOVE_H_
#define _EPOSMOVE_H_

#include <funcbloc.h>
#include <forte_bool.h>
#include <forte_byte.h>
#include <forte_real.h>
#include <forte_wstring.h>

class FORTE_EPOSMove: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_EPOSMove)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_BOOL &QI() {
    return *static_cast<CIEC_BOOL*>(getDI(0));
  };

  CIEC_BYTE &NODE() {
    return *static_cast<CIEC_BYTE*>(getDI(1));
  };

  CIEC_REAL &TARGET() {
    return *static_cast<CIEC_REAL*>(getDI(2));
  };

  CIEC_BYTE &MODE() {
    return *static_cast<CIEC_BYTE*>(getDI(3));
  };

  CIEC_REAL &SPEED() {
    return *static_cast<CIEC_REAL*>(getDI(4));
  };

  CIEC_REAL &ACCEL() {
    return *static_cast<CIEC_REAL*>(getDI(5));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_BOOL &QO() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  };

  CIEC_WSTRING &STATUS() {
    return *static_cast<CIEC_WSTRING*>(getDO(1));
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

   FORTE_FB_DATA_ARRAY(2, 6, 2, 0);

virtual void setInitialValues();

  void executeEvent(int pa_nEIID);

public:
  FUNCTION_BLOCK_CTOR(FORTE_EPOSMove){
  };

  virtual ~FORTE_EPOSMove(){};

};

#endif //close the ifdef sequence from the beginning of the file

