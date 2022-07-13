cmake_minimum_required(VERSION 3.20)
project(lab4)

set(CMAKE_CXX_STANDARD 14)

include_directories(Maze-Lab)

add_executable(lab4
        Maze-Lab/altmain.cpp
        Maze-Lab/main.cpp
        Maze-Lab/Pathfinder.cpp
        Maze-Lab/Pathfinder.h
        Maze-Lab/PathfinderInterface.h)
