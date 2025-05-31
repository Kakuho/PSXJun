#pragma once

#include <cstdint>
#include <stdexcept>

#include "common/register_base.hpp"

namespace Jun{

enum ExceptionCode: std::uint8_t{
  Interrupt = 0x0,
  AddressLoad = 0x4,
  AddressFetch = 0x5,
  BusFetch = 0x6,
  BusLoad = 0x7,
  SystemCall = 0x8,
  Breakpoint = 0x9,
  ReservedInstruction = 0xa,
  CoprocessorUnusable = 0xb,
  ArithmeticOverflow = 0xc,
  Unknown
};

class ExceptionRegister final: public RegisterBase{
  public:
    void SetException(ExceptionCode code){
      m_buffer &= 0b01111100; 
      m_buffer |= (code << 2);
    }

    ExceptionCode GetExceptionCode(){
      return static_cast<ExceptionCode>((m_buffer & 0b01111100) >> 2);
    }

    bool BranchDelay() const { return GetBit(31);}
    void SetBranchDelay(bool val) { SetBit(31, val);}

    std::uint8_t CoprocessorIndex() const{ 
      return (GetBit(29) << 1)| GetBit(28);
    }

    void SetCoprocessorIndex(std::uint8_t index){
      if(index > 3){
        throw std::invalid_argument{"Coprocessor Index > 3"};
      }
      SetBit(29, index & 0x2);
      SetBit(28, index & 0x1);
    }

    constexpr std::uint8_t InterruptsField() const{
      return m_buffer & 0xF0;
    }

    void SetInterruptField(std::uint8_t val){
      m_buffer &= ~0xF0;
      m_buffer |= (val << 8);
    }
};

}
