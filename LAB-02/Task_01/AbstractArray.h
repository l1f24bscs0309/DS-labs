// AbstractArray.h
#pragma once
#include <iostream>
class AbstractArray
{
    public:
        AbstractArray(int _maxCapacity = 0);
        AbstractArray(const AbstractArray & AA);
        virtual void add(int v) = 0; // increments currentIndex and add value if not full
        virtual bool remove(int & value) = 0; // if not empty returns the value at the currentIndex and decrements
        virtual bool get(int index, int & value) = 0; // return the value at the index if index is valid
        virtual void insert(int index, int value) = 0; // inserts the value at the index if index is valid, replaces
            bool isEmpty( );
        bool isFull( );
    protected:
        int currentIndex;
        int * values;
        int maxCapacity;
};

AbstractArray::AbstractArray(int _maxCapacity)
{
    currentIndex = -1;
    maxCapacity = _maxCapacity;
    values = new int[maxCapacity]{0};
}

AbstractArray::AbstractArray(const AbstractArray & AA)
{
    maxCapacity = AA.maxCapacity;
    values = new int[maxCapacity]{0};
    /*
       for(int i = 0; i < maxCapacity; i++)
       {
       values[i] = AA.values[i];
       }
       */
}
bool AbstractArray::isEmpty( )
{
    return (currentIndex < 0);
}
bool AbstractArray::isFull( )
{
    return (currentIndex == maxCapacity - 1);
}
