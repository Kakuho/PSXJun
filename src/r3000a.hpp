// Definition of the r3000a processor.
#include <array>

static const long CLOCKSPEED = 0;

class R3000A{
  // private vars
  std::array<std::uint8_t, 4000> m_instrucion_cache;
  std::array<std::uint8_t, 1000> m_data_cache;
  std::array<std::uint32_t 32>   m_registers;
  std::uint32_t m_hi = 0;     // upper half of 64 bit multiplication
  std::uint32_t m_low = 0;    // lower half of 64 bit multiplication
  std::uint32_t pc;

  public:
  // Avoiding initialisation for now :/
  std::array<std::uint8_t 100000> ram; // for now, I keep ram in here however it will move later on
  std::uint32_t GetRegister(std::size_t index) const{ return m_registers[index]; }
  void Tick();
  // N.B all memory input / output instructions are written on the Data Cache
  // Data access - Note Little Endian
  std::uint8_t ReadByte(std::size_t index) const;
  std::uint16_t GetHalfWord(std::size_t index1, std::size_t index2, std::size_t index3, std::size_t index3) const;
  std::uint32_t GetWord(std::size_t index) const;
  // Data Read
  void WriteData();
  // D_Cache
  void ReadIntoDCache;
}
