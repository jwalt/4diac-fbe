/*******************************************************************************
 * Copyright (c) 2015, 2016 fortiss GmbH
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *    Alois Zoitl - initial API and implementation and/or initial documentation
 *    Jose Cabral - expansion of capabilities
 *******************************************************************************/

// make cmpiler error checkers happy on non-win32
#ifndef _WIN32
#define _FIXED
#define _FAR
#define GNU_PACKED

#ifndef ULONG_PTR
#define ULONG_PTR unsigned long *
#endif
#endif

#include <pcio.h>
#include <cio.h>

#include "processinterface.h"
#include <string>
#include <mutex>
#include <cstdlib>



const char * const CIMCEAProcessInterface::scmOK = "OK";
const char * const CIMCEAProcessInterface::scmError = "Error";
const char * const CIMCEAProcessInterface::scmNotInitialised = "Not initialized";

static PcioBoardList boards = { 0, nullptr };
static std::mutex init_mutex;

static void deinit() {
  std::lock_guard<std::mutex> lg(init_mutex);
  if (!boards.Boards) return;

  PcioResult rc = PcioClose(&boards);
  if (rc != PCIO_OK) {
    DEVLOG_ERROR("PcioClose failed: 0x%08x.", rc);
    return;
  }
  boards.Boards = nullptr;
}

static std::array<std::array<uint16_t, 4>,10> outputs;

static bool init() {
  std::lock_guard<std::mutex> lg(init_mutex);
  if (boards.Boards) return true;

  PcioResult rc = PcioInit(&boards);
  if (rc != PCIO_OK) {
    DEVLOG_ERROR("PcioInit failed: 0x%08x.", rc);
    return false;
  }

  if (std::atexit(deinit)) {
    DEVLOG_ERROR("PcioClose atexit failed. Continuing anyways.");
  }

  for (auto b = 0u; b < boards.Count; b++) {
    outputs[b][0] = *(uint16_t*)(boards.Boards[b].BaseAddress + CIO_REG_SendData_0);
    outputs[b][1] = *(uint16_t*)(boards.Boards[b].BaseAddress + CIO_REG_SendData_1);
    outputs[b][2] = *(uint16_t*)(boards.Boards[b].BaseAddress + CIO_REG_SendData_2);
    outputs[b][3] = *(uint16_t*)(boards.Boards[b].BaseAddress + CIO_REG_SendData_3);
    DEVLOG_DEBUG("IMCEA Board %i, outputs = 0x%04x:0x%04x:0x%04x:0x%04x.",
               b, outputs[b][0], outputs[b][1], outputs[b][2], outputs[b][3]);
  }
  //memset(outputs.data(), 0xff, sizeof(outputs));
  return true;
}

CIMCEAProcessInterface::CIMCEAProcessInterface(
  CResource *paSrcRes,
  const SFBInterfaceSpec *paInterfaceSpec,
  const CStringDictionary::TStringId paInstanceNameId,
  TForteByte *paFBConnData,
  TForteByte *paFBVarsData)
  : CProcessInterfaceBase(paSrcRes, paInterfaceSpec, paInstanceNameId, paFBConnData, paFBVarsData)
{
}

CIMCEAProcessInterface::~CIMCEAProcessInterface() {
}

bool CIMCEAProcessInterface::initialise(bool){
  STATUS() = CIEC_STRING(scmNotInitialised);

  if (!init()) {
    DEVLOG_ERROR("The FB with PARAMS() = '%s' couldn't be initialized.",
                 PARAMS().getValue());
    return false;
  }

  auto params = std::string(PARAMS().getValue());
  _board = params[0]-'0';
  _slot = params[1]-'0';
  if (params[1] == 'B') _slot = PCIO_SLOT_BASE;

  _bit = 1 << ((params[2]-'0')*10 + (params[3]-'0'));

  if (_board > 9 || _slot > 3) {
    DEVLOG_ERROR("The FB with PARAMS() = '%s' couldn't be initialized. "
                 "PARAMS should be a 4-digit string <board><slot><2-digit bitnum>.",
                 PARAMS().getValue());
    return false;
  }

  outputs.at(_board).at(_slot) &= ~_bit;

  DEVLOG_INFO("IMCEA Board %i, Slot %i, bitmask 0x08x initialised.", _board, _slot, _bit);
  STATUS() = CIEC_STRING(scmOK);
  return true;
}

bool CIMCEAProcessInterface::deinitialise(){
  STATUS() = CIEC_STRING(scmOK);
  return true;
}

/* READ AND WRITE FUNCTIONS */

bool CIMCEAProcessInterface::readPin(){
  uint32_t value;
  auto rc = PcioReadDigitalInput(_board, (PcioSlot)_slot, &value);
  if (rc != PCIO_OK) {
    DEVLOG_ERROR("Reading pin failed for FB with PARAMS() = '%s'.", PARAMS().getValue());
    STATUS() = CIEC_STRING(scmError);
    return false;
  }
  DEVLOG_DEBUG("IMCEA Board %i, Slot %i => 0x%08x.", _board, _slot, value);

  IN_X() = CIEC_BOOL(!!(value & _bit));
  STATUS() = CIEC_STRING(scmOK);
  return true;
}

bool CIMCEAProcessInterface::writePin(){
  if (OUT_X()) outputs[_board][_slot] |= _bit;
  else outputs[_board][_slot] &= ~_bit;

  DEVLOG_DEBUG("IMCEA Board %i, Slot %i <= 0x%08x.", _board, _slot, outputs[_board][_slot]);

  auto rc = PcioWriteDigitalOutput(_board, (PcioSlot)_slot, outputs[_board][_slot]);
  if (rc != PCIO_OK) {
    DEVLOG_ERROR("Writing pin failed for FB with PARAMS() = '%s'.", PARAMS().getValue());
    STATUS() = CIEC_STRING(scmError);
    return false;
  }

  STATUS() = CIEC_STRING(scmOK);
  return true;
}
