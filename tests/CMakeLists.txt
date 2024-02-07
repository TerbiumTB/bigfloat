project(Tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests aritmetics_tests.cpp
        pi_tests.cpp)

target_link_libraries(tests bigfloat_lib)
target_link_libraries(tests pi_lib)

target_link_libraries(tests gtest gtest_main)