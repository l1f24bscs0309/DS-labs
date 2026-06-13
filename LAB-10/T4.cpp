#include <iostream>
using namespace std;
#include "Node.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include <fstream>


// read from file takes a binary search tree and a filename as parameters, reads words from the file and inserts them into the tree. it 
// calls the insert method of the binary search tree to add each word to the tree. if the file cannot be opened, it displays an error message and returns without modifying the tree.
// the function uses an ifstream object to read from the file, and a string variable to store each word as it is read. it continues to read words until the end of the file is reached, at which point it closes the file.
void readFromFile (BinarySearchTree<string> &tree , const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    string word;
    while (file >> word) {
        tree.insert(word);
    }
    file.close();
    }


// searchAndConvertToUpper takes a binary search tree as a parameter, prompts the user to enter a word to search for in the tree. if the word is found, it removes the word from the tree, converts it to upper case, and then re-inserts it back into the tree. if the word is not found, it displays a message indicating that the word was not found in the tree.
// the function uses the search method of the binary search tree to check if the word exists in the tree. if it does, it uses the remove method to delete the word from the tree, then iterates through each character of the word and converts it to upper case using the toupper function. finally, it re-inserts the modified word back into the tree using the insert method.
void searchAndConvertToUpper(BinarySearchTree<string> &tree) {
    string word;
    cout << "Enter a word to search: ";
    cin >> word;
if (tree.search(word)) {
    tree.remove(word); 
        cout << "Word found. Converting to upper case: " << endl;
        for (char &c : word) {
            c = toupper(c);
        }
        cout << word << endl;
        tree.insert(word);
    } else {
        cout << "Word not found in the tree." << endl;
    }
}

// readFromUserAndInsert takes a binary search tree as a parameter, prompts the user to enter a word to insert into the tree, and then calls the insert method of the binary search tree to add the word to the tree. it uses a string variable to store the user's input and displays a message prompting the user to enter a word before reading the input.
// the function does not perform any validation on the user's input, so it assumes that the user will enter a valid word. after inserting the word into the tree, it does not display any confirmation message, but the main function will display the in-order traversal of the tree after the insertion to show the updated tree structure.
void readFromUserAndInsert(BinarySearchTree<string> &tree) {
    string word;
    cout << "\n Enter a word to insert: ";
    cin >> word;
    tree.insert(word);

}

// deleteWord takes a binary search tree as a parameter, prompts the user to enter a word to delete from the tree, and then checks if the word exists in the tree using the search method. if the word is found, it calls the remove method of the binary search tree to delete the word from the tree and displays a message confirming that the word was deleted. if the word is not found, it displays a message indicating that the word was not found in the tree.
void deleteWord(BinarySearchTree<string> &tree) {
    string word;
    cout << "\n Enter a word to delete: ";
    cin >> word;
    if (tree.search(word)) {
        tree.remove(word);
        cout << "\nWord deleted from the tree." << endl;
    } else {
        cout << "\nWord not found in the tree." << endl;
    }
}

int main () {
    BinarySearchTree<string> tree;
    readFromFile(tree, "words.txt");
    cout << " In-order traversal of the binary search tree:" << endl;
    tree.display();
    cout << endl;

    searchAndConvertToUpper(tree);
    cout << " In-order traversal of the binary search tree after search:" << endl;
    tree.display();

        readFromUserAndInsert(tree);
        cout << " In-order traversal of the binary search tree after insertion:" << endl;
        tree.display();

        deleteWord(tree);
        cout << " In-order traversal of the binary search tree after deletion:" << endl;
        tree.display();

    return 0;

}
