// intbst.cpp
// Implements class IntBST
// David Aguirre

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if(n)
    {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if(!root)
    {
        root = new Node(value);
        return true;
    }
    else
    {
        return insert(value,root);
    }
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if(value==n->info)
    {
        return false;
    }
    if(value>n->info)
    {
        if(!n->right)
        {
            n->right = new Node(value);
            return true;
        }
        else
        {
            return insert(value,n->right);
        }
    }
    else
    {
        if(!n->left)
        {
            n->left = new Node(value);
            return true;
        }
        else
        {
            return insert(value,n->left);
        }
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if(n)
    {
        cout<< n->info << " ";
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if(!n) return;
    printInOrder(n->left);
    cout<<n->info << " ";
    printInOrder(n->right);    
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if(!n) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout<< n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(!n)
    {
        return 0;
    }
    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(!n)
    {
        return 0;
    }
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if(!n) return nullptr;
    if(n->info == value) return n;
    if(value > n->info) 
    {
        return getNodeFor(value,n->right);
    }
    else {
        return getNodeFor(value,n->left);
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    Node* testNode = getNodeFor(value,root);
    return testNode != nullptr;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
   Node* target = getNodeFor(value,root);
   if(!target) return nullptr;
   if(target->left){
        Node* curr = target->left;
        while(curr->right)
        {
            curr = curr->right;
        }
        return curr;
   }

   Node* predecessor = nullptr;
   Node* ancestor = root;
   while(ancestor != target)
   {
        if(value > ancestor->info)
        {
            predecessor = ancestor;
            ancestor = ancestor->right;
        }
        else{
            ancestor = ancestor->left;
        }
   }
   return predecessor;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* p = getPredecessorNode(value);
    if(p) return p->info;
    else return 0; 
    
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* target = getNodeFor(value,root);
    if(!target) return nullptr;

    if(target->right)
    {
        Node* curr = target->right;
        while(curr->left) curr = curr->left;
        return curr;
    }

    Node* successor = nullptr;
    Node* ancestor = root;
    while(ancestor != target)
    {
        if(value < ancestor->info){
            successor = ancestor;
            ancestor = ancestor->left;
        }
        else{
            ancestor =ancestor->right;
        }
    }
    return successor;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* p = getSuccessorNode(value);
    if(!p) return 0;
    return p->info;
}


// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist

bool IntBST::remove(int value){
    Node* parent = nullptr;
    Node* curr = root;
    
    while(curr && curr->info != value)
    {
        parent = curr;
        if(value < curr->info) curr = curr->left;
        else curr = curr->right;
    }

    if(!curr) return false;

    if (curr->left && curr->right) {
        Node* succParent = curr;
        Node* succ = curr->right;

        while (succ->left) {
            succParent = succ;
            succ = succ->left;
        }

        curr->info = succ->info;

        if (succParent->left == succ)
        {
            succParent->left = succ->right;
        }
        else
        {
            succParent->right = succ->right;
        }
        delete succ;
        return true;
    }

    Node* replacement = (curr->left) ? curr->left : curr->right;

    if(!parent)
    {
        root = replacement;
    }
    else if (parent->left == curr){
        parent->left = replacement;
    }
    else{
        parent->right = replacement;
    }

    delete curr;
    return true;
}
