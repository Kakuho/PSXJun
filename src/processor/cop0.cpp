#include "cop0.hpp"
#include <stdexcept>

namespace psxjun{

namespace processor{

Cop0::Cop0(){
  // NOT IMPLEMENTED!!
  //m_registers.INDX() = 0;
  m_registers.sr() |= 1 << 22;
  m_registers.sr() &= ~(1 << 15);
}

bool Cop0::GetStatus(status s) const{
  switch(s){
    case status::IEc:
          return m_registers.sr() & 1;
    case status::KUc:
          return m_registers.sr() & (1 << 1);
    case status::IEp:
          return m_registers.sr() & (1 << 2);
    case status::KUp:
          return m_registers.sr() & (1 << 3);
    case status::IEo:
          return m_registers.sr() & (1 << 4);
    case status::KUo:
          return m_registers.sr() & (1 << 4);
    case status::IsC:
          return m_registers.sr() & (1 << 13);
    case status::SwC:
          return m_registers.sr() & (1 << 14);
    case status::PZ:
          return m_registers.sr() & (1 << 15);
    case status::CM:
          return m_registers.sr() & (1 << 16);
    case status::PE:
          return m_registers.sr() & (1 << 17);
    case status::TS:
          return m_registers.sr() & (1 << 18);
    case status::BEV:
          return m_registers.sr() & (1 << 19);
    case status::RE:
          return m_registers.sr() & (1 << 21);
    default:
          throw std::runtime_error{"invalid status field"};
  }
}

excode Cop0::GetExcode() const{
  switch(m_registers.cause() & 0b1111110){
    case 0x00: return excode::INT;
    case 0x01: return excode::MOD;
    case 0x02: return excode::TLBL;
    case 0x03: return excode::TLBS;
    case 0x04: return excode::AdEL;
    case 0x05: return excode::AdES;
    case 0x06: return excode::IBE;
    case 0x07: return excode::DBE;
    case 0x08: return excode::Syscall;
    case 0x09: return excode::BP;
    case 0x0A: return excode::RI;
    case 0x0B: return excode::CpU;
    case 0x0C: return excode::ovf;
    default:   return excode::unknown;
  }
}

bool Cop0::InterruptPending() const{
}

} // processor

} // psxjun
