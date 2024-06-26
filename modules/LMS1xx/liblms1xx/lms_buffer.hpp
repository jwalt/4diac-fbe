/*
 * lms_buffer.h
 *
 *  Author: Mike Purvis <mpurvis@clearpathrobotics.com>
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

#include <array>
#include <cstdint>
#include <cstring>
#include <unistd.h>

#define LMS_BUFFER_SIZE 50000
#define LMS_STX 0x02
#define LMS_ETX 0x03

class LMSBuffer
{
  public:
    LMSBuffer() : total_length_(0), end_of_first_message_(0) {}

    bool hasData() const { return total_length_ > 0; }
    void clear() { total_length_ = 0; }

    void readFrom(int fd) {
      auto ret = read(fd, buffer_.data() + total_length_, buffer_.size() - total_length_);

      if (ret > 0) {
        total_length_ = uint16_t(total_length_ + ret);
        DEVLOG_DEBUG("Read %d bytes from fd, total length is %d.\n", ret, total_length_);
      } else {
        DEVLOG_WARNING("Buffer read() returned error.\n");
      }
    }

    char* getNextBuffer() {
      if (total_length_ == 0) {
        // Buffer is empty, no scan data present.
        DEVLOG_DEBUG("Empty buffer, nothing to return.\n");
        return NULL;
      }

      // The objective is to have a message starting at the start of the buffer, so if that's not
      // the case, then we look for a start-of-message character and shift the buffer back, discarding
      // any characters in the middle.
      auto start_of_message = (char*)memchr(buffer_.data(), LMS_STX, total_length_);
      if (!start_of_message) {
        // None found, buffer reset.
        DEVLOG_WARNING("No STX found, dropping %d bytes from buffer.\n", total_length_);
        total_length_ = 0;
      } else if (buffer_.data() != start_of_message) {
        // Start of message found, ahead of the start of buffer. Therefore shift the buffer back.
        DEVLOG_WARNING("Shifting buffer, dropping %d bytes, %d bytes remain.\n",
                (start_of_message - buffer_.data()), total_length_ - (start_of_message - buffer_.data()));
        shiftBuffer(start_of_message);
      }

      // Now look for the end of message character.
      end_of_first_message_ = (char*)memchr(buffer_.data(), LMS_ETX, total_length_);
      if (!end_of_first_message_) {
        // No end of message found, therefore no message to parse and return.
        DEVLOG_DEBUG("No ETX found, nothing to return.\n");
        return NULL;
      }

      // Null-terminate buffer.
      *end_of_first_message_ = 0;
      return buffer_.data();
    }

    void popLastBuffer() {
      if (end_of_first_message_) {
        shiftBuffer(end_of_first_message_ + 1);
        end_of_first_message_ = NULL;
      }
    }

  private:
    void shiftBuffer(char* new_start) {
      // Shift back anything remaining in the buffer.
      auto remaining_length = uint16_t(total_length_ - (new_start - buffer_.data()));

      if (remaining_length > 0) {
        memmove(buffer_.data(), new_start, remaining_length);
      }
      total_length_ = remaining_length;
    }

    std::array<char,LMS_BUFFER_SIZE> buffer_;
    uint16_t total_length_;
    char* end_of_first_message_;
};
