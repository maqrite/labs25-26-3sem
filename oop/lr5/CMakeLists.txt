cmake_minimum_required(VERSION 3.16)

cmake_minimum_required(VERSION 3.16)

project(PmrStackLab VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.16)

project(PmrStackLab VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/includes)

add_library(resource_lib src/Resource.cpp)
target_include_directories(resource_lib PUBLIC includes)

add_executable(pmr_stack_demo main.cpp)
target_link_libraries(pmr_stack_demo resource_lib)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG    v1.14.0
)

FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)
