#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>

class I2CDevice final {
public:
        I2CDevice(int bus_id, uint8_t addr)
                : m_bus(find_or_create_bus(bus_id))
                , m_addr(addr)
        {}
        I2CDevice() : I2CDevice(-1, 0) {}

        int write8(uint8_t reg, uint8_t byte);
        int write16(uint8_t reg, uint16_t value);
        uint8_t read8(uint8_t reg);
        uint16_t read16(uint8_t reg);

private:
        struct Bus final {
                Bus(const Bus &) = delete;
                Bus &operator=(const Bus &) = delete;
                Bus(Bus &&) = default;
                Bus &operator=(Bus &&) = default;
                ~Bus();
                Bus(int bus_id = -1);
                int m_fd = -1;
        };

        static Bus* find_or_create_bus(int bus_id);
        static std::unordered_map<int, Bus> busses;

        Bus *m_bus;
        uint8_t m_addr;
};
