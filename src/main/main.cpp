#include "./../system/psx.hpp"
#include "./../memory/memory.hpp"

using namespace psxjun::system;
using namespace psxjun::memory;

int main(){
  Psx system{"./../rom/SCPH1001.BIN"};
  system.run(100);
  /*
  Bios b{"./../rom/SCPH1001.BIN"};
  Bios& bios = b;
  std::cout << (unsigned)b[0] << '\n';
  */
}
