#include "psx_system.hpp"

namespace Jun{

PsxSystem::PsxSystem()
  :
    m_cpu{*this},
    m_memmap{*this}
{
}
    
void PsxSystem::Tick(){ 
  m_cpu.Tick();
  std::cout << "PSX Ticked :: New PC = " << GetCpu().State().PC() << '\n';
}

void PsxSystem::Run(){
  std::cout << "RUNNING!" << '\n';
  while(true) m_cpu.Tick();
}

void PsxSystem::Run(std::size_t ticks){
  for(int i = 0; i < ticks; i++){
    m_cpu.Tick();
  }
}

} // namespace Jun
