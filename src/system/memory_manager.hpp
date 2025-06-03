#pragma once

// Memory Manager represents all addressable memories within the system required for psx emulation, 
// containing both ram and mmio.
//
// In effect, it represents the memory mapping of the PSX system.

#include <cstdint>
#include <variant>
#include <optional>
#include <expected>

#include "memories.hpp"
#include "memory_map_addresses.hpp"
#include "mmio.hpp"
#include "memory_region.hpp"

namespace Jun{
  class PsxSystem;
}

namespace Jun{

class MemoryManager{
  public:
    enum class ExceptionCondition{
      BusError,
      AddressError
    };

  public:
    MemoryManager(PsxSystem& system);

    void LoadBios(std::string&& file){ m_bios.Load(std::move(file));}
    const std::string& BiosPath() const{ return m_bios.BiosPath();}

    bool CpuPrivilaged() const{ return true;}

    std::optional<ExceptionCondition> BadAddress(std::uint32_t address) const;
    std::optional<ExceptionCondition> BadAddress(std::uint32_t address, 
                                                 std::uint8_t bytes
                                                ) const;
    std::optional<ExceptionCondition> BadByte(std::uint32_t address) const;
    std::optional<ExceptionCondition> BadHalfWord(std::uint32_t address) const;
    std::optional<ExceptionCondition> BadWord(std::uint32_t address) const;

    std::uint8_t ReadByte(std::uint32_t address) const;
    void WriteByte(std::uint32_t address, std::uint8_t val);

    std::uint16_t ReadHalfWord(std::uint32_t address) const;
    void WriteHalfWord(std::uint32_t address, std::uint16_t val);

    std::uint32_t ReadWord(std::uint32_t address) const;
    void WriteWord(std::uint32_t address, std::uint32_t val);

    std::uint64_t ReadDoubleWord(std::uint32_t address) const;
    void WriteDoubleWord(std::uint32_t address, std::uint64_t val);

  private:
    bool WithinKuseg(std::uint32_t address) const;
    bool WithinKseg0(std::uint32_t address) const;
    bool WithinKseg1(std::uint32_t address) const;
    bool WithinKseg2(std::uint32_t address) const;

    bool WithinKuseg(std::uint32_t address, std::uint8_t bytes) const;
    bool WithinKseg0(std::uint32_t address, std::uint8_t bytes) const;
    bool WithinKseg1(std::uint32_t address, std::uint8_t bytes) const;
    bool WithinKseg2(std::uint32_t address, std::uint8_t bytes) const;

    std::uint8_t ReadByteFromKuseg(std::uint32_t address) const;
    std::uint8_t ReadByteFromKseg0(std::uint32_t address) const;
    std::uint8_t ReadByteFromKseg1(std::uint32_t address) const;
    std::uint8_t ReadByteFromKseg2(std::uint32_t address) const;

    void WriteByteToKuseg(std::uint32_t address, std::uint8_t val);
    void WriteByteToKseg0(std::uint32_t address, std::uint8_t val);
    void WriteByteToKseg1(std::uint32_t address, std::uint8_t val);
    void WriteByteToKseg2(std::uint32_t address, std::uint8_t val);

  private:
    Bios m_bios;
    PhysicalRam m_ram;
    MemoryMapIO m_mmio;
    PsxSystem& m_system;
};

} // namespace Jun
