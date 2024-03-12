#ifndef BUS_HPP
#define BUS_HPP

#include "./../processor/cpu.hpp"
#include "./../memory/memory.hpp"
#include "./../memory/memory_mapping.hpp"
#include "./memory_controller.hpp"

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

struct MemoryController;

// this is the system bus - it operates with respect to cpu address semantics.
class SystemBus{

  // TODO: add handles to GPU, SPU, CD-ROM, MDEC when implementing these subsystems
  
  processor::CPU& m_cpu;
  memory::Bios& m_bios;
  memory::Ram& m_ram;
  memory::ScratchPad& m_scratchpad;
  MemoryController& m_memory_controller;

  public:
  SystemBus(
      processor::CPU& cpu, 
      memory::Bios& bios, 
      memory::Ram& ram, 
      memory::ScratchPad& scratchpad,
      MemoryController& memory_ctrl
      );
  SystemBus() = delete;

  std::uint8_t GetByte(std::size_t index) const;
  std::uint32_t GetWord(std::size_t index) const;
  void WriteByte(std::size_t index, std::uint8_t val);
  void WriteWord(std::size_t index, std::uint32_t val);
};

} // namespace system

} // namespace psxjun

#endif
