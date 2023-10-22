#ifndef BUS_HPP
#define BUS_HPP

#include "./../processor/cpu.hpp"
#include "./../memory/memory.hpp"

#include <memory>

namespace psxjun{

namespace processor{
  class CPU;
}

namespace memory{
  class Bios;
  class Ram;
  class ScratchPad;
}

namespace system{

class Bus{

  // TODO: add handles to GPU, SPU, CD-ROM, MDEC when implementing these subsystems
  
  processor::CPU* m_cpu = nullptr;
  memory::Bios* m_bios = nullptr;
  memory::Ram* m_ram = nullptr;
  memory::ScratchPad* m_scratchpad = nullptr;

  public:
  Bus(
      processor::CPU* cpu, 
      memory::Bios*bios, 
      memory::Ram* ram, 
      memory::ScratchPad* scratchpad
      );
  Bus();


};

} // namespace system

} // namespace psxjun

#endif
