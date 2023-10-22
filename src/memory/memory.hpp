#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "./../system/bus.hpp"

#include <cstdint>
#include <array>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <bitset>

namespace psxjun{

namespace memory{

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
    std::uint16_t GetHalfWord(std::size_t index);
    std::uint32_t GetWord(std::size_t index);

  private:
};

} // namespace memory

} // namespace psxjun

#endif
