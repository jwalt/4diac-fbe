#ifdef FBT_INCLUDES
#include <filesystem>
#include <array>
#include <optional>
#include <unistd.h>
#include <fcntl.h>
#else

std::string sysfs_file;

std::string set_error(std::string s)
{
  var_STATUS = CIEC_WSTRING((s+" ("+strerror(errno)+")").c_str());
  return "";
}

std::string readstr(std::string info)
{
  int fd = open(sysfs_file.c_str(), O_RDONLY);
  if (fd < 0) return set_error(info + " open");

  std::array<char, 256> value;
  ssize_t sz = read(fd, value.data(), size_t(value.size()));
  if (sz < 0 || sz >= ssize_t(value.size())) return set_error(info + " read");

  int rc = close(fd);
  if (rc) return set_error(info + " close");

  return std::string(value.data(), sz);
}

std::string findSensor()
{
  for (auto &p : std::filesystem::directory_iterator("/sys/bus/w1/devices")) {
    DEVLOG_DEBUG("1Wire-Path: %s\n", p.path().c_str());
    if (p.path() != "/sys/bus/w1/devices/w1_bus_master1") return p.path().string();
  }

  return "";
}

float transfer()
{
  auto val = readstr("1-wire sensor");
  auto pos = val.find("t=");
  if (pos == val.npos) return NAN;

  return std::stof(val.substr(pos+2, val.size()-pos-3))/1000;
}

std::optional<TEventID> executeINIT()
{
  var_QO = CIEC_BOOL(0);

  if (!var_QI) {
    sysfs_file = "";
    var_STATUS = CIEC_WSTRING("CLOSED");

  } else do {
      sysfs_file = findSensor();
      if (sysfs_file.empty()) break;
      sysfs_file += "/w1_slave";
      var_QO = CIEC_BOOL(1);
      var_STATUS = CIEC_WSTRING("OK");
      
    } while (false);

  return scmEventINITOID;
}

std::optional<TEventID> executeREQ()
{
  if (var_QI && var_QO) do {
    auto val = transfer();
    if (!val) break;

    var_TEMP = CIEC_REAL(val);
    var_STATUS = CIEC_WSTRING("OK");
    return scmEventCNFID;
  } while (false);

  var_QO = CIEC_BOOL(0);
  return scmEventCNFID;
}

#endif
