#pragma once

#include "common/register_base.hpp"

namespace Jun{

class IndexRegister final: RegisterBase{
  public:
    bool ProbeResult(){ return m_buffer & 1 << 31;}
    void SetProbeResult();

    std::uint8_t TlbIndex(){ return m_buffer & (0x3F << 8);}
    void SetTlbIndex(std::uint8_t index);

  private:
    std::uint32_t m_buffer;
};

}
