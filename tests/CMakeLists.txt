project(Tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(tests Test1.cpp)

# linking Google_Tests_run with DateConverter_lib which will be tested
target_link_libraries(tests bigfloat_lib)

target_link_libraries(tests gtest gtest_main)