//
// Created by Dillon Jensen on 6/27/22.
//

#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "TodoListInterface.h"

using namespace std;

class TodoList: public TodoListInterface {
public:
    vector <string> tasks;
    TodoList() {
//        cout << "In constructor" << endl;
        string line;
        ifstream inFile("TODOList.txt");
        if(inFile.is_open()){
            while (getline (inFile, line)){
//                cout << line << endl;
                tasks.push_back(line);
            }
            inFile.close();
        }
        else{
            cout << "Could not open TODOList.txt" << endl;
        }
    }

    virtual ~TodoList() {
        cout << "... How would you like to proceed?" << endl;
        ofstream outfile;
        outfile.open("TODOList.txt", ofstream::out | ofstream::trunc);
        for (int i = 0; i < tasks.size(); i++){
            outfile << tasks[i] << endl;
        }
        outfile.close();
    }

    virtual void add(string _duedate, string _task) {
//        cout << "In add: " << "Duedate: " << _duedate << " Task: " << _task << endl;
//  XX      tasks.push_back(_duedate);
//  XX      tasks.push_back(_task);

        //NEW WAY THAT DOESN'T ADD DUPLICATE DAYS
        int shift = 0;
        vector <string> taskClone;
//        tasks.push_back("erase me");
        bool clone = false;
        //COPY THE THING; CHECK FOR CLONE DATES
        for (int i = 0; i < tasks.size(); i++){
            if (clone == true){
                taskClone.push_back("* " + _task);
                taskClone.push_back(tasks[i]);

//                cout << "Adding item " << _task << endl;
//                cout << "Adding item " << tasks[i] << endl;

                clone = false;
            }
            else{
//                cout << "Adding item " << tasks[i] << endl;
                taskClone.push_back(tasks[i]);
            }
            if (tasks[i] == _duedate){
                shift = 1;
                clone = true;
//                cout << "clone detected" << endl;
            }
//            cout << "shift = " << shift << endl;
        }
        //IF IT'S NOT A CLONE JUST PUT IT AT THE END
        if(shift == 0){
            tasks.push_back(_duedate);
            tasks.push_back("* " + _task);
        }
        else{
            if(tasks.size() != taskClone.size()) {
                tasks.push_back("erase me");
                cout << "task size: " << tasks.size() << endl;
                cout << "clone size: " << taskClone.size() << endl;
            }
            for (int i = 0; i < taskClone.size(); i++){
                tasks[i]=taskClone[i];
//                cout << "copying " << taskClone[i] << endl;
            }
        }
    } // = 0;

    virtual int remove(string _task) {
        vector <string> currentList;
        cout << "in remove" << endl;
        ifstream inFile;
        inFile.open("TODOList.txt");
        string line;
        if(inFile.is_open()){
            while(getline(inFile, line)){
                currentList.push_back(line);
            }
            bool found = false;
            int deleteID;

            for (int i = 0; i < currentList.size(); i++){
                cout << currentList[i];
                string adjust = "* " + _task;
//              cout << "Matchin' for " << adjust << endl; //COMMENT OUT
//              cout << "CurrentList size: " << currentList.size() << endl;
                if (adjust.compare(currentList[i])==0) {
                    cout << "   <---- ***TASK TO DELETE***";
                    found = true;
                    deleteID = i;
                }
                cout << endl;
                cout << "Found: " << found << endl;
            }
            if (found == true){
//                cout << "Deleting task " << tasks[deleteID] << endl;
                tasks.erase(tasks.begin() + deleteID);
//                tasks.erase(tasks.begin() + deleteID);
//              cout << "CurrentList size: " << currentList.size() << endl;
                }

            else{
                cout << "Task \"" << _task << "\" not found." << endl;
            }
        }

        inFile.close();
    } //= 0;

    virtual void printTodoList() {
        cout << "in print list" << endl;

        cout << "____________TO______________________________" << endl;
        cout << "________________DO__________________________" << endl;
        cout << "____________________LIST:___________________" << endl;

        //PRINT IT
        for (int i = 0; i < tasks.size(); i++){
            cout << tasks[i] << endl;
        }

        cout << "____________THAT'S__________________________" << endl;
        cout << "__________________THE_______________________" << endl;
        cout << "_______________________LIST.________________" << endl;

    } //= 0;

    virtual void printDaysTasks(string _date) {
//        cout << "In print m' day" << endl;
        bool dayFound = false;
        for (int i = 0; i < tasks.size(); i++){
            if (_date.compare(tasks[i])==0){
                dayFound = true;
                cout << "Printing day \"" << tasks[i] << "\" ..." << endl;
            }
            else if (tasks[i].rfind('*', 0) != 0){
                dayFound = false;
            }
            if (dayFound == true){
                cout << tasks[i] << endl;
            }
        }

    } //= 0;

    virtual void help() {
        cout << "************TODO LIST HELP MENU:************" << endl;
        cout << "Use \"./TODO add <due_date> <task>\" to add tasks." << endl;
        cout << "Use \"./TODO remove <task>\" to remove tasks." << endl;
        cout << "Use \"./TODO printDay <due_date>\" to print a day's tasks." << endl;
        cout << "Use \"./TODO printList\" to print your list." << endl;
        cout << "Use \"./TODO clear\" to clear your list." << endl;
    } //= 0;

    virtual void clear() {
        cout << "Clearing list ..." << endl;
        int size = tasks.size();
        for (int i = 0; i < size; i++){
            //CLEAR ALL ITEMS FROM THE LIST
            tasks.erase(tasks.begin());
        }
    }
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