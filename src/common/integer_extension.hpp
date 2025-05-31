#pragma once

// Helpers for sign and zero extensions

#include <cstdint>

namespace Jun{

constexpr std::uint32_t SignExtend32(std::uint16_t src){
  bool isNegative = src & 0x8000;
  std::uint32_t extended = src;
  if(isNegative){
    extended = extended | (~0xffff);
  }
  return extended;
}

constexpr std::uint32_t ZeroExtend32(std::uint16_t src){
  std::uint32_t extended = 0;
  extended |= src;
  return extended;
}

}
