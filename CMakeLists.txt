cmake_minimum_required(VERSION 2.8)

project(minalist-map C)
set(PROJECT_VERSION "1.0.0")

include (CTest)
enable_testing()

include_directories(include)
add_library(minimalist_map src/map.c)

install(TARGETS minimalist_map LIBRARY DESTINATION lib)
install(DIRECTORY include/minimalist DESTINATION include
  FILES_MATCHING PATTERN "*.h")
if (UNIX)
  configure_file(minimalist-map.pc.in minimalist-map.pc @ONLY)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/minimalist-map.pc
    DESTINATION lib/pkgconfig)
endif()


add_executable(run_tests tests/test_map.c)
target_link_libraries(run_tests minimalist_map)
add_test(test_map run_tests)
