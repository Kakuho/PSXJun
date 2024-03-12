#include "psx.hpp"

namespace psxjun{

namespace system{

Psx::Psx():
  m_cpu{ std::make_unique<CPU>() },
  m_ram{ std::make_unique<Ram>() },
  m_bios{ std::make_unique<Bios>()},
  m_scratchpad{ std::make_unique<ScratchPad>() },
  m_memory_controller{ std::make_unique<MemoryController>() },
  m_bus{ 
    std::make_unique<SystemBus>(
      *m_cpu,
      *m_bios,
      *m_ram,
      *m_scratchpad,
      *m_memory_controller
    ) 
  }
{
}

Psx::Psx(std::string&& biosFilePath):
  m_cpu{ std::make_unique<CPU>() },
  m_ram{ std::make_unique<Ram>() },
  m_bios{ std::make_unique<Bios>(biosFilePath)},
  m_scratchpad{ std::make_unique<ScratchPad>() },
  m_memory_controller{ std::make_unique<MemoryController>() },
  m_bus{ 
    std::make_unique<SystemBus>(
      *m_cpu,
      *m_bios,
      *m_ram,
      *m_scratchpad,
      *m_memory_controller
    ) 
  }
{
  m_cpu->HookSystemBus(*m_bus);
}

void Psx::run(){
  std::cout << "RUNNING!" << '\n';
}

void Psx::run(std::size_t ticks){
  for(int i = 0; i < ticks; i++){
    m_cpu->Tick();
  }
}

} // system

} // psxjun
