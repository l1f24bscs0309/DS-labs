#pragma once
#include "Stack.h"

class MyStack : public Stack
{
public:
    MyStack(int _maxCapacity = 0) : Stack(_maxCapacity) {};
    MyStack(const MyStack & ma) : Stack(ma) {};
    void push(int v);
    bool pop(int & v);
    bool get(int index, int & v);
    void insert(int index, int value);
};

void MyStack::push(int v)
{
    if (!isFull())
    {
        values[++currentIndex] = v;
        return;
    }
    cout << "Stack is full\n";
}

bool MyStack::pop(int & v)
{
    if (!isEmpty())
    {
        v = values[currentIndex--];
        return true;
    }
    return false;
}

bool MyStack::get(int index, int & v)
{
    if (index >= 0 && index <= currentIndex)
    {
        v = values[index];
        return true;
    }
    return false;
}

void MyStack::insert(int index, int value)
{
    if (index >= 0 && index <= currentIndex)
    {
        values[index] = value;
    }
}
