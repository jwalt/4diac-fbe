#ifdef FBT_INCLUDES
#include <filesystem>
#include <array>
#include <optional>
#include <unistd.h>
#include <fcntl.h>
#include "LMS1xxCommon.h"
#else


std::optional<TEventID> executeINIT()
{
  var_QO = CIEC_BOOL(0);
  const char *err = nullptr;

  if (!var_QI) {
    err = LMS1xx_deinit();

  } else do {
    err = LMS1xx_init();
    var_QO = CIEC_BOOL(!err);

  } while (false);

  var_STATUS = CIEC_WSTRING(err? err : "OK");
  return scmEventINITOID;
}

std::optional<TEventID> executeREQ()
{
  const char *err = nullptr;
  if (var_QI && var_QO) do {
    uint16_t val = 0;
    err = LMS1xx_fetchLatest();
    if (err) break;

    err = LMS1xx_measureNearest(val);
    if (err) break;

    var_DISTANCE = CIEC_UINT(val);
  } while (false);

  var_QO = CIEC_BOOL(!err);
  var_STATUS = CIEC_WSTRING(err? err : "OK");
  return scmEventCNFID;
}

#endif