cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(convex_billiard)

# Include headers from "include/"
include_directories(include)

# Find raylib (assumes raylib is installed)
find_package(raylib REQUIRED)

# Define your source files
set(SOURCES
    src/main.cpp
    src/simulation.cpp
)

# Create the executable
add_executable(convex_billiard ${SOURCES})

# Link raylib to your project
target_link_libraries(convex_billiard PRIVATE raylib)
