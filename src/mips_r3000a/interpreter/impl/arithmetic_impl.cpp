// Implementation of the arithmetic instructions of mips r3000

#include <cstdint>

#include "mips_r3000a/interpreter/interpreter.hpp"
#include "common/integer_extension.hpp"
#include "system/psx_system.hpp"

namespace Jun{

// !(x ^ y) is true iff x and y has the same sign
// x ^ y is true iff x and y does not have the same sign, both are zero

constexpr bool CheckAddOverflow(std::uint32_t a, std::uint32_t b){
  //  Addition has Overflown if:
  //    * The sign of both operands are the same
  //    * The sign of the result differs from the sign of the operand
  //
  //  Truth Table:
  //  a  b   sum  | of                 | !(a ^ b) && (sum ^ a)
  //  0  0   0      0    // ok           1 && 0 = 0
  //  0  0   1      1    // overflow     1 && 1 = 1
  //  0  1   0      0    // ok           0 && 0 = 0
  //  0  1   1      0    // ok           0 && 1 = 0
  //  1  0   0      0    // ok           0 && 1 = 0
  //  1  0   1      0    // ok           0 && 0 = 0
  //  1  1   0      1    // overflow     1 && 1 = 1
  //  1  1   1      0    // ok           1 && 0 = 0
  std::uint32_t sum = a + b;
  return (!(a ^ b) >> 31) & ((a ^ sum) >> 31);
}

constexpr bool CheckSubOverflow(std::uint32_t a, std::uint32_t b){
  //  Subtraction has Overflown if:
  //    * The sign of both operands are different
  //    * The sign of the result is different from the sign of minuend
  //      - if minuend is +ve, subtractand is -ve, then result should be +ve otherwise overflow
  //      - if minuend is -ve, subtractand is +ve, then result should be -ve otherwise overflow
  //
  //  Truth Table: 
  //  a  b   result  |  of  | (a ^ b) & (a ^ result)
  //  0  0   0          0     0 & 0 = 0
  //  0  0   1          0     0 & 1 = 0
  //  0  1   0          0     1 & 0 = 0
  //  0  1   1          1     1 & 1 = 1
  //  1  0   0          1     1 & 1 = 1
  //  1  0   1          0     1 & 0 = 0
  //  1  1   0          0     0 & 1 = 0
  //  1  1   1          0     0 & 0 = 0
  //
  //  a - b = sum
  std::uint32_t result = a - b;
  return ((a ^ b) >> 31) & ((a ^ result) >> 31);
}

// Arithmetic

void Interpreter::Add(Interpreter& interpreter, RegisterInstruction instruction){
  // Add 2 registers
  // Mnemonic: add rd, rs, rt
  std::uint32_t rsVal = interpreter.State().Reg(instruction.rs);
  std::uint32_t rtVal = interpreter.State().Reg(instruction.rt);
  if(CheckAddOverflow(rsVal, rtVal)){
    //Interpreter::TriggerOverflowExeption(interpreter);
    return;
  }
  else{
    interpreter.State().Reg(instruction.rd) = rsVal + rtVal;
  }
}

void Interpreter::Addu(Interpreter& interpreter, RegisterInstruction instruction){
  // Add 2 registers, unsigned
  // Mnemonic: add rd, rs, rt
  std::uint32_t rsVal = interpreter.State().Reg(instruction.rs);
  std::uint32_t rtVal = interpreter.State().Reg(instruction.rt);
  interpreter.State().Reg(instruction.rd) = rsVal + rtVal;
}

void Interpreter::Addi(Interpreter& interpreter, ImmediateInstruction instruction){
  // Add a register and an immediate
  // Mnemonic addi rt, rs, imm
  std::uint32_t rsVal = interpreter.State().Reg(instruction.rs);
  std::uint32_t immediate32 = SignExtend32(instruction.immediate);
  if(CheckAddOverflow(rsVal, immediate32)){
    //Interpreter::TriggerOverflowExeption(interpreter);
    return;
  }
  else{
    interpreter.State().Reg(instruction.rt) = rsVal + immediate32;
  }
}

void Interpreter::Addiu(Interpreter& interpreter, ImmediateInstruction instruction){
  // Add a register and an immediate, unsigned
  // Mnemonic: addi rt, rs, imm
  std::uint32_t rsVal = interpreter.State().Reg(instruction.rs);
  std::uint32_t immediate32 = SignExtend32(instruction.immediate);
  interpreter.State().Reg(instruction.rt) = rsVal + immediate32;
}

void Interpreter::Sub(Interpreter& interpreter, RegisterInstruction instruction){
  // Subtracts two registers
  // Mnemonic: sub rd, rs, rt
  std::uint32_t rsVal = interpreter.State().Reg(instruction.rs);
  std::uint32_t rtVal = interpreter.State().Reg(instruction.rt);
  if(CheckSubOverflow(rsVal, rtVal)){
    //Interpreter::TriggerOverflowExeption(interpreter);
    return;
  }
  else{
    interpreter.State().Reg(instruction.rd) = rsVal - rtVal;
  }
}

void Interpreter::Subu(Interpreter& interpreter, RegisterInstruction instruction){
  // Subtracts two registers, unsigned
  // Mnemonic: sub rd, rs, rt
  std::uint32_t rsVal = interpreter.State().Reg(instruction.rs);
  std::uint32_t rtVal = interpreter.State().Reg(instruction.rt);
  interpreter.State().Reg(instruction.rd) = rsVal - rtVal;

}

}
