#pragma once

//  Implementation of the load store opcodes of mips_r3000
//
//  Todo:
//
//    Load Hazards:
//      * Trigger Address Error Exception if memory is not aligned
//      * Trigger Bus Error Exception if the memory address is invalid

#include <cstdint>

#include "interpreter.hpp"
#include "common/integer_extension.hpp"
#include "system/psx_system.hpp"

namespace Jun{

void Interpreter::Lb(Interpreter& interpreter, ImmediateInstruction instruction){
  // Load Byte
  // Mnemonic: lb rt, imm(rs)
  std::uint32_t vaddress = interpreter.State().Reg(instruction.rs) + SignExtend32(instruction.immediate);
  if(interpreter.System().GetMemmap().IsAddressError(vaddress)){
    //Interpreter::TriggerBusLoadStoreException(interpreter);
  }
  else{
    interpreter.State().Reg(instruction.rt) = interpreter.System().GetMemmap().ReadByte(vaddress);
    interpreter.SetActiveDelaySlot(instruction.rt, interpreter.State().Reg(instruction.rt));
  }
}

void Interpreter::Lw(Interpreter& interpreter, ImmediateInstruction instruction){
  // Load Word
  // Mnemonic: lw rt, imm(rs)
  std::uint32_t vaddress = interpreter.State().Reg(instruction.rs) + SignExtend32(instruction.immediate);
  if(vaddress & 0x11){
    //Interpreter::TriggerAddressLoadFetchException(interpreter);
  }
  else{
    interpreter.State().Reg(instruction.rt) = interpreter.System().GetMemmap().ReadByte(vaddress);
    interpreter.SetActiveDelaySlot(instruction.rt, interpreter.State().Reg(instruction.rt));
  }
}

void Interpreter::Sw(Interpreter& interpreter, ImmediateInstruction instruction){
  // Store word
  // Mnemonic: Sw rt, imm(rs)
  std::uint32_t vaddress = interpreter.State().Reg(instruction.rs) + SignExtend32(instruction.immediate);
  if(vaddress & 0x11){
    //Interpreter::TriggerAddressStoreException(interpreter);
  }
  else{
    interpreter.State().Reg(instruction.rt) = interpreter.System().GetMemmap().ReadByte(vaddress);
    interpreter.SetActiveDelaySlot(instruction.rt, interpreter.State().Reg(instruction.rt));
  }
}

}
