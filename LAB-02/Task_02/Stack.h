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
    virtual bool pop(int & value) = 0;
    virtual bool get(int index, int & value) = 0;
    virtual void insert(int index, int value) = 0;
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
    values = new int[maxCapacity]{0};
}

bool Stack::isEmpty()
{
    return (currentIndex < 0);
}

bool Stack::isFull()
{
    return (currentIndex == maxCapacity - 1);
}
