#pragma once

// Encapsulation of external memories
//
// https://problemkaputt.de/psx-spx.htm#memorymap

#include <string>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <utility>

#include "common/memory_base.hpp"

namespace Jun{

static inline constexpr std::size_t BIOS_SIZE = 512*1024;
static inline constexpr std::size_t PRAM_SIZE = 1.9 * 1048576;
static inline constexpr std::size_t SCRATCHPAD_SIZE = 1000;

class Bios: public MemoryBase<BIOS_SIZE>{
  public:
    Bios() = default;
    void Load(std::string&& biosfile);
    const std::string& BiosPath() const{ return m_biosFile;}

    std::uint8_t Get(std::size_t index) const{return m_data[index];}

  private:
    std::string m_biosFile;
};

class PhysicalRam: public MemoryBase<PRAM_SIZE>{
  public:
    PhysicalRam() = default;
    std::uint8_t Get(std::size_t index) const{return m_data[index];}
};

class Scratchpad: public MemoryBase<SCRATCHPAD_SIZE>{

};

} // namespace Jun
