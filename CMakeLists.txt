cmake_minimum_required(VERSION 2.8)
project(minalist-map C)
include (CTest)
enable_testing()

include_directories(include)
add_library(minimalist_map src/map.c)

add_executable(run_tests tests/test_map.c)
target_link_libraries(run_tests minimalist_map)
add_test(test_map run_tests)
