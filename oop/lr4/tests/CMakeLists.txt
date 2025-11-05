include_directories(${PROJECT_SOURCE_DIR}/includes)

add_executable(lr4_tests
  test_main.cpp
  test_array.cpp
  test_polygon.cpp
)

target_link_libraries(lr4_tests
  PRIVATE
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(lr4_tests)
