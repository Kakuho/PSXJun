#include "system/psx_system.hpp"

int main(){
  Jun::PsxSystem system{};
  system.GetMemmap().LoadBios("./../rom/SCPH1001.BIN");
  system.Run(500);
}
