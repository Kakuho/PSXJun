#pragma once

// Cop0's Status Register

#include <cstdint>
#include <stdexcept>

#include "common/register_base.hpp"

namespace Jun{

class StatusRegister final : public RegisterBase{
  static inline constexpr std::uint32_t INTERRUPT_MASK_POS = 0xff << 8;
  public:
    StatusRegister() = default;
    StatusRegister(std::uint32_t val);

    bool CopUsable(std::uint8_t cop);
    void SetCopUsable(std::uint8_t cop, bool val);

    constexpr std::uint8_t InterruptMask()
    { return (m_buffer & INTERRUPT_MASK_POS) >> 8;}

    constexpr void SetInterruptMask(std::uint8_t pos, bool val)
    { SetBit(8 << pos, val);}

    constexpr bool ReverseEndian() const { return GetBit(25);}
    constexpr void SetReverseEndian(bool val) { SetBit(25, val);}

    constexpr bool BootExVector() const { return GetBit(22);}
    constexpr void SetBootExVector(bool val) { SetBit(22, val);}

    constexpr bool TlbShutdown() const { return GetBit(21);}
    constexpr void SetTlbShutdown(bool val) { SetBit(21, val);}

    constexpr bool ParityError() const { return GetBit(20);}
    constexpr void SetParityError(bool val) { SetBit(20, val);}

    constexpr bool CacheMiss() const { return GetBit(19);}
    constexpr void SetCacheMiss(bool val) { SetBit(19, val);}

    constexpr bool ParityZero() const { return GetBit(18);}
    constexpr void SetParityZero(bool val) { SetBit(18, val);}

    constexpr bool SwapCache() const { return GetBit(17);}
    constexpr void SetSwapCache(bool val) { SetBit(17, val);}

    constexpr bool IsolateCache() const { return GetBit(16);}
    constexpr void SetIsolateCache(bool val) { SetBit(16, val);}

    constexpr bool KernelCurr() const {return GetBit(1);}
    constexpr void SetKernelCurr(bool val) { SetBit(1, val);}

    constexpr bool IntEnableCurr() const { return GetBit(0);}
    constexpr void SetIntEnableCurr(bool val) { SetBit(0, val);}

    constexpr bool KernelPrev() const { return GetBit(3);}
    constexpr void SetKernelPrev(bool val) { SetBit(3, val);}

    constexpr bool IntEnablePrev() const { return GetBit(2);}
    constexpr void SetIntEnablePrev(bool val) { SetBit(2, val);}

    constexpr bool KernelOld() const { return GetBit(5);}
    constexpr void SetKernelOld(bool val) { SetBit(5, val);}

    constexpr bool IntEnableOld() const { return GetBit(4);}
    constexpr void SetIntEnableOld(bool val) { SetBit(4, val);}
};

} // namespace Jun
