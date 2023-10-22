#include "cpu.hpp"
#include "instruction.hpp"

namespace psxjun{

namespace processor{

// Registers

std::uint32_t CPU::GetRegisterValue(std::uint8_t index) const{
  if(index == 0){
    // zeroth register is hardwired to 0
    return 0;
  }
  else if (index <= 32){
    return m_registers[index];
  }
  else{
    /* TODO: should throw an out of bounds exception */
    std::cerr << "ERROR :: INDEX IS OUT OF BOUNDS" << '\n';
  }
}

// Memory getters

std::uint8_t CPU::ReadByte(std::size_t index) const{
  /* TODO: wrapping around the address space*/
  return m_ram[index];
}

std::uint16_t CPU::GetHalfWord(std::size_t index1, std::size_t index2, 
                               std::size_t index3, std::size_t index4) const{
  /* TODO   : wrapping around the address space */
  // Assumes: fetching bytes in the order M[index1], M[index2], M[index3], M[index4]
  std::uint8_t byte1 = ReadByte(index1);
  // R3000A is little endian, so the half word would be M[index4], M[index3], M[index2], M[index1].
}

std::uint32_t CPU::ReadWord(std::size_t index) const{
  return 0;
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

    std::uint8_t opcode = instruction::GetOpcode(GetInstruction());  // decode step
    Decode();
    // execute step
    switch(opcode){
      case 0:{ // R-type instruction
        switch(m_args.funct){
          case OP_ADD:    ADD(m_args.rd, m_args.rs, m_args.rt); break;
          case OP_ADDU:   ADDU(m_args.rd, m_args.rs, m_args.rt); break;
          case OP_SUB:    UnimplementedOp(); break;
          case OP_SUBU:   UnimplementedOp(); break;
          case OP_MULT:   UnimplementedOp(); break;
          case OP_MULTU:  UnimplementedOp(); break;
          case OP_DIV:    UnimplementedOp(); break;
          case OP_DIVU:   UnimplementedOp(); break;
          case OP_MFHI:   UnimplementedOp(); break;
          case OP_MTHI:   UnimplementedOp(); break;
          case OP_MFLO:   UnimplementedOp(); break;
          case OP_MTLO:   UnimplementedOp(); break;
          case OP_AND:    UnimplementedOp(); break;
          case OP_NOR:    UnimplementedOp(); break;
          case OP_XOR:    UnimplementedOp(); break;
          case OP_OR:     UnimplementedOp(); break;
          case OP_JALR:   UnimplementedOp(); break;
          case OP_JR:     UnimplementedOp(); break;
          case OP_SLT:    UnimplementedOp(); break;
          case OP_SLTU:   UnimplementedOp(); break;
          case OP_SLL:    UnimplementedOp(); break;
          case OP_SRL:    UnimplementedOp(); break;
          case OP_SRA:    UnimplementedOp(); break;
        }
      }
    // all other functions
    case OP_JP:        UnimplementedOp(); break;
    case OP_JAL:       UnimplementedOp(); break;
    case SP_SLTI:      UnimplementedOp(); break;
    case SP_SLTIU:     UnimplementedOp(); break;
    case SP_ANDI:      UnimplementedOp(); break;
    case SP_ORI:       UnimplementedOp(); break;
    case SP_BEQ:       UnimplementedOp(); break;
    case SP_BNE:       UnimplementedOp(); break;
    case SP_BLEZ:      UnimplementedOp(); break;
    case SP_BGTZ:      UnimplementedOp(); break;
    case SP_ADDI:      UnimplementedOp(); break;
    case SP_ADDIU:     UnimplementedOp(); break;
    case SP_LUI:       UnimplementedOp(); break;
    case SP_SW:        UnimplementedOp(); break;
    case SP_LB:        UnimplementedOp(); break;
    case SP_LW:        UnimplementedOp(); break;
    case SP_LBU:       UnimplementedOp(); break;
    case SP_LHU:       UnimplementedOp(); break;
    case SP_SB:        UnimplementedOp(); break;
    case SP_SH:        UnimplementedOp(); break;
    case OP_MFC0:      UnimplementedOp(); break;
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

// CPU opcodes functions

// ADDS - Must test the signedness of the operands

void CPU::ADD(std::int8_t rd, std::int8_t rs, std::int8_t rt){
  // rs, rt are treated as signed integers
  // rd ← rs + rt
  std::int32_t val = Register(rs) + Register(rt);
  bool overflowLow = (std::int32_t)Register(rs) > 0 && (std::int32_t)Register(rt) > 0 && val < 0;
  bool overflowHigh = (std::int32_t)Register(rs) < 0 && (std::int32_t)Register(rt) < 0 && val > 0;
  //---------------------------------------------------------------//
  std::bitset<32> bitpattern = val;
  std::cout << val << '|' << bitpattern << '\n';
  //---------------------------------------------------------------//
  if(overflowLow || overflowHigh){
    // TODO: perform an integer overflow exception
    std::cout << "AN OVERFLOW HAS OCCURED" << '\n';
  }
  else{
    Register(rd) = val;
  }
}

void CPU::ADDI(std::int8_t rt, std::int8_t rs, std::int16_t imm){
  // rs, imm are treated as signed integers
  // signedness doesn't matter in arithmetric
  Register(rt) = Register(rs) + imm;
}

void CPU::ADDIU(std::uint8_t rt, std::uint8_t rs, std::uint16_t imm){
  // signedness doesn't matter in arithmetric
  Register(rt) = Register(rs) + imm;
}

void CPU::ADDU(std::uint8_t rd, std::uint8_t rs, std::uint8_t rt){
  // signedness doesn't matter in arithmetric
  Register(rd) = Register(rs) + Register(rt);
}

}

}
