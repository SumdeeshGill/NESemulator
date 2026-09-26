cmake_minimum_required(VERSION 3.16)

project(NESemulator
VERSION 0.1
LANGUAGES C
)

# Use C17

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Put the executable in the build directory

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Find SDL2

find_package(SDL2 REQUIRED)

# Find all C source files

file(GLOB_RECURSE SOURCES
CONFIGURE_DEPENDS
${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

# Create the emulator executable

add_executable(NESemulator ${SOURCES})

# Tell the compiler where our headers are

target_include_directories(NESemulator PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link SDL2

target_link_libraries(NESemulator PRIVATE
SDL2::SDL2
)