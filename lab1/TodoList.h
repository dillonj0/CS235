//
// Created by Dillon Jensen on 6/27/22.
//

#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <iostream>
#include <string>
#include "TodoListInterface.h"

using namespace std;

class TodoList: public TodoListInterface {
public:
    TodoList() {
        cout << "In constructor" << endl;
    } //in cpp
    virtual ~TodoList() {
        cout << "In destructor" << endl;
    }
    //in cpp
    virtual void add(string _duedate, string _task) {
        cout << "In add" << endl;
    } // = 0;
    virtual int remove(string _task) {
        cout << "int remorve" << endl;
    } //= 0;
    virtual void printTodoList() {
        cout << "in print list" << endl;
    }//= 0;
    virtual void printDaysTasks(string _date) {
        cout << "In pintrdays" << endl;
    } //= 0;
};

#endif //TODO_LIST_H

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


/*
 *
****************** My original version ******************
#ifndef LAB1_TODOLISTINTERFACE_H
#define LAB1_TODOLISTINTERFACE_H

#include <iostream>
#include <list> //?

//using namespace std;

class TodoList {
public:
    TodoList(); //default constructor
    std::string GetTask();
    void AddTask(std::string task, std::string date);
    void RemoveTask(std::string task);
    void PrintList();
    void PrintDay();
private:
    list<std::string>
};

#endif
 */