#pragma once

#include <cstdint>
#include <array>
#include <ostream>
#include <iomanip>
#include <bitset>

namespace Jun{

template<std::size_t capacity>
class MemoryBase{
  public:
    void Dump(std::ostream& ost);
    std::uint8_t& operator[](std::size_t index){ return m_data[index]; }
    const std::uint8_t& operator[](std::size_t index) const{ return m_data[index]; }
  protected:
    std::array<std::uint8_t, capacity> m_data;
};

// Impl

template<std::size_t N>
void MemoryBase<N>::Dump(std::ostream& ost){
    /* performs a hex dump of the bios file stored in the class Bios */
  std::size_t i = 0;
  ost << "0x" << std::setw(8) << std::setfill('0')
            << std::hex << i << std::setw(3) << std::setfill(' ') << "|"
            << std::setw(2) << ' ';
  for(std::uint8_t byte: m_data){
    std::bitset<8> bits{ byte };
    ost << std::setw(2) << std::setfill('0') << std::hex << bits.to_ulong(); 
    // very slow
    i++;
    if(i % 16 == 0){
      ost << '\n' << "0x" << std::setw(8) << std::setfill('0')
                << std::hex << i << std::setw(3) << std::setfill(' ') << "|"
                << std::setw(2) << ' ';
    }
    else if(i % 8 == 0){
      ost << "\t\t";
    }
    else{
      ost << ' ';
    }
  }
}

} // namespace Jun
