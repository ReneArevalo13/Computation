cmake_minimum_required(VERSION 3.15)
project(ComputationApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# DEBUG 
#if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
#   add_link_options(-fsanitize=address)
#endif()

# Enforce global automated test tracking
enable_testing()

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

