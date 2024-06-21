#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rebalance(AVLNode<Key, Value>* node);
    int height(AVLNode<Key, Value>* node) const;
    int getBalance(AVLNode<Key, Value>* node) const;
    void rotateLeft(AVLNode<Key, Value>* x);
    void rotateRight(AVLNode<Key, Value>* y);

};

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
    AVLNode<Key, Value>* parent = nullptr;
    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_);

    // if tree is empty
    if (this->root_ == nullptr) {
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
        return;
    }

    // looping and checking where to add the new node
    
    while (current != nullptr) {
        parent = current;
        if (new_item.first < current->getKey()) {
            current = static_cast<AVLNode<Key, Value>*>(current->getLeft());
        } 
        else if (new_item.first > current->getKey()) {
            current = static_cast<AVLNode<Key, Value>*>(current->getRight());
        } 
        else {
            // If the key already exists in the tree
            current->setValue(new_item.second);
            delete newNode; 
            return;
        }
    }

    // Attaching the new node to parent node
    newNode->setParent(parent);
    if (parent == nullptr) {
        this->root_ = newNode;
    } else if (new_item.first < parent->getKey()) {
        parent->setLeft(newNode);
    } else {
        parent->setRight(newNode);
    }

    // Rebalancing the tree from inserted node 
    AVLNode<Key, Value>* nodeToRebalance = newNode;
    while (nodeToRebalance != nullptr) {
        rebalance(nodeToRebalance);
        nodeToRebalance = static_cast<AVLNode<Key, Value>*>(nodeToRebalance->getParent());
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    
    // No key is found
    if (current == nullptr) {
        return;  
    }

    // 2 children case
    if (current->getLeft() != nullptr && current->getRight() != nullptr) {
        AVLNode<Key, Value>* successorNode = static_cast<AVLNode<Key, Value>*>(this->successor(current));
        this->nodeSwap(current, successorNode);
    } 
    
    // If there are children case 
    AVLNode<Key, Value>* child = nullptr;
    if (current->getLeft() != nullptr) {
        child = current->getLeft();
    } 
    else if (current->getRight() != nullptr) {
        child = current->getRight();
    }

    AVLNode<Key, Value>* parent = current->getParent();
    
    // Cases to check for root, and updating parent 
    if (parent == nullptr) {
        this->root_ = child;
    } 
    else {
        if (parent->getLeft() == current) {
            parent->setLeft(child);
        } else {
            parent->setRight(child);
        }
    }

    // Updating parent
    if (child != nullptr) {
        child->setParent(parent);
    }

    delete current;

    // Rebalancing after the changes

    while (parent != nullptr) {
        parent->setHeight(1 + std::max(height(parent->getLeft()), height(parent->getRight())));
        rebalance(parent);
        parent = parent->getParent();
    }

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::rebalance(AVLNode<Key, Value>* node) {
    while (node != nullptr) {
        // Update the height of the current node
        node->setHeight(1 + std::max(height(node->getLeft()), height(node->getRight())));

        // Get the balance factor to check if this node became unbalanced
        int balance = getBalance(node);

        // Left heavy subtree

        if (balance > 1 && getBalance(node->getLeft()) < 0) { // Left-Right case
            rotateLeft(static_cast<AVLNode<Key, Value>*>(node->getLeft()));
            rotateRight(node);
        }
        else if(balance > 1){ // Left-Left case
            rotateRight(node);
        }
        // Right heavy subtree
        else if (balance < -1 && getBalance(node->getRight()) > 0) { // Right-Left case
            rotateRight(static_cast<AVLNode<Key, Value>*>(node->getRight()));
            rotateLeft(node);
        }
        else if(balance < -1){ // Right-Right case
            rotateLeft(node);
        }

        // Move up to parent
        node = static_cast<AVLNode<Key, Value>*>(node->getParent());
    }
}

template<typename Key, typename Value>
int AVLTree<Key, Value>::height(AVLNode<Key, Value>* node) const {
    if (node == nullptr) {
        return 0;
    }
    return node->getHeight();
}

template<typename Key, typename Value>
int AVLTree<Key, Value>::getBalance(AVLNode<Key, Value>* node) const {
    if (node == nullptr) {
        return 0;
    }
    return height(node->getLeft()) - height(node->getRight());
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node) {
    AVLNode<Key, Value>* right = node->getRight();
    node->setRight(right->getLeft());

    // Checking if the right child has a left subtree and updating parent accordingly
    if (right->getLeft() != nullptr) {
        right->getLeft()->setParent(node);
    }

    // updating right child parent to the node to be rotated's parent and changing pointers
    right->setParent(node->getParent());
    if (node->getParent() == nullptr) {
        this->root_ = right;
    } 
    else if (node == node->getParent()->getLeft()) {
        node->getParent()->setLeft(right);
    } 
    else {
        node->getParent()->setRight(right);
    }

    right->setLeft(node);
    node->setParent(right);

    // Update heights
    node->setHeight(1 + std::max(height(node->getLeft()), height(node->getRight())));
    right->setHeight(1 + std::max(height(right->getLeft()), height(right->getRight())));
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node) {
    AVLNode<Key, Value>* left = node->getLeft();
    node->setLeft(left->getRight());

    // Checking if left child has right subtree and updating parent accordingly
    if (left->getRight() != nullptr) {
        left->getRight()->setParent(node);
    }

    // Setting new parent and adjusting pointers
    left->setParent(node->getParent());
    if (node->getParent() == nullptr) {
        this->root_ = left;
    } 
    else if (node == node->getParent()->getRight()) {
        node->getParent()->setRight(left);
    } 
    else {
        node->getParent()->setLeft(left);
    }

    // Updating nodes children's and parents
    left->setRight(node);
    node->setParent(left);

    // Update heights
    node->setHeight(1 + std::max(height(node->getLeft()), height(node->getRight())));
    left->setHeight(1 + std::max(height(left->getLeft()), height(left->getRight())));
}

#endif
