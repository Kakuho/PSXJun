#include <iostream>
#include <cassert>
#include <bitset>
#include "./../instruction.hpp"

std::uint32_t RInstruction(std::uint8_t opcode, std::uint8_t rs, std::uint8_t rt, std::uint8_t rd, std::uint8_t shamt, std::uint8_t funct){
  // helper function to generate a R instruction
  // R - type instructions has 6 operands
  //  opcode: 6 bits
  //  rs:     5 bits
  //  rt:     5 bits
  //  rd:     5 bits
  //  shamt:  5 bits
  //  funct:  6 bits
  std::uint32_t buffer = 0;
    // pack opcode into buffer
  buffer |= opcode;
  buffer = buffer << 6;
    // pack rs into buffer
  buffer |= rs;
  buffer = buffer << 5;
    // pack rt into buffer
  buffer |= rt;
  buffer = buffer << 5;
    // pack rd into buffer
  buffer |= rd;
  buffer = buffer << 5;
    // pack shamt into buffer
  buffer |= shamt;
  buffer = buffer << 5;
    // pack funct into buffer
  buffer |= funct;
  return buffer;
}

std::uint32_t IInstruction(std::uint8_t opcode, std::uint8_t rs, std::uint8_t rt, std::uint16_t immediate){
  // helper function to generate a R instruction
}

std::uint32_t JInstruction(std::uint8_t opcode, std::uint32_t immediate){

}

void Test_InstructionForms(){
  std::bitset<32> val{RInstruction(0b0011'1111, 0b01'0101, 0, 0, 0, 0)};
  std::cout << val << '\n';
}

void Test_Getters(){
  //std::uint8_t 
}

int main(){
  Test_InstructionForms();
}
