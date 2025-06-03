#include "mmio.hpp"

namespace Jun{

MemoryMapIO::MemoryMapIO(){
  PopulateMemoryController();
}

void MemoryMapIO::PopulateMemoryController(){
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

}
