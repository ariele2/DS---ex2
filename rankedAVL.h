#ifndef RANKED_AVL_H
#define RANKED_AVL_H

#include <memory>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "trio.h"

struct Tnode_v2 {
    trio key;
    int height;
    int rank;
    std::shared_ptr<Tnode_v2> left, right, parent;
};

class rankedAVL {
    std::shared_ptr<Tnode_v2> root; 
    int max(int num1, int num2);
    void updateRank(std::shared_ptr<Tnode_v2> root);
    int height(std::shared_ptr<Tnode_v2> t); //returns the height of the node
    std::shared_ptr<Tnode_v2> findMinSubTree(std::shared_ptr<Tnode_v2> root); //finds the node with the smallest id in a given subtree
    std::shared_ptr<Tnode_v2> rightRotate(std::shared_ptr<Tnode_v2> to_rotate); //rotates to the right
    std::shared_ptr<Tnode_v2> leftRotate(std::shared_ptr<Tnode_v2> to_rotate); //rotates to the left
    std::shared_ptr<Tnode_v2> leftRightRotate(std::shared_ptr<Tnode_v2> to_rotate); //first rotate to the left then to the right
    std::shared_ptr<Tnode_v2> rightLeftRotate(std::shared_ptr<Tnode_v2> to_rotate); //first rotate to the right then to the left
    std::shared_ptr<Tnode_v2> insert(trio key, std::shared_ptr<Tnode_v2> root); //insert a id-data element to the tree keeping it balanced
    std::shared_ptr<Tnode_v2> remove(trio key, std::shared_ptr<Tnode_v2> root); //remove a id-data element by id from the tree, keeping it balanced 
    void inorder(std::shared_ptr<Tnode_v2> root); //makes inorder search on the tree
    void preorder(std::shared_ptr<Tnode_v2> root); //for debugging purpose only!
    void clearTree(std::shared_ptr<Tnode_v2> root); //clears all the tree, called by the destructor.
    public:
    rankedAVL() { //initialize root and smallest node to nullptr
        root = nullptr;
    }
    ~rankedAVL() { //makes all the pointers null, so shared ptr will release the data
        clearTree(root);
    }
    void printInorder(); //for debugging purpose only!
    void printPreorder(); //for debugging purpose only!
    void insert(trio key);
    void remove(trio key);
    trio findIBiggest(int i);
    bool isEmpty(); //return true if the tree is empty
    class AllocationError{};
};

void rankedAVL::updateRank(std::shared_ptr<Tnode_v2> root) {
    if (!root->right && !root->left) {
        root->rank = 1;
    }
    else if (root->right && !root->left) {
        root->rank = (root->right)->rank + 1;
    }
    else if (!root->right && root->left) {
        root->rank = (root->left)->rank + 1;
    }
    else {
        root->rank = (root->right)->rank + (root->left)->rank + 1;
    }
}

int rankedAVL::max(int num1, int num2) {
    return (num1>=num2 ? num1 : num2);
}

int rankedAVL::height(std::shared_ptr<Tnode_v2> t) {
    if (!t) { 
        return -1;
    }
    return t->height;
}

void rankedAVL::inorder(std::shared_ptr<Tnode_v2> root) {
    if (!root) {
        return;
    }
    inorder(root->left); //go to the left
    std::cout << "(" << root->key.getData1() << "," << root->key.getData2() << "," << root->key.getData3() << ") " << " rank:" << root->rank << "; "; //do something
    inorder(root->right); //go to the right
}

void rankedAVL::preorder(std::shared_ptr<Tnode_v2> root) {
    if (!root) {
        return;
    }
    std::cout << "(" << root->key.getData1() << "," << root->key.getData2() << "," << root->key.getData3() << ") " << " rank:" << root->rank << "; "; //do something
    preorder(root->left); //go to the left
    preorder(root->right); //go to the right
}

std::shared_ptr<Tnode_v2> rankedAVL::findMinSubTree(std::shared_ptr<Tnode_v2> root) {//returns the minimum element inside a sub tree
    if (!root) { //in case we are trying to find smallest node on non existing sub tree
        return nullptr;
    }
    else if (!(root->left)){
        return root;
    }
    else {
        return findMinSubTree(root->left);
    }
}

std::shared_ptr<Tnode_v2> rankedAVL::rightRotate(std::shared_ptr<Tnode_v2> to_rotate) { //rotates right, when the balance factor >= 2
    std::shared_ptr<Tnode_v2> heir = to_rotate->left; 
    to_rotate->left = heir->right; //to rotate takes the right sub tree of his heir
    if (heir->right) { //updates the parent of the right sub tree (if it was existed)
        (heir->right)->parent = to_rotate;
    }
    heir->parent = to_rotate->parent; 
    to_rotate->parent = heir;
    heir->right = to_rotate;
    // dont forget to update the heights...
    to_rotate->height = max(height(to_rotate->left), height(to_rotate->right))+1;
    updateRank(to_rotate);
    heir->height = max(height(heir->left), height(heir->right))+1;
    updateRank(heir);
    return heir;
}

std::shared_ptr<Tnode_v2> rankedAVL::leftRotate(std::shared_ptr<Tnode_v2> to_rotate) { //rotates left, when the balance factor <= -2
    std::shared_ptr<Tnode_v2> heir = to_rotate->right;
    to_rotate->right = heir->left; //to rotate takes the left sub tree of his heir
    if (heir->left) { //updates the parent of the left sub tree (if it was existed)
        (heir->left)->parent = to_rotate;
    }
    heir->parent = to_rotate->parent;
    to_rotate->parent = heir;
    heir->left = to_rotate;
    // dont forget to update the heights...
    to_rotate->height = max(height(to_rotate->left), height(to_rotate->right))+1;
    updateRank(to_rotate);
    heir->height = max(height(heir->left), height(heir->right))+1;
    updateRank(heir);
    return heir;
}

std::shared_ptr<Tnode_v2> rankedAVL::leftRightRotate(std::shared_ptr<Tnode_v2> to_rotate) { //left then right
    to_rotate->left = leftRotate(to_rotate->left);
    return rightRotate(to_rotate);
}

std::shared_ptr<Tnode_v2> rankedAVL::rightLeftRotate(std::shared_ptr<Tnode_v2> to_rotate) { //right then left
    to_rotate->right = rightRotate(to_rotate->right);
    return leftRotate(to_rotate);
}

std::shared_ptr<Tnode_v2> rankedAVL::insert(trio key, std::shared_ptr<Tnode_v2> root) {
    if (!root) { //if we reached a place with no such id then:
        root = std::shared_ptr<Tnode_v2>(new Tnode_v2()) ; //makes all the ptrs shared ones - no memory leaks.
        if (!root) {
            throw AllocationError();
        }
        root->key = key;
        root->height = 0;
        root->rank = 1;
        root->left = nullptr;
        root->right = nullptr;
        root->parent = nullptr;
    }
    else if (key < root->key) { //goes to the left if the id is smaller
        root->left = insert(key, root->left);
        if ((height(root->left)-height(root->right))>=2) { //after inserting, check if balance is needed
            if (key<(root->left)->key) {
                root = rightRotate(root);
            }
            else {
                root = leftRightRotate(root);
            }
        }
    }
    else if (key > root->key) { //goes to the right if the id is bigger
        root->right = insert(key, root->right);
        if ((height(root->left)-height(root->right))<=-2) { //after inserting, check if balance is needed
            if (key>(root->right)->key) {
                root = leftRotate(root);
            }
            else {
                root = rightLeftRotate(root);
            }
        }
    }
    else if (key == root->key) { //stops the search if the key exists already
        return root;
    }
    //update the parent for the new node if needed
    if (root->right) {
        if (!((root->right)->parent)) { //if the root->right has no parent, the it means its our new node
            (root->right)->parent = root; //update it to its parent
        }
    }
    else if (root->left) {
        if (!((root->left)->parent)) { //same as right
            (root->left)->parent = root;
        }
    }
    
    //update the height for all the nodes in the insertion path
    root->height = max(height(root->left),height(root->right))+1;
    //update the rank for all the nodes in the insertion path
    updateRank(root);
    return root;
}

std::shared_ptr<Tnode_v2> rankedAVL::remove(trio key, std::shared_ptr<Tnode_v2> root) {
    std::shared_ptr<Tnode_v2> temp;
    if (!root) { //element not found!
        return nullptr;
    }
    if (key < root->key) {
        root->left = remove(key, root->left);
    }
    else if (key > root->key) {
        root->right = remove(key, root->right);
    }
    //we found our node to remove, so:
    else {
        if (root->left && root->right) { //the node that we remove has 2 subtree childs.
            temp = findMinSubTree(root->right);
            root->key = temp->key;
            //goes to the right to remove the node that we replaced.
            root->right = remove(root->key, root->right);
        }
        else { //the node that we remove has 0/1 subtree childs.
            temp = root;
            if (!(root->left)) { 
                root = root->right;
                if (root) {
                    root->parent = temp->parent;
                }
            }
            else if (!(root->right)) { 
                root = root->left;
                if (root) {
                    root->parent = temp->parent;
                }
            }
            if (temp->parent) {
                if (temp->parent->left && (temp->parent)->left->key == key) {
                    temp->parent->left = nullptr;
                }
                else if (temp->parent->right && (temp->parent)->right->key == key) {
                    temp->parent->right = nullptr;
                }
            }
            temp = nullptr;
        }
    }
    if (!root) { //do nothing to the first recursive recall (cause the root value is now nullptr)
        return nullptr;
    }
    // updates the height for all the nodes in the removing path.
    root->height = max(height(root->left), height(root->right))+1;
    // updates the rank for all the nodes in the removing path.
    updateRank(root);
    // rotations!!! (if needed)
    if ((height(root->left)-height(root->right)) >= 2 ) { //the left side is unbalanced
        //check wether the problem is at the left or right side
        if (height((root->left)->left) - height((root->left)->right) == 1) {
            root = rightRotate(root);
        }
        else { //case the balance factor = 0 or -1.
            root = leftRightRotate(root);
        }
    }
    else if ((height(root->left)-height(root->right)) <= -2) {
        //check wether the problem is at the left or right side
        if (height((root->right)->left) - height((root->right)->right) == -1) {
            root = leftRotate(root);
        }
        else { //case the balance factor = 0 or -1.
            root = rightLeftRotate(root);
        }
    }
    return root;
}

void rankedAVL::clearTree(std::shared_ptr<Tnode_v2> root) { //post order traversal
    if (!root) {
        return;
    }
    clearTree(root->left);
    clearTree(root->right);
    if (root->parent) { //if the node has a parent, disconnect it
        root->parent = nullptr;
    }
    if (root->left) {
        root->left = nullptr;
    }
    if (root->right) {
        root->right = nullptr;
    }
}

//publice functions - for the user to use

void rankedAVL::printInorder() {
    inorder(root);
    std::cout<<std::endl;
}

void rankedAVL::printPreorder() {
    preorder(root);
    std::cout<<std::endl;
}

void rankedAVL::insert(trio key) {
    //insert always returns the root of the tree, and we will need to update it if necessary with the new updates.
    root = insert(key, root); 
}

void rankedAVL::remove(trio key) {
    //same as insert, need to update if necessary
    root = remove(key, root);
}

trio rankedAVL::findIBiggest(int i) {
    if (i>root->rank) {
        return trio(-1,-1,-1);
    }
    while (i>0) {
        if (i-1 == root->right->rank) {
            return root->key;
        }
        else if (i-1 < root->right->rank) {
            root = root->right;
        }
        else {
            i = i-root->right->rank-1;
            root = root->left;
        }
    }
    return trio(-1,-1,-1); //shouldnt reach here...
}

bool rankedAVL::isEmpty() {
    if (!root) {
        return true;
    }
    return false;
}

#endif //RANKED_AVL_H