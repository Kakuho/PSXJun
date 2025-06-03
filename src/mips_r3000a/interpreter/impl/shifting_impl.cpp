//  Implementation of the shifting instructions of mips r3000

#include <cstdint>

#include "mips_r3000a/interpreter/interpreter.hpp"
#include "common/integer_extension.hpp"
#include "system/psx_system.hpp"

namespace Jun{

void Interpreter::Sll(Interpreter& interpreter, RegisterInstruction instruction){
  // Shift a register left
  // Mnemonic: sll rt, rs, sa
  std::uint32_t rsVal = interpreter.State().Reg(instruction.rs);
  interpreter.State().Reg(instruction.rt) = rsVal << instruction.shamt;
}

void Interpreter::Lui(Interpreter& interpreter, ImmediateInstruction instruction){
  // Load Upper Immediate
  // Mnemonic: lui rt, imm
  std::uint32_t immediate = instruction.immediate << 16;
  interpreter.State().Reg(instruction.rt) = immediate;
}

} // namespace Jun
