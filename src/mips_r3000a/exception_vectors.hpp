#pragma once

#include <cstdint>

// Holds constants that represents the Virtual Addresses of exception vectors

namespace Jun{

namespace ExceptionVectors{

  static inline constexpr std::uint32_t Reset     = 0xbfc0'0000;
  static inline constexpr std::uint32_t UTlbMiss  = 0x8000'0000;
  static inline constexpr std::uint32_t Cop0Break = 0x8000'0040;
  static inline constexpr std::uint32_t General   = 0x8000'0080;

namespace Bev{

  // Boot Exception Vectors
  static inline constexpr std::uint32_t Reset     = 0xbfc0'0000;
  static inline constexpr std::uint32_t UTlbMiss  = 0xbfc0'0100;
  static inline constexpr std::uint32_t Cop0Break = 0xbfc0'0140;
  static inline constexpr std::uint32_t General   = 0xbfc0'0180;

} // namespace Bev

} // namespace Exceptions

} // namespace Jun
