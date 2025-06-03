#include "opcode_table.hpp"

namespace Debug{

OpcodeTable::OpcodeTable(){
  PopulateOpcodes();
}

void OpcodeTable::PopulateOpcodes(){
  PopulateImmediateTable();
  PopulateJumpTable();
  PopulateRegisterTable();
  PopulateBxxzTable();
}

// Instruction Population Code ... Quite Messy

void OpcodeTable::PopulateImmediateTable(){
  m_immediateTable[0x08] = {.opcode = 0x08, .toString = "addi",   .dummy = 0};

  m_immediateTable[0x09] = {.opcode = 0x09, .toString = "addiu",   .dummy = 0};

  m_immediateTable[0x0c] = {.opcode = 0x09, .toString = "andi",   .dummy = 0};

  m_immediateTable[0x04] = {.opcode = 0x04, .toString = "beq",   .dummy = 0};
  
  m_immediateTable[0x06] = {.opcode = 0x06, .toString = "blez",   .dummy = 0};

  m_immediateTable[0x05] = {.opcode = 0x05, .toString = "bne",   .dummy = 0};

  m_immediateTable[0x07] = {.opcode = 0x07, .toString = "bgtz",   .dummy = 0};

  m_immediateTable[0x20] = {.opcode = 0x20, .toString = "lb",   .dummy = 0};

  m_immediateTable[0x24] = {.opcode = 0x24, .toString = "lbu",   .dummy = 0};

  m_immediateTable[0x25] = {.opcode = 0x25, .toString = "lhu",   .dummy = 0};

  m_immediateTable[0x0f] = {.opcode = 0x0f, .toString = "lui",   .dummy = 0};

  m_immediateTable[0x23] = {.opcode = 0x23, .toString = "lw",   .dummy = 0};

  m_immediateTable[0x0d] = {.opcode = 0x0d, .toString = "ori",   .dummy = 0};

  m_immediateTable[0x28] = {.opcode = 0x28, .toString = "sb",   .dummy = 0};

  m_immediateTable[0x29] = {.opcode = 0x29, .toString = "sh",   .dummy = 0};

  m_immediateTable[0x0a] = {.opcode = 0x0a, .toString = "slti",   .dummy = 0};

  m_immediateTable[0x0b] = {.opcode = 0x0b, .toString = "sltiu",   .dummy = 0};

  m_immediateTable[0x2b] = {.opcode = 0x2b, .toString = "sw",   .dummy = 0};

}

void OpcodeTable::PopulateJumpTable(){
  m_jumpTable[0x02] = {.opcode = 0x02, .toString = "j",   .dummy = 0};
  m_jumpTable[0x03] = {.opcode = 0x03, .toString = "jal",   .dummy = 0};
}

void OpcodeTable::PopulateRegisterTable(){
  m_registerTable[0x00] = {.opcode = 0x00, .toString = "sll",   .funct = 0x00};

  m_registerTable[0x1a] = {.opcode = 0x1a, .toString = "div",   .funct = 0x1a};

  m_registerTable[0x1b] = {.opcode = 0x1b, .toString = "divu",   .funct = 0x1b};

  m_registerTable[0x02] = {.opcode = 0x02, .toString = "srl",   .funct = 0x02};

  m_registerTable[0x2a] = {.opcode = 0x2a, .toString = "slt",   .funct = 0x2a};

  m_registerTable[0x2b] = {.opcode = 0x2b, .toString = "sltu",   .funct = 0x2b};

  m_registerTable[0x03] = {.opcode = 0x03, .toString = "sra",   .funct = 0x03};

  m_registerTable[0x08] = {.opcode = 0x08, .toString = "jr",   .funct = 0x08};

  m_registerTable[0x09] = {.opcode = 0x09, .toString = "jalr",   .funct = 0x09};

  m_registerTable[0x10] = {.opcode = 0x10, .toString = "mfhi",   .funct = 0x10};

  m_registerTable[0x11] = {.opcode = 0x11, .toString = "mthi",   .funct = 0x11};

  m_registerTable[0x12] = {.opcode = 0x12, .toString = "mflo",   .funct = 0x12};

  m_registerTable[0x13] = {.opcode = 0x13, .toString = "mtlo",   .funct = 0x13};

  m_registerTable[0x18] = {.opcode = 0x18, .toString = "mult",   .funct = 0x18};
  
  m_registerTable[0x19] = {.opcode = 0x19, .toString = "multu",   .funct = 0x19};

  m_registerTable[0x20] = {.opcode = 0x20, .toString = "add",   .funct = 0x20};

  m_registerTable[0x21] = {.opcode = 0x21, .toString = "addu",   .funct = 0x21};

  m_registerTable[0x22] = {.opcode = 0x22, .toString = "sub",   .funct = 0x22};

  m_registerTable[0x23] = {.opcode = 0x23, .toString = "subu",   .funct = 0x23};

  m_registerTable[0x24] = {.opcode = 0x24, .toString = "and",   .funct = 0x24};

  m_registerTable[0x25] = {.opcode = 0x25, .toString = "or",   .funct = 0x25};

  m_registerTable[0x26] = {.opcode = 0x26, .toString = "xor",   .funct = 0x26};

  m_registerTable[0x27] = {.opcode = 0x27, .toString = "nor",   .funct = 0x27};
}

} // namespace Jun
