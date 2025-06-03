// Implementation of the logical instructions of mips r3000

#include <cstdint>

#include "mips_r3000a/interpreter/interpreter.hpp"
#include "common/integer_extension.hpp"
#include "system/psx_system.hpp"

namespace Jun{

void Interpreter::And(Interpreter& interpreter, RegisterInstruction instruction){
  // Bitwise and of 2 registers
  // Mnemonic: and rd, rs, rt
  std::uint32_t rsVal = interpreter.State().Reg(instruction.rs);
  std::uint32_t rtVal = interpreter.State().Reg(instruction.rt);
  interpreter.State().Reg(instruction.rd) = rsVal & rtVal;
}

void Interpreter::Andi(Interpreter& interpreter, ImmediateInstruction instruction){
  // Bitwise and of register and immediate
  // Mnemonic: and rt, rs, immediate
  std::uint32_t rsVal = interpreter.State().Reg(instruction.rs);
  std::uint32_t immExtended= ZeroExtend32(instruction.immediate);
  interpreter.State().Reg(instruction.rt) = rsVal & immExtended;
}

void Interpreter::Ori(Interpreter& interpreter, ImmediateInstruction instruction){
  // Bitwise or of register and immediate
  // Mnemonic: or rt, rs, immediate
  std::uint32_t rsVal = interpreter.State().Reg(instruction.rs);
  std::uint32_t immExtended= ZeroExtend32(instruction.immediate);
  interpreter.State().Reg(instruction.rt) = rsVal | immExtended;
}

}
