#ifndef NODE_H
#define NODE_H

// -------------------------------------------------------
// Node.h
// A generic Node class used to build a Binary Tree.
// Each node stores one data value, a pointer to its left
// child, and a pointer to its right child.
// -------------------------------------------------------

template <class T>
class Node
{
public:
    T     data;    // the value stored in this node
    Node* left;    // pointer to the left child  (nullptr if none)
    Node* right;   // pointer to the right child (nullptr if none)

    // Default constructor – sets both child pointers to null
    Node() : left(nullptr), right(nullptr) {}

    // Convenience constructor – initialise with a value
    Node(const T & val) : data(val), left(nullptr), right(nullptr) {}
};

#endif // NODE_H
