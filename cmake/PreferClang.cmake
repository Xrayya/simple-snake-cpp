# PreferClang.cmake
if (NOT CMAKE_CXX_COMPILER)
    find_program(CLANGXX clang++)
    find_program(CLANG clang)

    if (CLANGXX AND CLANG)
        message(STATUS "Clang found. Forcing Clang as compiler.")
        set(CMAKE_C_COMPILER ${CLANG} CACHE STRING "" FORCE)
        set(CMAKE_CXX_COMPILER ${CLANGXX} CACHE STRING "" FORCE)
    else()
        message(STATUS "Clang not found. Falling back to default compiler.")
    endif()
endif()
