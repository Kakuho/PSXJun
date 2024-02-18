#include "cpu.hpp"
#include "instruction.hpp"
#include <stdexcept>

namespace psxjun{

namespace processor{

CPU::CPU(){
  m_registers[0] = 0;
  m_pc = reset_vector;
}

CPU::CPU(system::SystemBus* sysbus):
  m_sysbus{sysbus}
{
  m_registers[0] = 0;
  m_pc = reset_vector;
}

// Registers

std::uint32_t CPU::GetRegisterValue(std::uint8_t index) const{
  if (index <= 32){
    return m_registers[index];
  }
  else{
    throw std::runtime_error{
      "ERROR: GetRegisterValue(uint8_t index): " + std::to_string(index) + " is out of bounds"
    };
  }
}

// Memory getters

std::uint8_t CPU::ReadByte(std::size_t index) const{
  /* TODO: wrapping around the address space*/
  return m_sysbus->GetByte(index);
}

std::uint16_t CPU::GetHalfWord(std::size_t index1, std::size_t index2, 
                               std::size_t index3, std::size_t index4) const{
  /* TODO   : wrapping around the address space */
  // Assumes: fetching bytes in the order M[index1], M[index2], M[index3], M[index4]
  std::uint8_t byte1 = ReadByte(index1);
  // R3000A is little endian, so the half word would be M[index4], M[index3], M[index2], M[index1].
}

std::uint32_t CPU::ReadWord(std::size_t index) const{
  return m_sysbus->GetWord(index);
}


// CPU operational functions
//---------------------------------------------------------------//
// Classic Fetch Decode Cycle:
//
// The CPU contains a buffer of ticks (m_ticks) which contains the amount of ticks
// needed / stored for each executed instruction. Tick() checks to see if there are any 
// pending ticks and proceeds only if there are no more ticks left in the buffer.
//
// Perhaps not the most cycle accurate, however later on I will do a survery to see how other 
// emulators handle cycle accuracy
//
//  * Fetch(): fetches the instruction from memory.
//
//    ^
//    |
//
//  * Tick(): checks to see if there is any buffered ticks. 
//            If not then proceeds to Fetch(), decode and executes the instruction.
//            Otherwise a call decrements the buffered ticks.
//
// 
//---------------------------------------------------------------//
//
// However the R3000A is a mips-1 processor and thus implements a 5 stage pipeline.
// Therefore more research is needed to understand how to create an emulator for a 
// 5-stage pipeline, as I expect timing considerations will be different, especially in regards
// to data hazards.
//
//---------------------------------------------------------------//

void CPU::Tick(){
  using namespace instruction;
  // first check if there are any buffered ticks
  if( GetTicks() ){
    return;
  }
  else{
    Fetch();
    std::cout << "pc = " << (unsigned)GetPC() << '\n';
    std::uint8_t opcode = instruction::GetOpcode(GetInstruction());  // decode step
    Decode();
    // execute step
    switch(opcode){
      case 0:{ // R-type instruction
        switch(m_args.funct){
          case OP_ADD:    ADD(m_args.rd, m_args.rs, m_args.rt); break;
          case OP_ADDU:   ADDU(m_args.rd, m_args.rs, m_args.rt); break;
          case OP_SUB:    UnimplementedOp("SUB"); break;
          case OP_SUBU:   UnimplementedOp("SUBU"); break;
          case OP_MULT:   UnimplementedOp("MULT"); break;
          case OP_MULTU:  UnimplementedOp("MULTU"); break;
          case OP_DIV:    UnimplementedOp("DIV"); break;
          case OP_DIVU:   UnimplementedOp("DIVU"); break;
          case OP_MFHI:   UnimplementedOp("MFHI"); break;
          case OP_MTHI:   UnimplementedOp("MTHI"); break;
          case OP_MFLO:   UnimplementedOp("MFLO"); break;
          case OP_MTLO:   UnimplementedOp("MTLO"); break;
          case OP_AND:    UnimplementedOp("AND"); break;
          case OP_NOR:    UnimplementedOp("NOR"); break;
          case OP_XOR:    UnimplementedOp("XOR"); break;
          case OP_OR:     UnimplementedOp("OR"); break;
          case OP_JALR:   UnimplementedOp("JALR"); break;
          case OP_JR:     UnimplementedOp("JR"); break;
          case OP_SLT:    UnimplementedOp("SLT"); break;
          case OP_SLTU:   UnimplementedOp("SLTU"); break;
          case OP_SLL:    UnimplementedOp("SLL"); break;
          case OP_SRL:    UnimplementedOp("SRL"); break;
          case OP_SRA:    UnimplementedOp("SRA"); break;
        }
      }
    // all other functions
    case OP_JP:        UnimplementedOp("JP"); break;
    case OP_JAL:       UnimplementedOp("JAL"); break;
    case SP_SLTI:      UnimplementedOp("SLTI"); break;
    case SP_SLTIU:     UnimplementedOp("SLTIU"); break;
    case SP_ANDI:      UnimplementedOp("ANDI"); break;
    case SP_ORI:       UnimplementedOp("ORI"); break;
    case SP_BEQ:       UnimplementedOp("BEQ"); break;
    case SP_BNE:       UnimplementedOp("BNE"); break;
    case SP_BLEZ:      UnimplementedOp("BLEZ"); break;
    case SP_BGTZ:      UnimplementedOp("BGTZ"); break;
    case SP_ADDI:      UnimplementedOp("ADDI"); break;
    case SP_ADDIU:     UnimplementedOp("ADDIU"); break;
    case SP_LUI:       UnimplementedOp("LUI"); break;
    case SP_SW:        UnimplementedOp("SW"); break;
    case SP_LB:        UnimplementedOp("LB"); break;
    case SP_LW:        UnimplementedOp("LW"); break;
    case SP_LBU:       UnimplementedOp("LBU"); break;
    case SP_LHU:       UnimplementedOp("LHU"); break;
    case SP_SB:        UnimplementedOp("SB"); break;
    case SP_SH:        UnimplementedOp("SH"); break;
    case OP_MFC0:      UnimplementedOp("MFC0"); break;
    }
  }
}

void CPU::Fetch(){
  SetInstruction( ReadWord( GetPC() ) );
}

void CPU::Decode(){
  using namespace instruction;
  // decodes the arguments 
  m_args.rs     = GetRs(GetInstruction());
  m_args.rt     = GetRt(GetInstruction());
  m_args.rd     = GetRd(GetInstruction());
  m_args.shamt  = GetShamt(GetInstruction());
  m_args.imm    = GetImm(GetInstruction());
}

// Exception testers

bool CPU::arithmeticOverflow(std::uint32_t val1, std::uint32_t val2) const{
  std::uint32_t result = val1 + val2;
  bool overflowLow = (std::int32_t)val1 > 0 && (std::int32_t)val2 > 0 
    && result < 0;
  bool overflowHigh = (std::int32_t)val1 < 0 && (std::int32_t)val2 < 0 
    && result > 0;
  std::bitset<32> bitpattern = result;
  std::cout << result << '|' << bitpattern << '\n';
  return (overflowLow || overflowHigh)? true: false;
}

// Exception triggers

void CPU::triggerOVF(){
  // TODO: Research to implement OVF
  std::cout << "AN OVERFLOW HAS OCCURED" << '\n';
  throw std::runtime_error{"ERROR :: OVF Exception not implemented"};
}

// CPU opcodes functions

// ADDS - Must test the signedness of the operands
void CPU::ADD(std::int8_t rd, std::int8_t rs, std::int8_t rt){
  // Mnemonic: ADD rd, rs, rt
  // rs, rt are treated as signed integers, integer overflow may occur
  if(arithmeticOverflow(Register(rs), Register(rt))){
    triggerOVF();
  }
  else{
    Register(rd) = Register(rs) + Register(rt);
  }
}

void CPU::ADDI(std::int8_t rt, std::int8_t rs, std::int16_t imm){
  // mnemonic: ADDI rt, rs, imm
  // rs is a 32 bit register, imm is a 16 bit, so need sign extension
  if(arithmeticOverflow(Register(rs), imm)){
    triggerOVF();
  }
  else{
    Register(rt) = Register(rs) + imm;
  }
}

void CPU::ADDIU(std::uint8_t rt, std::uint8_t rs, std::uint16_t imm){
  Register(rt) = Register(rs) + imm;
}

void CPU::ADDU(std::uint8_t rd, std::uint8_t rs, std::uint8_t rt){
  // signedness doesn't matter in arithmetric
  Register(rd) = Register(rs) + Register(rt);
}

// Mulitplication Division

void CPU::DIV(std::uint8_t rs, std::uint8_t rt){
  // An attempt to read LO or HI before the results are written will wait 
  // (interlock) until the results are ready.
  // Asynchronous execution does not affect the program result, but offers an 
  // opportunity for performance improvement by scheduling the divide so that 
  // other instructions canexecute in parallel.
  // (LO, HI) = rs/rt
  Lo() = rs / rt;
  Hi() = rs % rt;
}

void CPU::DIVU(std::uint8_t rs, std::uint8_t rt){
  // BE WARY OF SIGN ISSUES!!!!
  Lo() = rs / rt;
  Hi() = rs % rt;
}


// Logical 

void CPU::AND(std::uint8_t rs, std::uint8_t rt, std::uint8_t rd){
  Register(rs) = Register(rt) & Register(rd);
}

void CPU::ANDI(std::uint8_t rs, std::uint8_t rt, std::uint16_t imm){
  // the docs says it's zero extension so I assume immediate is a 16-bit unsigned
  Register(rs) = Register(rt) & imm;
}

} // namespace processor

} // namespace psxjun
