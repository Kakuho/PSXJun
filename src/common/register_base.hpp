#pragma once

// File contains definitions of misc COP0 registers.

#include <cstdint>
#include <cassert>

namespace Jun{

class RegisterBase{
  public:
    RegisterBase() = default;

    RegisterBase& operator|=(const RegisterBase& src);
    RegisterBase& operator|=(std::uint32_t val);

    RegisterBase& operator^=(const RegisterBase& src);
    RegisterBase& operator^=(std::uint32_t val);

    RegisterBase& operator<<=(const RegisterBase& src);
    RegisterBase& operator<<=(std::uint32_t val);

    RegisterBase& operator>>=(const RegisterBase& src);
    RegisterBase& operator>>=(std::uint32_t val);

    friend RegisterBase operator~(const RegisterBase& src);

    constexpr std::uint32_t Value() const{ return m_buffer;}

  protected:
    constexpr void SetBit(std::uint8_t pos, bool val){
      if(val){
        m_buffer |= 1 << pos;
      }
      else{
        m_buffer &= ~(1 << pos);
      }
    }

    constexpr bool GetBit(std::uint8_t pos) const{
      return m_buffer & (1 << pos);
    }

  public:
    std::uint32_t m_buffer;
};

}
