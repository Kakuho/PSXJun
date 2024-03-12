#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

// MIPS-1 bit masks for convenience
#include <cstdint>
#include <type_traits>

namespace psxjun{

namespace instruction{

  // Operands
    
  constexpr std::uint32_t OPCODE  = 0xFC'00'00'00;
  constexpr std::uint32_t RS      = 0x03'E0'00'00;
  constexpr std::uint32_t RT      = 0x00'1F'00'00;
  constexpr std::uint32_t RD      = 0x00'00'F8'00;
  constexpr std::uint32_t SHAMT   = 0x00'00'07'C0;
  constexpr std::uint32_t FUNCT   = 0x00'00'00'3F;
  constexpr std::uint32_t IMM     = 0x00'00'FF'FF;
  constexpr std::uint32_t ADDR     = 0x03'FF'FF'FF;
    
  // helpful functions for operands
  // The shifts are to rid the unncessary digits

  static inline std::uint8_t GetOpcode(std::uint32_t instruction){
    return (instruction & OPCODE) >> 26;

  }

  static inline std::uint8_t GetRs(std::uint32_t instruction){
    return (instruction & RS) >> 21;
  }

  static inline std::uint8_t GetRt(std::uint32_t instruction){
    return (instruction & RT) >> 16;
  }

  static inline std::uint8_t GetRd(std::uint32_t instruction){
    return (instruction & RD) >> 11;
  }


  static inline std::uint8_t GetShamt(std::uint32_t instruction){
    return (instruction & SHAMT) >> 6;
  }

  static inline std::uint8_t GetFunct(std::uint32_t instruction){
    return instruction & FUNCT;
  }

  static inline std::uint16_t GetImm(std::uint32_t instruction){
    return instruction & IMM;
  }

  static inline std::uint32_t GetAddr(std::uint32_t instruction){
    return instruction & ADDR;
  }

  // MIPS-1 Functions - https://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats
  // R - type instructions are encoded as such:
  //
  //    [OPCODE] rs rt rd shamt [FUNCT]
  //
  // where OPCODE is a 6 bit string of zeros and FUNCT (6-bit) determines the function to be performed
    
  static constexpr std::uint8_t OP_SLL   = 0x00;
  static constexpr std::uint8_t OP_DIV   = 0x1A;
  static constexpr std::uint8_t OP_DIVU  = 0x1B;
  static constexpr std::uint8_t OP_SRL   = 0x02;
  static constexpr std::uint8_t OP_SLT   = 0x2A;
  static constexpr std::uint8_t OP_SLTU  = 0x2B;
  static constexpr std::uint8_t OP_SRA   = 0x03;
  static constexpr std::uint8_t OP_JR    = 0x08;
  static constexpr std::uint8_t OP_JALR  = 0x09;
  static constexpr std::uint8_t OP_MFHI  = 0x10;
  static constexpr std::uint8_t OP_MTHI  = 0x11;
  static constexpr std::uint8_t OP_MFLO  = 0x12;
  static constexpr std::uint8_t OP_MTLO  = 0x13;
  static constexpr std::uint8_t OP_MULT  = 0x18;
  static constexpr std::uint8_t OP_MULTU = 0x19;
  static constexpr std::uint8_t OP_ADD   = 0x20;
  static constexpr std::uint8_t OP_ADDU  = 0x21;
  static constexpr std::uint8_t OP_SUB   = 0x22;
  static constexpr std::uint8_t OP_SUBU  = 0x23;
  static constexpr std::uint8_t OP_AND   = 0x24;
  static constexpr std::uint8_t OP_OR    = 0x25;
  static constexpr std::uint8_t OP_XOR   = 0x26;
  static constexpr std::uint8_t OP_NOR   = 0x27;

  // J - type instructions (Jump) are encoded as such:
  //
  //  [OPCODE] [IMM]
  //
  // where [OPCODE] is a 6-bit string, and IMM is a 26-bit string representing an address to jump to

  static constexpr std::uint8_t OP_J  = 0x02;
  static constexpr std::uint8_t OP_JAL = 0x03;

  // I - type instructions (Immediate) are encoded as such:
  //
  //  [OPCODE] rs rt [IMM]
  //
  // where OPCODE is a 6-bit string, and IMM is a 16-bit string where the immediate value is stored
  
  static constexpr std::uint8_t SP_SLTI  = 0x0A;
  static constexpr std::uint8_t SP_SLTIU = 0x0B;
  static constexpr std::uint8_t SP_ANDI  = 0x0C;
  static constexpr std::uint8_t SP_ORI   = 0x0D;
  static constexpr std::uint8_t SP_BEQ   = 0x04;
  static constexpr std::uint8_t SP_BNE   = 0x05;
  static constexpr std::uint8_t SP_BLEZ  = 0x06;
  static constexpr std::uint8_t SP_BGTZ  = 0x07;
  static constexpr std::uint8_t SP_ADDI  = 0x08;
  static constexpr std::uint8_t SP_ADDIU = 0x09;
  static constexpr std::uint8_t SP_LUI = 0x0F;
  static constexpr std::uint8_t SP_SW  = 0x2B;
  static constexpr std::uint8_t SP_LB  = 0x20;
  static constexpr std::uint8_t SP_LW  = 0x23;
  static constexpr std::uint8_t SP_LBU = 0x24;
  static constexpr std::uint8_t SP_LHU = 0x25;
  static constexpr std::uint8_t SP_SB  = 0x28;
  static constexpr std::uint8_t SP_SH  = 0x29;
    
  // Coprocessor Instructions
  
  static constexpr std::uint8_t OP_MFC0  = 0x10;

} // namespace instruction

} // namespace psxjun

#endif
