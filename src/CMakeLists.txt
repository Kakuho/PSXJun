set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRCS 
      main.cpp

      mips_r3000a/mips_manager.cpp
      mips_r3000a/mips_state.cpp
      mips_r3000a/opcode_table.cpp

      mips_r3000a/interpreter/interpreter.cpp
      mips_r3000a/interpreter/alu_impl.cpp
      mips_r3000a/interpreter/load_store_impl.cpp

      mips_r3000a/cop0/cop0_state.cpp
      mips_r3000a/cop0/misc_register.cpp
      mips_r3000a/cop0/status_register.cpp
      mips_r3000a/cop0/tbl_register_pair.cpp

      system/memories.cpp
      system/memory_manager.cpp
      system/mmio.cpp
      system/psx_system.cpp

      common/register_base.cpp
)

option(DEBUG_BUILD "Compile With Debug Flags" OFF)
if(DEBUG_BUILD)
  message("Compile with Debug Flags On")
  add_compile_options(-g -O0 -Wall -Wextra)
endif(DEBUG_BUILD)

target_sources(psxjun PRIVATE ${SRCS})
