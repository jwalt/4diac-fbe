/*
 * lms_structs.h
 *
 *  Author: Konrad Banachowicz
 *          Mike Purvis <mpurvis@clearpathrobotics.com>
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

#pragma once

#include <cstdint>

struct scanCfg {
  /* Scanning frequency. 1/100 Hz */
  int scaningFrequency;

  /* Scanning resolution. 1/10000 degree */
  int angleResolution;

  /* Start angle. 1/10000 degree */
  int startAngle;

  /* Stop angle. 1/10000 degree */
  int stopAngle;
};

struct scanDataCfg {

  /* Output channels. Defines which output channel is activated. */
  int outputChannel;

  /* Remission. Defines whether remission values are output. */
  bool remission;

  /* Remission resolution. Defines whether the remission values are output with 8-bit or 16bit resolution. */
  int resolution;

  /* Encoders channels. Defines which output channel is activated. */
  int encoder;

  /* Position. Defines whether position values are output. */
  bool position;

  /* Device name. Determines whether the device name is to be output. */
  bool deviceName;

  bool timestamp;

  /* Output interval. Defines which scan is output.
   *
   * 01 every scan
   * 02 every 2nd scan
   * ...
   * 50000 every 50000th scan
   */
  int outputInterval;
};

struct scanOutputRange {
  /* Scanning resolution. 1/10000 degree */
  int angleResolution;

  /* Start angle. 1/10000 degree */
  int startAngle;

  /* Stop angle. 1/10000 degree */
  int stopAngle;
};

struct scanData {
  /* Number of samples in dist1. */
  int dist_len1;

  /* Radial distance for the first reflected pulse */
  uint16_t dist1[1082];

  /* Number of samples in dist2. */
  int dist_len2;

  /* Radial distance for the second reflected pulse */
  uint16_t dist2[1082];

  /* Number of samples in rssi1. */
  int rssi_len1;

  /* Remission values for the first reflected pulse */
  uint16_t rssi1[1082];

  /* Number of samples in rssi2. */
  int rssi_len2;

  /* Remission values for the second reflected pulse */
  uint16_t rssi2[1082];
};
