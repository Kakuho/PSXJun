#include "cpu.hpp"
#include "instruction.hpp"
#include <cstddef>
#include <cstdint>
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
  // I would rather do endian here
  // byte_x where x \in [1,4] denotes the bytes in memory order
  std::uint8_t byte_1 = ReadByte(index);
  std::uint8_t byte_2 = ReadByte(index+1);
  std::uint8_t byte_3 = ReadByte(index+2);
  std::uint8_t byte_4 = ReadByte(index+3);
  // the cpu is little endian, thus:
  // byte_1, byte_2, byte_3, byte_4 in memory order becomes
  // [byte_4][byte_3][byte_2][byte_1] as a formed word
  std::uint32_t word = 0;
  word |= byte_4; 
  word = word << 8;
  word |= byte_3; 
  word = word << 8;
  word |= byte_2; 
  word  = word << 8;
  word |= byte_1; 
  return word;
}

void CPU::WriteByte(std::size_t index, std::uint8_t val){
  m_sysbus->WriteByte(index, val);
}

void CPU::WriteWord(std::size_t index, std::uint32_t val){
  m_sysbus->WriteWord(index, val);
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
  Fetch();
  std::cout << "tick = " << std::dec << m_ticks << '\n' << std::hex
            << "pc = " << (unsigned)GetPC() << '\n'
            << "instruction: " << std::hex << std::setw(8) << std::setfill('0') << m_ibuffer << '\n'
            << std::bitset<32>{m_ibuffer} << '\n';
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
        case OP_SLL:    SLL<true>(m_args.rs, m_args.rd, m_args.shamt); break;
        case OP_SRL:    UnimplementedOp("SRL"); break;
        case OP_SRA:    UnimplementedOp("SRA"); break;
      }
      break;
    }
    // all other functions
    case OP_J:        J<true>(); break;
    case OP_JAL:      UnimplementedOp("JAL"); break;
    case SP_SLTI:     UnimplementedOp("SLTI"); break;
    case SP_SLTIU:    UnimplementedOp("SLTIU"); break;
    case SP_ANDI:     UnimplementedOp("ANDI"); break;
    case SP_ORI:      ORI<true>(m_args.rs, m_args.rt, m_args.imm); break;
    case SP_BEQ:      BEQ<true>(m_args.rs, m_args.rt, m_args.imm); break;
    case SP_BNE:      BNE<true>(m_args.rs, m_args.rt, m_args.imm); break;
    case SP_BLEZ:     UnimplementedOp("BLEZ"); break;
    case SP_BGTZ:     UnimplementedOp("BGTZ"); break;
    case SP_ADDI:     ADDI<true>(m_args.rt, m_args.rs, m_args.imm); break;
    case SP_ADDIU:    ADDIU<true>(m_args.rs, m_args.rt, m_args.imm); break;
    case SP_LUI:      LUI<true>(m_args.rt, m_args.imm); break;
    case SP_SW:       SW<true>(m_args.rs, m_args.rt, m_args.imm); break;
    case SP_LB:       UnimplementedOp("LB"); break;
    case SP_LW:       LW<true>(m_args.rs, m_args.rt, m_args.imm); break;
    case SP_LBU:      UnimplementedOp("LBU"); break;
    case SP_LHU:      UnimplementedOp("LHU"); break;
    case SP_SB:       UnimplementedOp("SB"); break;
    case SP_SH:       UnimplementedOp("SH"); break;
    // coprocessor instructions
    case SELECT_COP0:{
      switch(m_args.funct){
      case 0x00:
        switch(m_args.rs){
          case OP_MFC0_HEAD: UnimplementedOp("MFC0"); break;
          case OP_MTC0_HEAD: MTC0<true>(m_args.rt, m_args.rd); break;
        }
        break;
      }
    } 
    break;
    case SELECT_COP2:{
    }
    break;
  }
  std::cout << "------------------------------------------------\n";
  m_ticks++;
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

// note signed integers are represented as 32bit two's complement.
// overflow may only occur:
//  1) if we add 2 +ves, and we get a -ve
//  2) if we subtract 2 -ves, and we get a +ve

bool CPU::signed_sub_overflow(std::uint32_t val1, std::uint32_t val2) const{
  std::uint32_t result = val1 + val2;
  bool is_overflow = ((std::int32_t)val1 < 0) && ((std::int32_t)val2 < 0)
    && (result > 0);
  std::bitset<32> bitpattern = result;
  std::cout << result << '|' << bitpattern << '\n';
  return is_overflow? true: false;
}

bool CPU::signed_add_overflow(std::uint32_t val1, std::uint32_t val2) const{
  std::uint32_t result = val1 + val2;
  bool is_overflow = ((std::int32_t)val1 > 0) && ((std::int32_t)val2 > 0)
    && (result < 0);
  std::bitset<32> bitpattern = result;
  std::cout << result << '|' << bitpattern << '\n';
  return is_overflow? true: false;
}

// Exception triggers

void CPU::trigger_overflow_ex(){
  // TODO: Research to implement OVF
  std::cout << "AN OVERFLOW HAS OCCURED" << '\n';
  throw std::runtime_error{"ERROR :: Overflow Exception not implemented"};
}

void CPU::trigger_addressLoad_ex(){
  std::cout << "AN ADDRESS LOAD ERROR HAS OCCURED" << '\n';
  throw std::runtime_error{"ERROR :: address load Exception not implemented"};
}

void CPU::trigger_addressStore_ex(){
  std::cout << "AN ADDRESS STORE ERROR HAS OCCURED" << '\n';
  throw std::runtime_error{"ERROR :: address store Exception not implemented"};
}


// CPU opcodes functions

// ALU

// ADDS - Must test the signedness of the operands

void CPU::ADD(std::int8_t rd, std::int8_t rs, std::int8_t rt){
  // Mnemonic: ADD rd, rs, rt
  // rs, rt are treated as signed integers, integer overflow may occur
  if(signed_add_overflow(Register(rs), Register(rt))){
    trigger_overflow_ex();
  }
  else{
    Register(rd) = Register(rs) + Register(rt);
  }
}

template<bool logging>
void CPU::ADDI(std::int8_t rt, std::int8_t rs, std::int16_t imm){
  std::uint32_t result = Register(rs) + signextend32(imm);
  if(logging){
    std::cout << "Input: ADDI rt, rs, imm" << "\n"
              << "rs = " <<  (unsigned)rs << ", gpr[rs] = " <<  (unsigned)Register(rs) << '\n'
              << "rt = " <<  (unsigned)rt << ", gpr[rt] = " <<  (unsigned)Register(rt) << '\n'
              << "imm = " <<  (unsigned)imm << '\n'
              << "Calculation: val = signextend32(imm) + gpr[rs], gpr[rt] = val" << '\n'
              << "signextend32(imm) = " << signextend32(imm) << '\n'
              << "val = " <<  result << '\n';
  }
  if(signed_add_overflow(Register(rs), signextend32(imm))){
    if(logging) std::cout << "Output: add overflow occured, no modification" << '\n';
    trigger_overflow_ex();
  }
  else{
    if(logging) std::cout << "Output: gpr[" << (unsigned)Register(rt) << "] = " << result << '\n';
    Register(rt) = result;
    PC() += 4;
  }
}

template<bool logging>
void CPU::ADDIU(std::uint8_t rs, std::uint8_t rt, std::uint16_t imm){
  PC() = PC() + 4;
  std::uint32_t result = Register(rs) + signextend32(imm);
  if(logging){
    std::cout << "Input: ADDIU rt, rs, imm | asm = " 
              << (unsigned)instruction::GetOpcode(m_ibuffer) 
              << "\n"
              << "rs = " <<  (unsigned)rs << ", gpr[rs] = " <<  (unsigned)Register(rs) << '\n'
              << "rt = " <<  (unsigned)rt << ", gpr[rt] = " <<  (unsigned)Register(rt) << '\n'
              << "imm = " <<  (unsigned)imm << '\n'
              << "Calculation: val = signextend32(imm) + gpr[rs], gpr[rt] = val" << '\n'
              << "signextend32(imm) = " << signextend32(imm) << '\n'
              << "val = " <<  result << '\n'
              << "Output: gpr[" << (unsigned)rt << "] = " << result << '\n';
  }

  Register(rt) = result;
}

void CPU::ADDU(std::uint8_t rd, std::uint8_t rs, std::uint8_t rt){
  // signedness doesn't matter in arithmetric
  Register(rd) = Register(rs) + Register(rt);
}

template<bool logging>
void CPU::SLL(std::int8_t rt,  std::int8_t rd, std::int8_t sa){
  PC() = PC() + 4;
  std::uint32_t result = Register(rt) << sa;
  if(logging){
    std::cout << "Input: SLL rs, rt, sa" << "\n"
              << "rt = " <<  (unsigned)rt << ", gpr[rt] = " <<  (unsigned)Register(rt) << '\n'
              << "rd = " <<  (unsigned)rd << ", gpr[rd] = " <<  (unsigned)Register(rd) << '\n'
              << "sa = " <<  (unsigned)sa << '\n'
              << "Calculations: gpr[rd] = gpr[rt] << sa" << '\n'
              << "gpr[rt] << sa  = " << result << '\n'
              << "Output: gpr[" << (unsigned)rd << "] = " << result << '\n';
  }
  Register(rd) = result;
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


template<bool logging>
void CPU::ORI(std::uint8_t rs, std::uint8_t rt, std::uint16_t imm){
  std::uint32_t val = Register(rs) | imm;
  if(logging){
    std::cout << "Input: ORI rs, rt, imm | asm = " 
              << (unsigned)instruction::GetOpcode(m_ibuffer) 
              << "\n"
              << "rs = " <<  (unsigned)rs << ", gpr[rs] = " <<  (unsigned)Register(rs) << '\n'
              << "rt = " <<  (unsigned)rt << ", gpr[rt] = " <<  (unsigned)Register(rt) << '\n'
              << "imm = " << imm << '\n'
              << "Calculation: rt = gpr[rs] | imm zero>> 16" << '\n'
              << "imm zero>> 16 = " << std::setw(8) << std::setfill('0') <<  imm << '\n'
              << "gpr[rs] | imm zero>> 16 = " << (unsigned)val << '\n'
              << "Output: gpr[" << (unsigned)rt << "] = " << (unsigned)val << '\n';
  }
  Register(rs) = val;
  PC() = PC() + 4;
}

// Load and Store

template<bool logging>
void CPU::LUI(std::uint8_t rt, std::uint16_t imm){
  std::uint32_t val = imm << 16;
  PC() = PC() + 4;
  if(logging == true){
    std::cout << "Input: LUI rt, imm | asm = " 
              <<  (unsigned)instruction::GetOpcode(m_ibuffer) << '\n'
              << "rt = " <<  (unsigned)rt << ", gpr[rt]  = " << (unsigned)Register(rt) << '\n'
              << "imm = " << imm << '\n'
              << "Calculation: gpr[rt] = imm << 16" << '\n'
              << "imm << 16 = " << (unsigned)val << '\n'
              << "Output: gpr[" << (unsigned)rt << "] = " << (unsigned)val << '\n';
  }
  Register(rt) = val;
}

template<bool logging>
void CPU::SW(std::uint8_t base, std::uint8_t rt, std::uint16_t offset){
  // store word
  // Do i need to implement Cache??
  std::uint32_t offset_ext = signextend32(offset);
  std::uint32_t vaddr = Register(base) + static_cast<int>(offset_ext);
  PC() = PC() + 4;
  if(logging == true){
    std::cout << std::hex
              << "Input: SW rt, offset(base)" << '\n'
              << "base = " <<  (unsigned)base 
              << ", gpr[base] = " << (unsigned)Register(base) << '\n'
              << "rt = " << (unsigned)rt << ", gpr[rt] = " << (unsigned)Register(rt) << '\n'
              << "offset = " << (unsigned)offset << '\n'
              << "Calculation: vaddr = gpr[base] + signextend32(offset), "
              << "RAM[vaddr] = gpr[rt]" <<'\n' 
              << "vaddr = " << vaddr << '\n';
  }
  // word boundary exception. Boundaries must be a multiple of 4, 
  if(vaddr & 0x3){
    if(logging == true) std::cout << "Output: Address Store Exception" << '\n';
    trigger_addressStore_ex();
  }
  if(m_cop0.GetStatus(status::IsC)){
    if(logging == true)
      std::cout << "Output: Cache isolation" << '\n';
    // this is for cache isolation - i.e, the writes is not back to memory, but 
    // onto the cache
  }
  if(logging == true)
    std::cout << "Output: RAM[" << vaddr << "] = gpr[" << (unsigned)rt << "] = " 
              << (unsigned)Register(rt) << '\n';
  WriteWord(vaddr, Register(rt));

}


template<bool logging>
void CPU::LW(std::uint8_t base, std::uint8_t rt, std::uint16_t offset){
  std::uint32_t offset_ext = signextend32(offset);
  std::uint32_t vaddr = Register(base) + static_cast<int>(offset_ext);
  if(logging == true){
    std::cout << std::hex
              << "Input: LW rt, offset(base)" << '\n'
              << "base = " <<  (unsigned)base 
              << ", gpr[base] = " << (unsigned)Register(base) << '\n'
              << "rt = " << (unsigned)rt << ", gpr[rt] = " << (unsigned)Register(rt) << '\n'
              << "offset = " << (unsigned)offset << '\n'
              << "Calculation: vaddr = gpr[base] + signextend32(offset), "
              << "gpr[rt] = RAM[vaddr]" <<'\n' 
              << "vaddr = " << vaddr << '\n'
              << "RAM[vaddr] = " << (unsigned)ReadWord(vaddr) << '\n';
  }
  // word boundary exception. Boundaries must be a multiple of 4, 
  if(vaddr & 0x3){
    if(logging == true) std::cout << "Output: Address Store Exception" << '\n';
    trigger_addressStore_ex();
  }
  if(m_cop0.GetStatus(status::IsC)){
    if(logging == true)
      std::cout << "Output: Cache isolation" << '\n';
    // this is for cache isolation - i.e, the writes is not back to memory, but 
    // onto the cache
  }
  if(logging == true)
    std::cout << "Output: gpr[" << (unsigned)rt << "] = RAM[" << vaddr << "] = "
              << (unsigned)ReadWord(vaddr) << '\n';
  Register(rt) = ReadWord(vaddr);
  PC() = PC() + 4;
}

// jumps

template<bool logging>
void CPU::J(){
  // TODO: Implement logging
  // the branch delay slots occurs first and then we jump
  // first form the address to jump to
  std::uint32_t imm = instruction::GetAddr(m_ibuffer);
  // delay slot is the instruction in the immediate next of the J instruction
  std::uint32_t addr = ((PC() + 4) & (0b1111u << 28)) | (imm << 2);
  if(logging){
    std::cout << "Input: J target" << '\n' 
              << "target = " << imm << '\n'
              << "Computation: vaddr = (PC() + 4)_{31...28}  | target << 2" << '\n'
              << "vaddr = " << addr << '\n'
              << "-----------------------------\n";
  }
  // I increment PC(), tick, and then proceed to handle op JP:
  std::cout << "BRANCH DELAY TIME!!!!\n"

            << "-----------------------------\n";
  PC() += 4;
  Tick();
  // now we finish handling J
  PC() = addr;
  if(logging){
    std::cout << "Output of J: pc = " << PC() << '\n';
  }
}

// Branching

template <bool logging>
void CPU::BEQ(std::uint8_t rs, std::uint8_t rt, std::uint16_t offset){
  if(logging == true){
    std::cout << "rs = " << (unsigned)rs << ", rt = " << (unsigned)rt 
              << ", offset = " << offset << '\n';
  }

  std::int16_t realoffset = offset;
  if(Register(rs) == Register(rt)){
    PC() = PC() + 1 + realoffset;
    std::cout << "BEQ DELAY OP" << '\n';
  }
}

template <bool logging>
void CPU::BNE(std::uint8_t rs, std::uint8_t rt, std::uint16_t offset){
  std::uint32_t vaddr = (PC()+4) + static_cast<int>(signextend32(offset << 2));
  if(logging == true){
    std::cout << std::hex
              << "Input: BNE rs, rt, offset" << '\n'
              << "rs = " <<  (unsigned)rs 
              << ", gpr[rs] = " << (unsigned)Register(rs) << '\n'
              << "rt = " << (unsigned)rt << ", gpr[rt] = " << (unsigned)Register(rt) << '\n'
              << "offset = " << (unsigned)offset << '\n'
              << "Calculation: vaddr = NEXTPC + signextend32(offset << 2), "
              << "if gpr[rs] != gpr[rt], branch to vaddr with delay" <<'\n' 
              << "NEXTPC = " << PC() + 4 << '\n'
              << "offset << 2 = " << (unsigned)(offset << 2) << '\n'
              << "signextend32(offset<<2) = " << signextend32(offset << 2) << '\n'
  /*TODO: -*/ << "integral signextend32(offset<<2) = " << (int)signextend32(offset << 2) << '\n'
              << "vaddr = " << vaddr << '\n';
  }

  if(Register(rs) != Register(rt)){
    if(logging){
      std::cout << "Output: gpr[rs] != gpr[rt], so we branch" << '\n' 
                << "-----------------------------\n"
                << "DELAY SLOT" << '\n'
                << "-----------------------------\n";
    }
    PC() = PC() + 4;
    Tick();
    // end of delay slot
    PC() = vaddr;
    if(logging) std::cout << "pc = " << (unsigned)vaddr << '\n';
  }
  else{
    if(logging) std::cout << "Output: gpr[rs] == gpr[rt], so no branch\n";
    PC() = PC() + 4;
  }
}

// Coprocessor

template<bool logging>
void CPU::MTC0(std::uint8_t rt, std::uint8_t rd){
  if(logging == true){
    std::cout << std::hex
              << "Input: MTC0 rt, rd" << '\n'
              << "rt = " <<  (unsigned)rt
              << ", gpr[rt] = " << (unsigned)Register(rt) << '\n'
              << "rd = " << (unsigned)rd << ", gpr[rd] = " << (unsigned)Register(rd) << '\n'
              << "Calculation: cop0.gpr[rd] = gpr[rt]" <<'\n'
              << "Output: cop0.gpr[rd] = " << (unsigned)Register(rt) << '\n';
  }
  m_cop0.Register(rd) = Register(rt);
  PC() += 4;
}

void CPU::dumpState() const{

}

} // namespace processor

} // namespace psxjun
