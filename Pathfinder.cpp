//
// Created by Dillon Jensen on 7/11/22.
//
#include "Pathfinder.h"
#include <fstream>
using namespace std;

// g++ -std=c++11 main.cpp Pathfinder.cpp -o Lab4
////       *** 7-5 in the book ***

Pathfinder::Pathfinder() {
    cout << endl;
    cout << "Starting process ..." << endl;
    // I guess we want the maze array to be all 1s to start.
    for (int i = 0; i < ROW_SIZE; i++){
        for (int j = 0; j < COL_SIZE; j++){
            for (int k = 0; k < MAZE_DEPTH; k++){
                maze[i][j][k] = 1;
            }
        }
    }
    // The maze should be full of 1s now.
}
Pathfinder::~Pathfinder() {
    cout << "*** PROCESS ENDED. ***" << endl;
}
//
////Part 1-----------------------------------------------------------------------------------
///*
//* toString
//*
//* Returns a string representation of the current maze. Returns a maze of all 1s if no maze
//* has yet been generated or imported.
//*
//* A valid string representation of a maze consists only of 125 1s and 0s (each separated
//* by spaces) arranged in five 5x5 grids (each separated by newlines) with no trailing newline. A valid maze must
//* also have 1s in the entrance cell (0, 0, 0) and in the exit cell (4, 4, 4).
//*
//* Cell (0, 0, 0) is represented by the first number in the string representation of the
//* maze. Increasing in x means moving toward the east, meaning cell (1, 0, 0) is the second
//* number. Increasing in y means moving toward the south, meaning cell (0, 1, 0) is the
//* sixth number. Increasing in z means moving downward to a new grid, meaning cell
//* (0, 0, 1) is the twenty-sixth cell in the maze. Cell (4, 4, 4) is represented by the last number.
//*
//* Returns:		string
//*				A single string representing the current maze
//*/
string Pathfinder::toString() const {
//    int tempMaze[ROW_SIZE][COL_SIZE][MAZE_DEPTH];
    string mazeString = "";
    for (int i = 0; i < MAZE_DEPTH; i++) {
        for (int j = 0; j < ROW_SIZE; j++) {
            for (int k = 0; k < COL_SIZE; k++) {
                mazeString = mazeString + to_string(maze[k][j][i]) + " ";
            }
            mazeString = mazeString + "\n";
        }
        mazeString = mazeString + "\n";
    }
    cout << "*** mazeString: ***" << endl;
    cout << mazeString;
    cout << "*** string finished. ***" << endl;
    return mazeString;
}
//
///*
//* createRandomMaze
//*
//* Generates a random maze and stores it as the current maze.
//*
//* The generated maze must contain a roughly equal number of 1s and 0s and must have a 1
//* in the entrance cell (0, 0, 0) and in the exit cell (4, 4, 4).  The generated maze may be
//* solvable or unsolvable, and this method should be able to produce both kinds of mazes.
//*/
void Pathfinder::createRandomMaze() {
//    int tempMaze[ROW_SIZE][COL_SIZE][MAZE_DEPTH];
    for (int i = 0; i < ROW_SIZE; i++){
        for (int j = 0; j < COL_SIZE; j++){
            for (int k = 0; k < MAZE_DEPTH; k++){
                maze[i][j][k] = rand() % 2;
            }
        }
    }
    maze[0][0][0] = 1;
    maze[ROW_SIZE - 1][COL_SIZE - 1][MAZE_DEPTH - 1] = 1;
}
////-----------------------------------------------------------------------------------------
//
////Part 2-----------------------------------------------------------------------------------
///*
//* importMaze
//*
//* Reads in a maze from a file with the given file name and stores it as the current maze.
//* Does nothing if the file does not exist or if the file's data does not represent a valid
//* maze.
//*
//* The file's contents must be of the format described above to be considered valid.
//*
//* Parameter:	file_name
//*				The name of the file containing a maze
//* Returns:		bool
//*				True if the maze is imported correctly; false otherwise
//*/
bool Pathfinder::importMaze(string file_name) {
    cout << "Importing file " << file_name << "..." <<endl;
    ifstream inFile;
    inFile.open(file_name);

    string temp;
    int tempMaze[ROW_SIZE][COL_SIZE][MAZE_DEPTH];
    for (int i = 0; i < MAZE_DEPTH; i++) {
        for (int j = 0; j < ROW_SIZE; j++) {
            for (int k = 0; k < COL_SIZE; k++) {
                inFile >> tempMaze[k][j][i]; //Row, column, depth
                if (tempMaze[k][j][i] != 0 && tempMaze[k][j][i] != 1) {
                    inFile.close();
                    cout << "There was an error: " << endl;
                    cout << tempMaze[k][j][i] << " was read at "
                        << k << " " << j << " " << i << " " << endl;
//                    outFile << file_name << " failed due to improper maze content at "
//                            << k << " " << j << " " << i << endl;
                    return false;
                }
            }
        }
    }
    int extraLineCheck;
    if (inFile >> extraLineCheck){
        // disqualifies any maze with a 126th data point o_<
        cout << "File has an extra layer of data: invalid." << endl;
//        outFile << file_name << " failed due to extra data" << endl;
        return false;
    }
    if (tempMaze[0][0][0] != 1 || tempMaze[ROW_SIZE - 1][COL_SIZE - 1][MAZE_DEPTH - 1] != 1){
        //disqualify maze: start and/or finish is not open
        cout << "Maze entrance or exit is invalid." << endl;
//        outFile << file_name << " failed due to blocked entrance/exit" << endl;
        return false;
    }
    cout << "Writing tempMaze to object maze ..." << endl;
    for (int i = 0; i < MAZE_DEPTH; i++) {
        for (int j = 0; j < ROW_SIZE; j++) {
            for (int k = 0; k < COL_SIZE; k++) {
                maze[i][j][k] = tempMaze[i][j][k]; //Row, column, depth
            }
        }
    }
    cout << "Done importing." << endl;
    inFile.close();
    return true;
}
////-----------------------------------------------------------------------------------------
//
////Part 3-----------------------------------------------------------------------------------
///*
//* solveMaze
//*
//* Attempts to solve the current maze and returns a solution if one is found.
//*
//* A solution to a maze is a list of coordinates for the path from the entrance to the exit
//* (or an empty vector if no solution is found). This list cannot contain duplicates, and
//* any two consecutive coordinates in the list can only differ by 1 for only one
//* coordinate. The entrance cell (0, 0, 0) and the exit cell (4, 4, 4) should be included
//* in the solution. Each string in the solution vector must be of the format "(x, y, z)",
//* where x, y, and z are the integer coordinates of a cell.
//*
//* Understand that most mazes will contain multiple solutions
//*
//* Returns:		vector<string>
//*				A solution to the current maze, or an empty vector if none exists
//*/
vector<string> Pathfinder::solveMaze() {
    find_maze_path(maze, 0, 0, 0);
    for(auto s:solution) {
        cout << s << endl;
    }
    return solution;
}
////-----------------------------------------------------------------------------------------
bool Pathfinder::find_maze_path(int grid[ROW_SIZE][COL_SIZE][MAZE_DEPTH], int r, int c, int l) {
    int tempGrid[ROW_SIZE][COL_SIZE][MAZE_DEPTH];
    //Write copy of maze, so we can modify it and
    //      later refer to our changes etc.
    for (int i = 0; i < MAZE_DEPTH; i++) {
        for (int j = 0; j < ROW_SIZE; j++) {
            for (int k = 0; k < COL_SIZE; k++) {
                tempGrid[i][j][k] = grid[i][j][k]; //Row, column, depth
            }
        }
    }
    // r, c, l = row, column, level
    cout << "find_maze_path ["<<r<<"]["<<c<<"]["<<l<<"]"<<endl;
//    cout << this->toString(); //Will print out a lot of text
    if (r < 0 || c < 0 || l < 0 || r >= ROW_SIZE || c >= COL_SIZE || l >=MAZE_DEPTH)
        return false;      // Cell is out of bounds.
    else if (tempGrid[r][c][l] != BACKGROUND)
        return false;      // Cell is on barrier or dead end.
    else if (r == ROW_SIZE - 1 && c == COL_SIZE - 1 && l == MAZE_DEPTH - 1) {
        tempGrid[r][c][l] = PATH;         // Cell is on path
        solution.push_back("("+to_string(r)+","+to_string(c)+","+ to_string(l)+")");
        return true;               // and is maze exit.
    }
    else {
        // Recursive case.
        // Attempt to find a path from each neighbor.
        // Tentatively mark cell as on path.
        tempGrid[r][c][l] = PATH;
        if (find_maze_path(tempGrid, r - 1, c, l) // Up
            || find_maze_path(tempGrid, r + 1, c, l) // Down
            || find_maze_path(tempGrid, r, c - 1, l) // Left
            || find_maze_path(tempGrid, r, c + 1, l) // Right
            || find_maze_path(tempGrid, r, c, l - 1) // In
            || find_maze_path(tempGrid, r, c, l + 1) // Out
            ) {
            solution.push_back("(" + to_string(r) + ", " + to_string(c) + ", " + to_string(l) + ")");
            return true;
        }
        else {
            tempGrid[r][c][l] = TEMPORARY;  // Dead end.
            return false;
        }
    }
}