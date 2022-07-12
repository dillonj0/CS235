//
// Created by Dillon Jensen on 7/11/22.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Pathfinder.h"

int main() {
    Pathfinder* pathptr = NULL;
    pathptr = new Pathfinder();
    pathptr->importMaze("3D_Maze.txt");
    cout << pathptr->toString();
    pathptr->solveMaze();
    exit(0);
}