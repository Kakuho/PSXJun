#include "psx.hpp"
#include <memory>

Psx::Psx():
  m_cpu{ std::make_unique<CPU>() },
  m_ram{ std::make_unique<Ram>() },
  m_bios{ std::make_unique<Bios>()},
  m_scratchpad{ std::make_unique<ScratchPad>() },
  m_bus{ std::make_unique<Bus>(
      m_cpu.get(),
      m_bios.get(),
      m_ram.get(),
      m_scratchpad.get()
      ) }
{

}

void Psx::run(){
  std::cout << "RUNNING!" << '\n';
}
