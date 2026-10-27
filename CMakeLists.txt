cmake_minimum_required(VERSION 3.15)
project(ComputationApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CRITICAL FOR NEOVIM: Generates compile_commands.json for clangd autocomplete
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 1. Add the main executable target
add_executable(computation_runner src/main.cpp)

# 2. Tell CMake to process our libraries first
add_subdirectory(num_methods)

# 3. Link our modular libraries into the main executable app
target_link_libraries(computation_runner PRIVATE
    num_methods_calculus
    num_methods_linalg
    num_methods_rootfinding
)

