#pragma once

#include <array>
#include <string>
#include <cstdint>

#include "cop0/cop0_state.hpp"

namespace Jun{

struct Gprs{
  static std::string Name(std::uint32_t index);

  const std::uint32_t& operator[](std::uint32_t index) const { return regs[index];}
  std::uint32_t& operator[](std::uint32_t index){ return regs[index];}

  std::array<std::uint32_t, 32> regs;
};

class MipsState{
  public:
    MipsState() = default;

    std::uint32_t Reg(std::uint8_t index) const noexcept { return m_gprs[index]; }
    std::uint32_t& Reg(std::uint8_t index) noexcept { return m_gprs[index]; }

    std::uint32_t PC() const noexcept{ return m_pc;}
    std::uint32_t& PC() noexcept{ return m_pc;}

    std::uint32_t Hi() const noexcept{ return m_high;}
    std::uint32_t& Hi() noexcept{ return m_high;}

    std::uint32_t Lo() const noexcept{ return m_low;}
    std::uint32_t& Lo() noexcept{ return m_low;}

  private:
    Gprs m_gprs;
    Cop0State m_cop0;
    std::uint32_t m_high;
    std::uint32_t m_low;
    std::uint32_t m_pc;
};

}
