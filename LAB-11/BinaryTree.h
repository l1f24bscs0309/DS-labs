#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Node.h"
#include <iostream>
#include <algorithm>   // std::max
using namespace std;

// -------------------------------------------------------
// BinaryTree.h
// An abstract base class that represents a generic Binary
// Tree.  It stores the root pointer and provides several
// concrete helper operations (height, node count, leaf
// count, copy, delete, traversals) as well as pure-virtual
// functions that every concrete subclass must implement.
// -------------------------------------------------------

template <class T>
class BinaryTree
{
protected:
    Node<T>* root;   // pointer to the root node of the tree

    // ---- protected helpers (used by subclasses) --------

    // deleteTree – removes every node from the tree and
    //              frees the heap memory they occupy.
    void deleteTree()
    {
        deleteSubTree(root);
        root = nullptr;
    }

    // deleteSubTree – recursive helper that post-order
    //                 deletes every node in the subtree
    //                 rooted at 'node'.
    void deleteSubTree(Node<T>* node)
    {
        if (node == nullptr) return;
        deleteSubTree(node->left);    // delete left side first
        deleteSubTree(node->right);   // then right side
        delete node;                  // finally this node
    }

    // copyTree – deep-copies every node from 'src' into
    //            this tree, creating brand-new Node objects.
    void copyTree(const BinaryTree<T>* src)
    {
        root = copySubTree(src->root);
    }

    // copySubTree – recursive helper that returns a new
    //               node (and its children) that mirrors
    //               the subtree rooted at 'node'.
    Node<T>* copySubTree(Node<T>* node)
    {
        if (node == nullptr) return nullptr;

        Node<T>* newNode = new Node<T>(node->data); // copy the value
        newNode->left  = copySubTree(node->left);   // copy left subtree
        newNode->right = copySubTree(node->right);  // copy right subtree
        return newNode;
    }

    // ---- private traversal helpers ---------------------

    void inorder(Node<T>* node) const
    {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node<T>* node) const
    {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node<T>* node) const
    {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    // height helper – returns the height of the subtree
    int heightHelper(Node<T>* node) const
    {
        if (node == nullptr) return 0;
        int leftH  = heightHelper(node->left);
        int rightH = heightHelper(node->right);
        return 1 + max(leftH, rightH);
    }

    // nodeCount helper – counts every node in the subtree
    int nodeCountHelper(Node<T>* node) const
    {
        if (node == nullptr) return 0;
        return 1 + nodeCountHelper(node->left) + nodeCountHelper(node->right);
    }

    // leavesCount helper – a leaf has no children
    int leavesCountHelper(Node<T>* node) const
    {
        if (node == nullptr) return 0;
        if (node->left == nullptr && node->right == nullptr)
            return 1;  // this node is a leaf
        return leavesCountHelper(node->left) + leavesCountHelper(node->right);
    }

public:
    // ---- constructors / destructor / assignment --------

    // Default constructor – creates an empty tree
    BinaryTree() : root(nullptr) {}

    // Copy constructor – deep-copies the other tree
    BinaryTree(const BinaryTree<T>& bt) : root(nullptr)
    {
        copyTree(&bt);
    }

    // Assignment operator – deep-copies, avoiding self-assignment
    const BinaryTree<T>& operator=(const BinaryTree<T>& bt)
    {
        if (this != &bt)
        {
            deleteTree();     // free existing nodes
            copyTree(&bt);    // copy from source
        }
        return *this;
    }

    // Virtual destructor – ensures subclass destructors run
    virtual ~BinaryTree()
    {
        deleteTree();
    }

    // ---- pure-virtual interface (must be overridden) ---
    virtual void insert(const T& value) = 0;
    virtual void remove(const T& value) = 0;
    virtual bool search(const T& value) const = 0;
    virtual bool isEmpty() const = 0;

    // ---- traversal display functions -------------------

    // inorderDisplay  – prints nodes Left → Root → Right
    //                   (gives sorted order for a BST)
    void inorderDisplay() const
    {
        inorder(root);
        cout << endl;
    }

    // preorderDisplay – prints nodes Root → Left → Right
    void preorderDisplay() const
    {
        preorder(root);
        cout << endl;
    }

    // postorderDisplay – prints nodes Left → Right → Root
    void postorderDisplay() const
    {
        postorder(root);
        cout << endl;
    }

    // ---- concrete utility functions --------------------

    // treeHeight – returns the number of levels in the tree
    //              (0 if tree is empty)
    int treeHeight() const
    {
        return heightHelper(root);
    }

    // treeNodeCount – returns the total number of nodes
    int treeNodeCount() const
    {
        return nodeCountHelper(root);
    }

    // treeLeavesCount – returns the number of leaf nodes
    //                   (nodes with no children)
    int treeLeavesCount() const
    {
        return leavesCountHelper(root);
    }
};

#endif // BINARYTREE_H
