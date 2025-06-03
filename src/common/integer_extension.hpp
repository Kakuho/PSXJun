#pragma once

// Helpers for sign and zero extensions

#include <cstdint>
#include <type_traits>

namespace Jun{

template<class T>
concept IntegralLessThan32Bit = 
  std::is_same_v<T, std::uint32_t> ||
  std::is_same_v<T, std::uint16_t> ||
  std::is_same_v<T, std::uint8_t> ||
  std::is_same_v<T, std::int32_t> ||
  std::is_same_v<T, std::int16_t> ||
  std::is_same_v<T, std::int8_t>;

template<IntegralLessThan32Bit T>
constexpr std::uint32_t SignExtend32(T src){
  bool isNegative = src & 0x8000;
  std::uint32_t extended = src;
  if(isNegative){
    extended = extended | (~0xffff);
  }
  return extended;
}

template<IntegralLessThan32Bit T, IntegralLessThan32Bit U>
constexpr T SignExtend(U src){
  bool isNegative = src & 0x8000;
  T extended = src;
  if(isNegative){
    extended = extended | (~0xffff);
  }
  return extended;
}

template<IntegralLessThan32Bit T>
constexpr std::uint32_t ZeroExtend32(T src){
  std::uint32_t extended = 0;
  extended |= src;
  return extended;
}

template<IntegralLessThan32Bit T, IntegralLessThan32Bit U>
constexpr T ZeroExtend(U src){
  T extended = 0;
  extended |= src;
  return extended;
}

}
