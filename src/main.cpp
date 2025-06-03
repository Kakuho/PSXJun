#include "system/psx_system.hpp"
#include "debugger/runtime.hpp"

int main(){
  Jun::PsxSystem system{};
  system.GetMemmap().LoadBios("./../rom/SCPH7001.BIN");
  Debug::StartRuntime(system);
  //system.Run(500);
}
