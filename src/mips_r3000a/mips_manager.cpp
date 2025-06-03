#include "mips_manager.hpp"
#include "system/psx_system.hpp"

namespace Jun{

MipsManager::MipsManager(PsxSystem& system)
  : 
    m_system{system},
    m_interpreter{m_state, m_system}
{
  Reset();
}

void MipsManager::Reset(){
  State().PC() = ExceptionVectors::Reset;
}

void MipsManager::Tick(){
  std::cout << "Ticked";
  m_interpreter.Tick();
}

void MipsManager::Run(){
  while(true){
    Tick();
  }
}

void MipsManager::HandleException(){
  m_state.PC() = ExceptionVectors::General;
}

std::string MipsManager::JumpOpcodeMnemonic(std::uint8_t opcode){
  switch(opcode){
    case 0x02:
      return "j";
    case 0x03:
      return "jal";
    default:
      return "unknown";
  }
}

std::string MipsManager::ImmediateOpcodeMnemonic(std::uint8_t opcode){
  switch(opcode){
    case 0x04:
      return "beq";
    case 0x05:
      return "bne";
    case 0x06:
      return "blez";
    case 0x07: 
      return "bgtz";
    case 0x08:
      return "addi";
    case 0x09:
      return "addiu";
    case 0x0a: 
      return "slti";
    case 0x0b: 
      return "sltiu";
    case 0x0c:
      return "andi";
    case 0x0d: 
      return "ori";
    case 0x0f: 
      return "lui";
    case 0x20: 
      return "lb";
    case 0x23: 
      return "lw";
    case 0x24: 
      return "lbu";
    case 0x25: 
      return "lhu";
    case 0x28: 
      return "sb";
    case 0x29: 
      return "sh";
    case 0x2b: 
      return "sw";
    default:
      return "unknown";
  }
}

std::string MipsManager::RegisterOpcodeMnemonic(std::uint8_t funct){
  switch(funct){
    case 0x00:
      return "sll";
    case 0x02: 
      return "srl";
    case 0x03: 
      return "sra";
    case 0x08: 
      return "jr";
    case 0x09:
      return "jalr";
    case 0x10: 
      return "mfhi";
    case 0x11: 
      return "mthi";
    case 0x12: 
      return "mflo";
    case 0x13: 
      return "mtlo";
    case 0x18: 
      return "mult";
    case 0x19: 
      return "multu";
    case 0x1a:
      return "div";
    case 0x1b:
      return "divu";
    case 0x20: 
      return "add";
    case 0x21: 
      return "addu";
    case 0x22: 
      return "sub";
    case 0x23: 
      return "subu";
    case 0x24: 
      return "and";
    case 0x25: 
      return "or";
    case 0x26: 
      return "xor";
    case 0x27: 
      return "nor";
    case 0x2a:
      return "slt";
    case 0x2b:
      return "sltu";
    default:
      return "unknown";
  }
}

std::string MipsManager::BxxzOpcodeMnemonic(std::uint8_t rt){
  switch(rt){
    case 0b00000:
      return "bltz";
    case 0b00001:
      return "bgez";
    case 0b10000:
      return "bltzal";
    case 0b10001:
      return "bgezal";
    default:
      return "unknown";
  }
}

} // namespace Jun
