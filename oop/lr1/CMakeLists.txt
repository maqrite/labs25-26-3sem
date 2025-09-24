cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc-14")
set(CMAKE_CXX_COMPILER "g++-14")

project(VowelCounter)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(my_functions function.cpp)

add_executable(app main.cpp)

target_link_libraries(app PRIVATE my_functions)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(run_tests test.cpp)

target_link_libraries(run_tests PRIVATE my_functions GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(run_tests)
