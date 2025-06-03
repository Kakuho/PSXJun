#pragma once

#include <cstdint>

namespace Jun{

static inline constexpr std::uint32_t WORD_SIZE = 4;

constexpr std::uint32_t CurrentWordBase(std::uint32_t address){
  return address - (address % WORD_SIZE);
}

constexpr std::uint32_t NextWordBase(std::uint32_t address){
  return CurrentWordBase(address) + WORD_SIZE;
}

}
