#include "mips_state.hpp"

namespace Jun{

MipsState::MipsState()
  : m_high{0},
    m_low{0},
    m_pc{0},
    m_cycles{0}
{
  for(std::uint8_t i = 0; i < 32; i++){
    m_gprs.regs[i] = 0;
  }
}

std::string Gprs::Name(std::uint32_t index){
  switch(index){
    case 0:
      return "ZR";
    case 1:
      return "AT";
    case 2:
      return "V0";
    case 3:
      return "V1";
    case 4:
      return "A0";
    case 5:
      return "A1";
    case 6:
      return "A2";
    case 7:
      return "A3";
    case 8:
      return "T0";
    case 9:
      return "T1";
    case 10:
      return "T2";
    case 11:
      return "T3";
    case 12:
      return "T4";
    case 13:
      return "T5";
    case 14:
      return "T6";
    case 15:
      return "T7";
    case 16:
      return "S0";
    case 17:
      return "S1";
    case 18:
      return "S2";
    case 19:
      return "S3";
    case 20:
      return "S4";
    case 21:
      return "S5";
    case 22:
      return "S6";
    case 23:
      return "S7";
    case 24:
      return "T8";
    case 25:
      return "T9";
    case 26:
      return "K0";
    case 27:
      return "K1";
    case 28:
      return "GP";
    case 29:
      return "SP";
    case 30:
      return "FP";
    case 31:
      return "RA";
    default:
      return "UNKNOWN";
  }
}

} // namespace Jun
