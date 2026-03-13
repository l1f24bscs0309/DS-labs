#pragma once
#include "Stack.h"
#include <string>
#include <cstring>


class MyStack : public Stack
{
public:
    MyStack(int _maxCapacity = 0) : Stack(_maxCapacity) {};
    MyStack(const MyStack & ma) : Stack(ma) {};
    void push(string v);
    bool pop(string & v);
    bool get(int index, string & v);
    void insert(int index, string value);
    // void copy(Stack* src , Stack* dest);
};


// void MyStack::copy(Stack* src , Stack* dest){
//     Stack* temp = new MyStack[MAX_SIZE];
//     for (int i = 0 ; i < MAX_SIZE ; i++){
//        int val;
//        val = src->pop(val);
//        temp->push(val);
//     }
//     for (int i = 0 ; i < MAX_SIZE ; i++){
//        int val;
//        val = temp->pop(val);
//        src->push(val);
//        dest->push(val);
//     }
//
// }

void MyStack::push(string v)
{
    if (!isFull())
    {
        words[++currentIndex] = v;
        return;
    }
    cout << "Stack is full\n";
}

bool MyStack::pop(string & v)
{
    if (!isEmpty())
    {
        v = words[currentIndex--];
        return true;
    }
    return false;
}

bool MyStack::get(int index, string & v)
{
    if (index >= 0 && index <= currentIndex)
    {
        v = words[index];
        return true;
    }
    return false;
}

void MyStack::insert(int index, string value)
{
    if (index >= 0 && index <= currentIndex)
    {
        words[index] = value;
    }
}

