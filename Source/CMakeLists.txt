cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
    CompilerDetection.hpp
    Vector4.cpp
    Vector4.hpp
    Vector4d.cpp
    Vector4d.hpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

enable_testing()
if (BUILD_UNIT_TEST)
    add_subdirectory(UnitTest)
endif()