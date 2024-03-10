#ifndef CPU_HPP
#define CPU_HPP

// Definition of the r3000a processor.

#include "./../system/bus.hpp"
#include "instruction.hpp"
#include "./../util/util.hpp"
#include "exceptionVectors.hpp"
#include "cop0.hpp"

#include <array>
#include <iostream>
#include <cstdint>
#include <bitset>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <concepts>
#include <sstream>
#include <bitset>

namespace psxjun{

namespace system{
  class SystemBus;
}

namespace processor{

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
  std::uint32_t m_hi = 0;     // upper half of 64 bit multiplication
  std::uint32_t m_low = 0;    // lower half of 64 bit multiplication
  std::uint32_t m_pc = 0;     // program counter
  std::size_t   m_ticks;
  arguments m_args;           // buffer for instructions parameters
  std::uint32_t m_ibuffer;    // buffer for the current instruction
  Cop0 m_cop0;

  // connections to the rest of the system

  system::SystemBus* m_sysbus;

  public:

  /* TODO: create initialisation functions */

  CPU();
  CPU(system::SystemBus* sysbus);
  void HookSystemBus(system::SystemBus& sysbus){
    m_sysbus = &sysbus;
  }

  // register related
  
  std::uint32_t Register(std::uint8_t index) const { return m_registers[index]; }
  std::uint32_t& Register(std::uint8_t index){ return m_registers[index]; }
  std::uint32_t GetRegisterValue(std::uint8_t index) const;

  std::uint32_t GetPC() const { return m_pc;}
  void SetPC(std::uint32_t addr){ m_pc = addr;}

  std::uint32_t& PC() { return m_pc;}
  const std::uint32_t& PC() const { return m_pc;}

  std::uint32_t GetHi() const { return m_hi;}
  std::uint32_t& Hi() {return m_hi;}
  std::uint32_t GetLow() const { return m_low;}
  std::uint32_t& Lo() {return m_low;}

  // instruction buffer functions

  void SetInstruction(std::uint32_t value){ m_ibuffer = value;}
  std::uint32_t GetInstruction() const{ return m_ibuffer;}

  // N.B  : memory input / output instructions are written to the Data Cache.
  //      : r3000a is a little endian processor.
  //      : r3000a defines a byte as 8 bit, halfword as 16 bits and a word as 
  //        32 bits.
  
  // Memory read operations
 
  std::uint8_t ReadByte(std::size_t index) const;
  std::uint16_t GetHalfWord(std::size_t index1, std::size_t index2, 
                            std::size_t index3, std::size_t index4) const;
  std::uint32_t ReadWord(std::size_t index) const;

  // Memory write operations

  void WriteByte(std::size_t index, std::uint8_t val);
  void WriteWord(std::size_t index, std::uint32_t val);

  // CPU operational functions

  void Tick();
  std::size_t GetTicks() const{ return m_ticks; }
  void Fetch();
  void Decode();
  void Execute();

  // CPU opcodes

  void UnimplementedOp(std::string&& op) const{ 
    throw std::runtime_error{
      "Opcode " + op + " is not implemented"
    };
  } 

  template<typename T1, typename T2, typename T3> 
    requires std::is_integral<T1>::value && 
             std::is_integral<T2>::value &&
             std::is_integral<T3>::value
  void UnimplementedOp(std::string&& op, T1 v1, T2 v2, T3 v3) const{
    std::stringstream output;
    output << "arguments: arg1 = " << v1 << ", arg2 = " << v2 << ", arg3 = " << v3 << '\n';
    throw std::runtime_error{
      "Opcode " + op + " is not implemented" + '\n' + output.str()
    };
  }

  // overflow detection

  bool arithmeticOverflow(std::uint32_t val1, std::uint32_t val2) const;

  // Exception Triggers

  void trigger_overflow_ex();  // OVF is the name for arithmetic overflow excpetion
  void trigger_addressLoad_ex();
  void trigger_addressStore_ex();

  // helper
  
  void InvalidOp() const{ std::cout << "INSTRUCTION IS INVALID" << '\n'; }

  // ALU
  
  void ADD(std::int8_t rd, std::int8_t rs, std::int8_t rt);
  void ADDI(std::int8_t rt, std::int8_t rs, std::int16_t imm);

  template<bool logging>
  void ADDIU(std::uint8_t rt, std::uint8_t rs, std::uint16_t imm);

  void ADDU(std::uint8_t rd, std::uint8_t rs, std::uint8_t rt);

  void SUB(std::int8_t rd, std::uint8_t rs, std::uint8_t rt);
  void SUBU(std::int8_t rd, std::int8_t rs, std::int8_t rt);

  // Bitwise

  template<bool logging>
  void SLL(std::int8_t rt, std::int8_t rd, std::int8_t sa);

  // Multiplication Division

  void DIV(std::uint8_t rs, std::uint8_t rt);
  void DIVU(std::uint8_t rs, std::uint8_t rt);

  // Logical

  void AND(std::uint8_t rs, std::uint8_t rt, std::uint8_t rd);
  void ANDI(std::uint8_t rs, std::uint8_t rt, std::uint16_t imm);

  template<bool logging>
  void ORI(std::uint8_t rs, std::uint8_t rt, std::uint16_t imm);

  // Load and Store

  template<bool logging>
  void LUI(std::uint8_t rt, std::uint16_t imm);

  template<bool logging>
  void SW(std::uint8_t base, std::uint8_t rt, std::uint16_t offset);

  // Jumps

  // Branching

  template<bool logging>
  void BEQ(std::uint8_t rs, std::uint8_t rt, std::uint16_t offset);
  

  // coprocessor

  void LWC0(std::uint8_t rt, std::uint16_t offset);
  void SWC0(std::uint8_t rt, std::uint16_t offset);
  void MTC0(std::uint8_t rt, std::uint8_t rd);
  void MFC0(std::uint8_t rt, std::uint8_t rd);
  void CTC0(std::uint8_t rt, std::uint8_t rd);
  void CFC0(std::uint8_t rt, std::uint8_t rd);
  void COP0(std::uint8_t rt, std::uint8_t rd);
  void RFE();

  // MISC
  
  void CACHE(std::uint8_t base, std::uint8_t op, std::int16_t imm){
    throw std::runtime_error{"Instruction CACHE is not implemented"};
  }

};

} // namespace processor

} // namesapce psxjun

#endif
