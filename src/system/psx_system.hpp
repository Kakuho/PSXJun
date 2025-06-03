#pragma once

// Main container which contains all the other subsystems neccessary for PSX emulation

#include <iostream>
#include <memory>

#include "memory_manager.hpp"

#include "mips_r3000a/mips_manager.hpp"

namespace Jun{

class PsxSystem{
  // TODO: add handles to GPU, SPU, CD-ROM, MDEC when implementing these subsystems
  public:
    PsxSystem();

    void LoadBios(std::string&& biosFile){ m_memmap.LoadBios(std::move(biosFile));}

    void Tick();

    void Run();
    void Run(std::size_t ticks);

    MipsManager& GetCpu(){ return m_cpu;}
    const MipsManager& GetCpu() const { return m_cpu;}

    MemoryManager& GetMemmap(){ return m_memmap;}
    const MemoryManager& GetMemmap() const { return m_memmap;}

  private:
    MipsManager m_cpu;
    MemoryManager m_memmap;
};

} // namespace Jun
