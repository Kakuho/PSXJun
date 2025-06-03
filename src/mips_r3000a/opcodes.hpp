#pragma once

#include <cstdint>
#include <string>

// References:
//  
// MIPS-1 Instructions - https://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats
// https://psx-spx.consoledev.net/cpuspecifications/#coprocessor-opcodeparameter-encoding

namespace Jun{

namespace MipsOpcodes{
  // MIPS-1 Functions - https://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats
  // R - type instructions are encoded as such:
    
  static inline constexpr std::uint8_t SLL   = 0x00;
  static inline constexpr std::uint8_t DIV   = 0x1A;
  static inline constexpr std::uint8_t DIVU  = 0x1B;
  static inline constexpr std::uint8_t SRL   = 0x02;
  static inline constexpr std::uint8_t SLT   = 0x2A;
  static inline constexpr std::uint8_t SLTU  = 0x2B;
  static inline constexpr std::uint8_t SRA   = 0x03;
  static inline constexpr std::uint8_t JR    = 0x08;
  static inline constexpr std::uint8_t JALR  = 0x09;
  static inline constexpr std::uint8_t MFHI  = 0x10;
  static inline constexpr std::uint8_t MTHI  = 0x11;
  static inline constexpr std::uint8_t MFLO  = 0x12;
  static inline constexpr std::uint8_t MTLO  = 0x13;
  static inline constexpr std::uint8_t MULT  = 0x18;
  static inline constexpr std::uint8_t MULTU = 0x19;
  static inline constexpr std::uint8_t ADD   = 0x20;
  static inline constexpr std::uint8_t ADDU  = 0x21;
  static inline constexpr std::uint8_t SUB   = 0x22;
  static inline constexpr std::uint8_t SUBU  = 0x23;
  static inline constexpr std::uint8_t AND   = 0x24;
  static inline constexpr std::uint8_t OR    = 0x25;
  static inline constexpr std::uint8_t XOR   = 0x26;
  static inline constexpr std::uint8_t NOR   = 0x27;

  // J - type instructions (Jump) are encoded as such:

  static inline constexpr std::uint8_t J  = 0x02;
  static inline constexpr std::uint8_t JAL = 0x03;

  // I - type instructions (Immediate) are encoded as such:

  static inline constexpr std::uint8_t SLTI  = 0x0A;
  static inline constexpr std::uint8_t SLTIU = 0x0B;
  static inline constexpr std::uint8_t ANDI  = 0x0C;
  static inline constexpr std::uint8_t ORI   = 0x0D;
  static inline constexpr std::uint8_t BEQ   = 0x04;
  static inline constexpr std::uint8_t BNE   = 0x05;
  static inline constexpr std::uint8_t BLEZ  = 0x06;
  static inline constexpr std::uint8_t BGTZ  = 0x07;
  static inline constexpr std::uint8_t ADDI  = 0x08;
  static inline constexpr std::uint8_t ADDIU = 0x09;
  static inline constexpr std::uint8_t LUI = 0x0F;
  static inline constexpr std::uint8_t SW  = 0x2B;
  static inline constexpr std::uint8_t LB  = 0x20;
  static inline constexpr std::uint8_t LW  = 0x23;
  static inline constexpr std::uint8_t LBU = 0x24;
  static inline constexpr std::uint8_t LHU = 0x25;
  static inline constexpr std::uint8_t SB  = 0x28;
  static inline constexpr std::uint8_t SH  = 0x29;
    
  // Coprocessor instructions

  static inline constexpr std::uint8_t SWC0 = 0x30;
  static inline constexpr std::uint8_t SWC2 = 0x32;
  static inline constexpr std::uint8_t LWC0 = 0x38;
  static inline constexpr std::uint8_t LWC2 = 0x3A;
  static inline constexpr std::uint8_t COP0 = 0x10; 
  static inline constexpr std::uint8_t COP2 = 0x12;

  // General coprocessor instructions

  static constexpr std::uint8_t MFC0_HEAD = 0x00;
  static constexpr std::uint8_t MFC0_TAIL = 0x00;
  static constexpr std::uint8_t CFC0_HEAD = 0x02;
  static constexpr std::uint8_t CFC0_TAIL = 0x00;
  static constexpr std::uint8_t MTC0_HEAD = 0x04;
  static constexpr std::uint8_t MTC0_TAIL = 0x00;
  static constexpr std::uint8_t CTC0_HEAD = 0x06;
  static constexpr std::uint8_t CTC0_TAIL = 0x00;
  static constexpr std::uint8_t BC0F_HEAD_0 = 0x08;
  static constexpr std::uint8_t BC0F_HEAD_1 = 0x00;
  static constexpr std::uint8_t BC0T_HEAD_0 = 0x08;
  static constexpr std::uint8_t BC0T_HEAD_1 = 0x01;

  // COP0 only instructions

  static constexpr std::uint8_t COP025 = 0x1;
  static constexpr std::uint8_t COP0RFE_HEAD = 0x10;
  static constexpr std::uint8_t COP0RFE_TAIL = 0x10;

} // namespace MipsOpcodes

} // namespace Jun
