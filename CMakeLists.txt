cmake_minimum_required(VERSION 3.10)
project(memory-arena)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add include path so both main and tests can find the header
include_directories(include)

# Main executable
add_executable(memory_arena_demo src/main.cpp)

# Google Test setup
enable_testing()
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(memory_arena_tests tests/memory_arena_test.cpp)
target_link_libraries(memory_arena_tests gtest_main)

# Register the tests
include(GoogleTest)
gtest_discover_tests(memory_arena_tests)
