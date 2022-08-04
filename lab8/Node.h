//
// Created by Dillon Jensen on 26/JULY/22.
// *** Updated 1/AUG/2022: Added getHeight() function.
// ***                     Added balance functionality.
//

#ifndef BST_LAB_NODE_H
#define BST_LAB_NODE_H

#include <iostream>
#include <sstream>

#include "NodeInterface.h"

using namespace std;

class Node : public NodeInterface {
public:
    Node();            // if they don't give initial data it's null
    Node(int newData); // if they give you initial data, member data is newData
    ~Node();
    friend class BST;
    string to_string() const;
    int getData() const;
    NodeInterface * getLeftChild() const;
    NodeInterface * getRightChild() const;
    int getHeight();
    int getBalance();
    Node *&getLeft();
    Node *&getRight();
    void setLeft(Node *ptr);
    void setRight(Node *ptr);
    void setData(int newData);
    void setBalance(int newBalance);
    void setBalance();

protected:
    int data;
    Node* right;
    Node* left;

private:
//    int HeightHelper(int depth);
    int balance;
};

#endif //BST_LAB_NODE_H
