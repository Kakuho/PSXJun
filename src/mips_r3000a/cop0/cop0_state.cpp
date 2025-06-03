#include "cop0_state.hpp"
#include <cmath>
#include <optional>

namespace Jun{

std::optional<std::string> Cop0RegisterName(std::uint8_t regIndex){
  switch(regIndex){
    case 3:
      // Breakpoint Register
      return "Bpc";
    case 5:
      // Breakpoint Data Address Register
      return "Bda";
    case 6:
      // Target Address Register
      return "Tar";
    case 7:
      // Debug and Cache Invalidate Control
      return "Dcic";
    case 8:
      // Bad Address Register
      return "BadA";
    case 9:
      // Breakpoint Data Address Mask Register
      return "Bdam";
    case 11:
      // Breakpoint Program Counter Mask
      return "Bpcm";
    case 12:
      return "Sr";
    case 13:
      return "Cause";
    case 14:
      // Exception Program Counter
      return "Epc";
    case 15:
      // Processor Revision Identifier
      return "Prid";
    default:
      return std::nullopt;
  };
}

std::optional<std::uint32_t> Cop0State::RegVal(std::uint8_t index) const{
  switch(index){
    case 3:
      // Breakpoint Register
      return std::nullopt;
    case 5:
      // Breakpoint Data Address Register
      return std::nullopt;
    case 6:
      // Target Address Register
      return std::nullopt;
    case 7:
      // Debug and Cache Invalidate Control
      return std::nullopt;
    case 8:
      // Bad Address Register
      return std::nullopt;
    case 9:
      // Breakpoint Data Address Mask Register
      return std::nullopt;
    case 11:
      // Breakpoint Program Counter Mask
      return std::nullopt;
    case 12:
      // Status Register
      return m_status.Value();
    case 13:
      // Exception Register
      return m_cause.Value();
    case 14:
      // Exception Program Counter
      return std::nullopt;
    case 15:
      // Processor Revision Identifier
      return std::nullopt;
    default:
      return std::nullopt;
  };
}

}
