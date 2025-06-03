#pragma once

// Represents a non contigous memory region which itself is made up of 
// contigous memory regions

#include "system/memory_manager.hpp"
#include <cstdint>
#include <set>
#include <functional>

namespace Jun{

template<std::uint32_t START, std::uint32_t END>
constexpr bool WithinRange(std::uint32_t address){
  if((START <= address) && (address <= END)){
    return true;
  }
  else{
    return false;
  }
}

struct MemoryInterval{
  std::size_t Size() const{ return end - start;}

  bool Contains(const MemoryInterval& src) const{
    if((start <= src.start) && (src.start <= end)){
      return true;
    }
    else if((start <= src.end) && (src.end <= end)){
      return true;
    }
    else{
      return false;
    }
  }

  bool operator<(const MemoryInterval& rhs){
    if(start < rhs.start){
      return true;
    }
    else{
      return false;
    }
  }

  std::uint32_t start;
  std::uint32_t end;
};

template<typename T>
class MemoryRegion{
  using AddrType = T;
  public:

    void AddRegion(MemoryInterval& interval){
      for(auto& intervalIndex: m_lut){
        if(intervalIndex.Contains(interval)){
          continue;
        }
        else{
          m_lut.insert(interval);
          return;
        }
      }
    }

    void AddStartEnd(AddrType start, AddrType end){
      MemoryInterval interval{start, end};
      AddRegion(interval);
    }

    void AddStartSize(AddrType start, std::size_t bytes){
      MemoryInterval interval{start, start + bytes};
      AddRegion(interval);
    }

  private:
    std::set<MemoryInterval> m_lut;
};

}
