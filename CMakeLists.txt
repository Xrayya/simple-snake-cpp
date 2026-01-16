cmake_minimum_required(VERSION 3.16)

project(
    snake
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(snake ${SOURCES})

target_include_directories(snake PRIVATE src)

target_compile_options(snake PRIVATE
    -Wall
    -Wextra
    -g
    -O0
)

