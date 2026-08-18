cmake_minimum_required(VERSION 3.26)

project(MathLibBenchmark VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    benchmark
    URL https://github.com/google/benchmark/archive/refs/tags/v1.9.5.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# We don't need to build Google's own benchmark tests.
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_EXCEPTIONS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(benchmark)

set(BENCHMARK_SOURCES
    Alloc.cpp
    Alloc.hpp
    BenchmarkHeader.hpp
    Vector2d_Benchmark.cpp
    Vector4d_Benchmark.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${BENCHMARK_SOURCES}
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        MathLib
        benchmark::benchmark_main
)