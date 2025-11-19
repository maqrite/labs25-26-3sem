add_executable(unit_tests tests.cpp)

target_link_libraries(unit_tests 
    resource_lib
    gtest_main
)

add_test(NAME PmrStackTests COMMAND unit_tests)
