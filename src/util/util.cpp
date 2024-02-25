#include "util.hpp"

namespace psxjun{

std::uint32_t signextend32(std::uint16_t src){
  bool isNegative = src & 0x8000;
  std::uint32_t extended = src;
  if(isNegative){
    extended = extended | (~0xffff);
  }
  return extended;
}

}
