// cop0 is the coprocessor of the cpu.
#ifndef COP0_HPP
#define COP0_HPP

#include <array>
#include <cstdint>

namespace psxjun{

namespace processor{

class Cop0Registers{
  private:
    std::array<std::uint32_t, 16> m_registers;

  public:

    std::uint32_t& indx()     {return m_registers[0];}
    std::uint32_t& tlbl()     {return m_registers[1];}
    std::uint32_t& bpc()      {return m_registers[2];}
    std::uint32_t& ctxt()     {return m_registers[3];}
    std::uint32_t& bda()      {return m_registers[4];}
    std::uint32_t& pidmask()  {return m_registers[5];}
    std::uint32_t& dcic()     {return m_registers[6];}
    std::uint32_t& badv()     {return m_registers[7];}
    std::uint32_t& bdam()     {return m_registers[8];}
    std::uint32_t& tlbh()     {return m_registers[9];}
    std::uint32_t& bpcm()     {return m_registers[10];}
    std::uint32_t& sr()       {return m_registers[11];}
    std::uint32_t& cause()    {return m_registers[12];}
    std::uint32_t& epc()      {return m_registers[13];}
    std::uint32_t& prid()     {return m_registers[14];}
    std::uint32_t& erreg()    {return m_registers[15];}

    // and of course their const versions 
    const std::uint32_t& indx()     const {return m_registers[0];}
    const std::uint32_t& tlbl()     const {return m_registers[1];}
    const std::uint32_t& bpc()      const {return m_registers[2];}
    const std::uint32_t& ctxt()     const {return m_registers[3];}
    const std::uint32_t& bda()      const {return m_registers[4];}
    const std::uint32_t& pidmask()  const {return m_registers[5];}
    const std::uint32_t& dcic()     const {return m_registers[6];}
    const std::uint32_t& badv()     const {return m_registers[7];}
    const std::uint32_t& bdam()     const {return m_registers[8];}
    const std::uint32_t& tlbh()     const {return m_registers[9];}
    const std::uint32_t& bpcm()     const {return m_registers[10];}
    const std::uint32_t& sr()       const {return m_registers[11];}
    const std::uint32_t& cause()    const {return m_registers[12];}
    const std::uint32_t& epc()      const {return m_registers[13];}
    const std::uint32_t& prid()     const {return m_registers[14];}
    const std::uint32_t& erreg()    const {return m_registers[15];}
};

enum class status{
  CU, RE, BEV, TS, PE, CM,
  PZ, SwC, IM, KUo, IEo, KUp,
  IEp, KUc, IEc, IsC
};

// the excode is found in cop0r13 and it tells you what exception occured
enum class excode{
  INT,
  MOD,
  TLBL,
  TLBS,
  AdEL,
  AdES,
  IBE,
  DBE,
  Syscall,
  BP,
  RI,
  CpU,
  ovf,
  unknown
};


class Cop0{
  Cop0Registers m_registers;
  public:
    Cop0();

    // Exception handling:
    // cop0r12 Status Register functionalities
    void SetStatus(std::uint8_t index, bool value);
    void SetStatus(status, bool value);
    bool GetStatus(status s) const;

    // cop0r13 Exception Cause Register
    excode GetExcode() const;
    void SetInterrupt(std::uint8_t index);
    bool InterruptPending() const;
};

} // processor

} // psxjun

namespace psxjun{
  namespace debug{
    // create a custom exception type
    struct Cop0Exception{

    };
  }
}

#endif
