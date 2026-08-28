cmake_minimum_required(VERSION 3.26)

project(MathLib VERSION 0.1.0 LANGUAGES CXX)
option(MATHLIB_USE_INTRINSIC "Enable INTRINSIC for math classes" OFF)
option(MATHLIB_USE_FMA "Enable INTRINSIC Fma for SIMD wrapper" OFF)

string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" PROCESSOR)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/MathlibEnableSimd.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CpuArchitecture.cmake)

foreach(SIMD_EXT IN LISTS MATHLIB_SIMD_EXT)
    message(STATUS "SIMD extension: ${SIMD_EXT}")
endforeach()


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(CTest)

add_subdirectory(Source)