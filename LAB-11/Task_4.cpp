/*
 *   1. Open para.txt with ifstream. Read word by word (operator>>
 *      splits on whitespace automatically).
 *   2. Strip punctuation from each word so "hello," and "hello"
 *      are treated as the same word.
 *   3. Insert each cleaned word into BinarySearchTree<string> tree.
 *   4. Display: call tree.inorderDisplay() – gives sorted order.
 *   5. Search & uppercase:
 *        - Call tree.search(word) → true/false.
 *        - If found: tree.remove(word), convert to uppercase,
 *          tree.insert(uppercaseWord).
 *   6. Insert: read word, tree.insert(word), display.
 *   7. Delete: read word, tree.remove(word), display.
 *
 *   Example progression (para.txt contains "the quick brown fox"):
 *     After reading: BST inorder → brown fox quick the
 *     User searches "fox" → FOUND, remove "fox", insert "FOX"
 *     BST inorder → FOX brown quick the
 *     User inserts "zebra" → BST inorder → FOX brown quick the zebra
 *     User deletes "quick" → BST inorder → FOX brown the zebra
 *
 * FUNCTIONS REUSED:
 *   tree.insert()  – to load words and re-insert uppercase version
 *   tree.search()  – to check if a word exists
 *   tree.remove()  – to delete the lowercase version before uppercasing
 *   tree.inorderDisplay() – to print the sorted tree after each step
 *
 * LEARNING:
 *   I learned how to use a BST with a non-numeric type (string).
 *   String comparison in C++ already follows alphabetical order,
 *   so the BST property works naturally. I also learned to clean
 *   input (strip punctuation) before inserting.
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>         // toupper, ispunct
#include "BinarySearchTree.h"
using namespace std;

// ---------------------------------------------------------------
// cleanWord – removes leading and trailing punctuation from a word
//             and converts to lowercase for uniform storage.
// ---------------------------------------------------------------
string cleanWord(const string& raw)
{
    string cleaned;

    // Remove non-alpha characters (punctuation, numbers)
    for (char c : raw)
    {
        if (isalpha(c))
            cleaned += tolower(c);  // store everything in lowercase
    }

    return cleaned;
}

// ---------------------------------------------------------------
// toUpperStr – converts every character in 's' to uppercase
// ---------------------------------------------------------------
string toUpperStr(const string& s)
{
    string result = s;
    for (char& c : result)
        c = toupper(c);
    return result;
}

// ---------------------------------------------------------------
// main
// ---------------------------------------------------------------
int main()
{
    BinarySearchTree<string> tree;  // BST that stores English words

    // ---- Step 1: Read words from para.txt ----
    ifstream inFile("para.txt");

    if (!inFile.is_open())
    {
        cout << "Could not open para.txt. Creating a sample file..." << endl;

        // Create a sample file so the program can still run
        ofstream outFile("para.txt");
        outFile << "the quick brown fox jumps over the lazy dog "
                   "a binary search tree is an efficient data structure "
                   "for storing and retrieving sorted information quickly";
        outFile.close();
        inFile.open("para.txt");
    }

    string rawWord;
    while (inFile >> rawWord)
    {
        string word = cleanWord(rawWord);   // strip punctuation / lowercase
        if (!word.empty())
            tree.insert(word);              // BST ignores duplicates
    }
    inFile.close();

    // ---- Step 2: Display all words in sorted order ----
    cout << "=== Words in BST (sorted inorder) ===" << endl;
    tree.inorderDisplay();

    cout << "\nTotal nodes  : " << tree.treeNodeCount()   << endl;
    cout << "Tree height  : " << tree.treeHeight()       << endl;
    cout << "Leaf nodes   : " << tree.treeLeavesCount()  << endl;

    // ---- Step 3: Search for a word and convert to UPPERCASE ----
    cout << "\n=== Search and convert to UPPERCASE ===" << endl;
    cout << "Enter a word to search: ";
    string searchWord;
    cin >> searchWord;
    searchWord = cleanWord(searchWord);  // normalise input

    if (tree.search(searchWord))
    {
        cout << "\"" << searchWord << "\" FOUND in tree." << endl;

        // Remove the lowercase version
        tree.remove(searchWord);

        // Insert the uppercase version
        string upperWord = toUpperStr(searchWord);
        tree.insert(upperWord);

        cout << "Converted to uppercase and re-inserted as \""
             << upperWord << "\"." << endl;
    }
    else
    {
        cout << "\"" << searchWord << "\" NOT FOUND in tree." << endl;
    }

    cout << "\nTree after uppercase conversion:" << endl;
    tree.inorderDisplay();

    // ---- Step 4: Insert a new word ----
    cout << "\n=== Insert a new word ===" << endl;
    cout << "Enter a word to insert: ";
    string insertWord;
    cin >> insertWord;
    insertWord = cleanWord(insertWord);

    if (!insertWord.empty())
    {
        tree.insert(insertWord);
        cout << "\"" << insertWord << "\" inserted." << endl;
    }

    cout << "\nTree after insertion:" << endl;
    tree.inorderDisplay();

    // ---- Step 5: Delete a word ----
    cout << "\n=== Delete a word ===" << endl;
    cout << "Enter a word to delete: ";
    string deleteWord;
    cin >> deleteWord;
    deleteWord = cleanWord(deleteWord);

    if (tree.search(deleteWord))
    {
        tree.remove(deleteWord);
        cout << "\"" << deleteWord << "\" deleted." << endl;
    }
    else
    {
        cout << "\"" << deleteWord << "\" NOT FOUND – nothing deleted." << endl;
    }

    cout << "\nTree after deletion:" << endl;
    tree.inorderDisplay();

    return 0;
}
