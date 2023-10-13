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

// Design: each memory system should share a common interface

class Bios{
  const static unsigned BIOS_SIZE = 512*1024; // Bios is 512KB 
                                              // https://problemkaputt.de/psx-spx.htm#memorymap
  std::array<std::uint8_t, BIOS_SIZE> m_data;
  std::string m_biosPath;
  std::ifstream m_ifst;
  
  public:
    Bios() = default;
    Bios(std::string file);

    void Dump() const; 
};


class Memory{
  public:

  private:
};

#endif
