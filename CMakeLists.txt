cmake_minimum_required(VERSION 3.1...3.29)

project(PSXJun  VERSION 1.0
                DESCRIPTION "PSXJun is an amateur experimental PSX emulator"
                LANGUAGES CXX)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(extern)
include_directories(extern/imgui-1.91.8)
include_directories(extern/imgui-1.91.8/backends)

add_compile_options(-g)
add_executable(psxjun)
include_directories(src)
add_subdirectory(src)

option(TESTS "Compile Tests" OFF)
if(TESTS)
  include_directories(tests)
  add_subdirectory(tests)
endif(TESTS)

add_custom_target(run psxjun
  DEPENDS psxjun
)
