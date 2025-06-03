set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(DEBUG_BUILD "Compile With Debug Flags" OFF)
if(DEBUG_BUILD)
  message("Compile with Debug Flags On")

endif(DEBUG_BUILD)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

set(IMGUI_DIR ./../extern/imgui-1.91.8)

set(SRCS 
      main.cpp

      mips_r3000a/mips_manager.cpp
      mips_r3000a/mips_state.cpp

      mips_r3000a/interpreter/interpreter.cpp

      mips_r3000a/interpreter/impl/arithmetic_impl.cpp
      mips_r3000a/interpreter/impl/comparison_impl.cpp
      mips_r3000a/interpreter/impl/coprocessor_impl.cpp
      mips_r3000a/interpreter/impl/jump_impl.cpp
      mips_r3000a/interpreter/impl/load_impl.cpp
      mips_r3000a/interpreter/impl/logical_impl.cpp
      mips_r3000a/interpreter/impl/multiply_divide_impl.cpp
      mips_r3000a/interpreter/impl/shifting_impl.cpp
      mips_r3000a/interpreter/impl/store_impl.cpp

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

set(DEBUGGER_SRC
    debugger/runtime.cpp
    debugger/menubar.cpp
    debugger/widgets/executor.cpp
    debugger/widgets/registers.cpp
)

set(IMGUI_FRONTEND
      ${IMGUI_DIR}/imgui.cpp
      ${IMGUI_DIR}/imgui_demo.cpp
      ${IMGUI_DIR}/imgui_draw.cpp
      ${IMGUI_DIR}/imgui_tables.cpp
      ${IMGUI_DIR}/imgui_widgets.cpp
)

set(IMGUI_BACKEND
      ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
      ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_compile_options(-g -O0 -Wall -Wextra)
target_link_libraries(psxjun glfw OpenGL)
target_sources(psxjun PRIVATE ${SRCS} ${DEBUGGER_SRC} 
                              ${IMGUI_FRONTEND} ${IMGUI_BACKEND})
