#include "memory_manager.hpp"
#include "system/memory_map_addresses.hpp"
#include "system/memory_region.hpp"
#include <cstdlib>

namespace Jun{

MemoryManager::MemoryManager(PsxSystem& system)
  :
    m_system{system}
{

}

std::optional<MemoryManager::ExceptionCondition> 
MemoryManager::BadAddress(std::uint32_t address) const{
  // This should be called whenever ReadByte and WriteByte is used
  if(WithinKuseg(address)){
    return std::nullopt;
  }
  else if(WithinKseg0(address)){
    if(!CpuPrivilaged()){
      return ExceptionCondition::AddressError;
    }
    else{
      return std::nullopt;
    }
  }
  else if(WithinKseg1(address)){
    if(!CpuPrivilaged()){
      return ExceptionCondition::AddressError;
    }
    else{
      return std::nullopt;
    }
  }
  else if(WithinKseg2(address)){
    if(!CpuPrivilaged()){
      return ExceptionCondition::AddressError;
    }
    else{
      return std::nullopt;
    }
  }
  return ExceptionCondition::BusError;
}

std::optional<MemoryManager::ExceptionCondition> 
MemoryManager::BadAddress(std::uint32_t address, std::uint8_t bytes) const{
  // This should be called whenever Read* and Write* is used, which requires 
  // more than one byte to be fetched
  if(WithinKuseg(address, bytes)){
    return std::nullopt;
  }
  else if(WithinKseg0(address, bytes)){
    if(!CpuPrivilaged()){
      return ExceptionCondition::AddressError;
    }
    else{
      return std::nullopt;
    }
  }
  else if(WithinKseg1(address, bytes)){
    if(!CpuPrivilaged()){
      return ExceptionCondition::AddressError;
    }
    else{
      return std::nullopt;
    }
  }
  else if(WithinKseg2(address, bytes)){
    if(!CpuPrivilaged()){
      return ExceptionCondition::AddressError;
    }
    else{
      return std::nullopt;
    }
  }
  return ExceptionCondition::BusError;
}

std::optional<MemoryManager::ExceptionCondition> 
MemoryManager::BadByte(std::uint32_t address) const{
  return BadAddress(address, 1);
}

std::optional<MemoryManager::ExceptionCondition> 
MemoryManager::BadHalfWord(std::uint32_t address) const{ 
  if(address & 1){
    return ExceptionCondition::AddressError;
  }

  return BadAddress(address, 2);
}

std::optional<MemoryManager::ExceptionCondition> 
MemoryManager::BadWord(std::uint32_t address) const{
  if(address & 2){
    return ExceptionCondition::AddressError;
  }
  return BadAddress(address, 4);
}

bool MemoryManager::WithinKuseg(std::uint32_t address) const{
  using namespace MemoryMap::Kuseg;
  return WithinRange<RAM_BEGIN, RAM_END>(address) ||
         WithinRange<EXPANSION1_BEGIN, EXPANSION1_END>(address) ||
         WithinRange<SCRATCHPAD_BEGIN, SCRATCHPAD_END>(address) ||
         WithinRange<MMIO_BEGIN, MMIO_END>(address) ||
         WithinRange<IO_EXPANSION_BEGIN, IO_EXPANSION_END>(address) ||
         WithinRange<SRAM_EXPANSION_BEGIN, SRAM_EXPANSION_END>(address) ||
         WithinRange<BIOS_BEGIN, BIOS_END>(address);
}

bool MemoryManager::WithinKseg0(std::uint32_t address) const{
  using namespace MemoryMap::Kseg0;
  return WithinRange<RAM_BEGIN, RAM_END>(address) ||
         WithinRange<EXPANSION1_BEGIN, EXPANSION1_END>(address) ||
         WithinRange<SCRATCHPAD_BEGIN, SCRATCHPAD_END>(address) ||
         WithinRange<MMIO_BEGIN, MMIO_END>(address) ||
         WithinRange<IO_EXPANSION_BEGIN, IO_EXPANSION_END>(address) ||
         WithinRange<SRAM_EXPANSION_BEGIN, SRAM_EXPANSION_END>(address) ||
         WithinRange<BIOS_BEGIN, BIOS_END>(address);
}
    
bool MemoryManager::WithinKseg1(std::uint32_t address) const{
  using namespace MemoryMap::Kseg1;
  return WithinRange<RAM_BEGIN, RAM_END>(address) ||
         WithinRange<EXPANSION1_BEGIN, EXPANSION1_END>(address) ||
         WithinRange<MMIO_BEGIN, MMIO_END>(address) ||
         WithinRange<IO_EXPANSION_BEGIN, IO_EXPANSION_END>(address) ||
         WithinRange<SRAM_EXPANSION_BEGIN, SRAM_EXPANSION_END>(address) ||
         WithinRange<BIOS_BEGIN, BIOS_END>(address);
}

bool MemoryManager::WithinKseg2(std::uint32_t address) const{
  using namespace MemoryMap::Kseg2;
  return WithinRange<CACHE_REGISTERS_BEGIN, CACHE_REGISTERS_END>(address);
}

bool MemoryManager::WithinKuseg(std::uint32_t address, std::uint8_t bytes) const{
  bool within = WithinKuseg(0);
  for(std::uint8_t i = 1; i < bytes; i++){
    within &= WithinKuseg(bytes + i);
  }
  return within;
}

bool MemoryManager::WithinKseg0(std::uint32_t address, std::uint8_t bytes) const{
  bool within = WithinKseg0(0);
  for(std::uint8_t i = 1; i < bytes; i++){
    within &= WithinKseg0(bytes + i);
  }
  return within;
}
bool MemoryManager::WithinKseg1(std::uint32_t address, std::uint8_t bytes) const{
  bool within = WithinKseg1(0);
  for(std::uint8_t i = 1; i < bytes; i++){
    within &= WithinKseg1(bytes + i);
  }
  return within;
}
bool MemoryManager::WithinKseg2(std::uint32_t address, std::uint8_t bytes) const{
  bool within = WithinKseg2(0);
  for(std::uint8_t i = 1; i < bytes; i++){
    within &= WithinKseg2(bytes + i);
  }
  return within;
}

std::uint8_t MemoryManager::ReadByte(std::uint32_t address) const{
  if(WithinKuseg(address)){
    return ReadByteFromKuseg(address);
  }
  else if(WithinKseg0(address)){
    return ReadByteFromKseg0(address);
  }
  else if(WithinKseg1(address)){
    return ReadByteFromKseg1(address);
  }
  else{
    return ReadByteFromKseg2(address);
  }
}

std::uint8_t MemoryManager::ReadByteFromKuseg(std::uint32_t address) const{
  using namespace MemoryMap::Kuseg;
  if(address >= RAM_BEGIN && address <= RAM_END){
    return m_ram[address - RAM_BEGIN];
  }
  else if(address >= EXPANSION1_BEGIN && address <= EXPANSION1_END){
    throw std::runtime_error{"Invalid Get from ScratchPad :: is not implemented"};
  }
  else if(address >= SCRATCHPAD_BEGIN && address <= SCRATCHPAD_END){
    throw std::runtime_error{"Invalid Get from ScratchPad :: is not implemented"};
  }
  else if(address >= MMIO_BEGIN && address <= MMIO_END){
    throw std::runtime_error{"Invalid Get from IO Port Registers :: is not implemented"};
  }
  else if(address >= IO_EXPANSION_BEGIN && address <= IO_EXPANSION_END){
    throw std::runtime_error{"ReadByteFromKuseg() :: "
      "Invalid Get from IO Expansion Registers :: is not implemented"};
  }
  else if(address >= SRAM_EXPANSION_BEGIN && address <= SRAM_EXPANSION_END){
    throw std::runtime_error{"Invalid Get from IO Port Registers :: is not implemented"};
  }
  else if(address >= BIOS_BEGIN && address <= BIOS_END){
    return m_bios[address - BIOS_BEGIN];
  }
  else{
    throw std::runtime_error{"MemoryManager::ReadByteFromKuseg(addr) Out of bounds"};
  }
}

std::uint8_t MemoryManager::ReadByteFromKseg0(std::uint32_t address) const{
  using namespace MemoryMap::Kseg0;
  if(address >= RAM_BEGIN && address <= RAM_END){
    return m_ram[address - RAM_BEGIN];
  }
  else if(address >= EXPANSION1_BEGIN && address <= EXPANSION1_END){
    throw std::runtime_error{"Invalid Get from ScratchPad :: is not implemented"};
  }
  else if(address >= SCRATCHPAD_BEGIN && address <= SCRATCHPAD_END){
    throw std::runtime_error{"Invalid Get from ScratchPad :: is not implemented"};
  }
  else if(address >= MMIO_BEGIN && address <= MMIO_END){
    throw std::runtime_error{"Invalid Get from IO Port Registers :: is not implemented"};
  }
  else if(address >= IO_EXPANSION_BEGIN && address <= IO_EXPANSION_END){
    throw std::runtime_error{"Invalid Get from IO Port Registers :: is not implemented"};
  }
  else if(address >= SRAM_EXPANSION_BEGIN && address <= SRAM_EXPANSION_END){
    throw std::runtime_error{"Invalid Get from IO Port Registers :: is not implemented"};
  }
  else if(address >= BIOS_BEGIN && address <= BIOS_END){
    return m_bios[address - BIOS_BEGIN];
  }
  else{
    throw std::runtime_error{"MemoryManager::ReadByteFromKseg0(addr) Out of bounds"};
  }
}

std::uint8_t MemoryManager::ReadByteFromKseg1(std::uint32_t address) const{
  // Note: Throws BusErrorException when invalid address
  using namespace MemoryMap::Kseg1;
  if(address >= RAM_BEGIN && address <= RAM_END){
    return m_ram[address - RAM_BEGIN];
  }
  else if(address >= EXPANSION1_BEGIN && address <= EXPANSION1_END){
    throw std::runtime_error{"Invalid Get from ScratchPad :: is not implemented"};
  }
  else if(address >= MMIO_BEGIN && address <= MMIO_END){
    throw std::runtime_error{"Invalid Get from IO Port Registers :: is not implemented"};
  }
  else if(address >= IO_EXPANSION_BEGIN && address <= IO_EXPANSION_END){
    throw std::runtime_error{"Invalid Get from IO Port Registers :: is not implemented"};
  }
  else if(address >= SRAM_EXPANSION_BEGIN && address <= SRAM_EXPANSION_END){
    throw std::runtime_error{"ReadByteFromKseg1() :: "
      "Invalid Get from SRAM Expansion Registers :: is not implemented"};
  }
  else if(address >= BIOS_BEGIN && address <= BIOS_END){
    return m_bios[address - BIOS_BEGIN];
  }
  else{
    throw std::runtime_error{"MemoryManager::ReadByteFromKseg1(addr) Out of bounds"};
  }
}

std::uint8_t MemoryManager::ReadByteFromKseg2(std::uint32_t address) const{
  using namespace MemoryMap::Kseg2;
  if(address >= CACHE_REGISTERS_BEGIN && address <= CACHE_REGISTERS_END){
    throw std::runtime_error{"Invalid Get from ScratchPad :: "
      "cachem control registers are not implemented"};
  }
  else{
    throw std::runtime_error{"MemoryManager::ReadByteFromKseg2(addr) Out of bounds"};
  }
}

void MemoryManager::WriteByte(std::uint32_t address, std::uint8_t val){
  if(WithinKuseg(address)){
    WriteByteToKuseg(address, val);
  }
  else if(WithinKseg0(address)){
    WriteByteToKseg0(address, val);
  }
  else if(WithinKseg1(address)){
    WriteByteToKseg1(address, val);

  }
  else{
    WriteByteToKseg2(address, val);
  }
}

void MemoryManager::WriteByteToKuseg(std::uint32_t address, std::uint8_t val){
  using namespace MemoryMap::Kuseg;
  if(address >= RAM_BEGIN && address <= RAM_END){
    m_ram[address - RAM_BEGIN] = val;
  }
  else if(address >= EXPANSION1_BEGIN && address <= EXPANSION1_END){
    throw std::runtime_error{"Invalid Get from ScratchPad :: is not implemented"};
  }
  else if(address >= SCRATCHPAD_BEGIN && address <= SCRATCHPAD_END){
    throw std::runtime_error{"Invalid Get from ScratchPad :: is not implemented"};
  }
  else if(address >= MMIO_BEGIN && address <= MMIO_END){
    m_mmio[address] = val;
  }
  else if(address >= IO_EXPANSION_BEGIN && address <= IO_EXPANSION_END){
    throw std::runtime_error{"Invalid Get from IO Port Registers :: is not implemented"};
  }
  else if(address >= SRAM_EXPANSION_BEGIN && address <= SRAM_EXPANSION_END){
    throw std::runtime_error{"Invalid Get from IO Port Registers :: is not implemented"};
  }
  else if(address >= BIOS_BEGIN && address <= BIOS_END){
    m_bios[address - BIOS_BEGIN] = val;
  }
  else{
    throw std::runtime_error{"MemoryManager::ReadByteFromKuseg(addr) Out of bounds"};
  }
}

void MemoryManager::WriteByteToKseg0(std::uint32_t address, std::uint8_t val){
  using namespace MemoryMap::Kseg0;
  if(address >= RAM_BEGIN && address <= RAM_END){
    m_ram[address - RAM_BEGIN] = val;
  }
  else if(address >= EXPANSION1_BEGIN && address <= EXPANSION1_END){
    throw std::runtime_error{"Invalid Get from ScratchPad :: is not implemented"};
  }
  else if(address >= SCRATCHPAD_BEGIN && address <= SCRATCHPAD_END){
    throw std::runtime_error{"Invalid Get from ScratchPad :: is not implemented"};
  }
  else if(address >= MMIO_BEGIN && address <= MMIO_END){
    throw std::runtime_error{"Invalid Get from IO Port Registers :: is not implemented"};
  }
  else if(address >= IO_EXPANSION_BEGIN && address <= IO_EXPANSION_END){
    throw std::runtime_error{"Invalid Get from IO Port Registers :: is not implemented"};
  }
  else if(address >= SRAM_EXPANSION_BEGIN && address <= SRAM_EXPANSION_END){
    throw std::runtime_error{"Invalid Get from IO Port Registers :: is not implemented"};
  }
  else if(address >= BIOS_BEGIN && address <= BIOS_END){
    m_bios[address - BIOS_BEGIN] = val;
  }
  else{
    throw std::runtime_error{"MemoryManager::ReadByteFromKuseg(addr) Out of bounds"};
  }
}

void MemoryManager::WriteByteToKseg1(std::uint32_t address, std::uint8_t val){
  using namespace MemoryMap::Kseg1;
  if(address >= RAM_BEGIN && address <= RAM_END){
    m_ram[address - RAM_BEGIN] = val;
  }
  else if(address >= EXPANSION1_BEGIN && address <= EXPANSION1_END){
    throw std::runtime_error{"Invalid Get from ScratchPad :: is not implemented"};
  }
  else if(address >= MMIO_BEGIN && address <= MMIO_END){
    throw std::runtime_error{"Invalid Get from IO Port Registers :: is not implemented"};
  }
  else if(address >= IO_EXPANSION_BEGIN && address <= IO_EXPANSION_END){
    throw std::runtime_error{"Invalid Get from IO Port Registers :: is not implemented"};
  }
  else if(address >= SRAM_EXPANSION_BEGIN && address <= SRAM_EXPANSION_END){
    throw std::runtime_error{"Invalid Get from IO Port Registers :: is not implemented"};
  }
  else if(address >= BIOS_BEGIN && address <= BIOS_END){
    m_bios[address - BIOS_BEGIN] = val;
  }
  else{
    throw std::runtime_error{"MemoryManager::ReadByteFromKuseg(addr) Out of bounds"};
  }
}

void MemoryManager::WriteByteToKseg2(std::uint32_t address, std::uint8_t val){
  using namespace MemoryMap::Kseg2;
  if(address >= CACHE_REGISTERS_BEGIN && address <= CACHE_REGISTERS_END){
    throw std::runtime_error{"Invalid Get from ScratchPad :: "
      "cachem control registers are not implemented"};
  }
  else{
    throw std::runtime_error{"MemoryManager::ReadByteFromKseg2(addr) Out of bounds"};
  }
}

std::uint16_t MemoryManager::ReadHalfWord(std::uint32_t address) const{
  // the system is configured for little endian
  std::uint8_t first = ReadByte(address);
  std::uint8_t second = ReadByte(address + 1); 
  std::uint16_t hword = second;
  hword = hword << 8;
  hword |= first;
  return hword;
}

void MemoryManager::WriteHalfWord(std::uint32_t address, std::uint16_t hword){
  // the system is configured for little endian
  std::uint8_t first = hword >> 8;
  std::uint8_t second = hword & 0xFF;
  WriteByte(address, second);
  WriteByte(address + 1, first);
}

std::uint32_t MemoryManager::ReadWord(std::uint32_t address) const{
  // the system is configured for little endian
  std::uint8_t first = ReadByte(address);
  std::uint8_t second = ReadByte(address + 1); 
  std::uint8_t third = ReadByte(address + 2); 
  std::uint8_t fourth = ReadByte(address + 3); 
  std::uint32_t word = fourth;
  word = word << 8;
  word |= third;
  word = word << 8;
  word |= second;
  word = word << 8;
  word |= first;
  return word;
}

void MemoryManager::WriteWord(std::uint32_t address, std::uint32_t word){
  // the system is configured for little endian
  std::uint8_t first = (word >> 24) & 0xFF;
  std::uint8_t second = (word >> 16) & 0xFF;
  std::uint8_t third = (word >> 8) & 0xFF;
  std::uint8_t fourth = word & 0xFF;
  WriteByte(address, fourth);
  WriteByte(address + 1, third);
  WriteByte(address + 2, second);
  WriteByte(address + 3, first);
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
  std::uint32_t dword = eighth;
  dword = dword << 8;
  dword |= seventh;
  dword = dword << 8;
  dword |= sixth;
  dword = dword << 8;
  dword |= fifth;
  dword = dword << 8;
  dword |= fourth;
  dword = dword << 8;
  dword |= third;
  dword = dword << 8;
  dword |= second;
  dword = dword << 8;
  dword |= first;
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
  WriteByte(address, eighth);
  WriteByte(address + 1, seventh);
  WriteByte(address + 2, sixth);
  WriteByte(address + 3, fifth);
  WriteByte(address + 4, fourth);
  WriteByte(address + 5, third);
  WriteByte(address + 6, second);
  WriteByte(address + 7, first);
}

} // namespace Jun
