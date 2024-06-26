#pragma once

#include <cstdint>

extern const char *LMS1xx_init();
extern const char *LMS1xx_deinit();
extern const char *LMS1xx_fetchLatest();
extern const char *LMS1xx_measureNearest(uint16_t &val);
extern const char *LMS1xx_measureFarthest(uint16_t &val);
