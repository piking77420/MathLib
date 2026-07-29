cmake_minimum_required(VERSION 3.26)

project(UnitTest VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL
        https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# Prevent GoogleTest from overriding the MSVC runtime configuration.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        Vector4d_Test.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        MathLib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})