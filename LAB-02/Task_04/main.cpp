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
    MyStack rev(MAX_SIZE);
    string word;
    while (!temp.isEmpty()) {
        temp.pop(word);
        rev.push(word);
    }
    string w;
    while (!rev.isEmpty()) {
        rev.pop(w);
        cout << w << " ";
    }
    cout << endl;
}

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
    MyStack words(MAX_SIZE);   
    MyStack freq(MAX_SIZE);   
    MyStack temp(*s);

    string word;
    while (!temp.isEmpty()) {
        temp.pop(word);

        MyStack checkWords(words);
        MyStack checkFreq(freq);
        MyStack newWords(MAX_SIZE);
        MyStack newFreq(MAX_SIZE);

        string w, f;
        bool found = false;

        while (!checkWords.isEmpty()) {
            checkWords.pop(w);
            checkFreq.pop(f);
            if (w == word) {
                found = true;
                int count = stoi(f) + 1;
                newWords.push(w);
                newFreq.push(to_string(count));
            } else {
                newWords.push(w);
                newFreq.push(f);
            }
        }

        if (!found) {
            newWords.push(word);
            newFreq.push("1");
        }

        words = MyStack(MAX_SIZE);
        freq  = MyStack(MAX_SIZE);
        MyStack tempNew(newWords);
        MyStack tempFreq(newFreq);

        MyStack revWords(MAX_SIZE);
        MyStack revFreq(MAX_SIZE);
        while (!tempNew.isEmpty()) {
            tempNew.pop(w);
            tempFreq.pop(f);
            revWords.push(w);
            revFreq.push(f);
        }
        words = revWords;
        freq  = revFreq;
    }

    cout << "Word Frequencies:" << endl;
    MyStack dispWords(words);
    MyStack dispFreq(freq);
    string w, f;
    while (!dispWords.isEmpty()) {
        dispWords.pop(w);
        dispFreq.pop(f);
        cout << w << " : " << f << endl;
    }
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
