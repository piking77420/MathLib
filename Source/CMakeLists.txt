cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(MATHLIB_SOURCES 
    CpuInstructionSet.cpp
    CpuInstructionSet.hpp
    MathLibHeader.hpp
    Vector2.cpp
    Vector2.hpp
    Vector2d.cpp
    Vector2d.hpp
    Vector4.cpp
    Vector4.hpp
    Vector4d.cpp
    Vector4d.hpp)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${MATHLIB_SOURCES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

foreach(SIMD_EXT IN LISTS MATHLIB_SIMD_EXT)
        mathlib_enable_simd(${PROJECT_NAME} ${SIMD_EXT})
endforeach()

enable_testing()
if (BUILD_UNIT_TEST)
    add_subdirectory(UnitTest)
endif()

