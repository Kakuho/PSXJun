#ifndef MEMORY_CONTROLLER_HPP
#define MEMORY_CONTROLLER_HPP

#include <cstdint>
#include <unordered_map>
#include <string>

namespace psxjun{

namespace system{

struct MemoryControllerRegister{
  std::string name;
  std::uint32_t value;
};

// memory controller contains 32-bit registers, initialised by the bios
struct MemoryController{

  std::uint32_t m_biosrom_data_size;
  std::uint32_t m_ram_size;
  std::unordered_map<std::uint32_t, MemoryControllerRegister> m_lut;
  MemoryController(){
    m_lut.insert({0x1f801000, MemoryControllerRegister{"Expansion 1 Base addr", 0}});
    m_lut.insert({0x1f801004, MemoryControllerRegister{"Expansion 2 Base addr", 0}});
    m_lut.insert({0x1f801008, MemoryControllerRegister{"Expansion 1 Delay/Size", 0}});
    m_lut.insert({0x1F80100C, MemoryControllerRegister{"Expansion 3 Delay/Size", 0}}); 
    m_lut.insert({0x1F801010, MemoryControllerRegister{"BIOS ROM Delay/Size", 0}}); 
    m_lut.insert({0x1F801014, MemoryControllerRegister{"SPU Delay/Size", 0}}); 
    m_lut.insert({0x1F801018, MemoryControllerRegister{"CDROM Delay/Size", 0}}); 
    m_lut.insert({0x1F80101C, MemoryControllerRegister{"Expansion 2 Delay/Size", 0}}); 
    m_lut.insert({0x1F801020, MemoryControllerRegister{"COM_DELAY / Common Delay", 0}}); 
    m_lut.insert({0x1F801060, MemoryControllerRegister{"RAM_SIZE", 0}}); 
    m_lut.insert({0xFFFE0130, MemoryControllerRegister{"BIU_CONFIG", 0}}); 
  }

  std::uint32_t& operator[](std::uint32_t index){
    return m_lut[index].value;
  }

  bool Contains(std::size_t index) const{
    if(m_lut.contains(index)) return true;
    else return false;
  }

};

} // namespace system

} // namespace psxjun

#endif
