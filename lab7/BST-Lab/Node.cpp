//
// Created by Dillon Jensen on 26/JULY/22.
//

#include "Node.h"

Node::Node(){
    cout << "*** In NODE CONSTRUCTOR (no data) ***" << endl;
    right = NULL;
    left = NULL;
}

Node::Node(int newData){
    cout << "*** In NODE CONSTRUCTOR (with data " << newData << ") ***" << endl;
    data = newData;
    right = NULL;
    left = NULL;
}

Node::~Node(){
    cout << "*** In NODE DESTRUCTOR ***" << endl;
}

string Node::to_string() const{
    cout << "*** In NODE TO STRING ***" << endl;
    ostringstream os;
    os << data;
    return os.str();
}

/*
* Returns the data that is stored in this node
*
* @return the data that is stored in this node.
*/
int Node::getData() const {
    cout << "*** In NODE GETDATA ***" << endl;
    cout << "Data: " << data << endl;
    return data;
}

/*
* Returns the left child of this node or null if it doesn't have one.
*
* @return the left child of this node or null if it doesn't have one.
*/
NodeInterface * Node::getLeftChild() const {
    cout << "*** In NODE GET childL ***" << endl;
    cout << "childL: " << left << endl;
    return left;
}

/*
* Returns the right child of this node or null if it doesn't have one.
*
* @return the right child of this node or null if it doesn't have one.
*/
NodeInterface * Node::getRightChild() const {
    cout << "*** In NODE GET childR ***" << endl;
    cout << "childR: " << right << endl;
    return right;
}

Node *& Node::getLeft() {
    cout << "*** In NODE GET LEFT ***" << endl;
    cout << "childL: " << left << endl;
    return left;
}

Node *& Node::getRight() {
    cout << "*** In NODE GET RIGHT ***" << endl;
    cout << "childR: " << right << endl;
    return right;
}

void Node::setLeft(Node *ptr){
    cout << "*** IN NODE SET LEFT ***" << endl;
    left = ptr;
}

void Node::setRight(Node *ptr){
    cout << "*** IN NODE SET RIGHT ***" << endl;
    right = ptr;
}

void Node::setData(int newData){
    cout << "*** IN NODE SET DATA ***" << endl;
    data = newData;
}