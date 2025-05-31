#pragma once

#include <cstdint>
#include <cassert>

#include "common/register_base.hpp"

namespace Jun{

class TblRegisterPair{
  public:
    TblRegisterPair(): buffer{0}{}

    RegisterBase& High(){ return pairs[0];}
    const RegisterBase& High() const{ return pairs[0];}

    RegisterBase& Low(){ return pairs[1];}
    const RegisterBase& Low() const{ return pairs[1];}

    std::uint32_t VirtPageNum();
    std::uint8_t Pid();
    std::uint32_t PageFrameNum();

    bool NonCacheable();
    bool Dirty();
    bool Valid();
    bool Global();

  public:
    union{
      std::uint64_t buffer;
      RegisterBase pairs[2];
    };
};

static_assert(sizeof(TblRegisterPair) == 8);

}
