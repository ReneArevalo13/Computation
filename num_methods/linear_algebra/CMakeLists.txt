cmake_minimum_required(VERSION 3.15)

# fetch dependencies
include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)

set(LINALG_SOURCES
    src/gaussian_elimination.cpp
    src/matrix_io.cpp
)

add_library(num_methods_linalg STATIC ${LINALG_SOURCES})

target_include_directories(num_methods_linalg
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(linalg_tests
    tests/test_guassian_elimination.cpp
)

target_link_libraries(linalg_tests
    PRIVATE
        num_methods_linalg
        Catch2::CatchWithMain
)

add_test(NAME LinAlgMatrixTests COMMAND linalg_tests)

