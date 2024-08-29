cmake_minimum_required(VERSION 3.13)
project("Unit Test reverbation API")

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tests_exe "../src/lib/txt_file.cpp" "test.cpp")
add_compile_definitions(PATHS_DO_NOT_DEFINE)

target_include_directories(tests_exe
    PRIVATE
    $(GTEST_INCLUDE_DIRS))

target_link_libraries(tests_exe
    PRIVATE
    GTest::GTest)

target_compile_options(tests_exe PRIVATE -Wall -ggdb -O0)