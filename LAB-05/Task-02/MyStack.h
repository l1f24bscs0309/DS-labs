#pragma once
#include "Stack.h"
class MyStack: public Stack
{
 public:
  MyStack(int _currentIndex = 0): Stack(){};
  MyStack(const MyStack & ma): Stack(ma){};
  void push(int v);
  bool pop(int & v);
  int top();
};

void MyStack::push(int v)
{
     ll.insertAtFirst(v);
      return;
}

bool MyStack::pop(int & v)
  {
    if(!isEmpty())
    {
        v = ll.removeFromFirst();
      return true;
    }
    return false;
}

int MyStack::top()
{
    int v;
  if(!isEmpty())
    {
        v = ll.removeFromFirst();
        ll.insertAtFirst(v);
    }
  return -1;
}
