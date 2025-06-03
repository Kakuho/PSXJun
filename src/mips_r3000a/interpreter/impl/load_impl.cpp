//  Implementation of the load opcodes of mips_r3000
//
//  Load Hazards:
//    * Trigger Address Error Exception if memory is not aligned
//    * Trigger Bus Error Exception if the memory address is invalid
//    * Loads will be delayed and the register wont be updated until the instruction after next
//        (lwl and lwr are exempt)

#include <cstdint>

#include "mips_r3000a/interpreter/interpreter.hpp"
#include "common/integer_extension.hpp"
#include "common/alignment.hpp"
#include "system/psx_system.hpp"

namespace Jun{

void Interpreter::Lb(Interpreter& interpreter, ImmediateInstruction instruction){
  // Load Byte - Mnemonic: lb rt, imm(rs)
  std::uint32_t vaddress = interpreter.State().Reg(instruction.rs) + SignExtend<std::uint32_t>(instruction.immediate);
  if(auto error = interpreter.System().GetMemmap().BadByte(vaddress); error){
    switch(error.value()){
      case MemoryManager::ExceptionCondition::AddressError:
        return;
      case MemoryManager::ExceptionCondition::BusError:
        return;
    };
  }
  else{
    interpreter.State().Reg(instruction.rt) = SignExtend<std::uint32_t>(interpreter.System().GetMemmap().ReadByte(vaddress));
    interpreter.SetActiveDelaySlot(instruction.rt, interpreter.State().Reg(instruction.rt));
  }
}

void Interpreter::Lbu(Interpreter& interpreter, ImmediateInstruction instruction){
  // Load Byte Unsigned- Mnemonic: lbu rt, imm(rs)
  std::uint32_t vaddress = interpreter.State().Reg(instruction.rs) + SignExtend<std::uint32_t>(instruction.immediate);
  if(auto error = interpreter.System().GetMemmap().BadByte(vaddress); error){
    switch(error.value()){
      case MemoryManager::ExceptionCondition::AddressError:
        return;
      case MemoryManager::ExceptionCondition::BusError:
        return;
    };
  }
  else{
    interpreter.State().Reg(instruction.rt) = ZeroExtend<std::uint32_t>(interpreter.System().GetMemmap().ReadByte(vaddress));
    interpreter.SetActiveDelaySlot(instruction.rt, interpreter.State().Reg(instruction.rt));
  }
}

void Interpreter::Lh(Interpreter& interpreter, ImmediateInstruction instruction){
  // Load Halfword - Mnemonic: lh rt, imm(rs)
  std::uint32_t vaddress = interpreter.State().Reg(instruction.rs) + SignExtend<std::uint32_t>(instruction.immediate);
  if(auto error = interpreter.System().GetMemmap().BadHalfWord(vaddress); error){
    switch(error.value()){
      case MemoryManager::ExceptionCondition::AddressError:
        return;
      case MemoryManager::ExceptionCondition::BusError:
        return;
    };
  }
  else{
    interpreter.State().Reg(instruction.rt) = SignExtend<std::uint32_t>(interpreter.System().GetMemmap().ReadHalfWord(vaddress));
    interpreter.SetActiveDelaySlot(instruction.rt, interpreter.State().Reg(instruction.rt));
  }
}

void Interpreter::Lhu(Interpreter& interpreter, ImmediateInstruction instruction){
  // Load Halfword - Mnemonic: lhu rt, imm(rs)
  std::uint32_t vaddress = interpreter.State().Reg(instruction.rs) + SignExtend<std::uint32_t>(instruction.immediate);
  if(auto error = interpreter.System().GetMemmap().BadHalfWord(vaddress); error){
    switch(error.value()){
      case MemoryManager::ExceptionCondition::AddressError:
        return;
      case MemoryManager::ExceptionCondition::BusError:
        return;
    };
  }
  else{
    interpreter.State().Reg(instruction.rt) = ZeroExtend<std::uint32_t>(interpreter.System().GetMemmap().ReadHalfWord(vaddress));
    interpreter.SetActiveDelaySlot(instruction.rt, interpreter.State().Reg(instruction.rt));
  }
}

void Interpreter::Lw(Interpreter& interpreter, ImmediateInstruction instruction){
  // Load Word - Mnemonic: lw rt, imm(rs)
  std::uint32_t vaddress = interpreter.State().Reg(instruction.rs) + SignExtend32(instruction.immediate);
  if(auto error = interpreter.System().GetMemmap().BadWord(vaddress); error){
    switch(error.value()){
      case MemoryManager::ExceptionCondition::AddressError:
        return;
      case MemoryManager::ExceptionCondition::BusError:
        return;
    };
  }
  else{
    interpreter.State().Reg(instruction.rt) = interpreter.System().GetMemmap().ReadWord(vaddress);
    interpreter.SetActiveDelaySlot(instruction.rt, interpreter.State().Reg(instruction.rt));
  }
}

void Interpreter::Lwl(Interpreter& interpreter, ImmediateInstruction instruction){
  // Load Word Left - Mnemonic: lwl rt, imm(rs)
  // Assumes little endian
  std::uint32_t vaddress = interpreter.State().Reg(instruction.rs) + SignExtend32(instruction.immediate);
  if(auto error = interpreter.System().GetMemmap().BadAddress(vaddress, 4); error){ // No need to check for alignment
    switch(error.value()){
      case MemoryManager::ExceptionCondition::AddressError:
        return;
      case MemoryManager::ExceptionCondition::BusError:
        return;
    };
  }
  else{
    std::uint32_t prevVal = interpreter.State().Reg(instruction.rt);
    for(std::uint8_t i = 0; i <= NextWordBase(vaddress) - vaddress; i++){
      interpreter.State().Reg(instruction.rt) &= ~(0xFF << ((4-i)*8 - 7));
      interpreter.State().Reg(instruction.rt) |= interpreter.System().GetMemmap().ReadByte(vaddress + i) << i*8 ;
    }
  }
}

void Interpreter::Lwr(Interpreter& interpreter, ImmediateInstruction instruction){
  // Load Word Right - Mnemonic: lwr rt, imm(rs)
  // Assumes little endian
  std::uint32_t vaddress = interpreter.State().Reg(instruction.rs) + SignExtend32(instruction.immediate);
  if(auto error = interpreter.System().GetMemmap().BadAddress(vaddress, 4); error){ // No need to check for alignment
    switch(error.value()){
      case MemoryManager::ExceptionCondition::AddressError:
        return;
      case MemoryManager::ExceptionCondition::BusError:
        return;
    };
  }
  else{
    std::uint32_t prevVal = interpreter.State().Reg(instruction.rt);
    for(std::uint8_t i = 0; i <= NextWordBase(vaddress) - vaddress; i++){
      interpreter.State().Reg(instruction.rt) &= ~(0xFF << ((4-i)*8 - 7));
      interpreter.State().Reg(instruction.rt) |= interpreter.System().GetMemmap().ReadByte(vaddress + i) << i*8 ;
    }
  }
}

} // namespace Jun
