//
// Created by Dillon Jensen on 26/JULY/22.
//

#include "BST.h"
//#include "Node.h"

BST::BST(){
    cout << "*** IN BST CONSTRUCTOR ***" << endl;
    root = NULL;
//    root = new Node();
}

BST::~BST(){
    cout << "*** IN BST DESTRUCTOR ***" << endl;
    clear();
}

//Please note that the class that implements this interface must be made
//of objects which implement the NodeInterface

/*
* Returns the root node for this tree
*
* @return the root node for this tree.
*/
Node * BST::getRootNode() const{
    cout << "IN BST GET ROOT NODE" << endl;
    return this->root;
}

/*
* Attempts to add the given int to the BST tree
*
* @return true if added
* @return false if unsuccessful (i.e. the int is already in tree)
*/
bool BST::add(int data){
    cout << "*** IN BST ADD ***" << endl;
    cout << "Attempting to add " << data << " at root." << endl;
    return addAtNode(this->root, data);
}
bool BST::addAtNode(Node *&target, int data){
    //// **********  PRINT TARGET DATA   ************
    cout << "Target data: ";
    if (target != NULL) {
        cout << target->to_string() << endl;
    }
    else {
        cout << "NULL" << endl;
    }
    //// ********** END PRINT TARGET DATA ************

    //if the target is NULL, put the data there.
    if (target == NULL) {
        cout << "Adding data " << data << " at target node." << endl;
        target = new Node(data);
        return true;
    } else {
        // if the target data is the same as new data, don't add.
        if (target->getData() == data) {
            int tempData = target->getData();
            cout << "Data " << data << " is already in the tree." << endl;
            cout << "(" << data << " = " << tempData << ")" << endl;
            return false;
        }
            // if the target data is greater than new data, run addAtNode on left child.
        else if (data < target->getData()) {
            cout << "Attempting to add at left child" << endl;
            return addAtNode(target->getLeft(), data);
        }
            // if the target data is less than new data, run addAtNode on right child.
        else if (target->getData() < data) {
            cout << "Attempting to add at right child" << endl;
            return addAtNode(target->getRight(), data);
        }
    }
    // If we get this far in the function we did something wrong.
    cout << "Something went wrong when adding data " << data << endl;
    return false;
}

/*
* Attempts to remove the given int from the BST tree
*
* @return true if successfully removed
* @return false if remove is unsuccessful(i.e. the int is not in the tree)
*/
bool BST::remove(int data){
    cout << "*** IN BST REMOVE ***" << endl;
    cout << "Attempting to remove " << data << " at root." << endl;
    return removeAtNode(this->root, data);
}
bool BST::removeAtNode(Node *&target, int data) {
    //// **********  PRINT TARGET DATA   ************
    cout << "Target data: ";
    if (target != NULL) {
        cout << target->to_string() << endl;
    }
    else {
        cout << "NULL" << endl;
    }
    //// ********** END PRINT TARGET DATA ************

    //if the target is null, item is not at location, return false
    if (target == NULL){
        return false;
    }
    if (data < target->getData()){
        // return the result of deleting from the left subtree
        return removeAtNode(target->getLeft(), data);
    }
    else if (target->getData() < data){
        // return the result of deleting from the right subtree
        return removeAtNode(target->getRight(), data);
    }
    else { // Target is the data:
        Node * previous = target;
        if (target->getLeft() == NULL){
            target = target->getRight();
        }
        else if (target->getRight() == NULL){
            target = target->getLeft();
        }
        else {
            ReplaceParent(previous, previous->getLeft());
        }
        delete previous;
        return true;
//        if (target->getLeft() == NULL && target->getRight() == NULL){
//            // If the target has no children, set the parent to reference NULL.
//            parent = NULL;
//        }
//        else if (target->getLeft() == NULL || target->getRight() == NULL){
//            // If the target has only one child, set the parent to reference that kiddo
//            if (target->getLeft() == NULL){
//                parent = target->getRight();
//            }
//            else {
//                parent = target->getLeft;
//            }
//        }
//        else {
//            // Find the inorder predecessor: todo: line 14 from the book (p. 476)
//            if (target->getLeft()->getRight() == NULL){
//                // If the left child has no right child it is the inorder predecessor
//                parent = target->getLeft();
//            }
//            else{
//                // Find the rightmost node in the right subtree of the left child.
//                // Copy its data into the local root's data and remove it by
//                //    setting its parent to reference its left child.
//
//            }
//        }
//        delete previous;
//        return true;
    }
}
/* Recursive function to swap out the node in the case that we need to
* locate the inorder predecessor for the remove function.
*/
void BST::ReplaceParent(Node *&old, Node *&current){
    if (current->getRight() != NULL) {
        ReplaceParent(old, current->getRight());
    }
    else {
        old->setData(current->getData());
        old = current;
        current = current->getLeft();
    }
}

/*
* Removes all nodes from the tree, resulting in an empty tree.
*/
void BST::clear(){
    cout << "*** IN BST CLEAR ***" << endl;
    clearHelper(root);
}
void BST::clearHelper(Node *&node){
    if (node != NULL){
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
        node = NULL;
    }
}