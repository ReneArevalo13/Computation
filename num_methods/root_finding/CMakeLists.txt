# Create the static library target out of your source files
add_library(num_methods_rootfinding STATIC src/rootfinding.cpp)

# Tell anyone linking to this library where its header files live
target_include_directories(num_methods_rootfinding
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

