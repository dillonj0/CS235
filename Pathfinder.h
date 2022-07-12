//
// Created by Dillon Jensen on 11/JUL/22.
//

#ifndef PATHFINDER_H
#define PATHFINDER_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
//#include <random>

#include "PathfinderInterface.h"

using namespace std;

class Pathfinder : public PathfinderInterface {
protected: // I put this first so we can use the constants here in the function find_maze_path
    static const int ROW_SIZE = 5;
    static const int COL_SIZE = 5;
    static const int MAZE_DEPTH = 5;
    const int BACKGROUND = 1;
    const int WALL = 0;
    const int TEMPORARY = 2; // Used to show this path has been explored
    const int PATH = 3;
    int maze[ROW_SIZE][COL_SIZE][MAZE_DEPTH]; // To hold values
    vector<string> solution;

public:
    Pathfinder();
    ~Pathfinder();
    string toString() const;
    void createRandomMaze();
    bool importMaze(string file_name);
    vector<string> solveMaze();

    bool find_maze_path(int grid[ROW_SIZE][COL_SIZE][MAZE_DEPTH], int r, int c, int l);
};

#endif