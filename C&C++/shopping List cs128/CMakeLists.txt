cmake_minimum_required(VERSION 3.16)
project(shopingList)

set(CMAKE_CXX_STANDARD 14)

add_executable(shopingList main.cpp Item.hpp Shoppinglist.cc Shoppinglist.hpp)
