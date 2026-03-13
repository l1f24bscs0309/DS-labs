#pragma once
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

#define MAX_SIZE 100

class Stack
{
public:
    Stack(int _maxCapacity = 0);
    Stack(const Stack & AA);
    virtual void push(string v) = 0;
    virtual bool pop(string &val) = 0;
    virtual bool get(int index, string & value) = 0;
    virtual void insert(int index, string value) = 0;
    // virtual void copy(Stack* src , Stack* dest) = 0;
    bool isEmpty();
    bool isFull();
protected:
    int currentIndex;
    string * words;
    int maxCapacity;
};

Stack::Stack(int _maxCapacity)
{
    currentIndex = -1;
    maxCapacity = _maxCapacity;
    words = new string[maxCapacity]{};
}

Stack::Stack(const Stack & AA)
{
    maxCapacity = AA.maxCapacity;
    currentIndex = AA.currentIndex;

    words = new string[maxCapacity];

    for(int i = 0; i <= currentIndex; i++)
    {
        words[i] = AA.words[i];
    }
}

bool Stack::isEmpty()
{
    return (currentIndex < 0);
}

bool Stack::isFull()
{
    return (currentIndex == maxCapacity - 1);
}
