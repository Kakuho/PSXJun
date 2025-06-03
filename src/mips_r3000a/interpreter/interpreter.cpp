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
  Reset();
}

void Interpreter::Reset(){
  m_state.PC() = ExceptionVectors::Reset;
}
    

std::uint8_t Interpreter::NextOpcode() const{
  std::uint32_t instruction = m_system.GetMemmap().ReadWord(m_state.PC());
  std::uint8_t nextOpcode = (instruction & 0xFC000000) >> 26;
  return nextOpcode;
}

std::uint32_t Interpreter::NextInstructionHex() const{
  std::uint32_t instruction = m_system.GetMemmap().ReadWord(m_state.PC());
  return instruction;
}

InstructionVariant Interpreter::CurrentInstruction() const{
  std::variant<RegisterInstruction, ImmediateInstruction, JumpInstruction> instruction;
  std::uint8_t nextOpcode = m_system.GetMemmap().ReadByte(m_state.PC());
  if(nextOpcode == 0){
    instruction = RegisterInstruction{m_system.GetMemmap().ReadWord(m_state.PC())};
  }
  else if(nextOpcode == 0x01){
    // Is a branch instruction, branches are immediate format, but all of them 
    // has a leading opcode of 000001, and the secondary opcode (rt) determines 
    // the actual branch
    instruction = ImmediateInstruction{m_system.GetMemmap().ReadWord(m_state.PC())};
  }
  else if(JumpFunctionTable().contains(nextOpcode)){
    instruction = JumpInstruction{m_system.GetMemmap().ReadWord(m_state.PC())};
  }
  else{
    instruction = ImmediateInstruction{m_system.GetMemmap().ReadWord(m_state.PC())};
  }
  return instruction;
}

void Interpreter::Tick(){
  /*
  if(ExceptionPending()){
    // handle exception
  }
  */
  if(auto isInvalid = m_system.GetMemmap().BadAddress(m_state.PC(), 32); isInvalid){
    switch(isInvalid.value()){
      case MemoryManager::ExceptionCondition::BusError:
        // raise bus error
        return;
      case MemoryManager::ExceptionCondition::AddressError:
        // raise address error
        return;
      default:
        throw std::invalid_argument{"Interpreter::Tick() "
          "Recieved an unexpected exception error"
        };
    }
  }
  else{
    std::uint8_t nextOpcode = NextOpcode();
    if(nextOpcode == 0){
      RegisterInstruction instruction = m_system.GetMemmap().ReadWord(m_state.PC());
      RegisterFunctionTable().at(instruction.shamt)(*this, instruction);
    }
    else if(nextOpcode == 0x01){
      throw std::invalid_argument{"Interpreter::Tick() "
        "nextOpcode == 0x01 :: bxxz instructions are not implemented yet"
      };
    }
    else if(JumpFunctionTable().contains(nextOpcode)){
      JumpInstruction instruction = m_system.GetMemmap().ReadWord(m_state.PC());
      JumpFunctionTable().at(nextOpcode)(*this, instruction);
    }
    else{
      ImmediateInstruction instruction = m_system.GetMemmap().ReadWord(m_state.PC());
      ImmediateFunctionTable().at(nextOpcode)(*this, instruction);
    }
    State().Cycles()++;
    State().PC() += 4;
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
