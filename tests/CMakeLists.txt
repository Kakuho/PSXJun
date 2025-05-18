set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message("Compiling Tests")
add_compile_options(-g -O0 -Wall -Wextra)
set(SRCS
      main.cpp
)

add_executable(tests ${SRCS})

add_custom_target(run-tests tests
  DEPENDS tests
)
