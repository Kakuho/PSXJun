#ifndef MEM_MAPPING_HPP
#define MEM_MAPPING_HPP

#include <cstdint>

namespace psxjun{

namespace memory{

static inline constexpr std::uint32_t RAM_BEGIN  = 0x0000'0000;
static inline constexpr std::uint32_t RAM_END    = 0x001f'ffff;

static inline constexpr std::uint32_t SCRATCHPAD_BEGIN   = 0x1f80'0000;
static inline constexpr std::uint32_t SCRATCHPAD_END     = 0x1f80'03ff;

static inline constexpr std::uint32_t REGISTER_BEGIN = 0x1f80'1000;
static inline constexpr std::uint32_t REGISTER_END   = 0x1f80'2fff;

static inline constexpr std::uint32_t RAM_MIRROR1_BEGIN  = 0x8000'0000;
static inline constexpr std::uint32_t RAM_MIRROR1_END    = 0x801f'ffff;

static inline constexpr std::uint32_t RAM_MIRROR2_BEGIN  = 0xa000'0000;
static inline constexpr std::uint32_t RAM_MIRROR2_END    = 0xa01f'ffff;

static inline constexpr std::uint32_t BIOS_BEGIN  = 0xbfc0'0000;
static inline constexpr std::uint32_t BIOS_END    = 0xbfc7'ffff;

} // namespace memory

} // namespace psxjun

#endif
