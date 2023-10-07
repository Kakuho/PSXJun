// MIPS-1 bit masks for convenience
#include <cstdint>


namespace Instruction{
    // R instructions
    
  constexpr std::uint8_t R_HEADER = 0b0000'0000;
  constexpr std::uint8_t FUNCT    = 0b0011'1111;

    // Operands
    
  constexpr std::uint8_t RS     = 0b0001'1111;
  constexpr std::uint8_t RT     = 0b0001'1111;
  constexpr std::uint8_t SHAMT  = 0b0001'1111;
    
    // helpful functions for operands

  std::uint8_t Getrs(std::uint32_t instruction){

  }

  std::uint8_t Getrt(std::uint32_t instruction){

  }

  std::uint8_t Getrd(std::uint32_t instruction){

  }


  std::uint8_t GetShamt(std::uint32_t instruction){

  }

  std::uint16_t GetImmediateI(std::uint32_t instruction){

  }

  std::uint32_t GetImmediateJ(std::uint32_t instruction){

  }

    // MIPS-1 Functions - https://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats
    // R - type instructions are encoded as such:
    //
    //    [OPCODE] rs rt rd shamt [FUNCT]
    //
    // where OPCODE is a 6 bit string of zeros and FUNCT (6-bit) determines the function to be performed
    
  constexpr std::uint8_t OP_ADD   = 0x20;
  constexpr std::uint8_t OP_ADDU  = 0x21;
  constexpr std::uint8_t OP_SUB   = 0x22;
  constexpr std::uint8_t OP_SUBU  = 0x23;
  constexpr std::uint8_t OP_MULT  = 0x18;
  constexpr std::uint8_t OP_MULTU = 0x19;
  constexpr std::uint8_t OP_DIV   = 0x1A;
  constexpr std::uint8_t OP_DIVU  = 0x1B;

  constexpr std::uint8_t OP_MFHI  = 0x10;
  constexpr std::uint8_t OP_MTHI  = 0x11;
  constexpr std::uint8_t OP_MFLO  = 0x12;
  constexpr std::uint8_t OP_MTLO  = 0x13;

  constexpr std::uint8_t OP_AND = 0x24;
  constexpr std::uint8_t OP_NOR = 0x27;
  constexpr std::uint8_t OP_XOR = 0x26;
  constexpr std::uint8_t OP_OR  = 0x25;

  constexpr std::uint8_t OP_JALR  = 0x09;
  constexpr std::uint8_t OP_JR    = 0x08;

  constexpr std::uint8_t OP_SLT   = 0x2A;
  constexpr std::uint8_t OP_SLTU  = 0x2B;
  constexpr std::uint8_t OP_SLL   = 0x00;
  constexpr std::uint8_t OP_SRL   = 0x02;
  constexpr std::uint8_t OP_SRA   = 0x03;

    // J - type instructions (Jump) are encoded as such:
    //
    //  [OPCODE] [IMM]
    //
    // where [OPCODE] is a 6-bit string, and IMM is a 26-bit string representing an address to jump to

  constexpr std::uint8_t OP_JP  = 0x02;
  constexpr std::uint8_t OP_JAL = 0x03;

    // I - type instructions (Immediate) are encoded as such:
    //
    //  [OPCODE] rs rt [IMM]
    //
    // where OPCODE is a 6-bit string, and IMM is a 16-bit string where the immediate value is stored
  
  constexpr std::uint8_t SP_SLTI  = 0x0A;
  constexpr std::uint8_t SP_SLTIU = 0x0B;

  constexpr std::uint8_t SP_ANDI  = 0x0C;
  constexpr std::uint8_t SP_ORI   = 0x0D;

  constexpr std::uint8_t SP_BEQ   = 0x04;
  constexpr std::uint8_t SP_BNE   = 0x05;
  constexpr std::uint8_t SP_BLEZ  = 0x06;
  constexpr std::uint8_t SP_BGTZ  = 0x07;

  constexpr std::uint8_t SP_ADDI  = 0x08;
  constexpr std::uint8_t SP_ADDIU = 0x09;

  constexpr std::uint8_t SP_LUI = 0x0F;
  constexpr std::uint8_t SP_SW  = 0x2B;

  constexpr std::uint8_t SP_LB  = 0x20;
  constexpr std::uint8_t SP_LW  = 0x23;
  constexpr std::uint8_t SP_LBU = 0x24;
  constexpr std::uint8_t SP_LHU = 0x25;
  constexpr std::uint8_t SP_SB  = 0x28;
  constexpr std::uint8_t SP_SH  = 0x29;
}
