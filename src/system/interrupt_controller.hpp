#pragma once

#include <cstdint>

#include "common/register_base.hpp"
#include "psx_system.hpp"

namespace Jun{

namespace Interrupts{

enum class Irq: std::uint32_t{
  Vblank = 0,
  Gpu = 1,
  Cdrom = 2,
  Dma = 3,
  Timer0 = 4,
  Timer1 = 5,
  Timer2 = 6,
  ControllerMemoryCard = 7,
  Sio = 8,
  Spu = 0
};

struct StatusRegister: public RegisterBase{
  public:
    void SetBit(std::uint8_t pos, bool val){ RegisterBase::SetBit(pos, val);}
    bool GetBit(std::uint8_t pos){ return RegisterBase::GetBit(pos);}
};

struct MaskRegister: RegisterBase{
  public:
    void SetBit(std::uint8_t pos, bool val){ RegisterBase::SetBit(pos, val);}
    bool GetBit(std::uint8_t pos){ return RegisterBase::GetBit(pos);}
};

class InterruptController{
  public:
    InterruptController(PsxSystem& system): m_system{system}{}

    std::uint32_t Status() const { return m_status.Value();}
    void AcknowledgeInterrupt(Interrupts::Irq irq);

    std::uint32_t Masks() const;
    void SetMask(Interrupts::Irq irq);
    void ClearMask(Interrupts::Irq irq);

    StatusRegister& GetStatusRegister() { return m_status;}
    const StatusRegister& GetStatusRegister() const { return m_status;}

    MaskRegister& GetMaskRegister() { return m_mask;}
    const MaskRegister& GetMaskRegister() const { return m_mask;}

    void Trigger(Interrupts::Irq irq);
    bool InterruptPending();

    void RelayToCpu();

  private:
    StatusRegister m_status;
    MaskRegister m_mask;
    PsxSystem& m_system;
};

} // namespace Interrupts

} // namespace Jun
