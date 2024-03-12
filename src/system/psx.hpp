#ifndef PSX_HPP
#define PSX_HPP

#include "./../processor/cpu.hpp"
#include "./../memory/memory.hpp"
#include "memory_controller.hpp"
#include "bus.hpp"

#include <memory>


namespace psxjun{

using processor::CPU;

using memory::Ram;
using memory::Bios;
using memory::ScratchPad;

namespace system{

  struct MemoryController;

class Psx{
  std::unique_ptr<CPU>  m_cpu;
  std::unique_ptr<Bios> m_bios;
  std::unique_ptr<Ram>  m_ram;
  std::unique_ptr<ScratchPad> m_scratchpad;
  std::unique_ptr<MemoryController> m_memory_controller;
  std::unique_ptr<SystemBus> m_bus;
  // TODO: add handles to GPU, SPU, CD-ROM, MDEC when implementing these subsystems

  public:
    Psx();
    Psx(std::string&& biosFilePath);
    void run();
    void run(std::size_t ticks);
};

}

}
#endif
