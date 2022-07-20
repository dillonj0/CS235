//
// Created by Dillon Jensen on 7/19/22.
//
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#include "LinkedListInterface.h"

using namespace std;

template <class T>
class LinkedList : public LinkedListInterface <T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& the_data, Node* next_val = NULL) :
            // IF WE DON'T FEED IT ANY NEXT VALUE, IT WILL CONSTRUCT TO NULL
            data(the_data), next (next_val) {}
    };
    Node *myList; // A POINTER TO THE HEAD OF THE LIST.
    int num_items;
    bool isNewItem(T value){
        // RETURNS TRUE IF THE PROPOSED NEW ITEM IS NOT ALREADY IN THE LIST.
        for(Node *ptr = myList; ptr != NULL; ptr = ptr->next){
            if (ptr->data == value){
                cout << "*** DUPLICATE ITEM :(" << endl;
                return false;
            }
        }
        return true;
    }

public:
    LinkedList(void) {
        cout << "*** in CONSTRUCTOR ***" << endl;
        myList = NULL;
        num_items = 0;
    }

    ~LinkedList(void) {
        cout << "*** in DESTRUCTOR ***" << endl;
        clear();
    }

    /*
    insertHead

    A node with the given value should be inserted at the beginning of the list.

    Do not allow duplicate values in the list.
    */
    void insertHead(T value) {
        cout << "*** in INSERT HEAD ***" << endl;
        cout << "Inserting item " << value << endl;

        if (isNewItem(value)) {
            Node *ptr = myList;
            myList = new Node(value);
            myList->next = ptr;
            // REMEMBER TO INCREMENT NUM_ITEMS.
            num_items ++;
        }
        else {
            cout << "*** item DUPLICATE; not added ***" << endl;
        }
    }

    /*
    insertTail

    A node with the given value should be inserted at the end of the list.

    Do not allow duplicate values in the list.
    */
    void insertTail(T value) {
        cout << "*** in INSERT TAIL ***" << endl;
        cout << "Inserting item " << value << endl;

        if (isNewItem(value)) {
            // FIND END OF LIST:
            Node *lastPtr;
            if (myList == NULL){
                insertHead(value);
                return;
            }
            for(Node *ptr = myList; ptr != NULL; ptr = ptr->next){
                lastPtr = ptr;
            }
            Node *newPtr = new Node(value);
            newPtr->next = lastPtr->next;
            lastPtr->next = newPtr;
            // REMEMBER TO INCREMENT NUM_ITEMS.
            num_items ++;
        }
        else {
            cout << "*** item DUPLICATE; not added ***" << endl;
        }
    }

    /*
    insertAfter

    A node with the given value should be inserted immediately after the
    node whose value is equal to insertionNode.

    A node should only be added if the node whose value is equal to
    insertionNode is in the list. Do not allow duplicate values in the list.
    */
    void insertAfter(T value, T insertionNode) {
        cout << "*** in INSERT AFTER ***" << endl;
        cout << "Inserting item " << value << " after " << insertionNode << endl;

        if (isNewItem(value)) {
            // FIND ITEM IN LIST:
            for(Node *ptr = myList; ptr != NULL; ptr = ptr->next){
                if (insertionNode == ptr->data){
                    Node *newPtr = new Node(value);
                    newPtr->next = ptr->next;
                    ptr->next = newPtr;
                    // REMEMBER TO INCREMENT NUM_ITEMS.
                    num_items ++;
                    return;
                }
            }
            cout << "*** Item " << insertionNode << " not found, no new item inserted." << endl;
        }
        else {
            cout << "*** item DUPLICATE; not added ***" << endl;
        }
    }

    /*
    remove

    The node with the given value should be removed from the list.

    The list may or may not include a node with the given value.
    */
    void remove(T value) {
        cout << "*** in REMOVE ***" << endl;
        // IF THE ITEM ISN'T IN THE LIST, DO NOTHING.
        if (isNewItem(value)){
            cout << "Item " << value << " not found in list." << endl;
            return;
        }
        // ELSE REMOVE ITEM.
        cout << "Removing item " << value << endl;

        for(Node *ptr = myList; ptr != NULL; ptr = ptr->next){
            if (value == ptr->data){
                Node *temp = ptr; // TEMP POINTER TO THE HEAD
                myList = ptr->next; // MOVE HEAD POINTER TO SECOND NODE
                delete temp; // DELETE HEAD
                num_items--;
                return;
            }
            if (value == ptr->next->data){
                Node *temp = ptr->next;
                ptr->next = ptr->next->next;
                delete temp;
                num_items--;
                return;
            }
        }
    }

    /*
    clear

    Remove all nodes from the list.
    */
    void clear() {
        cout << "*** in CLEAR ***" << endl;
        for(Node *ptr = myList; ptr != NULL; ptr = ptr->next){
            remove(myList->data);
        }
    }

    /*
    at

    Returns the value of the node at the given index. The list begins at
    index 0.

    If the given index is out of range of the list, throw an out of range exception.
    */
    T at(int index){
        cout << "*** in AT ***" << endl;
        if ((index < 0) || (index >= size())){
            cout << "index " << index << " out of range." << endl;
            throw out_of_range("out of range");
        }
        int counter = 0;
        cout << "*** DATA AT " << index << ": ";
        for(Node *tempPtr = myList; tempPtr != NULL; tempPtr = tempPtr->next){
            if (counter == index) {
                cout << tempPtr->data << endl;
                return tempPtr->data;
            }
            counter++;
        }
        cout << endl;
        cout << "index " << index << " out of range." << endl;
        throw out_of_range("out of range");
    }

    /*
    size

    Returns the number of nodes in the list.
    */
    int size() {
        cout << "*** in SIZE ***" << endl;
        cout << "num_items size: " << num_items << endl;
        int counter = 0;
        for(Node *ptr = myList; ptr != NULL; ptr = ptr->next){
            counter++;
        }
        cout << "Counter size: " << counter << endl;
//        num_items = counter;
        return counter;
    }

    /*
    toString

    Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
    There should be no trailing space at the end of the string

    For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
    "1 2 3 4 5"
    */
    string toString() {
        cout << "*** in TO STRING ***" << endl;

        stringstream ss;
        for(Node *ptr = myList; ptr != NULL; ptr = ptr->next){
//            ss << "ptr: " << ptr << ", val: " << ptr->data
//               << " next: " << ptr-> next << endl;
            ss << ptr->data;
            if (ptr->next != NULL){
                ss << " ";
            }
        }
        string output = ss.str();
        cout << "List:" << endl;
        cout << output << endl;
        return output;
    }
};


#endif //LINKEDLIST_LAB_LINKEDLIST_H
