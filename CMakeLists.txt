cmake_minimum_required(VERSION 3.26)

project(MathLib VERSION 0.1.0 LANGUAGES CXX)
option(BUILD_UNIT_TEST "Build unit tests" ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/MathlibEnableSimd.cmake)

string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" PROCESSOR)

if(PROCESSOR MATCHES "^(x86_64|amd64|x64)$")
    message(STATUS "Target architecture: x86-64")
    set(CPU_X86_64 TRUE)

elseif(PROCESSOR MATCHES "^(x86|i[3-6]86)$")
    message(STATUS "Target architecture: x86")
    set(CPU_X86 TRUE)

elseif(PROCESSOR MATCHES "^(aarch64|arm64)$")
    message(STATUS "Target architecture: ARM64")
    set(CPU_ARM64 TRUE)

elseif(PROCESSOR MATCHES "^arm")
    message(STATUS "Target architecture: ARM")
    set(CPU_ARM TRUE)

else()
    message(WARNING "Unknown architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

if (CPU_ARM64)
set(MATHLIB_SIMD_EXT NEON SVE)
endif()

if (CPU_X86_64)
set(MATHLIB_SIMD_EXT SSE2 AVX AVX2 AVX512F)
endif()

foreach(SIMD_EXT IN LISTS MATHLIB_SIMD_EXT)
    message(STATUS "SIMD extension: ${SIMD_EXT}")
endforeach()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(CTest)

add_subdirectory(Source)