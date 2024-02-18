#ifndef EXCEPTION_VECTORS_HPP
#define EXCEPTION_VECTORS_HPP

#include <cstdint>

namespace psxjun{

namespace processor{
  constexpr std::uint32_t reset_vector          {0xbfc0'0000};
  constexpr std::uint32_t utlb_miss_vector      {0x8000'0000};
  constexpr std::uint32_t break_vector          {0x8000'0040};
  constexpr std::uint32_t general_vector        {0x8000'0080};
  // *_bev are the vectors when bev is set - bev is set on bootstrap, and thus 
  // the vector are on bios rom
  // appaz not really used anyways
  constexpr std::uint32_t reset_vector_bev      {0xbfc0'0000};
  constexpr std::uint32_t utlb_miss_vector_bev  {0xbfc0'0100};
  constexpr std::uint32_t break_vector_bev      {0xbfc0'0140};
  constexpr std::uint32_t general_vector_bev    {0xbfc0'0180};
}

}

#endif
