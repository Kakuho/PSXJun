#include "opcodetable.hpp"
#include <stdexcept>

namespace Jun{

OpcodeTable::OpcodeTable(){
  PopulateOpcodes();
}

void OpcodeTable::PopulateOpcodes(){
  PopulateIInstr();
  PopulateJInstr();
  PopulateRInstr();
}

const OpcodeTable::OpcodeEntry& OpcodeTable::operator[](std::uint8_t opcode) const{ 
  if(opcode == 0){
    throw std::runtime_error{"OpcodeTable cannot be indexed by 0"};
  }
  else{
    return m_opcodes.at(opcode);
  }
}

const OpcodeTable::OpcodeEntry& OpcodeTable::RInstr(std::uint8_t functs) const{
  try{
    return m_rinstrs.at(functs);
  }
  catch(std::out_of_range& e){
    throw std::runtime_error{"OpcodeTable Reg not found"};
  }
}

// Instruction Population Code ... Quite Messy

void OpcodeTable::PopulateIInstr(){
  m_opcodes[0x08] = 
  {.opcode = 0x08, .toString = "addi", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x09] = 
  {.opcode = 0x09, .toString = "addiu", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x0c] = 
  {.opcode = 0x09, .toString = "andi", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x04] = 
  {.opcode = 0x04, .toString = "beq", .type = InstrType::Imm, .dummy = 0};
  
  m_opcodes[0x06] = 
  {.opcode = 0x06, .toString = "blez", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x05] = 
  {.opcode = 0x05, .toString = "bne", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x07] = 
  {.opcode = 0x07, .toString = "bgtz", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x20] = 
  {.opcode = 0x20, .toString = "lb", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x24] = 
  {.opcode = 0x24, .toString = "lbu", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x25] = 
  {.opcode = 0x25, .toString = "lhu", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x0f] = 
  {.opcode = 0x0f, .toString = "lui", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x23] = 
  {.opcode = 0x23, .toString = "lw", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x0d] = 
  {.opcode = 0x0d, .toString = "ori", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x28] = 
  {.opcode = 0x28, .toString = "sb", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x29] = 
  {.opcode = 0x29, .toString = "sh", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x0a] = 
  {.opcode = 0x0a, .toString = "slti", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x0b] = 
  {.opcode = 0x0b, .toString = "sltiu", .type = InstrType::Imm, .dummy = 0};

  m_opcodes[0x2b] = 
  {.opcode = 0x2b, .toString = "sw", .type = InstrType::Imm, .dummy = 0};
}

void OpcodeTable::PopulateJInstr(){
  m_opcodes[0x02] = 
  {.opcode = 0x02, .toString = "j", .type = InstrType::Jump, .dummy = 0};

  m_opcodes[0x03] = 
  {.opcode = 0x03, .toString = "jal", .type = InstrType::Jump, .dummy = 0};
}

void OpcodeTable::PopulateRInstr(){
  m_rinstrs[0x00] = 
  {.opcode = 0x00, .toString = "sll", .type = InstrType::Reg, .funct = 0x00};

  m_rinstrs[0x1a] = 
  {.opcode = 0x00, .toString = "div", .type = InstrType::Reg, .funct = 0x1a};

  m_rinstrs[0x1b] = 
  {.opcode = 0x00, .toString = "divu", .type = InstrType::Reg, .funct = 0x1b};

  m_rinstrs[0x02] = 
  {.opcode = 0x00, .toString = "srl", .type = InstrType::Reg, .funct = 0x02};

  m_rinstrs[0x2a] = 
  {.opcode = 0x00, .toString = "slt", .type = InstrType::Reg, .funct = 0x2a};

  m_rinstrs[0x2b] = 
  {.opcode = 0x00, .toString = "sltu", .type = InstrType::Reg, .funct = 0x2b};

  m_rinstrs[0x03] = 
  {.opcode = 0x00, .toString = "sra", .type = InstrType::Reg, .funct = 0x03};

  m_rinstrs[0x08] = 
  {.opcode = 0x00, .toString = "jr", .type = InstrType::Reg, .funct = 0x08};

  m_rinstrs[0x09] = 
  {.opcode = 0x00, .toString = "jalr", .type = InstrType::Reg, .funct = 0x09};

  m_rinstrs[0x10] = 
  {.opcode = 0x00, .toString = "mfhi", .type = InstrType::Reg, .funct = 0x10};

  m_rinstrs[0x11] = 
  {.opcode = 0x00, .toString = "mthi", .type = InstrType::Reg, .funct = 0x11};

  m_rinstrs[0x12] = 
  {.opcode = 0x00, .toString = "mflo", .type = InstrType::Reg, .funct = 0x12};

  m_rinstrs[0x13] = 
  {.opcode = 0x00, .toString = "mtlo", .type = InstrType::Reg, .funct = 0x13};

  m_rinstrs[0x18] = 
  {.opcode = 0x00, .toString = "mult", .type = InstrType::Reg, .funct = 0x18};
  
  m_rinstrs[0x19] = 
  {.opcode = 0x00, .toString = "multu", .type = InstrType::Reg, .funct = 0x19};

  m_rinstrs[0x20] = 
  {.opcode = 0x00, .toString = "add", .type = InstrType::Reg, .funct = 0x20};

  m_rinstrs[0x21] = 
  {.opcode = 0x00, .toString = "addu", .type = InstrType::Reg, .funct = 0x21};

  m_rinstrs[0x22] = 
  {.opcode = 0x00, .toString = "sub", .type = InstrType::Reg, .funct = 0x22};

  m_rinstrs[0x23] = 
  {.opcode = 0x00, .toString = "subu", .type = InstrType::Reg, .funct = 0x23};

  m_rinstrs[0x24] = 
  {.opcode = 0x00, .toString = "and", .type = InstrType::Reg, .funct = 0x24};

  m_rinstrs[0x25] = 
  {.opcode = 0x00, .toString = "or", .type = InstrType::Reg, .funct = 0x25};

  m_rinstrs[0x26] = 
  {.opcode = 0x00, .toString = "xor", .type = InstrType::Reg, .funct = 0x26};

  m_rinstrs[0x27] = 
  {.opcode = 0x00, .toString = "nor", .type = InstrType::Reg, .funct = 0x27};
}

} // namespace Jun
