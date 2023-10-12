#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <array>
#include <cstdint>

// Design: each mmeory peripheral should share a common interface

class Bios{
  const static unsigned BIOS_SIZE = 512*1000; // Bios is 512KB https://problemkaputt.de/psx-spx.htm#memorymap
  std::array<std::uint8_t, BIOS_SIZE> m_data;
  
  public:
    Bios() = default;
}


class Memory{
  std::array<
  public:

  private:
}

#endif
