#pragma once

#include <cstdint>
#include <cassert>
#include <variant>

namespace Jun{

struct RegisterInstruction{
  RegisterInstruction(): val{0}{}
  RegisterInstruction(std::uint32_t val): val{val}{}
  union{
    struct{
      std::uint32_t opcode: 6;
      std::uint32_t rs: 5;
      std::uint32_t rt: 5;
      std::uint32_t rd: 5;
      std::uint32_t shamt: 5;
      std::uint32_t funct: 6;
    };
    std::uint32_t val;
  };
};


static_assert(sizeof(RegisterInstruction) == 4);

struct ImmediateInstruction{
  ImmediateInstruction(): val{0}{}
  ImmediateInstruction(std::uint32_t val): val{val}{}
  union{
    struct{
      std::uint32_t immediate: 16;
      std::uint32_t rt: 5;
      std::uint32_t rs: 5;
      std::uint32_t opcode: 6;
    };
    std::uint32_t val;
  };
};

static_assert(sizeof(ImmediateInstruction) == 4);

struct JumpInstruction{
  JumpInstruction(): val{0}{}
  JumpInstruction(std::uint32_t val): val{val}{}
  union{
    struct{
      std::uint32_t opcode: 6;
      std::uint32_t target: 26;
    };
    std::uint32_t val;
  };
};

static_assert(sizeof(JumpInstruction) == 4);

enum class InstructionType{Register, Immediate, Jump};

using InstructionVariant = std::variant<
  RegisterInstruction,
  ImmediateInstruction,
  JumpInstruction
>;

struct Instruction{
  InstructionType type;
  Instruction(std::uint32_t val): buffer{val}{}
  union{
    RegisterInstruction reg;
    ImmediateInstruction imm;
    JumpInstruction jump;
    std::uint32_t buffer;
  };
};

}
