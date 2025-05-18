set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRCS 
      main.cpp

      system/bus.cpp
      system/bus.hpp
      system/psx.cpp
      system/psx.hpp

      memory/memory.cpp
      memory/memory.hpp
      memory/memory_mapping.hpp

      processor/cop0.cpp
      processor/cop0.hpp
      processor/cpu.cpp
      processor/cpu.hpp
      processor/instruction.hpp

      util/util.hpp
      util/util.cpp
)

add_executable(psxjun ${SRCS})

option(DEBUG_BUILD "Compile With Debug Flags" OFF)
if(DEBUG_BUILD)
  message("Compile with Debug Flags On")
  add_compile_options(-g -O0 -Wall -Wextra)
endif(DEBUG_BUILD)

add_custom_target(run psxjun
  DEPENDS psxjun
)
