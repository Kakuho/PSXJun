#pragma once
#include <optional>

#include "common/register_base.hpp"
#include "status_register.hpp"
#include "misc_register.hpp"
#include "tbl_register_pair.hpp"
#include "exception_register.hpp"

namespace Jun{

std::optional<std::string> Cop0RegisterName(std::uint8_t regIndex);

class Cop0State{
  public:
    Cop0State() = default;

    std::size_t Size(){ return 16;}

    std::optional<std::uint32_t> RegVal(std::uint8_t index) const;

    const IndexRegister& Index() const {return m_index;}
    IndexRegister& Index() { return m_index;}

    //const std::uint32_t& Random() const { return registers[1];}
    //std::uint32_t& Random() { return registers[1];}

    const RegisterBase& TblLow() const { return m_tblPair.Low();}
    RegisterBase& TblLow() { return m_tblPair.High();}

    /*
    const std::uint32_t& BpPc() const { return registers[3];}
    std::uint32_t& BpPc() { return registers[3];}

    const std::uint32_t& Context() const { return registers[4];}
    std::uint32_t& Context() { return registers[4];}

    const std::uint32_t& BpData() const { return registers[5];}
    std::uint32_t& BpData() { return registers[5];}

    const std::uint32_t& PidMask() const { return registers[6];}
    std::uint32_t& PidMask() { return registers[6];}

    const std::uint32_t& DCIntCtrl() const { return registers[7];}
    std::uint32_t& DCIntCtrl() { return registers[7];}

    const std::uint32_t& BadVaddr() const { return registers[8];}
    std::uint32_t& BadVaddr() { return registers[8];}

    const std::uint32_t& BkDataMask() const { return registers[9];}
    std::uint32_t& BkDataMask() { return registers[9];}

    const std::uint32_t& TblHigh() const { return registers[10];}
    std::uint32_t& TblHigh() { return registers[10];}

    const std::uint32_t& BpCounterMask() const { return registers[11];}
    std::uint32_t& BpCounterMask() { return registers[11];}
    */

    const StatusRegister& Status() const { return m_status;}
    StatusRegister& Status() { return m_status;}

    const ExceptionRegister& Cause() const { return m_cause;}
    ExceptionRegister& Cause() { return m_cause;}

    /*
    const std::uint32_t& ExPc() const { return registers[14];}
    std::uint32_t& ExPc() { return registers[14];}

    const std::uint32_t& ProcId() const { return registers[15];}
    std::uint32_t& ProcId() { return registers[15];}
    */

  private:
    TblRegisterPair m_tblPair;
    IndexRegister m_index;
    StatusRegister m_status;
    ExceptionRegister m_cause;
};

}
