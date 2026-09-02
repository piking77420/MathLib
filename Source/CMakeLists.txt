cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(MATHLIB_SOURCES
    AVX.hpp
    CpuInstructionSet.cpp
    CpuInstructionSet.hpp
    NEON.hpp
    MathLibHeader.hpp
    Matrix2x2.hpp
    Matrix3x3.hpp
    Matrix4x4.hpp
    MatrixTransformation.hpp
    SSE.hpp
    Vector2.hpp
    Vector3.hpp
    Vector4.hpp)

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

if (MATHLIB_USE_INTRINSIC)
    target_compile_definitions(${PROJECT_NAME} PUBLIC MATH_LIB_INTRINSIC)
endif()

if (MATHLIB_USE_FMA)
    target_compile_definitions(${PROJECT_NAME} PUBLIC SIMD_FMA)
endif()

if (CPU_X86_64 OR CPU_X86)
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" AND MATHLIB_USE_FMA)
        target_compile_options(${PROJECT_NAME} PUBLIC -mfma)
    endif()
endif()


enable_testing()
if (BUILD_UNIT_TEST)
    add_subdirectory(UnitTest)
endif()

if (BUILD_BENCHMARK)
    add_subdirectory(Benchmark)
endif()

