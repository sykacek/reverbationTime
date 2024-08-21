cmake_minimum_required(VERSION 3.13)
project("Test reverbation API")

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(tests_exe ../src/libs/*c)

target_include_directories(tests_exe
    PRIVATE
    $(GTEST_INCLUDE_DIRS))

target_link_libraries(tests_exe
    PRIVATE
    GTest::GTest)

target_compile_options(tests_exe PRIVATE -Wall)