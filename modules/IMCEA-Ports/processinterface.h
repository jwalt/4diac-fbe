#pragma once

#include "../../org.eclipse.4diac.forte/src/stdfblib/io/processinterfacebase.h"

struct CIMCEAProcessInterface : public CProcessInterfaceBase {
    CIMCEAProcessInterface(CResource *, const SFBInterfaceSpec *,
                           const CStringDictionary::TStringId,
                           TForteByte *, TForteByte *);
    virtual ~CIMCEAProcessInterface();

  protected:
    bool initialise(bool paIsInput);
    bool deinitialise();
    bool writePin();
    bool readPin();

  private:
    unsigned _board;
    unsigned _slot;
    uint32_t _bit;

    static const char * const scmOK;
    static const char * const scmError;
    static const char * const scmNotInitialised;
};

typedef CIMCEAProcessInterface CProcessInterface;
