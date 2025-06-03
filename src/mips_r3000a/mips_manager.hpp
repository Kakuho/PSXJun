#pragma once

// This is the main interface to interact with the processor
//
// *  MipsManager will own the cpu state, meanwhile the interpreter will 
//    only contain a reference to this state
//
// *  MipsManager will also own the interpreter itself

#include <variant>

#include "interpreter/interpreter.hpp"

#include "exception_vectors.hpp"
#include "mips_state.hpp"
#include "instructions.hpp"

namespace Jun{
  class PsxSystem;
}

namespace Jun{

class MipsManager{
  public:
    MipsManager(PsxSystem& system);
    ~MipsManager() = default;

    static std::string JumpOpcodeMnemonic(std::uint8_t opcode);
    static std::string ImmediateOpcodeMnemonic(std::uint8_t opcode);
    static std::string RegisterOpcodeMnemonic(std::uint8_t funct);
    static std::string BxxzOpcodeMnemonic(std::uint8_t rt);

    void Reset();
    void Shutdown();

    void Tick();
    void Run();

    bool ExceptionPending() const noexcept{ return m_exceptionPending;}
    bool ExternalExceptionPending() const noexcept{ return m_externalExceptionPending;}

    void HandleException();
    void HandleExternalException();

    std::uint8_t NextOpcode(){ return m_interpreter.NextOpcode();}
    std::uint32_t NextInstructionHex(){ return m_interpreter.NextInstructionHex();}

    std::variant<RegisterInstruction, ImmediateInstruction, JumpInstruction>
    CurrentInstruction() const{ return m_interpreter.CurrentInstruction();}

    MipsState& State(){ return m_state;}
    const MipsState& State() const{ return m_state;}

  private:
    PsxSystem& m_system;
    MipsState m_state;
    Interpreter m_interpreter;
    bool m_exceptionPending;
    bool m_externalExceptionPending;
};

}

