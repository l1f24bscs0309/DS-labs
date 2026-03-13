#pragma once
#include <iostream>
using namespace std;

#define MAX_SIZE 10

class Stack
{
public:
    Stack(int _maxCapacity = 0);
    Stack(const Stack & AA);
    virtual void push(int v) = 0;
    virtual bool pop(int &val) = 0;
    virtual bool get(int index, int & value) = 0;
    virtual void insert(int index, int value) = 0;
    // virtual void copy(Stack* src , Stack* dest) = 0;
    bool isEmpty();
    bool isFull();
protected:
    int currentIndex;
    int * values;
    int maxCapacity;
};

Stack::Stack(int _maxCapacity)
{
    currentIndex = -1;
    maxCapacity = _maxCapacity;
    values = new int[maxCapacity]{0};
}

Stack::Stack(const Stack & AA)
{
    maxCapacity = AA.maxCapacity;
    currentIndex = AA.currentIndex;

    values = new int[maxCapacity];

    for(int i = 0; i <= currentIndex; i++)
    {
        values[i] = AA.values[i];
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
