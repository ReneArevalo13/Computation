add_library(num_methods_calculus STATIC src/calculus.cpp)

target_include_directories(num_methods_calculus
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
