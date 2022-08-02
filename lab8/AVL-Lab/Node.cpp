//
// Created by Dillon Jensen on 26/JULY/22.
// *** Updated 1/AUG/2022: Added getHeight() function.
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
//    cout << "*** In NODE TO STRING ***" << endl;
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
//    cout << "*** In NODE GETDATA ***" << endl;
//    cout << "Data: " << data << endl;
    return data;
}

/*
* Returns the left child of this node or null if it doesn't have one.
*
* @return the left child of this node or null if it doesn't have one.
*/
NodeInterface * Node::getLeftChild() const {
//    cout << "*** In NODE GET childL ***" << endl;
    if (left != NULL) {
        cout << "childL: " << left->getData() << endl;
    }
    return left;
}

/*
* Returns the right child of this node or null if it doesn't have one.
*
* @return the right child of this node or null if it doesn't have one.
*/
NodeInterface * Node::getRightChild() const {
//    cout << "*** In NODE GET childR ***" << endl;
    if (right != NULL) {
        cout << "childR: " << right->getData() << endl;
    }
    return right;
}

/*
	* Returns the height of this node. The height is the number of nodes
	* along the longest path from this node to a leaf.  While a conventional
	* interface only gives information on the functionality of a class and does
	* not comment on how a class should be implemented, this function has been
	* provided to point you in the right direction for your solution.  For an
	* example on height, see page 448 of the text book.
	*
	* @return the height of this tree with this node as the local root.
	*/
int Node::getHeight(){
    int R = 0; // Will stay 0 if no right child.
    int L = 0; // Will stay 0 if no left child.
    if (right != NULL){ // Set R to height of right tree
        R = right->getHeight();
    }
    if (left != NULL){ // Set L to height of left tree
        L = left->getHeight();
    }
    if (R > L){
        return R + 1; // If there are child roots, they'll add up
    } else {
        return L + 1; // End result should be the longest leg.
    }
}
int Node::getBalance(){
    return balance;
}

//int Node::HeightHelper(int depth){
//    int rDepth = 0;
//    int lDepth = 0;
//    if (left != NULL){
//        lDepth = left->HeightHelper(depth + 1);
//    }
//    if (right != NULL){
//        rDepth = right->HeightHelper(depth + 1);
//    }
//    if (rDepth > lDepth){
//        depth += rDepth;
//    } else {
//        depth += lDepth;
//    }
//    return depth;
//}

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
void Node::setBalance(int changeBalance){
    cout << "*** IN NODE SET BALANCE ***" << endl;
    balance += changeBalance;
}