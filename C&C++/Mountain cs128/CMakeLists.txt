cmake_minimum_required(VERSION 3.16)
project(Mountain)

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ../)
add_executable(Mountain  Color.cc  Color.hpp  Grayscale_image.hpp  Path.cc  Path.hpp  Path_image.cc  Path_image.hpp  elevation_dataset.cc  elevation_dataset.hpp  grayscale_image.cc  main.cpp)
