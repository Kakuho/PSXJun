#include "memory.hpp"

namespace psxjun{

namespace memory{

// PSX BIOS

Bios::Bios(std::string file): 
  m_biosPath{std::move(file)}, 
  m_ifst{m_biosPath, std::ios::binary | std::ios::ate}{
  if(m_ifst){
    std::size_t size = m_ifst.tellg();
    m_ifst.seekg(0);
    std::uint8_t buffer[size];
    m_ifst.read(reinterpret_cast<char*>(buffer), size);
    std::copy(buffer, buffer + size, m_data.begin());
    std::cout << "SUCCESSFULLY READ BIOS" << '\n';
  }
  else{
    std::cerr << "ERROR IN READING SOURCE PATH FOR BIOS" << '\n';
  }
}

void Bios::Dump() const{
  /* performs a hex dump of the bios file stored in the class Bios */
  std::size_t i = 0;  
  std::cout << "0x" << std::setw(8) << std::setfill('0') << std::hex << i << std::setw(3) << std::setfill(' ') << "|" << std::setw(2) << ' ';
  for(std::uint8_t byte: m_data){
    std::bitset<8> bits{ byte };
    std::cout << std::setw(2) << std::setfill('0') << std::hex << bits.to_ulong(); // very slow
    i++;
    if(i % 16 == 0){
      std::cout << '\n' << "0x" << std::setw(8) << std::setfill('0') << std::hex << i << std::setw(3) << std::setfill(' ') << "|" << std::setw(2) << ' ';

    }
    else if(i % 8 == 0){
      std::cout << "\t\t";
    }
    else{
      std::cout << ' ';
    }
  }
}

// PSX RAM

// PSX ScratchPad - also ram

//---------------------------------------------------------------//

std::uint8_t Memory::GetByte(std::size_t index){
  if(index > RAM_BEGIN && index < RAM_END){
    // get memory from the ram
  }
  else if(index > SCRATCHPAD_BEGIN && index < SCRATCHPAD_END){
    // get memory from the scratchpad
  }
  else if(index > REGISTER_BEGIN && index < REGISTER_END){
    // get memory from hw registers
  }
  else if(index > RAM_MIRROR1_BEGIN && index < RAM_MIRROR1_END){
    // get memory from the ram
  }
  else if(index > RAM_MIRROR2_BEGIN && index < RAM_MIRROR2_END){
    // get memory from the ram
  }
  else if(index > BIOS_BEGIN && index < BIOS_END){
    // get memory from the bios
  }
  else{
    // throw out of memory exception
  }
}

} // namespace memory

} // namespace psxjun
