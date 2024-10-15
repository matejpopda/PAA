# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(PAA_projekt VERSION 1.0.0)

# Set the C++ standard (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(include)

# Add source files to the executable
add_executable(code src/main.cpp)

# Optionally link external libraries
# target_link_libraries(MyExecutable some_library)

# For unit tests (if using them), you can create separate test executables
# add_executable(MyTests tests/test_main.cpp)
