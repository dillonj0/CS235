//
// Created by Dillon Jensen on 8/1/22.
//

#pragma once

#include "NodeInterface.h"
#include "AVLInterface.h"
//#include "AVL_Tree.h"
#include "Node.h"

#include <iostream>

using namespace std;

class AVL : public AVLInterface {
public:
    AVL() {
        cout << "*** IN AVL CONSTRUCTOR *** " << endl;
        root = NULL;
    }
    virtual ~AVL() {
        cout << "*** IN AVL DESTRUCTOR *** " << endl;
        clear();
    }
    NodeInterface * getRootNode() const;
    bool add(int data);
    bool remove(int data);
    void clear();

protected:
    Node *root;

private:
    bool addAtNode(Node *&target, int data); // recursive function to insert new node.
    bool removeAtNode(Node *&target, int data); // recursive function to remove node.
    void ReplaceParent(Node *&old, Node *&current);
    void clearHelper(Node *&node);
    bool increase;
    bool decrease;
    void rebalanceRight(Node *&root);
    void rebalanceLeft(Node *&root);
    void rotateRight(Node *&root);
    void rotateLeft(Node *&root);
    void balanceWholeTree(Node *& target);
};