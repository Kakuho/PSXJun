#pragma once

//  OpcodeTable is a lookup table for each mips r3000 opcode
//  Only required for the debugger, the psx emulator itself doesn't really need this

#include <unordered_map>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace Jun{
  enum class InstrType{
    Imm,
    Reg,
    Jump
  };

  class OpcodeTable{
    public:
      struct OpcodeEntry{
        std::uint8_t opcode;
        std::string toString;
        InstrType type;
        union{
          std::uint8_t funct;
          char dummy;
        };
      };

    public:
      OpcodeTable();
      const OpcodeEntry& operator[](std::uint8_t opcode) const;
      const OpcodeEntry& RInstr(std::uint8_t functs) const;

    private:
      void PopulateOpcodes();
      void PopulateIInstr();
      void PopulateJInstr();
      void PopulateRInstr();

    private:
      std::unordered_map<std::uint8_t, OpcodeEntry> m_opcodes;
      std::unordered_map<std::uint8_t, OpcodeEntry> m_rinstrs;  // index using functs
  };
}
