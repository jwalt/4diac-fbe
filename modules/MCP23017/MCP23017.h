#ifdef FBT_INCLUDES
#include "I2CDevice.h"
#include <optional>
#else

I2CDevice m_dev;

enum {
  IODIRA = 0,
  IODIRB = 1,
  GPIOA = 18,
  GPIOB = 19
};

std::optional<TEventID> executeINIT()
{
  var_QO = CIEC_BOOL(0);

  if (!var_QI) {
    // nothing
  } else do {
    m_dev = I2CDevice(uint16_t(var_BUS_NUM), uint8_t(var_I2C_ADDR));
    m_dev.write8(IODIRA, var_OE_A^0xff);
    m_dev.write8(IODIRB, var_OE_B^0xff);
    var_QO = CIEC_BOOL(1);
  } while (false);

  return scmEventINITOID;
}

std::optional<TEventID> executeREQ_A()
{
  if (var_QI && var_QO) do {
      if (var_QI) {
        if (var_OE_A) m_dev.write8(GPIOA, var_SD_A & var_OE_A);
        var_RD_A = CIEC_BYTE(m_dev.read8(GPIOA));
      }
      return scmEventCNF_AID;
  } while (false);

  var_QO = CIEC_BOOL(0);
  return scmEventCNF_AID;
}

std::optional<TEventID> executeREQ_B()
{
  if (var_QI && var_QO) do {
      if (var_QI) {
        if (var_OE_B) m_dev.write8(GPIOA, var_SD_B & var_OE_B);
        var_RD_B = CIEC_BYTE(m_dev.read8(GPIOB));
      }
      return scmEventCNF_BID;
  } while (false);

  var_QO = CIEC_BOOL(0);
  return scmEventCNF_BID;
}


#endif
