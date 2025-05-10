cmake_minimum_required(VERSION 3.10)

# Name of the project
project(SFWE401_CardGame C)

# Set the C standard (adjust if needed)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Create the executable
add_executable(game old_175_code/main.c)

if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
  target_compile_options(game PRIVATE
    "-Xclang"                # switch to front-end mode
    "-analyze"               # run the analyzer
    "-Xclang"                # again prefix for the next front-end flag
    "-analyzer-output=html"  # tell it to emit HTML reports
  )
endif()

