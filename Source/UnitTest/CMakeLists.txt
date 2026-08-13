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
    Utils_Test.cpp
    SimdExtension_Test.cpp
    Vector4d_Test.cpp)

add_executable(
        ${PROJECT_NAME}
        ${TEST_SOURCES}
    )

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    MathLib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})




