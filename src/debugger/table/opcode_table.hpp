#pragma once

//  OpcodeTable is a lookup table for each mips r3000 opcode
//  Only required for the debugger, the psx emulator itself doesn't really need this

#include <unordered_map>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace Debug{

class OpcodeTable{
  public:
    struct OpcodeEntry{
      std::uint8_t opcode;
      std::string toString;
      union{
        std::uint8_t funct;
        char dummy;
      };
    };

  public:
    OpcodeTable();

    using TableType = std::unordered_map<std::uint8_t, OpcodeEntry>;

    TableType& ImmediateTable(){ return m_immediateTable;}
    const TableType& ImmediateTable() const{ return m_immediateTable;}

    TableType& JumpTable(){ return m_jumpTable;}
    const TableType& JumpTable() const{ return m_jumpTable;}

    TableType& RegisterTable(){ return m_registerTable;}
    const TableType& RegisterTable() const{ return m_registerTable;}

    TableType& BxxzTable(){ return m_bxxzTable;}
    const TableType& BxxzTable() const{ return m_bxxzTable;}

  private:
    void PopulateOpcodes();
    void PopulateImmediateTable();
    void PopulateJumpTable();
    void PopulateRegisterTable();
    void PopulateBxxzTable();

  private:
    std::unordered_map<std::uint8_t, OpcodeEntry> m_immediateTable;
    std::unordered_map<std::uint8_t, OpcodeEntry> m_jumpTable;
    std::unordered_map<std::uint8_t, OpcodeEntry> m_registerTable;  // indexed using the funct field
    std::unordered_map<std::uint8_t, OpcodeEntry> m_bxxzTable;      // indexed using the secondary field
    std::unordered_map<std::uint8_t, OpcodeEntry> m_rinstrs;  // index using functs
};

}
