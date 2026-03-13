#include <string>
#include <iostream>
#include "Stack.h"
#include "MyStack.h"
#include <fstream>
using namespace std;

void readWordsFromFile(MyStack *s, ifstream &file) {
    string word;
    while (file >> word && !s->isFull()) {
        s->push(word);
    }
    file.close();
}

void display(MyStack *s) {
    MyStack temp(*s);
    string word;
    while (!temp.isEmpty()) {
        temp.pop(word);
        cout << word << " ";
    }
    cout << endl;
}

// Task 1: Copy words in reverse order into another stack and display
MyStack* reverseCopy(MyStack *s) {
    MyStack temp(*s);
    MyStack *rev = new MyStack(MAX_SIZE);

    string word;
    while (!temp.isEmpty()) {
        temp.pop(word);
        rev->push(word);
    }

    cout << "Reverse Copy: ";
    display(rev);
    return rev;
}

void removeDuplicates(MyStack *s) {
    MyStack result(MAX_SIZE);
    MyStack temp(*s);

    string word;
    while (!temp.isEmpty()) {
        temp.pop(word);

        MyStack check(result);
        string checkWord;
        bool found = false;

        while (!check.isEmpty()) {
            check.pop(checkWord);
            if (checkWord == word) {
                found = true;
                break;
            }
        }

        if (!found) {
            result.push(word);
        }
    }

    cout << "After Removing Duplicates: ";
    display(&result);
}


void countFrequency(MyStack *s) {
}

int main() {
    MyStack stack(MAX_SIZE);

    ifstream file("para.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open para.txt" << endl;
        return 1;
    }

    readWordsFromFile(&stack, file);

    cout << "Original Stack: ";
    display(&stack);
    cout << endl;

    MyStack *rev = reverseCopy(&stack);
    cout << endl;

    removeDuplicates(rev);
    cout << endl;

    countFrequency(&stack);

    delete rev;
    return 0;
}
