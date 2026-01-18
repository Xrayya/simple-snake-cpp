cmake_minimum_required(VERSION 3.16...4.99)

project(
    snake
    VERSION 0.1
    LANGUAGES CXX
)

# ========================
# Global C++ config
# ========================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ========================
# Sources
# ========================
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(snake ${SOURCES})
target_include_directories(snake PRIVATE src)

# ========================
# Warnings (always on)
# ========================
target_compile_options(snake PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# ========================
# Debug-only flags
# ========================
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring Debug build with sanitizers")

    target_compile_options(snake PRIVATE
        -g
        -O0
        -fno-omit-frame-pointer
        -fsanitize=address
        -fsanitize=undefined
    )

    target_link_options(snake PRIVATE
        -fsanitize=address
        -fsanitize=undefined
    )
endif()

# ========================
# Fetch raylib
# ========================
include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)

# Safe defaults for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)

target_link_libraries(snake PRIVATE raylib)

