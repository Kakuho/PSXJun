// MIPS-1 bit masks for convenience
#include <cstdint>


namespace Instruction{

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

  std::uint8_t GetOpcode(std::uint32_t instruction){
    return (instruction & OPCODE) >> 26;

  }

  std::uint8_t GetRs(std::uint32_t instruction){
    return (instruction & RS) >> 21;
  }

  std::uint8_t GetRt(std::uint32_t instruction){
    return (instruction & RT) >> 16;
  }

  std::uint8_t GetRd(std::uint32_t instruction){
    return (instruction & RD) >> 11;
  }


  std::uint8_t GetShamt(std::uint32_t instruction){
    return (instruction & SHAMT) >> 6;
  }

  std::uint8_t GetFunction(std::uint32_t instruction){
    return instruction & FUNCT;
  }

  std::uint16_t GetImm(std::uint32_t instruction){
    return instruction & IMM;
  }

  std::uint32_t GetAddr(std::uint32_t instruction){
    return instruction & ADDR;
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
