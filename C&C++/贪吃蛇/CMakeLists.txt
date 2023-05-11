cmake_minimum_required(VERSION 3.16)
project(c__test)

set(CMAKE_CXX_STANDARD 17)

add_executable(c__test main.cpp)
target_link_libraries(c__test ncurses)
