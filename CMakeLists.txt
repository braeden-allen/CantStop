cmake_minimum_required(VERSION 3.30)
project(CantStop)

set(CMAKE_CXX_STANDARD 20)

add_executable(CantStop main.cpp
        Dice.cpp
        Dice.h
        Player.h
        Player.cpp
        enums.hpp
        enums.cpp
        tools.cpp
        tools.hpp
        Column.cpp
        Column.hpp)
