cmake_minimum_required(VERSION 3.10)

# Name of the project
project(SFWE401_CardGame C)

# Set the C standard (adjust if needed)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Create the executable
add_executable(game old_175_code/main.c)

# at the bottom of your CMakeLists.txt
if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
  # Tell clang to run its static analyzer
  target_compile_options(game PRIVATE
    -Xclang -analyze
    -Xclang -analyzer-output=html    # emit an HTML report per translation unit
  )
endif()
