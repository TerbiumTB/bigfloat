cmake_minimum_required(VERSION 3.26)
project(bigfloat)

set(CMAKE_CXX_STANDARD 20)
#include(cmake-build-debug/Core.cmake)

add_executable(main main.cpp)
add_executable(pi pi_lib/pi.cpp)

include_directories(bigfloat_lib)
add_subdirectory(bigfloat_lib)

include_directories(pi_lib)
add_subdirectory(pi_lib)



target_link_libraries(main bigfloat_lib)
target_link_libraries(pi bigfloat_lib)

add_subdirectory(Tests)
enable_testing()

#include(FetchContent)
#FetchContent_Declare(
#        lib
#        # Specify the commit you depend on and update it regularly.
#        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
#)
#
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(lib)
#
#target_link_libraries(main lib)