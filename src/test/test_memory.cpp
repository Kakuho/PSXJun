#include "./../memory.hpp"

void testBios(){
  Bios bs{"./../../rom/SCPH5500.BIN"};
  bs.Dump();
}

int main(){
  testBios();
}
