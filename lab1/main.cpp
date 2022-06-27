//
// Created by Dillon Jensen on 27/JUN/2022
//

#include <iostream>
#include "TodoListInterface.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

/*
 * FUNCTIONALITY OF FINISHED PRODUCT
 *
 * * [ ] Store tasks in a text file
 * * * * DAY (due date)
 * * * * EVENT (event)
 *
 * * [ ] Four functions
 * * * * 1) Add a task
 * * * * * * * ./TODO add <date> <task>
 * * * * 2) Remove a task
 * * * * * * * ./TODO remove <task>
 * * * * 3) Print all the tasks on the list
 * * * * * * * ./TODO printList
 * * * * 4) Print everything for a specific day
 * * * * * * * ./TODO printDay <day>
 *
 * * [ ] main.cpp only calls the four pure virtual functions
 *          in TodoListInterface.h
 * * * * ---> Essentially, you can run your program using
 *              anyone else's main.cpp with your interface file.
 */