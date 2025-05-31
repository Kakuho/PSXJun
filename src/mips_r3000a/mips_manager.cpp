#pragma once

#include "mips_manager.hpp"
#include "mips_r3000a/exception_vectors.hpp"
#include "system/psx_system.hpp"

namespace Jun{

MipsManager::MipsManager(PsxSystem& system)
  : 
    m_system{system},
    m_interpreter{m_state, m_system}
{

}

void MipsManager::Tick(){
  m_interpreter.Tick();
}

void MipsManager::Run(){
  while(true){
    Tick();
  }
}

void MipsManager::HandleException(){
  m_state.PC() = ExceptionVectors::General;
}

} // namespace Jun
