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
#include <stdexcept>

#include "memory_mapping.hpp"

namespace psxjun{

namespace memory{

static inline constexpr unsigned BIOS_SIZE = 512*1024; // Bios is 512KB 
static inline constexpr unsigned RAM_SIZE = 1.9 * 1048576;
const static unsigned ScratchPad_SIZE = 1024; // Scratchpad is 1024 bytes

// Memory subsystems

// each memory system should share a common interface
template<std::size_t capacity>
class ContiguousMemory{
  public:
    std::uint8_t& operator[](std::size_t index){ return m_data[index]; }
    const std::uint8_t& operator[](std::size_t index) const{ return m_data[index]; }
  protected:
    std::array<std::uint8_t, capacity> m_data{};
};

// https://problemkaputt.de/psx-spx.htm#memorymap
class Bios: public ContiguousMemory<BIOS_SIZE>{
  std::string m_biosPath;
  std::ifstream m_ifst;
  
  public:
    Bios() = default;
    Bios(std::string file);
    void Dump() const; 
    std::uint8_t Get(std::size_t index){return m_data[index];}
};

// Physical RAM
class Ram: public ContiguousMemory<RAM_SIZE>{
  public:
    Ram() = default;
    void Dump() const;
};

// Cache
class ScratchPad: public ContiguousMemory<ScratchPad_SIZE>{
  public:
    ScratchPad() = default;
    void Dump() const; 
};

//---------------------------------------------------------------//

// overreaching memory class for the psx system

class Memory{
    Ram& m_ram;
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
