#include "cpu.hpp"
#include "instruction.hpp"

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
  // first check if there are any buffered ticks
  if( GetTicks() ){
    return;
  }
  else{
    Fetch();
    std::uint8_t opcode = Instruction::GetOpcode(GetInstruction());  // decode step
    Decode();
    // execute step
    switch(opcode){
      case 0:{ // R-type instruction
        switch(m_args.funct){
          case Instruction::OP_ADD:    ADD(m_args.rd, m_args.rs, m_args.rt); break;
          case Instruction::OP_ADDU:   ADDU(m_args.rd, m_args.rs, m_args.rt); break;
          case Instruction::OP_SUB:    UnimplementedOp(); break;
          case Instruction::OP_SUBU:   UnimplementedOp(); break;
          case Instruction::OP_MULT:   UnimplementedOp(); break;
          case Instruction::OP_MULTU:  UnimplementedOp(); break;
          case Instruction::OP_DIV:    UnimplementedOp(); break;
          case Instruction::OP_DIVU:   UnimplementedOp(); break;
          case Instruction::OP_MFHI:   UnimplementedOp(); break;
          case Instruction::OP_MTHI:   UnimplementedOp(); break;
          case Instruction::OP_MFLO:   UnimplementedOp(); break;
          case Instruction::OP_MTLO:   UnimplementedOp(); break;
          case Instruction::OP_AND:    UnimplementedOp(); break;
          case Instruction::OP_NOR:    UnimplementedOp(); break;
          case Instruction::OP_XOR:    UnimplementedOp(); break;
          case Instruction::OP_OR:     UnimplementedOp(); break;
          case Instruction::OP_JALR:   UnimplementedOp(); break;
          case Instruction::OP_JR:     UnimplementedOp(); break;
          case Instruction::OP_SLT:    UnimplementedOp(); break;
          case Instruction::OP_SLTU:   UnimplementedOp(); break;
          case Instruction::OP_SLL:    UnimplementedOp(); break;
          case Instruction::OP_SRL:    UnimplementedOp(); break;
          case Instruction::OP_SRA:    UnimplementedOp(); break;
        }
      }
    // all other functions
    case Instruction::OP_JP:        UnimplementedOp(); break;
    case Instruction::OP_JAL:       UnimplementedOp(); break;
    case Instruction::SP_SLTI:      UnimplementedOp(); break;
    case Instruction::SP_SLTIU:     UnimplementedOp(); break;
    case Instruction::SP_ANDI:      UnimplementedOp(); break;
    case Instruction::SP_ORI:       UnimplementedOp(); break;
    case Instruction::SP_BEQ:       UnimplementedOp(); break;
    case Instruction::SP_BNE:       UnimplementedOp(); break;
    case Instruction::SP_BLEZ:      UnimplementedOp(); break;
    case Instruction::SP_BGTZ:      UnimplementedOp(); break;
    case Instruction::SP_ADDI:      UnimplementedOp(); break;
    case Instruction::SP_ADDIU:     UnimplementedOp(); break;
    case Instruction::SP_LUI:       UnimplementedOp(); break;
    case Instruction::SP_SW:        UnimplementedOp(); break;
    case Instruction::SP_LB:        UnimplementedOp(); break;
    case Instruction::SP_LW:        UnimplementedOp(); break;
    case Instruction::SP_LBU:       UnimplementedOp(); break;
    case Instruction::SP_LHU:       UnimplementedOp(); break;
    case Instruction::SP_SB:        UnimplementedOp(); break;
    case Instruction::SP_SH:        UnimplementedOp(); break;
    case Instruction::OP_MFC0:      UnimplementedOp(); break;
    }
  }
}

void CPU::Fetch(){
  SetInstruction( ReadWord( GetPC() ) );
}

void CPU::Decode(){
  // decodes the arguments 
  m_args.rs = Instruction::GetRs(GetInstruction());
  m_args.rt = Instruction::GetRt(GetInstruction());
  m_args.rd = Instruction::GetRd(GetInstruction());
  m_args.shamt = Instruction::GetShamt(GetInstruction());
  m_args.imm = Instruction::GetImm(GetInstruction());
}

// CPU opcodes functions

// ADDS - Must test the signedness of the operands

void CPU::ADD(std::int8_t rd, std::int8_t rs, std::int8_t rt){
  // rs, rt are treated as signed integers
  Register(rd) = Register(rs) + Register(rt);
}

void CPU::ADDI(std::int8_t rt, std::int8_t rs, std::int16_t imm){
  // rs, imm are treated as signed integers
  Register(rt) = Register(rs) + imm;
}

void CPU::ADDIU(std::uint8_t rt, std::uint8_t rs, std::uint16_t imm){
  Register(rt) = Register(rs) + imm;
}

void CPU::ADDU(std::uint8_t rd, std::uint8_t rs, std::uint8_t rt){
  Register(rd) = Register(rs) + Register(rt);
}
