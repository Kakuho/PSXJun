#include "memory_manager.hpp"

namespace Jun{

MemoryManager::MemoryManager(PsxSystem& system)
  :
    m_system{system}
{

}

bool MemoryManager::IsAddressError(std::uint32_t address){

}
    
std::uint8_t MemoryManager::ReadByte(std::uint32_t address) const{
  if(address >= RAM_BEGIN && address <= RAM_END){
    return m_ram[address];
  }
  else if(address >= SCRATCHPAD_BEGIN && address <= SCRATCHPAD_END){
    throw std::runtime_error{"Invalid Get from ScratchPad::is not implemented"};
  }
  else if(address >= REGISTER_BEGIN && address <= REGISTER_END){
    throw std::runtime_error{"Invalid Get from HWRegisters::is not implemented"};
  }
  else if(address >= RAM_MIRROR1_BEGIN && address <= RAM_MIRROR1_END){
    // for now I assume i don't need to write cache
    std::uint32_t mask = ~(0b1111 << 28);
    return m_ram[address & mask];
  }
  else if(address >= RAM_MIRROR2_BEGIN && address <= RAM_MIRROR2_END){
    // for now I assume i don't need to write cache
    std::uint32_t mask = ~(0b1111 << 28);
    return m_ram[address & mask];
  }
  else if(address >= BIOS_BEGIN && address <= BIOS_END){
    // get memory from the bios
    std::uint32_t bios_mask = ~(0xfff << 20);
    return m_bios[address & bios_mask];
  }
  else{
    // I'm not sure what's supposed to happen here, is cop0 supposed to issue an 
    // exception/interrupt?
    throw std::runtime_error{"MemoryManager::ReadByte(addr) Out of bounds"};
  }
}

void MemoryManager::WriteByte(std::uint32_t address, std::uint8_t val){
  if(address >= RAM_BEGIN && address <= RAM_END){
    m_ram[address] = val;
  }
  else if(address >= SCRATCHPAD_BEGIN && address <= SCRATCHPAD_END){
    // get memory from the scratchpad
    throw std::runtime_error{"Invalid Write to ScratchPad::is not implemented"};
  }
  else if(address >= REGISTER_BEGIN && address <= REGISTER_END){
    // get memory from hw registers
    throw std::runtime_error{"Invalid Write to HWRegisters::is not implemented"};
  }
  else if(address >= RAM_MIRROR1_BEGIN && address <= RAM_MIRROR1_END){
    // for now I assume i don't need to write cache
    std::uint32_t mask = ~(0b1111 << 28);
    m_ram[address & mask] = val;
  }
  else if(address >= RAM_MIRROR2_BEGIN && address <= RAM_MIRROR2_END){
    // for now I assume i don't need to write cache
    std::uint32_t mask = ~(0b1111 << 28);
    m_ram[address & mask] = val;
  }
  else if(address >= BIOS_BEGIN && address <= BIOS_END){
    // get memory from the bios
    std::uint32_t bios_mask = ~(0xfff << 20);
    //std::cout << "bios map: " << (unsigned)(address & bios_mask) << '\n';
    m_bios[address & bios_mask] = val;
  }
  else{
    // I'm not sure what's supposed to happen here, is cop0 supposed to issue an 
    // exception/interrupt?
    throw std::runtime_error{"Out of bounds :: not sure what to actually put here"};
  }
}

std::uint16_t MemoryManager::ReadHalfWord(std::uint32_t address) const{
  // the system is configured for little endian
  std::uint8_t first = ReadByte(address);
  std::uint8_t second = ReadByte(address + 1); 
  std::uint16_t hword = first;
  hword = hword << 8;
  hword |= second;
  return hword;
}

void MemoryManager::WriteHalfWord(std::uint32_t address, std::uint16_t hword){
  // the system is configured for little endian
  std::uint8_t first = hword >> 8;
  std::uint8_t second = hword & 0xFF;
  WriteByte(address, first);
  WriteByte(address + 1, second);
}

std::uint32_t MemoryManager::ReadWord(std::uint32_t address) const{
  // the system is configured for little endian
  std::uint8_t first = ReadByte(address);
  std::uint8_t second = ReadByte(address + 1); 
  std::uint8_t third = ReadByte(address + 2); 
  std::uint8_t fourth = ReadByte(address + 3); 
  std::uint32_t word = first;
  word = word << 8;
  word |= second;
  word = word << 16;
  word |= third;
  word = word << 24;
  word |= fourth;
  return word;
}

void MemoryManager::WriteWord(std::uint32_t address, std::uint32_t word){
  // the system is configured for little endian
  std::uint8_t first = (word >> 24) & 0xFF;
  std::uint8_t second = (word >> 16) & 0xFF;
  std::uint8_t third = (word >> 8) & 0xFF;
  std::uint8_t fourth = word & 0xFF;
  WriteByte(address, first);
  WriteByte(address + 1, second);
  WriteByte(address + 2, third);
  WriteByte(address + 3, fourth);
}

std::uint64_t MemoryManager::ReadDoubleWord(std::uint32_t address) const{
  // the system is configured for little endian
  std::uint8_t first = ReadByte(address);
  std::uint8_t second = ReadByte(address + 1); 
  std::uint8_t third = ReadByte(address + 2); 
  std::uint8_t fourth = ReadByte(address + 3); 
  std::uint8_t fifth = ReadByte(address + 4); 
  std::uint8_t sixth = ReadByte(address + 5); 
  std::uint8_t seventh = ReadByte(address + 6); 
  std::uint8_t eighth = ReadByte(address + 7); 
  std::uint32_t dword = first;
  dword = dword << 8;
  dword |= second;
  dword = dword << 8;
  dword |= third;
  dword = dword << 8;
  dword |= fourth;
  dword = dword << 8;
  dword |= fifth;
  dword = dword << 8;
  dword |= sixth;
  dword = dword << 8;
  dword |= seventh;
  dword = dword << 8;
  dword |= eighth;
  return dword;
}
    
void MemoryManager::WriteDoubleWord(std::uint32_t address, std::uint64_t word){
  // the system is configured for little endian
  std::uint8_t first = (word >> 56) & 0xFF;
  std::uint8_t second = (word >> 48) & 0xFF;
  std::uint8_t third = (word >> 40) & 0xFF;
  std::uint8_t fourth = (word >> 32) & 0xFF;
  std::uint8_t fifth = (word >> 24) & 0xFF;
  std::uint8_t sixth = (word >> 16) & 0xFF;
  std::uint8_t seventh = (word >> 8) & 0xFF;
  std::uint8_t eighth = word & 0xFF;
  WriteByte(address, first);
  WriteByte(address + 1, second);
  WriteByte(address + 2, third);
  WriteByte(address + 3, fourth);
  WriteByte(address + 4, fifth);
  WriteByte(address + 5, sixth);
  WriteByte(address + 6, seventh);
  WriteByte(address + 7, eighth);
}

} // namespace Jun
