cmake_minimum_required(VERSION 3.26)

project(UnitTest VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL
        https://github.com/google/googletest/archive/fa8438ae6b70c57010177de47a9f13d7041a6328.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# Prevent GoogleTest from overriding the MSVC runtime configuration.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

set(TEST_SOURCES
    SimdExtension_test.cpp
    Vector4d_Test.cpp)

function(add_buildTest_variant level)
    set(MATH_LIB_TARGET "MathLib_${level}")
    set(EXECUTABLE_TARGET "${PROJECT_NAME}_${level}")

    add_executable(
        ${EXECUTABLE_TARGET}
        ${TEST_SOURCES}
    )

    target_link_libraries(
        ${EXECUTABLE_TARGET}
        PRIVATE
            ${MATH_LIB_TARGET}
            GTest::gtest_main
    )
    include(GoogleTest)
    gtest_discover_tests(${EXECUTABLE_TARGET})
endfunction()

foreach(SIMD_EXT IN LISTS MATHLIB_SIMD_EXT)
    add_buildTest_variant(${SIMD_EXT})
endforeach()



