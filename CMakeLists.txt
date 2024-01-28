cmake_minimum_required(VERSION 3.26)
project(very_long_float)

set(CMAKE_CXX_STANDARD 20)
include(cmake-build-debug/Core.cmake)

add_executable(very_long_float main.cpp)

add_library(ver_lon_float STATIC main.cpp
        bigfloat.cpp
        bigfloat.h)