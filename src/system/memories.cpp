#include "memories.hpp"

namespace Jun{

void Bios::Load(std::string&& biosfile){
  std::ifstream biosStream{biosfile, std::ios::binary | std::ios::ate};
  if(biosStream){
    std::size_t size = biosStream.tellg();
    biosStream.seekg(0);
    std::uint8_t buffer[size];
    biosStream.read(reinterpret_cast<char*>(buffer), size);
    std::copy(buffer, buffer + size, m_data.begin());
    std::cout << "SUCCESSFULLY READ BIOS" << '\n';
  }
  else{
    std::cerr << "ERROR IN READING SOURCE PATH FOR BIOS" << '\n';
  }
  m_biosFile = std::move(biosfile);
}

}
