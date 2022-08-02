//
// Created by Dillon Jensen on 8/1/22.
//

#include "AVL.h"

//Please note that the class that implements this interface must be made
//of objects which implement the NodeInterface

/*
* Returns the root node for this tree
*
* @return the root node for this tree.
*/
NodeInterface * AVL::getRootNode() const {
    cout << "In AVL::getRootNode"<<endl;
    return(this->root);
}

/*
* Attempts to add the given int to the BST tree
*
* @return true if added
* @return false if unsuccessful (i.e. the int is already in tree)
*/
bool AVL::add(int data){
    cout << "*** IN AVL ADD ***" << endl;
    cout << "Attempting to add " << data << " at root." << endl;
    return addAtNode(this->root, data);
}
bool AVL::addAtNode(Node *&target, int data){
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
        increase = true;
        return true;
    } else {
        // if the target data is the same as new data, don't add.
        if (target->getData() == data) {
            int tempData = target->getData();
            cout << "Data " << data << " is already in the tree." << endl;
            cout << "(" << data << " = " << tempData << ")" << endl;
            increase = false;
            return false;
        }
            // if the target data is greater than new data, run addAtNode on left child.
        if (data < target->getData()) {
            cout << "Attempting to add at left child" << endl;
            bool added = addAtNode(target->getLeft(), data);
            if (increase){
                target->setBalance(-1);
                cout << "Balance at node " << target->getData() << ": "
                     << target->getBalance() << endl;
                if (target->getBalance() == 0){
                    increase = false;
                }
                if (target->getBalance() < -1){
                    rebalanceLeft(target);
                }
            }
            return added;
        }
            // if the target data is less than new data, run addAtNode on right child.
        if (target->getData() < data) {
            cout << "Attempting to add at right child" << endl;
            bool added = addAtNode(target->getRight(), data);
            if (increase){
                target->setBalance(1);
                cout << "Balance at node " << target->getData() << ": "
                     << target->getBalance() << endl;
                if (target->getBalance() == 0){
                    increase = false;
                }
                if (target->getBalance() > 1){
                    rebalanceRight(target);
                }
            }
            return added;
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
bool AVL::remove(int data){
    cout << "*** IN AVL REMOVE ***" << endl;
    cout << "Attempting to remove " << data << " at root." << endl;
    return removeAtNode(this->root, data);
}
bool AVL::removeAtNode(Node *&target, int data) {
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
    }
}
/* Recursive function to swap out the node in the case that we need to
* locate the inorder predecessor for the remove function.
*/
void AVL::ReplaceParent(Node *&old, Node *&current){
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
void AVL::clear(){
    cout << "*** IN AVL CLEAR ***" << endl;
    clearHelper(root);
}
void AVL::clearHelper(Node *&node){
    if (node != NULL){
        clearHelper(node->getLeft());
        clearHelper(node->getRight());
        delete node;
        node = NULL;
    }
}

void AVL::rebalanceRight(Node *&root){
    //// TODO:: MAKE THIS A MIRROR OF REBALANCE-LEFT
    cout << "        *** Rebalance Right ***     " << endl;
    // Obtain a reference to the Right child
    Node* RChild = root->getRight();
    //See whether right-left-heavy
    if(RChild->getBalance() < 0){ // RL Case
        //// ADJUST THE BALANCES TO THE NEW VALUES AFTER THE ROTATION THAT FOLLOWS:
        Node* RLChild = RChild->getLeft();
        if(RLChild->getBalance() > 0){ // RLR Case
            cout << "RLR" << endl;
            RChild->setBalance(-1 * RChild->getBalance()); // 0
            RLChild->setBalance(-1 * RLChild->getBalance()); // 0
            root->setBalance(-1 * root->getBalance() - 1); // +1, left heavy
        } else if (RLChild->getBalance() == 0){ // RLB case
            cout << "RLB" << endl;
            RChild->setBalance(-1 * RChild->getBalance()); // 0
            RLChild->setBalance(-1 * RLChild->getBalance()); // 0
            root->setBalance(-1 * root->getBalance()); // 0
        } else { // RLL Case
            cout << "RLL" << endl;
            RChild->setBalance(-1 * RChild->getBalance() + 1); // +1, right heavy
            RLChild->setBalance(-1 * RLChild->getBalance()); // 0
            root->setBalance(-1 * root->getBalance()); // 0
        }
        //// DONE ADJUSTING BALANCES.
        // Rotate the right subtree right
        rotateRight(RChild);
    }
    else { // RR case
        RChild->setBalance(-1 * RChild->getBalance()); // 0
        root->setBalance(-1 * root->getBalance()); // 0
    }
    // Perform a left rotation:
    rotateLeft(root);
}

void AVL::rebalanceLeft(Node *&root){
    cout << "        *** Rebalance Left ***     " << endl;
    // Obtain a reference to the left child
    Node* LChild = root->getLeft();
    //See whether left-right-heavy
    if(LChild->getBalance() > 0){ // LR Case
        //// ADJUST THE BALANCES TO THE NEW VALUES AFTER THE ROTATION THAT FOLLOWS:
        Node* LRChild = LChild->getRight();
        if(LRChild->getBalance() < 0){ // LRL Case
            cout << "LRL" << endl;
            LChild->setBalance(-1 * LChild->getBalance()); // 0
            LRChild->setBalance(-1 * LRChild->getBalance()); // 0
            root->setBalance(-1 * root->getBalance() + 1); // +1, right heavy
        } else if (LRChild->getBalance() == 0){ // LRB case
            cout << "LRB" << endl;
            LChild->setBalance(-1 * LChild->getBalance()); // 0
            LRChild->setBalance(-1 * LRChild->getBalance()); // 0
            root->setBalance(-1 * root->getBalance()); // 0
        } else { // LRR Case
            cout << "LRR" << endl;
            LChild->setBalance(-1 * LChild->getBalance() - 1); // -1, left heavy
            LRChild->setBalance(-1 * LRChild->getBalance()); // 0
            root->setBalance(-1 * root->getBalance()); // 0
        }
        //// DONE ADJUSTING BALANCES.
        // Rotate the left subtree left
        rotateLeft(LChild);
    }
    else { // LL case
        LChild->setBalance(-1 * LChild->getBalance()); // 0
        root->setBalance(-1 * root->getBalance()); // 0
    }
    // Perform a right rotation:
    rotateRight(root);
}

void AVL::rotateRight(Node *&root) {
    cout << "Rebalance Right" << endl;
    cout << "root of rebalance: " << root->getData() << endl;
    // remember root->left location (temp)
    // set root->left to value of temp->right
    // set temp->right to root
    // set root to temp
    Node* temp = root->getLeft();
    root->setLeft(temp->getRight());
    cout << "O-O" << endl;
    temp->setRight(root);
    cout << "o^P" << endl;
    root = temp;
}

void AVL::rotateLeft(Node *&root){
    Node* temp = root->getRight();
    root->setRight(temp->getLeft());
    cout << "O-O" << endl;
    temp->setLeft(root);
    cout << "o^P" << endl;
    root = temp;
}