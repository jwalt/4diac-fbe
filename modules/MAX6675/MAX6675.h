#ifdef FBT_INCLUDES
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <optional>
#else

int spi_fd = -1;

bool set_error(std::string s)
{
  var_STATUS = CIEC_WSTRING((s+" ("+strerror(errno)+")").c_str());
  return false;
}

bool writestr(const char *file, const char *value, std::string info)
{
  int fd = open(file, O_WRONLY);
  if (fd < 0) return set_error(info + " open");

  size_t sz = write(fd, value, strlen(value));
  if (sz != strlen(value)) return set_error(info + " write");

  int rc = close(fd);
  if (rc) return set_error(info + " close");

  return true;
}

bool setCS(bool active)
{
  return writestr("/sys/class/gpio/gpio60/value", (active?"0":"1"), "CS value");
}

bool initCS()
{
  if (!writestr("/sys/devices/platform/ocp/ocp:P9_12_pinmux/state",
                "gpio", "CS pinmux")) return false;
  if (!writestr("/sys/class/gpio/gpio60/direction",
                "out", "CS direction")) return false;
  return setCS(false);
}

int initSPI()
{
  if (!writestr("/sys/devices/platform/ocp/ocp:P9_29_pinmux/state",
                "spi", "MISO pinmux")) return false;
  if (!writestr("/sys/devices/platform/ocp/ocp:P9_31_pinmux/state",
                "spi_sclk", "SCLK pinmux")) return false;

  int fd = open("/dev/spidev1.0", O_RDWR);
  if (fd < 0) return set_error("can't open device");


  uint32_t mode = 0;
  int ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
  if (ret == -1) return set_error("can't set spi mode");

  ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
  if (ret == -1 || mode != 0) return set_error("can't get spi mode");


  uint8_t bits = 16;
  ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
  if (ret == -1) return set_error("can't set bits per word");

  ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
  if (ret == -1 || bits != 16) return set_error("can't get bits per word");


  uint32_t speed = 500000;
  ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
  if (ret == -1) return set_error("can't set max speed hz");

  ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
  if (ret == -1 || speed != 500000) return set_error("can't get max speed hz");

  return fd;
}

int transfer(int fd)
{
  uint16_t out = 0;
  struct spi_ioc_transfer tr{};
  tr.len = 2;
  tr.delay_usecs = 0;
  tr.speed_hz = 500000;
  tr.bits_per_word = 16;
  tr.tx_nbits = 1;
  tr.rx_nbits = 1;
  tr.tx_buf = (uintptr_t)&out;
  tr.rx_buf = (uintptr_t)&out;


  int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
  if (ret < 1) return set_error("can't send spi message");

  if (out & 2) return set_error("invalid data: device id == 1");
  if (out & 4) return set_error("invalid data: no thermocouple detected");
  if (out & 0x8000) return set_error("invalid data: sign bit set");
  if (!out) return set_error("invalid data: all bits zero");

  return out >> 3;
}

std::optional<TEventID> executeINIT()
{
  var_QO = CIEC_BOOL(0);

  if (!var_QI) {
    if (spi_fd > 0) close(spi_fd);
    spi_fd = -1;
    var_STATUS = CIEC_WSTRING("CLOSED");

  } else do {

      if (!initCS()) break;
      int fd = initSPI();
      if (fd <= 0) break;

      spi_fd = fd;
      var_QO = CIEC_BOOL(1);
      var_STATUS = CIEC_WSTRING("OK");
      
    } while (false);

  return scmEventINITOID;
}

std::optional<TEventID> executeREQ()
{
  if (var_QI && var_QO) do {
    if (!setCS(true)) break;
    int val = transfer(spi_fd);
    if (!val) break;
    if (!setCS(false)) break;

    var_TEMP = CIEC_WORD(val);
    var_STATUS = CIEC_WSTRING("OK");
    return scmEventCNFID;
  } while (false);

  var_QO = CIEC_BOOL(0);
  return scmEventCNFID;
}
#endif