#ifndef PSX_HPP
#define PSX_HPP

#include "cpu.hpp"
#include "memory.hpp"
#include "bus.hpp"

#include <memory>

class Psx{
  std::unique_ptr<CPU>  m_cpu;
  std::unique_ptr<Bios> m_bios;
  std::unique_ptr<Ram>  m_ram;
  std::unique_ptr<ScratchPad> m_scratchpad;
  std::unique_ptr<Bus> m_bus;
  // TODO: add handles to GPU, SPU, CD-ROM, MDEC when implementing these subsystems

  public:
    Psx();
    void ConfigureBus();

    void run();

  private:
};

#endif
