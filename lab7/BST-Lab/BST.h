//
// Created by Dillon Jensen on 26/JULY/22.
//

#ifndef BST_LAB_BST_H
#define BST_LAB_BST_H

#include <iostream>

#include "BSTInterface.h"
#include "Node.h"

using namespace std;

class BST : public BSTInterface {
public:
    BST();
    ~BST();

    Node *getRootNode() const;

    bool add(int data); // calls addAtNode to start adding process.
    bool remove(int data); // calls removeAtNode to start remove process.
    void clear();
//    bool IsLeaf() const;

protected:
    Node *root;

private:
    bool addAtNode(Node *&target, int data); // recursive function to insert new node.
    bool removeAtNode(Node *&target, int data); // recursive function to remove node.
    void ReplaceParent(Node *&old, Node *&current);

    void clearHelper(Node *&node);
};

#endif //BST_LAB_BST_H
