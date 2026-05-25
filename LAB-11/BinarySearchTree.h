#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "BinaryTree.h"
#include <iostream>
using namespace std;

// -------------------------------------------------------
// BinarySearchTree.h
// A Binary Search Tree (BST) that inherits from BinaryTree.
//
// BST property: for every node N,
//   - all values in the LEFT  subtree are LESS    than N.data
//   - all values in the RIGHT subtree are GREATER than N.data
//
// This class implements all pure-virtual functions from
// BinaryTree and adds a display() function.
// -------------------------------------------------------

template <class T> class BinarySearchTree : public BinaryTree<T> {
public:
  // ---- constructors / destructor / assignment --------

  // Default constructor – creates an empty BST
  BinarySearchTree() : BinaryTree<T>() {}

  // Copy constructor – deep-copies an existing BST
  BinarySearchTree(const BinarySearchTree<T> &bt) : BinaryTree<T>(bt) {}

  // Assignment operator
  const BinarySearchTree<T> &operator=(const BinarySearchTree<T> &bt) {
    BinaryTree<T>::operator=(bt);
    return *this;
  }

  // Destructor – BinaryTree's virtual destructor handles cleanup
  ~BinarySearchTree() {}

  // ---- isEmpty -------------------------------------------
  // Returns true if the tree has no nodes at all.
  bool isEmpty() const { return this->root == nullptr; }

  // ---- insert --------------------------------------------
  // Adds 'value' to the correct position in the BST so that
  // the BST property is maintained.
  // Duplicate values are NOT inserted.
  void insert(const T &value) {
    Node<T> *newNode = new Node<T>(value); // create a new node

    if (this->root == nullptr) {
      // Tree is empty – the new node becomes the root
      this->root = newNode;
      return;
    }

    // Walk down the tree to find the right spot
    Node<T> *current = this->root;
    while (true) {
      if (value < current->data) {
        // Go left
        if (current->left == nullptr) {
          current->left = newNode; // empty spot found
          return;
        }
        current = current->left;
      } else if (value > current->data) {
        // Go right
        if (current->right == nullptr) {
          current->right = newNode; // empty spot found
          return;
        }
        current = current->right;
      } else {
        // Value already exists – discard the new node
        delete newNode;
        return;
      }
    }
  }

  // ---- search --------------------------------------------
  // Returns true if 'value' exists in the BST, false otherwise.
  // Uses the BST property to skip irrelevant subtrees.
  bool search(const T &value) const {
    Node<T> *current = this->root;

    while (current != nullptr) {
      if (value == current->data)
        return true; // found it
      else if (value < current->data)
        current = current->left; // look left
      else
        current = current->right; // look right
    }

    return false; // value not found
  }

  // ---- remove --------------------------------------------
  // Deletes the node whose data equals 'value'.
  // Handles three cases:
  //   1) Node has no children  → just delete it
  //   2) Node has one child    → replace node with its child
  //   3) Node has two children → replace data with in-order
  //                              successor, then delete successor
  void remove(const T &value) { this->root = removeHelper(this->root, value); }

  // ---- display -------------------------------------------
  // Prints the tree in sorted (in-order) order.
  void display() const {
    if (isEmpty()) {
      cout << "(empty tree)" << endl;
      return;
    }
    cout << "BST (inorder): ";
    this->inorderDisplay();
  }

private:
  // ---- removeHelper --------------------------------------
  // Recursive helper for remove().
  // Returns the (possibly new) root of the subtree after
  // the deletion.
  Node<T> *removeHelper(Node<T> *node, const T &value) {
    if (node == nullptr)
      return nullptr; // value not found

    if (value < node->data) {
      // Value is in the left subtree
      node->left = removeHelper(node->left, value);
    } else if (value > node->data) {
      // Value is in the right subtree
      node->right = removeHelper(node->right, value);
    } else {
      // Found the node to delete
      if (node->left == nullptr && node->right == nullptr) {
        // Case 1: leaf node – simply delete it
        delete node;
        return nullptr;
      } else if (node->left == nullptr) {
        // Case 2a: only right child – replace node with it
        Node<T> *temp = node->right;
        delete node;
        return temp;
      } else if (node->right == nullptr) {
        // Case 2b: only left child – replace node with it
        Node<T> *temp = node->left;
        delete node;
        return temp;
      } else {
        // Case 3: two children
        // Find the in-order successor (smallest value in
        // the right subtree), copy its data here, then
        // delete the successor from the right subtree.
        Node<T> *successor = node->right;
        while (successor->left != nullptr)
          successor = successor->left;

        node->data = successor->data; // overwrite with successor
        node->right = removeHelper(node->right, successor->data);
      }
    }

    return node;
  }
};

#endif // BINARYSEARCHTREE_H
