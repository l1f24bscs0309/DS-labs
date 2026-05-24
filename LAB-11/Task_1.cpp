/*

 *   In this task I have to write iterative (no recursion allowed)
 *   functions that work directly on BST nodes. Each function takes
 *   a pointer to the root node (or a specific node) and performs
 *   an operation: searching for a value, adding a value, finding a
 *   node, finding the next-larger node, and deleting a single node.
 *   search:
 *     Start at root. If current node's data equals value → found.
 *     If value is smaller → go left. If value is larger → go right.
 *     Repeat until we find it or reach a null pointer (not found).
 *     BST progression example (searching 7 in 5→3→7→9):
 *       Start at 5 → 7 > 5 → go right
 *       At 9 → 7 < 9 → go left
 *       At 7 → found! Return true.
 *
 *   addValue:
 *     Same walk as search. When we reach a null child pointer,
 *     that is where the new node belongs. Create it and attach.
 *     Example inserting 6 into (5, 3, 7):
 *       Start 5 → 6>5 go right
 *       At 7 → 6<7 go left
 *       Left of 7 is null → attach new node(6) there.
 *       Result: 5 → right:7 → left:6
 *
 *   find (by exact value):
 *     Same as search but returns the Node pointer instead of bool.
 *
 *   find (next larger):
 *     The "next larger" node in a BST is called the in-order
 *     successor. Algorithm:
 *     a) If the node has a right subtree → go right once, then
 *        keep going left until null. That is the successor.
 *     b) If no right subtree → walk from root, track the last
 *        node where we turned left; that is the successor.
 *
 *   deleteNode:
 *     Three cases (iterative):
 *     Case 1 – No children: find parent, set parent's pointer null.
 *     Case 2 – One child:   find parent, replace pointer with child.
 *     Case 3 – Two children: find in-order successor (leftmost of
 *              right subtree), copy its data into current node,
 *              then delete the successor (which has at most one child).
 *
 * FUNCTIONS REUSED:
 *   I reuse the same BST walk (start at root, go left if smaller,
 *   go right if larger) in all five functions. This reduces repeated
 *   code and follows the BST property consistently.
 *   Example progression after several calls on tree 50,30,70,20,40,60,80:
 *     addValue(root, 35): 50→30→40→35(inserted as left child of 40)
 *       (50, 30, 70, 20, 40, 60, 80, 35)
 *     find(root, 35)    : 50→30→40→35 → returns &35
 *     deleteNode(&35)   : leaf → parent(40).left = null
 *       (50, 30, 70, 20, 40, 60, 80)
 *
 * LEARNING:
 *   I learned how the BST ordering property makes each operation
 *   O(h) where h is the tree height – we never have to look at
 *   every node, only along one path from root to leaf.
 *   I also learned the three delete cases and why the in-order
 *   successor is the safest replacement for a two-child node.
 */

#include <iostream>
#include "Node.h"
using namespace std;

// ---------------------------------------------------------------
// search – iteratively looks for 'value' in the BST.
// Returns true if found, false otherwise.
// ---------------------------------------------------------------
template <class T>
bool search(Node<T>* root, T value)
{
    Node<T>* current = root;

    while (current != nullptr)
    {
        if (value == current->data)
            return true;               // found the value

        if (value < current->data)
            current = current->left;   // value is in the left side
        else
            current = current->right;  // value is in the right side
    }

    return false;  // reached a null pointer – value not in tree
}

// ---------------------------------------------------------------
// addValue – inserts 'value' into the correct BST position.
// Uses an iterative walk; does nothing if value already exists.
// NOTE: root must NOT be nullptr when this is called; for an
//       empty tree the caller should create the root first.
// ---------------------------------------------------------------
template <class T>
void addValue(Node<T>* root, T value)
{
    if (root == nullptr) return;  // cannot add to a completely null tree here

    Node<T>* current = root;
    Node<T>* parent  = nullptr;

    // Walk down to find the insertion point
    while (current != nullptr)
    {
        parent = current;

        if (value < current->data)
            current = current->left;
        else if (value > current->data)
            current = current->right;
        else
            return;  // duplicate – do not insert
    }

    // Create the new node and attach it to the parent
    Node<T>* newNode = new Node<T>(value);

    if (value < parent->data)
        parent->left = newNode;   // new node goes to left of parent
    else
        parent->right = newNode;  // new node goes to right of parent
}

// ---------------------------------------------------------------
// find (exact match) – returns a pointer to the node that holds
// 'value', or nullptr if not found.
// ---------------------------------------------------------------
template <class T>
Node<T>* find(Node<T>* root, T value)
{
    Node<T>* current = root;

    while (current != nullptr)
    {
        if (value == current->data)
            return current;            // found – return the node

        if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }

    return nullptr;  // not found
}

// ---------------------------------------------------------------
// findNextLarger – returns a pointer to the node that holds the
// smallest value that is LARGER than 'value' (in-order successor).
// Returns nullptr if no such node exists.
// ---------------------------------------------------------------
template <class T>
Node<T>* findNextLarger(Node<T>* root, T value)
{
    Node<T>* successor = nullptr;
    Node<T>* current   = root;

    while (current != nullptr)
    {
        if (value < current->data)
        {
            // current is a candidate successor; go left to find
            // a smaller (but still larger than value) candidate
            successor = current;
            current   = current->left;
        }
        else
        {
            // current is not larger – go right
            current = current->right;
        }
    }

    return successor;  // nullptr if no larger value exists
}

// ---------------------------------------------------------------
// deleteNode – deletes exactly ONE given node from the tree.
// 'root' is passed by reference so the root pointer can change
// if the root itself is deleted.
// Three cases handled:
//   1) Leaf node (no children)
//   2) One child
//   3) Two children (replace with in-order successor)
// ---------------------------------------------------------------
template <class T>
void deleteNode(Node<T>*& root, Node<T>* nodeToDelete)
{
    if (root == nullptr || nodeToDelete == nullptr) return;

    // --- Case 3: node has TWO children ---
    // Replace node's data with in-order successor's data, then
    // delete the successor (which has at most one child).
    if (nodeToDelete->left != nullptr && nodeToDelete->right != nullptr)
    {
        // Find in-order successor: leftmost node of right subtree
        Node<T>* successorParent = nodeToDelete;
        Node<T>* successor       = nodeToDelete->right;

        while (successor->left != nullptr)
        {
            successorParent = successor;
            successor       = successor->left;
        }

        // Copy successor's data into the node we want to "delete"
        nodeToDelete->data = successor->data;

        // Now delete the successor (it has at most a right child)
        if (successorParent == nodeToDelete)
            successorParent->right = successor->right;
        else
            successorParent->left  = successor->right;

        delete successor;
        return;
    }

    // --- Cases 1 and 2: zero or one child ---
    // We need to find the parent of nodeToDelete.
    Node<T>* parent  = nullptr;
    Node<T>* current = root;

    while (current != nullptr && current != nodeToDelete)
    {
        parent = current;
        if (nodeToDelete->data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (current == nullptr) return;  // node not in tree

    // The child that will replace nodeToDelete (may be nullptr)
    Node<T>* child = (nodeToDelete->left != nullptr)
                     ? nodeToDelete->left
                     : nodeToDelete->right;

    if (parent == nullptr)
    {
        // Deleting the root node
        root = child;
    }
    else if (parent->left == nodeToDelete)
        parent->left  = child;
    else
        parent->right = child;

    delete nodeToDelete;
}

// ---------------------------------------------------------------
// Helper – inserts a root for an empty tree and returns it
// ---------------------------------------------------------------
template <class T>
Node<T>* createRoot(T value)
{
    return new Node<T>(value);
}

// ---------------------------------------------------------------
// Helper – prints the tree in sorted (in-order) order
// ---------------------------------------------------------------
template <class T>
void printInorder(Node<T>* node)
{
    if (node == nullptr) return;
    printInorder(node->left);
    cout << node->data << " ";
    printInorder(node->right);
}

// ---------------------------------------------------------------
// main – tests all five functions
// ---------------------------------------------------------------
int main()
{

    Node<int>* root = createRoot(50);
    addValue(root, 30);
    addValue(root, 70);
    addValue(root, 20);
    addValue(root, 40);
    addValue(root, 60);
    addValue(root, 80);

    cout << "Tree after insertions (inorder): ";
    printInorder(root);
    cout << endl;

    // --- Test search ---
    cout << "\n--- search ---" << endl;
    cout << "search(root, 40): " << (search(root, 40) ? "FOUND" : "NOT FOUND") << endl;
    cout << "search(root, 99): " << (search(root, 99) ? "FOUND" : "NOT FOUND") << endl;

    // --- Test find (exact) ---
    cout << "\n--- find (exact value) ---" << endl;
    Node<int>* found = find(root, 60);
    cout << "find(root, 60): " << (found ? "FOUND node with data=" + to_string(found->data) : "NOT FOUND") << endl;

    // --- Test findNextLarger ---
    cout << "\n--- findNextLarger ---" << endl;
    Node<int>* nextLarger = findNextLarger(root, 40);
    cout << "Next larger than 40: " << (nextLarger ? to_string(nextLarger->data) : "none") << endl;
    nextLarger = findNextLarger(root, 80);
    cout << "Next larger than 80: " << (nextLarger ? to_string(nextLarger->data) : "none") << endl;

    // --- Test deleteNode ---
    cout << "\n--- deleteNode ---" << endl;

    // Delete a leaf (20)
    Node<int>* toDelete = find(root, 20);
    deleteNode(root, toDelete);
    cout << "After deleting 20 (leaf): ";
    printInorder(root);
    cout << endl;

    // Delete a node with one child (30, which now has only right child 40)
    toDelete = find(root, 30);
    deleteNode(root, toDelete);
    cout << "After deleting 30 (one child): ";
    printInorder(root);
    cout << endl;

    // Delete a node with two children (50 – the root)
    toDelete = find(root, 50);
    deleteNode(root, toDelete);
    cout << "After deleting 50 (two children, root): ";
    printInorder(root);
    cout << endl;

    return 0;
}
