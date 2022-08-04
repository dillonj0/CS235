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
//    cout << "In AVL::getRootNode"<<endl;
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
    }
    if (data < target->getData()){ //// INSERT ON LEFT
        bool added = addAtNode(target->getLeft(), data);
        if (increase) {
            if (target->getBalance() == 0) { //// BALANCED
                target->setBalance(-1);
            } else if (target->getBalance() == 1) { //// RIGHT HEAVY
                target->setBalance(0); // = 0
                increase = false;
            } else if (target->getBalance() == -1) { //// LEFT HEAVY x9
                rebalanceLeft(target);
                increase = false;
            }
        }
        return added;
    }
    if (data > target->getData()){ //// INSERT ON RIGHT
        bool added = addAtNode(target->getRight(), data);
        if (increase) {
            if (target->getBalance() == 0) { //// BALANCED
                target->setBalance(1);
            } else if (target->getBalance() == 1) { //// RIGHT HEAVY x9
                rebalanceRight(target);
                increase = false;
            } else if (target->getBalance() == -1) { //// LEFT HEAVY
                target->setBalance(0); // = 0;
                increase = false;
            }
        }
        return added;
    }
    else {
        cout << "DATA " << data << " ALREADY IN THE TREE" << endl;
        increase = false;
        return false;
    }
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
    bool finished = removeAtNode(this->root, data);

    cout << "Balancing tree: " << endl;
    balanceWholeTree(this->root);

    return finished;
}
void AVL::balanceWholeTree(Node *& target){
    //// **********  PRINT TARGET DATA   ************
    cout << "Target data: ";
    if (target != NULL) {
        cout << target->to_string() << endl;
    }
    else {
        cout << "NULL" << endl;
    }
    //// ********** END PRINT TARGET DATA ************
    if (target == NULL){
        return;
    }
    else{
        balanceWholeTree(target->getLeft());
        balanceWholeTree(target->getRight());
        target->setBalance();
        if (target->getBalance() < -1){
            cout << "Too heavy on left. Rebalancing left." << endl;
            rebalanceLeft(target);
        } else if (target->getBalance() > 1){
            cout << "Too heavy on right. Rebalancing right." << endl;
            rebalanceRight(target);
        }
    }
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

    // if the target is null, item is not at location, return false
    if (target == NULL){
        return false;
    }
    // if the target is too small, try deleting the left node
        // rebalance from descending deletes
    else if (data < target->getData()){
        bool removed = removeAtNode(target->getLeft(), data);
        if (target->getBalance() < -1){
            rebalanceLeft(target);
        } else if (target->getBalance() > 1){
            rebalanceRight(target);
        }
        return removed;
    }
    // if the target is too big, try deleting the right node
        // rebalance from descending deletes
    else if (data > target->getData()){
        bool removed = removeAtNode(target->getRight(), data);
        if (target->getBalance() < -1){
            rebalanceLeft(target);
        } else if (target->getBalance() > 1){
            rebalanceRight(target);
        }
        return removed;
    }
    // else it's the node: delete her.
    else {
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
    cout << "        *** Rebalance Right (at node " << root->getData() << ") ***     " << endl;
    // Obtain a reference to the right child
    Node* RChild = root->getRight();
    cout << "RChild: " << RChild->getData() << endl;
    cout << "******* Balance: " << RChild->getBalance() << endl;
    //See whether right-left-heavy
    if(RChild->getBalance() < 0){ // LR Case
        //// ADJUST THE BALANCES TO THE NEW VALUES AFTER THE ROTATION THAT FOLLOWS:
        cout << "RLChild: " << RChild->getLeft() << endl;
        Node* RLChild = RChild->getLeft();
        if(RLChild->getBalance() == 1){ // RLR Case
            cout << "RLR" << endl;
            RChild->setBalance(0); // 0
            RLChild->setBalance(0); // 0
            root->setBalance(-1); // -1, Left heavy
        } else if (RLChild->getBalance() == 0){ // RLB case
            cout << "RLB" << endl;
            RChild->setBalance(0); // 0
            RLChild->setBalance(0); // 0
            root->setBalance(0); // 0
        } else { // RLL Case
            cout << "RLL" << endl;
            RChild->setBalance(1); // +1, right heavy
            RLChild->setBalance(0); // 0
            root->setBalance(0); // 0
        }
        //// DONE ADJUSTING BALANCES.
        // Rotate the right subtree right
        rotateRight(root->getRight());
//        root->getRight()->getLeft()->setBalance();
//        root->getRight()->setBalance();
//        root->setBalance();
    }
    else { // RR case
        cout << "RR" << endl;
        RChild->setBalance(0); // 0
        root->setBalance(0); // 0
    }
    // Perform a Left rotation:
    rotateLeft(root);
}

void AVL::rebalanceLeft(Node *&root){
    cout << "        *** Rebalance Left (at node " << root->getData() << ") ***     " << endl;
    // Obtain a reference to the left child
    Node* LChild = root->getLeft();
    cout << "LChild: " << LChild->getData() << endl;
    cout << "******* Balance: " << LChild->getBalance() << endl;
    //See whether left-right-heavy
    if(LChild->getBalance() > 0){ // LR Case
        //// ADJUST THE BALANCES TO THE NEW VALUES AFTER THE ROTATION THAT FOLLOWS:
        Node* LRChild = LChild->getRight();
        if(LRChild->getBalance() == -1){ // LRL Case
            cout << "LRL" << endl;
            LChild->setBalance(0); // 0
            LRChild->setBalance(0); // 0
            root->setBalance(1); // +1, right heavy
        } else if (LRChild->getBalance() == 0){ // LRB case
            cout << "LRB" << endl;
            LChild->setBalance(0); // 0
            LRChild->setBalance(0); // 0
            root->setBalance(0); // 0
        } else { // LRR Case
            cout << "LRR" << endl;
            LChild->setBalance(-1); // -1, left heavy
            LRChild->setBalance(0); // 0
            root->setBalance(0); // 0
        }
        //// DONE ADJUSTING BALANCES.
        // Rotate the left subtree left
        rotateLeft(root->getLeft());
//        root->getLeft()->getRight()->setBalance();
//        root->getLeft()->setBalance();
//        root->setBalance();
    }
    else { // LL case
        cout << "LL" << endl;
        LChild->setBalance(0); // 0
        root->setBalance(0); // 0
    }
    // Perform a right rotation:
    rotateRight(root);
}

void AVL::rotateRight(Node *&root) {
    cout << "Rotate right at " << root->getData() << endl;
    // remember root->left location (temp)
    // set root->left to value of temp->right
    // set temp->right to root
    // set root to temp
    Node* temp = root->getLeft();
    root->setLeft(temp->getRight());
    temp->setRight(root);
    root = temp;
}

void AVL::rotateLeft(Node *&root){
    cout << "Rotate left at " << root->getData() << endl;
    Node* temp = root->getRight();
    root->setRight(temp->getLeft());
    temp->setLeft(root);
    root = temp;
}