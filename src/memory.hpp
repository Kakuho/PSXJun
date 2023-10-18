#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>
#include <array>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <bitset>


//---------------------------------------------------------------//

// Memory subsystems
// Design: each memory system should share a common interface

class Bios{
  static inline constexpr unsigned BIOS_SIZE = 512*1024; // Bios is 512KB 
                                                          // https://problemkaputt.de/psx-spx.htm#memorymap
  std::array<std::uint8_t, BIOS_SIZE> m_data;
  std::string m_biosPath;
  std::ifstream m_ifst;
  
  public:
    Bios() = default;
    Bios(std::string file);
    void Dump() const; 
};

class Ram{
  static inline constexpr unsigned RAM_SIZE = 1.9 * 1048576;
  std::array<std::uint8_t, RAM_SIZE> m_data;

  public:
    Ram() = default;
    void Dump();
};

class ScratchPad{
  const static unsigned ScratchPad_SIZE = 1024; // Scratchpad is 1024 bytes
  std::array<std::uint8_t, ScratchPad_SIZE> m_data;

  public:
    ScratchPad() = default;
    void Dump() const; 
};

//---------------------------------------------------------------//

// overreaching memory class for the psx system

class Memory{
    Bios& bios;
    ScratchPad& spad;

  public:
    Memory();

    std::uint8_t GetByte(std::size_t index);

  private:
    // useful for the memory mapping
    static inline constexpr unsigned KERNEL_BEGIN = 0;
    static inline constexpr unsigned KERNEL_END   =  0x0000'FFFF;

    static inline constexpr unsigned RAM_BEGIN  = 0x0001'0000;
    static inline constexpr unsigned RAM_END    = 0x001f'ffff;

    static inline constexpr unsigned SCRATCHPAD_BEGIN   = 0x1f80'0000;
    static inline constexpr unsigned SCRATCHPAD_END     = 0x1f80'03ff;

    static inline constexpr unsigned REGISTER_BEGIN = 0x1f80'1000;
    static inline constexpr unsigned REGISTER_END   = 0x1f80'2fff;

    static inline constexpr unsigned RAM_MIRROR1_BEGIN  = 0x8000'0000;
    static inline constexpr unsigned RAM_MIRROR1_END    = 0x801f'ffff;

    static inline constexpr unsigned RAM_MIRROR2_BEGIN  = 0xa000'0000;
    static inline constexpr unsigned RAM_MIRROR2_END    = 0xa01f'ffff;

    static inline constexpr unsigned BIOS_BEGIN  = 0xbfc0'0000;
    static inline constexpr unsigned BIOS_END    = 0xbfc7'ffff;
};

#endif
