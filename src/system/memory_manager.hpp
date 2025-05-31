#pragma once

// Memory Manager represents all addressable memories within the system required for psx emulation, 
// containing both ram and mmio.
//
// In effect, it represents the memory mapping of the PSX system.

#include <cstdint>

#include "memories.hpp"

namespace Jun{
  class PsxSystem;
}

namespace Jun{

class MemoryManager{
  // memory map constants
  static inline constexpr std::uint32_t RAM_BEGIN  = 0x0000'0000;
  static inline constexpr std::uint32_t RAM_END    = 0x001f'ffff;

  static inline constexpr std::uint32_t SCRATCHPAD_BEGIN   = 0x1f80'0000;
  static inline constexpr std::uint32_t SCRATCHPAD_END     = 0x1f80'03ff;

  static inline constexpr std::uint32_t REGISTER_BEGIN = 0x1f80'1000;
  static inline constexpr std::uint32_t REGISTER_END   = 0x1f80'2fff;

  static inline constexpr std::uint32_t RAM_MIRROR1_BEGIN  = 0x8000'0000;
  static inline constexpr std::uint32_t RAM_MIRROR1_END    = 0x801f'ffff;

  static inline constexpr std::uint32_t RAM_MIRROR2_BEGIN  = 0xa000'0000;
  static inline constexpr std::uint32_t RAM_MIRROR2_END    = 0xa01f'ffff;

  static inline constexpr std::uint32_t BIOS_BEGIN  = 0xbfc0'0000;
  static inline constexpr std::uint32_t BIOS_END    = 0xbfc7'ffff;

  public:
    MemoryManager(PsxSystem& system);

    void LoadBios(std::string&& file){ m_bios.Load(std::move(file));}

    bool IsAddressError(std::uint32_t address);

    std::uint8_t ReadByte(std::uint32_t address) const;
    void WriteByte(std::uint32_t address, std::uint8_t val);

    std::uint16_t ReadHalfWord(std::uint32_t address) const;
    void WriteHalfWord(std::uint32_t address, std::uint16_t val);

    std::uint32_t ReadWord(std::uint32_t address) const;
    void WriteWord(std::uint32_t address, std::uint32_t val);

    std::uint64_t ReadDoubleWord(std::uint32_t address) const;
    void WriteDoubleWord(std::uint32_t address, std::uint64_t val);

  private:
    Bios m_bios;
    PhysicalRam m_ram;
    PsxSystem& m_system;
};

} // namespace Jun
