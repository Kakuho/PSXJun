#include "status_register.hpp"
#include <stdexcept>

namespace Jun{

bool StatusRegister::CopUsable(std::uint8_t cop){
  if(cop > 3){
    throw std::invalid_argument{"StatusRegister::CopUsable(cop) cop > 3"};
  }
  return GetBit(cop + 28);
}

void StatusRegister::SetCopUsable(std::uint8_t cop, bool val){
  if(cop > 3){
    throw std::invalid_argument{"StatusRegister::SetCopUsable(cop, val) cop > 3"};
  }
  SetBit(cop + 28, val);
}

}
