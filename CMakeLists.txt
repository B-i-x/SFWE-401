cmake_minimum_required(VERSION 3.10)

# Name of the project
project(SFWE401_CardGame C)

# Set the C standard (adjust if needed)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Create the executable
add_executable(game old_175_code/main.c)