cmake_minimum_required(VERSION 3.15)
project(MultimediaDatabase)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include path
include_directories(${CMAKE_SOURCE_DIR}/include)


# Recursively collect all source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
    MDB.cpp
)

# Create the executable
add_executable(MDB ${SOURCES})
