#pragma once

// Class type to encapsulate the memory mapped io port registers

#include <cstdint>
#include <unordered_map>
#include <string>

namespace Jun{

struct MemoryControllerRegister{
  std::string name;
  std::uint32_t value;
};

class MemoryMapIO{
  public:
    MemoryMapIO();

    std::uint32_t& operator[](std::uint32_t index){ return m_lut[index].value;}
    const std::uint32_t& operator[](std::uint32_t index) const
    { return m_lut.at(index).value;}

    bool Contains(std::size_t index) const{
      if(m_lut.contains(index)) return true;
      else return false;
    }

  private:
    void PopulateMemoryController();


    std::unordered_map<std::uint32_t, MemoryControllerRegister> m_lut;
};

} // namespace Jun
