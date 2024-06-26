/*
 * LMS1xx.cpp
 *
 *  Created on: 09-08-2010
 *  Author: Konrad Banachowicz
 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define NOLOG
#undef LOGDEBUG
#include "../../../forte/src/arch/devlog.h"

#include "LMS1xx.hpp"

#define STX "\002"
#define ETX "\003"

LMS1xx::LMS1xx() : connected_(false) {}

LMS1xx::~LMS1xx() {}

void LMS1xx::connect(std::string host, int port) {
  if (connected_) {
    DEVLOG_WARNING("Already connected to LMS.\n");
    return;
  }

  DEVLOG_DEBUG("Creating non-blocking socket.\n");
  socket_fd_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (socket_fd_ <= 0) {
    DEVLOG_ERROR("Could not create socket for LMS.\n");
    return;
  }

  struct sockaddr_in stSockAddr;
  stSockAddr.sin_family = PF_INET;
  stSockAddr.sin_port = htons(port);
  inet_pton(AF_INET, host.c_str(), &stSockAddr.sin_addr);

  DEVLOG_DEBUG("Connecting socket to laser.\n");
  int ret = ::connect(socket_fd_, (struct sockaddr *) &stSockAddr, sizeof(stSockAddr));

  if (ret) {
    DEVLOG_ERROR("Could not connect to LMS.\n");
    return;
  }

  fcntl(socket_fd_, F_SETFL, fcntl(socket_fd_, F_GETFL, 0) | O_NONBLOCK);

  connected_ = true;
  DEVLOG_DEBUG("Connected succeeded.\n");
}

void LMS1xx::disconnect() {
  if (connected_) {
    close(socket_fd_);
    connected_ = false;
  }
}

bool LMS1xx::isConnected() {
  return connected_;
}

int LMS1xx::sendCommand(const char *cmd, std::array<char,100> &buf) {
  DEVLOG_DEBUG("TX: <STX> %s <ETX>\n", cmd);
  write(socket_fd_, STX, 1);
  write(socket_fd_, cmd, strlen(cmd));
  write(socket_fd_, ETX, 1);

  fd_set rfds;
  FD_ZERO(&rfds);
  FD_SET(socket_fd_, &rfds);
  select(socket_fd_ + 1, &rfds, NULL, NULL, NULL);

  auto len = read(socket_fd_, buf.data(), 100);
  if (len <= 1) {
    DEVLOG_ERROR("no packet recieved\n");
    return 0;
  }

  if (buf[0] != LMS_STX) {
    DEVLOG_WARNING("invalid packet recieved\n");
    return 0;
  }
  
  buf[(unsigned)len] = 0;
  DEVLOG_DEBUG("RX: %s\n", buf.data());

  return int(len);
}

void LMS1xx::startMeas() {
  sendCommand("sMN LMCstartmeas");
}

void LMS1xx::stopMeas() {
  sendCommand("sMN LMCstopmeas");
}

status_t LMS1xx::queryStatus() {
  std::array<char,100> buf;
  if (!sendCommand("sRN STlms", buf)) return undefined;

  int ret;
  sscanf((buf.data() + 10), "%d\n", &ret);

  return (status_t) ret;
}

void LMS1xx::login() {
  sendCommand("sMN SetAccessMode 03 F4724744");
}

void LMS1xx::logout() {
  sendCommand("sMN Run");
}

scanCfg LMS1xx::getScanCfg() {
  scanCfg cfg;

  std::array<char,100> buf;
  if (!sendCommand("sRN LMPscancfg", buf)) return cfg;

  sscanf(buf.data() + 1, "%*s %*s %X %*d %X %X %X\n", &cfg.scaningFrequency,
         &cfg.angleResolution, &cfg.startAngle, &cfg.stopAngle);
  
  return cfg;
}

void LMS1xx::setScanCfg(const scanCfg &cfg) {
  char buf[100];
  sprintf(buf, "sMN mLMPsetscancfg %X +1 %X %X %X",
          cfg.scaningFrequency, cfg.angleResolution, cfg.startAngle,
          cfg.stopAngle);

  sendCommand(buf);
}

void LMS1xx::setScanDataCfg(const scanDataCfg &cfg) {
  char buf[100];
  sprintf(buf, "sWN LMDscandatacfg %02X 00 %d %d 0 %02X 00 %d %d 0 %d +%d",
          cfg.outputChannel, cfg.remission ? 1 : 0,
          cfg.resolution, cfg.encoder, cfg.position ? 1 : 0,
          cfg.deviceName ? 1 : 0, cfg.timestamp ? 1 : 0, cfg.outputInterval);

  sendCommand(buf);
}

scanOutputRange LMS1xx::getScanOutputRange() {
  scanOutputRange outputRange;

  std::array<char,100> buf;
  if (!sendCommand("sRN LMPoutputRange", buf)) return outputRange;

  sscanf(buf.data() + 1, "%*s %*s %*d %X %X %X", &outputRange.angleResolution,
         &outputRange.startAngle, &outputRange.stopAngle);
  return outputRange;
}

void LMS1xx::scanContinous(bool start) {
  if (start) {
    sendCommand("sEN LMDscandata 1");
  } else {
    sendCommand("sEN LMDscandata 0");
  }
}

bool LMS1xx::getScanData(scanData& scan_data) {
  fd_set rfds;
  FD_ZERO(&rfds);
  FD_SET(socket_fd_, &rfds);

  // Wait up to 200ms waiting for more data from the laser.
  for(;;) {
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 200000;

    DEVLOG_DEBUG("entering select()\n", tv.tv_usec);
    int retval = select(socket_fd_ + 1, &rfds, NULL, NULL, &tv);
    DEVLOG_DEBUG("returned %d from select()\n", retval);

    // Select timed out or there was an fd error.
    if (!retval) return false;

    buffer_.readFrom(socket_fd_);

    // Will return pointer if a complete message exists in the buffer,
    // otherwise will return null.
    char* buffer_data = buffer_.getNextBuffer();
    if (!buffer_data) continue;

    parseScanData(buffer_data, scan_data);
    buffer_.popLastBuffer();
    return true;
  }
}

void LMS1xx::flush() {
  buffer_.clear();
  char buf[1024];
  while (read(socket_fd_, buf, sizeof(buf)) > 0);
}


void LMS1xx::parseScanData(char* buffer, scanData& data) {
  char* tok = strtok(buffer, " "); //Type of command
  tok = strtok(NULL, " "); //Command
  tok = strtok(NULL, " "); //VersionNumber
  tok = strtok(NULL, " "); //DeviceNumber
  tok = strtok(NULL, " "); //Serial number
  tok = strtok(NULL, " "); //DeviceStatus
  tok = strtok(NULL, " "); //MessageCounter
  tok = strtok(NULL, " "); //ScanCounter
  tok = strtok(NULL, " "); //PowerUpDuration
  tok = strtok(NULL, " "); //TransmissionDuration
  tok = strtok(NULL, " "); //InputStatus
  tok = strtok(NULL, " "); //OutputStatus
  tok = strtok(NULL, " "); //ReservedByteA
  tok = strtok(NULL, " "); //ScanningFrequency
  tok = strtok(NULL, " "); //MeasurementFrequency
  tok = strtok(NULL, " ");
  tok = strtok(NULL, " ");
  tok = strtok(NULL, " ");
  tok = strtok(NULL, " "); //NumberEncoders
  int NumberEncoders;
  sscanf(tok, "%d", &NumberEncoders);
  for (int i = 0; i < NumberEncoders; i++) {
    tok = strtok(NULL, " "); //EncoderPosition
    tok = strtok(NULL, " "); //EncoderSpeed
  }

  tok = strtok(NULL, " "); //NumberChannels16Bit
  int NumberChannels16Bit;
  sscanf(tok, "%d", &NumberChannels16Bit);
  DEVLOG_DEBUG("NumberChannels16Bit : %d\n", NumberChannels16Bit);

  for (int i = 0; i < NumberChannels16Bit; i++) {
    int type = -1; // 0 DIST1 1 DIST2 2 RSSI1 3 RSSI2
    char content[6];
    tok = strtok(NULL, " "); //MeasuredDataContent
    sscanf(tok, "%s", content);
    if (!strcmp(content, "DIST1")) {
      type = 0;
    }
    else if (!strcmp(content, "DIST2")) {
      type = 1;
    }
    else if (!strcmp(content, "RSSI1")) {
      type = 2;
    }
    else if (!strcmp(content, "RSSI2")) {
      type = 3;
    }
    tok = strtok(NULL, " "); //ScalingFactor
    tok = strtok(NULL, " "); //ScalingOffset
    tok = strtok(NULL, " "); //Starting angle
    tok = strtok(NULL, " "); //Angular step width
    tok = strtok(NULL, " "); //NumberData
    int NumberData;
    sscanf(tok, "%X", &NumberData);
    DEVLOG_DEBUG("NumberData %i: %d\n", i, NumberData);

    if (type == 0) {
      data.dist_len1 = NumberData;
    } else if (type == 1) {
      data.dist_len2 = NumberData;
    } else if (type == 2) {
      data.rssi_len1 = NumberData;
    } else if (type == 3) {
      data.rssi_len2 = NumberData;
    }

    for (int j = 0; j < NumberData; j++) {
      int dat;
      tok = strtok(NULL, " "); //data
      sscanf(tok, "%X", &dat);

      if (type == 0) {
        data.dist1[j] = dat;
      } else if (type == 1) {
        data.dist2[j] = dat;
      } else if (type == 2) {
        data.rssi1[j] = dat;
      } else if (type == 3) {
        data.rssi2[j] = dat;
      }
    }
  }

  tok = strtok(NULL, " "); //NumberChannels8Bit
  int NumberChannels8Bit;
  sscanf(tok, "%d", &NumberChannels8Bit);
  DEVLOG_DEBUG("NumberChannels8Bit : %d  \n", NumberChannels8Bit);

  for (int i = 0; i < NumberChannels8Bit; i++) {
    int type = -1;
    char content[6];
    tok = strtok(NULL, " "); //MeasuredDataContent
    sscanf(tok, "%s", content);
    if (!strcmp(content, "DIST1")) {
      type = 0;
    } else if (!strcmp(content, "DIST2")) {
      type = 1;
    } else if (!strcmp(content, "RSSI1")) {
      type = 2;
    } else if (!strcmp(content, "RSSI2")) {
      type = 3;
    }
    tok = strtok(NULL, " "); //ScalingFactor
    tok = strtok(NULL, " "); //ScalingOffset
    tok = strtok(NULL, " "); //Starting angle
    tok = strtok(NULL, " "); //Angular step width
    tok = strtok(NULL, " "); //NumberData
    int NumberData;
    sscanf(tok, "%X", &NumberData);
    DEVLOG_DEBUG("NumberData %i: %d  \n", i, NumberData);

    if (type == 0) {
      data.dist_len1 = NumberData;
    } else if (type == 1) {
      data.dist_len2 = NumberData;
    } else if (type == 2) {
      data.rssi_len1 = NumberData;
    } else if (type == 3) {
      data.rssi_len2 = NumberData;
    }
    for (int j = 0; j < NumberData; j++)
    {
      int dat;
      tok = strtok(NULL, " "); //data
      sscanf(tok, "%X", &dat);

      if (type == 0) {
        data.dist1[j] = dat;
      } else if (type == 1) {
        data.dist2[j] = dat;
      } else if (type == 2) {
        data.rssi1[j] = dat;
      } else if (type == 3) {
        data.rssi2[j] = dat;
      }
    }
  }
}

void LMS1xx::saveConfig() {
  sendCommand("sMN mEEwriteall");
}

void LMS1xx::startDevice() {
  sendCommand("sMN Run");
}
