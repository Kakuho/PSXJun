#ifndef PSX_HPP
#define PSX_HPP

#include "cpu.hpp"
#include "memory.hpp"

class Psx{
  private:
    CPU cpu;
    Memory mmu;
};

#endif
