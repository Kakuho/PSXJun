#include "memory.hpp"

// PSX BIOS

Bios::Bios(std::string file): 
  m_biosPath{std::move(file)}, 
  m_ifst{m_biosPath, std::ios::binary | std::ios::ate}{
  if(m_ifst){
    std::size_t size = m_ifst.tellg();
    m_ifst.seekg(0);
    std::uint8_t buffer[size];
    m_ifst.read(reinterpret_cast<char*>(buffer), size);
    std::copy(buffer, buffer + size, m_data.begin());
    std::cout << "SUCCESSFULLY READ BIOS" << '\n';
  }
  else{
    std::cerr << "ERROR IN READING SOURCE PATH FOR BIOS" << '\n';
  }
}

void Bios::Dump() const{
  std::size_t i = 0;
  for(std::uint8_t byte: m_data){
    std::bitset<8> bits{ byte };
    std::cout << std::setw(2) << std::setfill('0') << std::hex << bits.to_ulong(); // very slow
    i++;
    if(i % 16 == 0){
      std::cout << '\n';
    }
    else if(i % 8 == 0){
      std::cout << "\t\t";
    }
    else{
      std::cout << ' ';
    }
  }
}


