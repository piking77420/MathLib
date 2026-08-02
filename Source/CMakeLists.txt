cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(MATHLIB_SOURCES 
    CpuInstructionSet.cpp
    CpuInstructionSet.hpp
    CompilerDetection.hpp
    Vector4.cpp
    Vector4.hpp
    Vector4d.cpp
    Vector4d.hpp)

function(add_mathlib_variant level)
    string(TOLOWER "${level}" level_lower)

    set(library_target "MathLib_${level}")
    set(executable_target "MathTest_${level}")

    add_library(
        ${library_target}
        STATIC
        ${MATHLIB_SOURCES}
    )

    target_include_directories(
        ${library_target}
        PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    mathlib_enable_simd(${library_target} ${level})
endfunction()

foreach(SIMD_EXT IN LISTS MATHLIB_SIMD_EXT)
    add_mathlib_variant(${SIMD_EXT})
endforeach()

enable_testing()
if (BUILD_UNIT_TEST)
    add_subdirectory(UnitTest)
endif()

