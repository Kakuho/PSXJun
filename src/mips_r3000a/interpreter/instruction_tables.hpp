#pragma once

#include <unordered_map>
#include <cstdint>

#include "interpreter.hpp"

namespace Jun{

constexpr void PopulateRegisterInterpreterTable(std::unordered_map<std::uint8_t, Interpreter::RegisterFunction>& rtable){
  rtable[0x00] = Interpreter::Sll;
  rtable[0x20] = Interpreter::Add;
  rtable[0x21] = Interpreter::Addu;
  rtable[0x22] = Interpreter::Sub;
  rtable[0x23] = Interpreter::Subu;
  rtable[0x24] = Interpreter::And;
}

constexpr void PopulateImmediateInterpreterTable(std::unordered_map<std::uint8_t, Interpreter::ImmediateFunction>& table){
  table[0x08] = Interpreter::Addi;
  table[0x09] = Interpreter::Addiu;
  table[0x0c] = Interpreter::Andi;
  table[0x0d] = Interpreter::Ori;
  table[0x0f] = Interpreter::Lui;
  table[0x20] = Interpreter::Lb;
  table[0x23] = Interpreter::Lw;
  table[0x2b] = Interpreter::Sw;
}

}
