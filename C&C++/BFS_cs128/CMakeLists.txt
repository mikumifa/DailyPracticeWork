cmake_minimum_required(VERSION 3.16)
project(BFS_cs128)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "*.cc")
file(GLOB HEADERS "*.hpp")

# 生成可执行文件
add_executable(BFS_cs128 ${SOURCES} ${HEADERS})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})