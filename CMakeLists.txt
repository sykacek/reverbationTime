cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(REV)
file(GLOB SOURCES "src/lib/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES} "src/main.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE headers)

add_executable(STATS ${SOURCES} "src/stats_main.cpp")
target_include_directories(STATS PRIVATE src/headers)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
target_compile_options(STATS PRIVATE -Wall)