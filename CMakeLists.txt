cmake_minimum_required(VERSION 3.26)

project(MathLib VERSION 0.1.0 LANGUAGES CXX)
option(BUILD_UNIT_TEST "Build unit tests" ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(CTest)

add_subdirectory(Source)