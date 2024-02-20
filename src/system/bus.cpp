#include "bus.hpp"

namespace psxjun{

namespace system{

SystemBus::SystemBus(
    processor::CPU& cpu, 
    memory::Bios& bios, 
    memory::Ram& ram, 
    memory::ScratchPad& scratchpad
    ):
  m_cpu{cpu},
  m_bios{bios},
  m_ram{ram},
  m_scratchpad{scratchpad} {}

std::uint8_t SystemBus::GetByte(std::size_t index) const{
  using namespace memory;
  if(index >= RAM_BEGIN && index <= RAM_END){
    return m_ram[index];
  }
  else if(index >= SCRATCHPAD_BEGIN && index <= SCRATCHPAD_END){
    // get memory from the scratchpad
    throw std::runtime_error{"Invalid Get from ScratchPad::is not implemented"};
  }
  else if(index >= REGISTER_BEGIN && index <= REGISTER_END){
    // get memory from hw registers
    throw std::runtime_error{"Invalid Get from HWRegisters::is not implemented"};
  }
  else if(index >= RAM_MIRROR1_BEGIN && index <= RAM_MIRROR1_END){
    // for now I assume i don't need to write cache
    std::uint32_t mask = ~(0b1111 << 28);
    return m_ram[index & mask];
  }
  else if(index >= RAM_MIRROR2_BEGIN && index <= RAM_MIRROR2_END){
    // for now I assume i don't need to write cache
    std::uint32_t mask = ~(0b1111 << 28);
    return m_ram[index & mask];
  }
  else if(index >= BIOS_BEGIN && index <= BIOS_END){
    // get memory from the bios
    std::uint32_t bios_mask = ~(0xfff << 20);
    //std::cout << "bios map: " << (unsigned)(index & bios_mask) << '\n';
    return m_bios[index & bios_mask];
  }
  else{
    // I'm not sure what's supposed to happen here, is cop0 supposed to issue an 
    // exception/interrupt?
    throw std::runtime_error{"Out of bounds :: not sure what to actually put here"};
  }
}

std::uint32_t SystemBus::GetWord(std::size_t index) const{
  //std::cout << std::hex << index << '\n';
  // the system is configured for little endian
  std::uint8_t first = GetByte(index);
  std::uint8_t second = GetByte(index + 1); 
  std::uint8_t third = GetByte(index + 2); 
  std::uint8_t fourth = GetByte(index + 3); 
  std::uint32_t word = 0;
  word |= first;
  word = word << 8;
  word |= second;
  word = word << 16;
  word |= third;
  word = word << 24;
  word |= fourth;
  return word;
}

} // namespace system

} // namespace psxjun
