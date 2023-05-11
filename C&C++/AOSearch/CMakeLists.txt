cmake_minimum_required(VERSION 3.23)
project(project_c)

set(CMAKE_CXX_STANDARD 14)

include_directories(./CMakeProject1)

add_executable(project_c
        ./CMakeProject1/AOsearch.cpp
        ./CMakeProject1/Lib.cpp
        ./CMakeProject1/Lib.h)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/222000229)