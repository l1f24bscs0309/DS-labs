#pragma once
#include <iostream>
using namespace std;
class Queue
{
    public:
        Queue() :count(0) {}
        Queue(const Queue & q) : count(q.count){}
        virtual ~Queue() {}

        bool isEmpty() const;
        bool isFull() const;
        virtual void enqueue(const  int & value) = 0;
        virtual int dequeue() = 0;
        virtual void display(ostream &) const = 0;
    protected:
        int count;
};

// Check if queue is empty
bool Queue::isEmpty() const
{
    return (count == 0);
}
