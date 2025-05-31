#pragma once

#include <unordered_map>

#include "mips_r3000a/mips_state.hpp"
#include "mips_r3000a/instructions.hpp"
#include "mips_r3000a/exception_vectors.hpp"
#include "mips_r3000a/cop0/exception_register.hpp"

namespace Jun{
  class PsxSystem;
}

namespace Jun{

struct DelaySlot{
  std::uint8_t regIndex;
  std::uint32_t prevValue;
  bool active;
};

class Interpreter{
  public:
    Interpreter(MipsState& state, PsxSystem& system);

    void Reset();
    void Shutdown();

    void Tick();
    void Run();

    MipsState& State(){ return m_state;}
    const MipsState& State() const{ return m_state;}

    PsxSystem& System(){ return m_system;}
    const PsxSystem& System() const{ return m_system;}

    DelaySlot& GetDelaySlot(){ return m_delaySlot;}
    const DelaySlot& GetDelaySlot() const { return m_delaySlot;}

    void SetActiveDelaySlot(std::uint8_t regIndex, std::uint32_t value);
    void DisableDelaySlot() { m_delaySlot.active = false;}
    void EnableDelaySlot() { m_delaySlot.active = true;}

    //  Exception Handling
    //  PSX exceptions / interrupts are only routed to bit 10
    
    bool ExceptionPending() const { return m_exceptionPending;}
    bool InternalExceptionPending() const { return m_internalExceptionPending;}
    bool ExternalExceptionPending() const { return m_externalExceptionPending;}
    bool SoftwareExceptionPending() const { return m_softwareExceptionPending;}
    
    void TriggerInternalException();
    void TriggerExternalException();
    void TriggerSoftwareException();
    void TriggerInternalException(ExceptionCode excode);

    static void TriggerAddressLoadFetchException(Interpreter& interpreter);
    static void TriggerAddressStoreException(Interpreter& interpreter);

    static void TriggerBusFetchException(Interpreter& interpreter);
    static void TriggerBusLoadStoreException(Interpreter& interpreter);

    static void TriggerSystemCallException(Interpreter& interpreter);
    static void TriggerBreakpointExeption(Interpreter& interpreter);
    static void TriggerCoprocessorExeption(Interpreter& interpreter);

    static void TriggerReservedInstructionExeption(Interpreter& interpreter);
    static void TriggerOverflowExeption(Interpreter& interpreter);

    static void HandleInternalException();

    // implement these later if you want for full mips emulation

    static void TriggerTLBModifyException(Interpreter& interpreter) = delete;
    static void TriggerTLBLoadException(Interpreter& interpreter) = delete;
    static void TriggerTLBStoreException(Interpreter& interpreter) = delete;
    
    // Instruction Types

    using RegisterFunction = void(*)(Interpreter&, RegisterInstruction);
    using JumpFunction = void(*)(Interpreter&, JumpInstruction);
    using ImmediateFunction = void(*)(Interpreter&, ImmediateInstruction);

    // Instruction Tables

    std::unordered_map<std::uint8_t, RegisterFunction>& RegisterFunctionTable()
    { return m_registerTable;}

    std::unordered_map<std::uint8_t, JumpFunction>& JumpFunctionTable()
    { return m_jumpTable;}

    std::unordered_map<std::uint8_t, ImmediateFunction>& ImmediateFunctionTable()
    { return m_immediateTable;}

    // Load Stores

    static void Lb(Interpreter& interpreter, ImmediateInstruction instruction);
    static void Lw(Interpreter& interpreter, ImmediateInstruction instruction);

    static void Sw(Interpreter& interpreter, ImmediateInstruction instruction);

    // ALU

    // Arithmetic

    static void Add(Interpreter& interpreter, RegisterInstruction instruction);
    static void Addu(Interpreter& interpreter, RegisterInstruction instruction);
    static void Addi(Interpreter& interpreter, ImmediateInstruction instruction);
    static void Addiu(Interpreter& interpreter, ImmediateInstruction instruction);
    static void Sub(Interpreter& interpreter, RegisterInstruction instruction);
    static void Subu(Interpreter& interpreter, RegisterInstruction instruction);

    // Logical

    static void And(Interpreter& interpreter, RegisterInstruction instruction);
    static void Andi(Interpreter& interpreter, ImmediateInstruction instruction);
    static void Ori(Interpreter& interpreter, ImmediateInstruction instruction);

    // Shifts

    static void Lui(Interpreter& interpreter, ImmediateInstruction instruction);
    static void Sll(Interpreter& interpreter, RegisterInstruction instruction);

  private:
    MipsState& m_state;
    PsxSystem& m_system;
    std::unordered_map<std::uint8_t, RegisterFunction> m_registerTable;
    std::unordered_map<std::uint8_t, JumpFunction> m_jumpTable;
    std::unordered_map<std::uint8_t, ImmediateFunction> m_immediateTable;
    Instruction m_currentInstruction;
    Instruction m_lastInstruction;
    DelaySlot m_delaySlot;
    std::uint32_t m_lastPc;
    std::uint32_t m_lastVal;

    bool m_exceptionPending;
    bool m_internalExceptionPending;
    bool m_externalExceptionPending;
    bool m_softwareExceptionPending;
};

}
