namespace psxjun{

namespace memorymap{

static inline constexpr unsigned RAM_BEGIN  = 0x0000'0000;
static inline constexpr unsigned RAM_END    = 0x001f'ffff;

static inline constexpr unsigned SCRATCHPAD_BEGIN   = 0x1f80'0000;
static inline constexpr unsigned SCRATCHPAD_END     = 0x1f80'03ff;

static inline constexpr unsigned REGISTER_BEGIN = 0x1f80'1000;
static inline constexpr unsigned REGISTER_END   = 0x1f80'2fff;

static inline constexpr unsigned RAM_MIRROR1_BEGIN  = 0x8000'0000;
static inline constexpr unsigned RAM_MIRROR1_END    = 0x801f'ffff;

static inline constexpr unsigned RAM_MIRROR2_BEGIN  = 0xa000'0000;
static inline constexpr unsigned RAM_MIRROR2_END    = 0xa01f'ffff;

static inline constexpr unsigned BIOS_BEGIN  = 0xbfc0'0000;
static inline constexpr unsigned BIOS_END    = 0xbfc7'ffff;

} // namespace memorymap

} // namespace psxjun
