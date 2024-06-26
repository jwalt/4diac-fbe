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

#include "SpawnProgram_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SpawnProgram_fbt_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_SpawnProgram, g_nStringIdSpawnProgram)

const CStringDictionary::TStringId FORTE_SpawnProgram::scmDataInputNames[] = {g_nStringIdEXECUTABLE, g_nStringIdARG, g_nStringIdWAIT};
const CStringDictionary::TStringId FORTE_SpawnProgram::scmDataInputTypeIds[] = {g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdBOOL};
const CStringDictionary::TStringId FORTE_SpawnProgram::scmDataOutputNames[] = {g_nStringIdSTATUS, g_nStringIdRESULT};
const CStringDictionary::TStringId FORTE_SpawnProgram::scmDataOutputTypeIds[] = {g_nStringIdWSTRING, g_nStringIdDINT};
const TDataIOID FORTE_SpawnProgram::scmEIWith[] = {1, 0, 2, scmWithListDelimiter};
const TForteInt16 FORTE_SpawnProgram::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_SpawnProgram::scmEventInputNames[] = {g_nStringIdREQ};
const TDataIOID FORTE_SpawnProgram::scmEOWith[] = {1, 0, scmWithListDelimiter};
const TForteInt16 FORTE_SpawnProgram::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_SpawnProgram::scmEventOutputNames[] = {g_nStringIdCNF};
const SFBInterfaceSpec FORTE_SpawnProgram::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEOWith, scmEOWithIndexes,
  3, scmDataInputNames, scmDataInputTypeIds,
  2, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_SpawnProgram::FORTE_SpawnProgram(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, &scmFBInterfaceSpec, paInstanceNameId),
    var_conn_STATUS(var_STATUS),
    var_conn_RESULT(var_RESULT),
    conn_CNF(this, 0),
    conn_EXECUTABLE(nullptr),
    conn_ARG(nullptr),
    conn_WAIT(nullptr),
    conn_STATUS(this, 0, &var_conn_STATUS),
    conn_RESULT(this, 1, &var_conn_RESULT) {
};

void FORTE_SpawnProgram::setInitialValues() {
	var_EXECUTABLE = u""_WSTRING;
	var_ARG = u""_WSTRING;
	var_WAIT = 0_BOOL;
	var_STATUS = u""_WSTRING;
	var_RESULT = 0_DINT;
}

#include <string>
#include <spawn.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
extern char **environ;
using namespace std;

void FORTE_SpawnProgram::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch(paEIID) {
    case scmEventREQID: {
      // FIXME: this relies on the fact that right now, WSTRING is basically
      // STRING and programs can just use it with UTF-8
      char *const argv[3] = { var_EXECUTABLE.getValue(), var_ARG.getValue(), NULL };
      pid_t pid = 0;

      posix_spawn_file_actions_t fa;
      posix_spawn_file_actions_init(&fa);
      // Try to limit the effect of leaking sensitive file descriptors (i.e.,
      // bugs). Unfortunately this will always unreliable, since there is no
      // reliable and portable alternative. Let's hope nothing sensitive has an
      // FD >=1024 without FD_CLOEXEC flag set.
      for (int i = 3; i < 1024; i++) posix_spawn_file_actions_adddup2(&fa, 0, i);
      for (int i = 3; i < 1024; i++) posix_spawn_file_actions_addclose(&fa, i);

      posix_spawnattr_t attr;
      posix_spawnattr_init(&attr);
      posix_spawnattr_setflags(&attr, POSIX_SPAWN_SETSIGDEF|POSIX_SPAWN_SETSIGMASK);
      sigset_t mask;
      sigfillset(&mask);
      posix_spawnattr_setsigdefault(&attr, &mask);
      sigemptyset(&mask);
      posix_spawnattr_setsigmask(&attr, &mask);
      
      if (posix_spawnp(&pid, var_EXECUTABLE.getValue(), &fa, &attr, argv, environ)) {
        var_STATUS = CIEC_WSTRING("Could not spawn program");
      } else if (var_WAIT) {
        int status;
        do {
          int st = waitpid(pid, &status, WUNTRACED | WCONTINUED);
          if (st == -1) {
            var_STATUS = CIEC_WSTRING("Wait failed");
            break;
          }

          if (WIFEXITED(status)) var_STATUS = CIEC_WSTRING("Process exited");
          else if (WIFSIGNALED(status)) var_STATUS = CIEC_WSTRING("Process was killed");
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        var_RESULT = CIEC_DINT(WIFEXITED(status)?WEXITSTATUS(status):WTERMSIG(status));
      } else {
        var_RESULT = CIEC_DINT(pid);
      }
      
      posix_spawnattr_destroy(&attr);
      posix_spawn_file_actions_destroy(&fa);
      sendOutputEvent(scmEventCNFID, paECET);
      break;
    }
  }
}

void FORTE_SpawnProgram::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(1, var_ARG, conn_ARG);
      readData(0, var_EXECUTABLE, conn_EXECUTABLE);
      readData(2, var_WAIT, conn_WAIT);
      break;
    }
    default:
      break;
  }
}

void FORTE_SpawnProgram::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(1, var_RESULT, conn_RESULT);
      writeData(0, var_STATUS, conn_STATUS);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_SpawnProgram::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_EXECUTABLE;
    case 1: return &var_ARG;
    case 2: return &var_WAIT;
  }
  return nullptr;
}

CIEC_ANY *FORTE_SpawnProgram::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_STATUS;
    case 1: return &var_RESULT;
  }
  return nullptr;
}

CEventConnection *FORTE_SpawnProgram::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_SpawnProgram::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_EXECUTABLE;
    case 1: return &conn_ARG;
    case 2: return &conn_WAIT;
  }
  return nullptr;
}

CDataConnection *FORTE_SpawnProgram::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_STATUS;
    case 1: return &conn_RESULT;
  }
  return nullptr;
}

