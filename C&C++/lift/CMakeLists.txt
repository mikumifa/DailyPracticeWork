cmake_minimum_required(VERSION 3.16)
project(line C)

set(CMAKE_C_STANDARD 11)
find_package(Threads)

add_executable(line assignment2_handout.c lift.h)
target_link_libraries(line ${CMAKE_THREAD_LIBS_INIT})
