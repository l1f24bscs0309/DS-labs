/*
 *   split(bt, btLeft, btRight):
 *     The root of 'bt' separates left and right subtrees.
 *     To split: copy every value in bt's left subtree into btLeft,
 *     and every value in bt's right subtree into btRight. I do this
 *     by collecting values with an inorder traversal and reinserting.
 *     Example – tree (20 30 40 50 60 70 80):
 *       btLeft  ← values < root(50): 20 30 40
 *       btRight ← values > root(50): 60 70 80
 *
 *   insert(bt, toInsert):
 *     Do an inorder traversal of 'toInsert', and for each value
 *     call bt.insert(). This adds every node of toInsert into bt.
 *     Example: bt=(10 20 30), toInsert=(25 35):
 *       Insert 25 into bt → (10 20 25 30)
 *       Insert 35 into bt → (10 20 25 30 35)
 *
 *   deleteTreeFromNode(bt, value):
 *     1. Search for the node with 'value'.
 *     2. Collect all values in its subtree (inorder traversal
 *        starting from that node).
 *     3. Call bt.remove() for each of those values.
 *     Example: bt=(20 30 40 50 60 70 80), delete from node 70:
 *       Subtree of 70 contains: 70, 80.
 *       Remove 70 and 80 from bt → (20 30 40 50 60)
 *
 * FUNCTIONS REUSED:
 *   I reuse bt.insert() and bt.remove() from BinarySearchTree,
 *   and write small helper traversal functions to collect values
 *   from a subtree into a vector.
 *
 * LEARNING:
 *   I learned that global functions can manipulate objects by
 *   taking them by reference. I also learned how to collect all
 *   values from a subtree without exposing the internal node
 *   pointers – by using a helper that traverses from a given node.
 *
 */

#include <iostream>
#include <vector>
#include "BinarySearchTree.h"
using namespace std;

// ---------------------------------------------------------------
// collectInorder – traversal helper.
// Collects all values from the subtree rooted at 'node' into
// 'values' in sorted (inorder) order.
// ---------------------------------------------------------------
template <class T>
void collectInorder(Node<T>* node, vector<T>& values)
{
    if (node == nullptr) return;
    collectInorder(node->left,  values);
    values.push_back(node->data);
    collectInorder(node->right, values);
}

// ---------------------------------------------------------------
// split – divides 'bt' into left and right subtrees.
// btLeft  receives all values from bt's left subtree.
// btRight receives all values from bt's right subtree.
// The original tree 'bt' is passed by value so it is not changed.
// ---------------------------------------------------------------
template <class T>
void split(BinarySearchTree<T> bt,
           BinarySearchTree<T>& btLeft,
           BinarySearchTree<T>& btRight)
{
    // We need access to the root to get left/right subtrees.
    // We use the friend trick via a helper that traverses the copy.
    // Because we can't access 'root' directly from outside the
    // class we collect values using inorderDisplay logic via
    // a known workaround: we insert all values and then re-split.
    // Simpler approach: collect all values sorted, then split at
    // the midpoint value (root). We rebuild by inserting into btLeft
    // and btRight.

    // Collect all values from bt in sorted order
    vector<T> values;
    // We cast to BinaryTree* to access the protected 'root' via
    // a small local helper class. Instead, we use the following
    // clean approach: provide a protected accessor in BinaryTree.
    // Since the lab headers are minimal, we collect via a wrapper.

    // Practical approach: provide a getRoot helper in the BST.
    // Since we cannot change the class header (lab restriction),
    // we use a sub-class trick inline:
    struct Accessor : public BinarySearchTree<T> {
        Node<T>* getRoot() const { return this->root; }
    };
    Accessor& acc = reinterpret_cast<Accessor&>(bt);
    Node<T>* rootNode = acc.getRoot();

    if (rootNode == nullptr) return;  // nothing to split

    // Collect left subtree values
    vector<T> leftValues, rightValues;
    collectInorder(rootNode->left,  leftValues);
    collectInorder(rootNode->right, rightValues);

    // Rebuild btLeft and btRight
    for (const T& v : leftValues)
        btLeft.insert(v);

    for (const T& v : rightValues)
        btRight.insert(v);
}

// ---------------------------------------------------------------
// insert – inserts every node of 'toInsert' into 'bt'.
// Traverses toInsert inorder and calls bt.insert() for each value.
// ---------------------------------------------------------------
template <class T>
void insert(BinarySearchTree<T>& bt, BinarySearchTree<T> toInsert)
{
    struct Accessor : public BinarySearchTree<T> {
        Node<T>* getRoot() const { return this->root; }
    };
    Accessor& acc = reinterpret_cast<Accessor&>(toInsert);

    vector<T> values;
    collectInorder(acc.getRoot(), values);

    for (const T& v : values)
        bt.insert(v);
}

// ---------------------------------------------------------------
// findNodeByValue – walks the BST iteratively to find the node
// that holds 'value'. Returns nullptr if not found.
// (We use the Accessor pattern again to read the root.)
// ---------------------------------------------------------------
template <class T>
Node<T>* findNodeByValue(BinarySearchTree<T>& bt, const T& value)
{
    struct Accessor : public BinarySearchTree<T> {
        Node<T>* getRoot() const { return this->root; }
    };
    Accessor& acc = reinterpret_cast<Accessor&>(bt);
    Node<T>* current = acc.getRoot();

    while (current != nullptr)
    {
        if (value == current->data)  return current;
        if (value < current->data)   current = current->left;
        else                         current = current->right;
    }
    return nullptr;
}

// ---------------------------------------------------------------
// deleteTreeFromNode – finds the node with 'value' in 'bt', then
// deletes that node and all its descendants.
// ---------------------------------------------------------------
template <class T>
void deleteTreeFromNode(BinarySearchTree<T>& bt, const T& value)
{
    // Find the target node
    Node<T>* targetNode = findNodeByValue(bt, value);
    if (targetNode == nullptr)
    {
        cout << "Value " << value << " not found in tree." << endl;
        return;
    }

    // Collect all values in the subtree rooted at targetNode
    vector<T> toRemove;
    collectInorder(targetNode, toRemove);

    // Remove each of those values from the BST
    for (const T& v : toRemove)
        bt.remove(v);
}

// ---------------------------------------------------------------
// printBST – helper to display a BST inline
// ---------------------------------------------------------------
template <class T>
void printBST(const string& label, BinarySearchTree<T>& bst)
{
    cout << label;
    bst.display();
}

// ---------------------------------------------------------------
// main – tests all three global functions
// ---------------------------------------------------------------
int main()
{
    // Build a tree: 50, 30, 70, 20, 40, 60, 80
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    cout << "=== Original tree ===" << endl;
    printBST("", bst);

    // --- Test split ---
    cout << "\n=== split(bst, btLeft, btRight) ===" << endl;
    BinarySearchTree<int> btLeft, btRight;
    split(bst, btLeft, btRight);
    printBST("btLeft  (values from left subtree of root 50): ", btLeft);
    printBST("btRight (values from right subtree of root 50): ", btRight);

    // --- Test insert (merge) ---
    cout << "\n=== insert(btLeft, btRight) – merge right into left ===" << endl;
    insert(btLeft, btRight);
    printBST("btLeft after merge: ", btLeft);

    // --- Test deleteTreeFromNode ---
    cout << "\n=== deleteTreeFromNode(bst, 70) ===" << endl;
    cout << "Before: ";
    bst.display();
    deleteTreeFromNode(bst, 70);  // deletes 70 and its subtree (60 stays, 70 and 80 go)
    cout << "After removing subtree at node 70: ";
    bst.display();

    cout << "\n=== deleteTreeFromNode(bst, 30) ===" << endl;
    cout << "Before: ";
    bst.display();
    deleteTreeFromNode(bst, 30);  // deletes 30, 20, 40
    cout << "After removing subtree at node 30: ";
    bst.display();

    return 0;
}
