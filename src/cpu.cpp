std::

// The MIPS ISA contains fixed size 32-bit instructions.
std::uint32_t CPU::GetIntruction() const{
  std::uint32_t buffer = GetWord(ram[pc[0]], ram[pc[1]], ram[pc[2]], ram[pc[3]]);
}
