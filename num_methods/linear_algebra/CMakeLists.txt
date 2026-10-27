set(LINALG_SOURCES
    src/gaussian_elimination.cpp
)

add_library(num_methods_linalg STATIC {LINALG_SOURCES})

target_include_directories(num_methods_linalg
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

