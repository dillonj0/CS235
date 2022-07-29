//
// Created by Dillon Jensen on 26/JULY/22.
//

#ifndef BST_LAB_NODE_H
#define BST_LAB_NODE_H

#include <iostream>
#include <sstream>

//#include "BST.h"
#include "NodeInterface.h"

using namespace std;

//template<typename T>
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

    Node *&getLeft();
    Node *&getRight();
    void setLeft(Node *ptr);
    void setRight(Node *ptr);
    void setData(int newData);

protected:
    // T data;
    int data;
    Node* right;
    Node* left;
};

////template<typename T>
//ostream& operator << (ostream& out, const Node& node){
//    return out << node.to_string();
//}
#endif //BST_LAB_NODE_H
