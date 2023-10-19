#ifndef CPU_HPP
#define CPU_HPP

// Definition of the r3000a processor.

#include "instruction.hpp"
#include "bus.hpp"

#include <array>
#include <iostream>
#include <cstdint>

static const long CLOCKSPEED = -1;

struct arguments{
  std::uint8_t funct;
  std::uint8_t rs;  
  std::uint8_t rt;  
  std::uint8_t rd;  
  std::uint8_t shamt;
  std::uint16_t imm;  
};

// The PSX CPU is a MIPS R3000A cpu.
class CPU{

  std::array<std::uint32_t, 32>   m_registers;
  /* TODO: memory should be moved into its own class */
  std::array<std::uint8_t, 4000> m_instrucion_cache;
  std::array<std::uint8_t, 1000> m_data_cache;
  std::array<std::uint8_t, 100000> m_ram;  

  std::uint32_t m_hi = 0;     // upper half of 64 bit multiplication
  std::uint32_t m_low = 0;    // lower half of 64 bit multiplication
  std::uint32_t m_pc;         // program counter
  std::size_t   m_ticks;      // stores the number of ticks
  
  // helpers for instructions, opcode decoding
  arguments m_args;
  std::uint32_t m_ibuffer;    // buffer for the current instruction

  public:
  /* TODO: create initialisation functions */

  CPU();

  // register related
  
  std::uint32_t Register(std::uint8_t index) const { return m_registers[index]; }
  std::uint32_t& Register(std::uint8_t index){ return m_registers[index]; }
  std::uint32_t GetRegisterValue(std::uint8_t index) const;

  std::uint32_t GetPC() const { return m_pc;}
  void SetPC(std::uint32_t addr){ m_pc = addr;}

  std::uint32_t GetHi() const { return m_hi;}
  std::uint32_t GetLow() const { return m_low;}

  // instruction buffer functions

  void SetInstruction(std::uint32_t value){ m_ibuffer = value;}
  std::uint32_t GetInstruction() const{ return m_ibuffer;}

  // N.B  : memory input / output instructions are written to the Data Cache
  //      : r3000a is a little endian processor 
  //      : r3000a defines a byte as 8 bit, halfword as 16 bits and a word as 32 bits
    
  std::uint8_t ReadByte(std::size_t index) const;
  std::uint16_t GetHalfWord(std::size_t index1, std::size_t index2, 
                            std::size_t index3, std::size_t index4) const;
  std::uint32_t ReadWord(std::size_t index) const;

  // CPU operational functions

  void Tick();
  std::size_t GetTicks() const{ return m_ticks; }
  void Fetch();
  void Decode();
  void Execute();

  // CPU opcodes

  void UnimplementedOp() const{ std::cout << "OPERATION NOT IMPLEMENTED!" << '\n';} // helper
  void InvalidOp() const{ std::cout << "INSTRUCTION IS INVALID" << '\n'; }

  // Adds
  void ADD(std::int8_t rd, std::int8_t rs, std::int8_t rt);
  void ADDI(std::int8_t rt, std::int8_t rs, std::int16_t imm);
  void ADDIU(std::uint8_t rt, std::uint8_t rs, std::uint16_t imm);
  void ADDU(std::uint8_t rd, std::uint8_t rs, std::uint8_t rt);

  // Subtractions

  void SUB(std::int8_t rd, std::uint8_t rs, std::uint8_t rt);
  void SUBU(std::int8_t rd, std::int8_t rs, std::int8_t rt);

  // Logical And

};

#endif
