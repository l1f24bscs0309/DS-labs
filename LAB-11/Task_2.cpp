/*
 *   In this task I must implement all the public functions of the
 *   BinarySearchTree class (which inherits from BinaryTree). The
 *   class functions are already declared in the header files. I
 *   need to write the bodies for: insert, remove, search, isEmpty,
 *   and display.
 *
 *
 *   Example progression (insert order: 50, 30, 70, 20, 40, 60, 80):
 *     Empty tree → insert(50) → (50)
 *     → insert(30) → (30, 50)
 *     → insert(70) → (30, 50, 70)
 *     → insert(20) → (20, 30, 50, 70)   ... and so on
 *     Final inorder: 20 30 40 50 60 70 80
 *
 *   After remove(30) – node with two children:
 *     Successor of 30 is 40. Replace 30's data with 40, delete 40.
 *     Inorder: 20 40 50 60 70 80
 *
 * FUNCTIONS REUSED:
 *   All implementations come from BinarySearchTree.h and BinaryTree.h.
 *   In this file I reuse insert() to build the tree, search() to
 *   verify values, display() to show the current state, and the
 *   three traversal functions (inorder, preorder, postorder) from
 *   the base class to verify the tree structure.
 *
 * LEARNING:
 *   I learned how a class hierarchy works: BinaryTree is abstract
 *   (has pure-virtual functions) and BinarySearchTree provides the
 *   concrete implementations. The virtual destructor in BinaryTree
 *   ensures the subclass destructor also runs when we delete through
 *   a base-class pointer.
 *
 * ----------------------------------------------------------------
 */

#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

int main()
{
    BinarySearchTree<int> bst;

    // --- isEmpty on fresh tree ---
    cout << "Is tree empty? " << (bst.isEmpty() ? "Yes" : "No") << endl;

    // --- insert values ---
    cout << "\n--- Inserting: 50, 30, 70, 20, 40, 60, 80 ---" << endl;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    bst.display();   // should print sorted: 20 30 40 50 60 70 80

    // --- isEmpty after inserts ---
    cout << "Is tree empty? " << (bst.isEmpty() ? "Yes" : "No") << endl;

    // --- Utility functions inherited from BinaryTree ---
    cout << "\nTree height      : " << bst.treeHeight()      << endl;
    cout << "Total node count : " << bst.treeNodeCount()   << endl;
    cout << "Leaf node count  : " << bst.treeLeavesCount() << endl;

    // --- Three traversal orders ---
    cout << "\nInorder   (sorted): ";  bst.inorderDisplay();
    cout << "Preorder  (root first): "; bst.preorderDisplay();
    cout << "Postorder (root last) : "; bst.postorderDisplay();

    // --- search ---
    cout << "\n--- search ---" << endl;
    cout << "search(40): " << (bst.search(40) ? "FOUND" : "NOT FOUND") << endl;
    cout << "search(99): " << (bst.search(99) ? "FOUND" : "NOT FOUND") << endl;

    // --- remove leaf (20) ---
    cout << "\n--- remove(20) – leaf node ---" << endl;
    bst.remove(20);
    bst.display();

    // --- remove node with one child ---
    cout << "\n--- remove(30) – now has only right child 40 ---" << endl;
    bst.remove(30);
    bst.display();

    // --- remove node with two children (50, the root) ---
    cout << "\n--- remove(50) – two children ---" << endl;
    bst.remove(50);
    bst.display();

    // --- Try inserting a duplicate ---
    cout << "\n--- Inserting duplicate 70 (should be ignored) ---" << endl;
    bst.insert(70);
    bst.display();

    // --- Copy constructor test ---
    cout << "\n--- Copy constructor test ---" << endl;
    BinarySearchTree<int> bst2(bst);
    cout << "bst2.display(): ";
    bst2.display();

    // --- Assignment operator test ---
    cout << "\n--- Assignment operator test ---" << endl;
    BinarySearchTree<int> bst3;
    bst3 = bst;
    cout << "bst3.display(): ";
    bst3.display();

    return 0;
}
