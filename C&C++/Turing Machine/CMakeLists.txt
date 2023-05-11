cmake_minimum_required(VERSION 3.16)
project(Machine)
SET(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 11)


# 添加源文件
set(SOURCES
        TuringMachineState.cpp
        DenseTuringMachine.cpp
        TuringTape.cpp
        MenuSystem.cpp
        SparseTuringMachine.cpp
        Main.cpp
        )

# 添加头文件
set(HEADERS
        TuringMachineState.h
        DenseTuringMachine.h
        TuringTape.h
        MenuSystem.h
        SparseTuringMachine.h
        TuringMachineState.h)

add_executable(Machine ${SOURCES} ${HEADERS})
