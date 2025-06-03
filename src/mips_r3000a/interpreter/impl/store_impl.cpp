//  Implementation of the store opcodes of mips_r3000
//
//  Store Hazards:
//    * Trigger Address Error Exception if memory is not aligned or due to privilage levels
//    * Trigger Bus Error Exception if the memory address is invalid 
//    * Certain MMIO ports will read the full 32-bit value of registers, even if the instruction
//      is not a 32-bit store.

#include <cstdint>

#include "mips_r3000a/interpreter/interpreter.hpp"
#include "common/integer_extension.hpp"
#include "system/psx_system.hpp"

namespace Jun{

void Interpreter::Sb(Interpreter& interpreter, ImmediateInstruction instruction){
  // Store Byte - Mnemonic: Sb rt, imm(rs)
  std::uint32_t vaddress = interpreter.State().Reg(instruction.rs) + SignExtend<std::uint32_t>(instruction.immediate);
  if(auto error = interpreter.System().GetMemmap().BadWord(vaddress); error){
    switch(error.value()){
      case MemoryManager::ExceptionCondition::AddressError:
        return;
      case MemoryManager::ExceptionCondition::BusError:
        return;
    };
  }
  else{
    interpreter.System().GetMemmap().WriteByte(vaddress, interpreter.State().Reg(instruction.rt) & 0xFF);
  }
}

void Interpreter::Sh(Interpreter& interpreter, ImmediateInstruction instruction){
  // Store half word (16 bits) - Mnemonic: Sh rt, imm(rs)
  std::uint32_t vaddress = interpreter.State().Reg(instruction.rs) + SignExtend<std::uint32_t>(instruction.immediate);
  if(auto error = interpreter.System().GetMemmap().BadWord(vaddress); error){
    switch(error.value()){
      case MemoryManager::ExceptionCondition::AddressError:
        return;
      case MemoryManager::ExceptionCondition::BusError:
        return;
    };
  }
  else{
    interpreter.System().GetMemmap().WriteByte(vaddress, interpreter.State().Reg(instruction.rt) & 0xFFFF);
  }
}

void Interpreter::Sw(Interpreter& interpreter, ImmediateInstruction instruction){
  // Store word (32 bits) - Mnemonic: Sw rt, imm(rs)
  std::uint32_t vaddress = interpreter.State().Reg(instruction.rs) + SignExtend<std::uint32_t>(instruction.immediate);
  if(auto error = interpreter.System().GetMemmap().BadWord(vaddress); error){
    switch(error.value()){
      case MemoryManager::ExceptionCondition::AddressError:
        return;
      case MemoryManager::ExceptionCondition::BusError:
        return;
    };
  }
  else{
    interpreter.System().GetMemmap().WriteByte(vaddress, interpreter.State().Reg(instruction.rt));
  }
}

}
