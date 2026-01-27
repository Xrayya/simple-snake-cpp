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

    -Wdeprecated-copy
    -Wdangling
    -Wunused-private-field
    -Wshadow
    -Wnon-virtual-dtor
    -Wweak-vtables
    -Woverloaded-virtual
    -Wsuggest-override
    -Wlifetime
    -Wslicing

    -Werror=sign-compare
    -Werror=return-type
    -Werror=unreachable-code
    -Werror=missing-field-initializers
    -Werror=conversion
    -Werror=missing-field-initializers
    -Werror=deprecated-copy
    -Werror=dangling
    -Werror=non-virtual-dtor
    -Werror=weak-vtables
    -Werror=overloaded-virtual
    -Werror=suggest-override
    -Werror=lifetime
    -Werror=slicing
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

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  message(STATUS "Optimizing for Release build")

    target_compile_options(snake PRIVATE
      -O2
    )

    target_link_options(snake PRIVATE
      -O2
    )
endif()

# ========================
# Fetch raylib
# ========================

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
    message(STATUS "raylib ${RAYLIB_VERSION} not found")
  include(FetchContent)
  FetchContent_Declare(
      raylib
      GIT_REPOSITORY https://github.com/raysan5/raylib.git
      GIT_TAG ${RAYLIB_VERSION}
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    message(STATUS "Populating raylib ${RAYLIB_VERSION}...")
    set(FETCHCONTENT_QUIET NO)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
  endif()
endif()

target_link_libraries(snake PRIVATE raylib)
