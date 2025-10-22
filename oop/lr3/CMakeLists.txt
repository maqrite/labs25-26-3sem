cmake_minimum_required(VERSION 3.14)

project(LabOOP CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB LIB_SOURCES "src/*.cpp")

add_library(lab_logic STATIC ${LIB_SOURCES})

target_include_directories(lab_logic
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

add_executable(main_app main.cpp)

target_link_libraries(main_app PRIVATE lab_logic)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG       v1.14.0
)

set(FETCHCONTENT_QUIET ON)
FetchContent_MakeAvailable(googletest)

add_executable(test_runner tests/test_runner.cpp)

target_link_libraries(test_runner
  PRIVATE
  lab_logic
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_runner)
