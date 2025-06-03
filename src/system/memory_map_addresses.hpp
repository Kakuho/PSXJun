#pragma once

//  PS1 Memory Map
//
//  Reference:
//
//  KUSEG     KSEG0     KSEG1
//  00000000h 80000000h A0000000h  2048K  Main RAM (first 64K reserved for BIOS)
//  1F000000h 9F000000h BF000000h  8192K  Expansion Region 1 (ROM/RAM)
//  1F800000h 9F800000h    --      1K     Scratchpad (D-Cache used as Fast RAM)
//  1F801000h 9F801000h BF801000h  4K     I/O Ports
//  1F802000h 9F802000h BF802000h  8K     Expansion Region 2 (I/O Ports)
//  1FA00000h 9FA00000h BFA00000h  2048K  Expansion Region 3 (SRAM BIOS region for DTL cards)
//  1FC00000h 9FC00000h BFC00000h  512K   BIOS ROM (Kernel) (4096K max)
//
//        FFFE0000h (in KSEG2)     0.5K   Internal CPU control registers (Cache Control)
//
//  Notes:
//    
//    * KSEG0 and KSEG1 are kernel memory regions
//    * KUSEG is user memory region
//    * KSEG2 is repurposed from kernel virtual memory to cache control registers

#include <cstdint>

namespace Jun{

namespace MemoryMap{

namespace Kseg2{
  // Kseg2 used for cache control

  static inline constexpr std::uint32_t BEGIN = 0xC000'0000;
  static inline constexpr std::uint32_t END   = 0xFFFF'FFFF;

  static inline constexpr std::uint32_t CACHE_REGISTERS_BEGIN  = 0xFFFE'0000;
  static inline constexpr std::uint32_t CACHE_REGISTERS_END    = 0xFFFE'01ff;

} // namespace Kseg2

namespace Kseg1{
  // Kseg1 is the physical memory, mapped to the cpu bus.

  static inline constexpr std::uint32_t BEGIN = 0xA000'0000;
  static inline constexpr std::uint32_t END   = 0xBFFF'FFFF;

  static inline constexpr std::uint32_t RAM_BEGIN  = 0xA000'0000;
  static inline constexpr std::uint32_t RAM_END    = 0xA020'0000;

  static inline constexpr std::uint32_t EXPANSION1_BEGIN  = 0xBF00'0000;
  static inline constexpr std::uint32_t EXPANSION1_END    = 0xBF80'0000;

  static inline constexpr std::uint32_t MMIO_BEGIN = 0xBF80'1000;
  static inline constexpr std::uint32_t MMIO_END   = 0xBF80'1fff;

  static inline constexpr std::uint32_t IO_EXPANSION_BEGIN  = 0xBF80'2000;
  static inline constexpr std::uint32_t IO_EXPANSION_END    = 0xBF80'3fff;

  static inline constexpr std::uint32_t SRAM_EXPANSION_BEGIN  = 0xBFA0'0000;
  static inline constexpr std::uint32_t SRAM_EXPANSION_END    = 0xBFBF'FFFF;

  static inline constexpr std::uint32_t BIOS_BEGIN            = 0xBFC0'0000;
  static inline constexpr std::uint32_t BIOS_END              = 0xBFC7'FFFF;

} // namespace Kseg1

namespace Kseg0{
  // Kseg0 is a mirror of Kseg1 but with cache enabled

  static inline constexpr std::uint32_t BEGIN = 0x8000'0000;
  static inline constexpr std::uint32_t END   = 0x9FFF'FFFF;

  static inline constexpr std::uint32_t RAM_BEGIN  = 0x8000'0000;
  static inline constexpr std::uint32_t RAM_END    = 0x801F'FFFF;

  static inline constexpr std::uint32_t EXPANSION1_BEGIN  = 0x9F00'0000;
  static inline constexpr std::uint32_t EXPANSION1_END    = 0x9F7F'FFFF;

  static inline constexpr std::uint32_t SCRATCHPAD_BEGIN  = 0x9F80'0000;
  static inline constexpr std::uint32_t SCRATCHPAD_END    = 0x9F80'03FF;

  static inline constexpr std::uint32_t MMIO_BEGIN = 0x9F80'1000;
  static inline constexpr std::uint32_t MMIO_END   = 0x9F80'1fff;

  static inline constexpr std::uint32_t IO_EXPANSION_BEGIN  = 0x9F80'2000;
  static inline constexpr std::uint32_t IO_EXPANSION_END    = 0x9F80'3fff;

  static inline constexpr std::uint32_t SRAM_EXPANSION_BEGIN  = 0x9FA0'0000;
  static inline constexpr std::uint32_t SRAM_EXPANSION_END    = 0x9FBF'FFFF;

  static inline constexpr std::uint32_t BIOS_BEGIN  = 0x9FC0'0000;
  static inline constexpr std::uint32_t BIOS_END    = 0x9FC7'FFFF;

} // namespace Kseg0

namespace Kuseg{
  // Kuseg is Mips' user virtual memory. 
  // Psx decides to identity map Kseg1 into Kuseg starting at memory address 0.
  //
  // Kuseg is a memory region addressing 2GiB of memory, and thus any memory address 
  // after 512MiB is an error

  static inline constexpr std::uint32_t BEGIN = 0x0000'0000;
  static inline constexpr std::uint32_t END   = 0x7FFF'FFFF;

  static inline constexpr std::uint32_t RAM_BEGIN  = 0x0000'0000;
  static inline constexpr std::uint32_t RAM_END    = 0x001F'FFFF;

  static inline constexpr std::uint32_t EXPANSION1_BEGIN  = 0x1F00'0000;
  static inline constexpr std::uint32_t EXPANSION1_END    = 0x1F7F'FFFF;

  static inline constexpr std::uint32_t SCRATCHPAD_BEGIN  = 0x1F80'0000;
  static inline constexpr std::uint32_t SCRATCHPAD_END    = 0x1F80'03FF;

  static inline constexpr std::uint32_t MMIO_BEGIN = 0x1F80'1000;
  static inline constexpr std::uint32_t MMIO_END   = 0x1F80'1fff;

  static inline constexpr std::uint32_t IO_EXPANSION_BEGIN  = 0x1F80'2000;
  static inline constexpr std::uint32_t IO_EXPANSION_END    = 0x1F80'3fff;

  static inline constexpr std::uint32_t SRAM_EXPANSION_BEGIN  = 0x1FA0'0000;
  static inline constexpr std::uint32_t SRAM_EXPANSION_END    = 0x1FBF'FFFF;

  static inline constexpr std::uint32_t BIOS_BEGIN  = 0x1FC0'0000;
  static inline constexpr std::uint32_t BIOS_END    = 0x1FC7'FFFF;

} // namespace Kuseg

} // namespace MemoryMap

} // namespace Jun
