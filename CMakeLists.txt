cmake_minimum_required(VERSION 3.30)
project(CantStop)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(CantStop main.cpp
        Dice.cpp
        Dice.hpp
        Player.hpp
        Player.cpp
        enums.hpp
        enums.cpp
        tools.cpp
        tools.hpp
        Column.cpp
        Column.hpp
        Game.hpp
        Game.cpp)
