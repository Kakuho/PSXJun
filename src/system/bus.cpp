#include "bus.hpp"

namespace psxjun{

namespace system{

Bus::Bus(
    processor::CPU* cpu, 
    memory::Bios* bios, 
    memory::Ram* ram, 
    memory::ScratchPad* scratchpad
    ):
  m_cpu{cpu},
  m_bios{bios},
  m_ram{ram},
  m_scratchpad{scratchpad} {}

} // namespace system

} // namespace psxjun
