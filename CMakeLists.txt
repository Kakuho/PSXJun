cmake_minimum_required(VERSION 3.7...3.27)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(PSXJun  VERSION 1.0
                DESCRIPTION "PSXJun is a amateur experimental PSX emulator"
                LANGUAGES CXX)

# ThirdParty
add_executable(PSXJun
                src/main/main.cpp

                src/system/bus.cpp
                src/system/bus.hpp
                src/system/psx.cpp
                src/system/psx.hpp

                src/memory/memory.cpp 
                src/memory/memory.hpp
                src/memory/memory_mapping.hpp


                src/processor/cop0.cpp 
                src/processor/cop0.hpp
                src/processor/cpu.cpp 
                src/processor/cpu.hpp
                src/processor/instruction.hpp
                )
