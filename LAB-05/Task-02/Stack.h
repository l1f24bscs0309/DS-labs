#pragma once
#include "AbstractStack.h"
#include "myLinkedList.h"

class Stack: public AbstractStack{
public:
    Stack():AbstractStack(){};
    Stack(const Stack & s): AbstractStack(s){};
    void push(int v);
    bool pop(int & value);

    myLinkedList ll;
};

void Stack::push(int v){
    ll.insertAtFirst(v);
    count++;
}

bool Stack::pop(int & value)
{
    if (isEmpty())
    {
        cout << "Stack is empty; returning false" << endl;
        return false;
    }
    else
    {
        value = ll.removeFromFirst();
        count--;
        return true;
    }
}
