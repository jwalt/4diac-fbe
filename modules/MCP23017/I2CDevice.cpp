#include "I2CDevice.h"
extern "C" {
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <asm/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
}

#include <string>

using namespace std;

unordered_map<int, I2CDevice::Bus> I2CDevice::busses;

I2CDevice::Bus::~Bus() { close(m_fd); };
I2CDevice::Bus::Bus(int bus_id)
        : m_fd(bus_id < 0? -1 : open(("/dev/i2c-"+to_string(bus_id)).c_str(), O_RDWR))
{}

I2CDevice::Bus *I2CDevice::find_or_create_bus(int bus_id) {
        if (busses.find(bus_id) == busses.end()) busses[bus_id] = Bus(bus_id);
        return &busses[bus_id];
}

static int smbus_access(int fd, uint8_t addr, bool write, uint8_t reg, unsigned size, i2c_smbus_data *value)
{
        ioctl(fd, I2C_SLAVE, addr);
        i2c_smbus_ioctl_data req;
        req.read_write = write?I2C_SMBUS_WRITE:I2C_SMBUS_READ;
        req.command = reg;
        req.size = size;
        req.data = value;
        return ioctl(fd, I2C_SMBUS, &req);
}

uint8_t I2CDevice::read8(uint8_t reg) {
        i2c_smbus_data data;
        smbus_access(m_bus->m_fd, m_addr, false, reg, I2C_SMBUS_BYTE_DATA, &data);
        return data.byte;
}

uint16_t I2CDevice::read16(uint8_t reg) {
        i2c_smbus_data data;
        smbus_access(m_bus->m_fd, m_addr, false, reg, I2C_SMBUS_WORD_DATA, &data);
        return data.word;
}

int I2CDevice::write8(uint8_t reg, uint8_t val) {
        i2c_smbus_data data;
        data.byte = val;
        return smbus_access(m_bus->m_fd, m_addr, false, reg, I2C_SMBUS_BYTE_DATA, &data);
}

int I2CDevice::write16(uint8_t reg, uint16_t val) {
        i2c_smbus_data data;
        data.word = val;
        return smbus_access(m_bus->m_fd, m_addr, false, reg, I2C_SMBUS_WORD_DATA, &data);
}
