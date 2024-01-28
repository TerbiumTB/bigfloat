cmake_minimum_required(VERSION 3.26)
project(very_long_float)

set(CMAKE_CXX_STANDARD 20)
include(cmake-build-debug/Core.cmake)

add_library(bigfloat STATIC
        bigfloat.cpp
        bigfloat.h)

add_executable(main main.cpp)
target_link_libraries(main bigfloat)

