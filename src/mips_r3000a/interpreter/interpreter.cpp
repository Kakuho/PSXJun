#pragma once

#include "mips_r3000a/exception_vectors.hpp"
#include "instruction_tables.hpp"
#include "system/psx_system.hpp"

namespace Jun{

Interpreter::Interpreter(MipsState& state, PsxSystem& system)
  : 
    m_state{state}, 
    m_system{system},
    m_currentInstruction{0},
    m_lastInstruction{0},
    m_delaySlot{0, 0, false},
    m_lastPc{0},
    m_lastVal{0}
{
  PopulateRegisterInterpreterTable(RegisterFunctionTable());
  PopulateImmediateInterpreterTable(ImmediateFunctionTable());
}

void Interpreter::Reset(){
  m_state.PC() = ExceptionVectors::Reset;
}

void Interpreter::Tick(){
  /*
  if(ExceptionPending()){
    // handle exception
  }
  */
  std::uint8_t nextOpcode = m_system.GetMemmap().ReadByte(m_state.PC());
  if(nextOpcode == 0){
    RegisterInstruction instruction = m_system.GetMemmap().ReadWord(m_state.PC());
    RegisterFunctionTable().at(instruction.shamt)(*this, instruction);
  }
  else if(JumpFunctionTable().contains(nextOpcode)){
    JumpInstruction instruction = m_system.GetMemmap().ReadWord(m_state.PC());
    JumpFunctionTable().at(nextOpcode)(*this, instruction);
  }
  else{
    ImmediateInstruction instruction = m_system.GetMemmap().ReadWord(m_state.PC());
    ImmediateFunctionTable().at(nextOpcode)(*this, instruction);
  }
}

void Interpreter::Run(){
  while(true){
    Tick();
  }
}

void Interpreter::SetActiveDelaySlot(std::uint8_t regIndex, std::uint32_t value){
  m_delaySlot.regIndex = regIndex;
  m_delaySlot.prevValue = value;
  m_delaySlot.active = true;
}

void Interpreter::TriggerInternalException(){

}

} // namespace Jun
