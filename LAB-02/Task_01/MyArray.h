// MyArray.h
#pragma once
#include <iostream>
using namespace std;
#include "AbstractArray.h"

class MyArray: public AbstractArray
{
    public:
        MyArray(int _currentIndex = 0): AbstractArray(_currentIndex){};
        MyArray(const MyArray & ma): AbstractArray(ma){};
        void add(int v);
        bool remove(int & v);
        bool get(int index, int & v);
        void insert(int index, int value);
};
void MyArray::add(int v)
{
    if(!isFull())
    {
        values[++currentIndex] = v;
        return;
    }
    cout << "Array is full\n";
}
bool MyArray::remove(int & v)
{
    if(!isEmpty())
    {
        v = values[currentIndex--];
        return true;
    }
    return false;
}
bool MyArray::get(int index, int & v)
{
    if(index >= 0 && index <= currentIndex)
    {
        v = values[index];
        return true;
    }
    return false;
}
void MyArray::insert(int index, int value)
{
    if(index > 0 && index <= currentIndex)
    {
        values[index] = value;
        return;
    }
    cout << index << " is invalid\n";
}
