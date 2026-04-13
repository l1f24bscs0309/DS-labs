#pragma once
#include "myLinkedList.h"
#include "Queue.h"
class MyQueue: public Queue
{
public:
  void enqueue(const int & value);
  int dequeue();
  void display(ostream &) const;
protected:
  myLinkedList ll;
};

// Add (insert element at topOfQIndex)
void MyQueue::enqueue(const int & value)
{
  if (isEmpty()) {  // First element insertion
      ll.insertAtLast(value);
      count++;
}
}

// Remove (remove element from  startOfQIndex)
int MyQueue::dequeue() {
  if (isEmpty()) {
    cout << "MyQueue is EMPTY! Cannot remove." << endl;
    return -1;
  }
  int removedValue = ll.removeFromFirst();
  count--;
  return removedValue;
}

// Display the queue
void MyQueue::display(ostream & W) const
{
    if (isEmpty()) {
        W << "MyQueue is EMPTY!" << endl;
        return;
    }
    W << "MyQueue: ";
    myLinkedList tempList = ll; // Create a copy to display without modifying the original
    tempList.display();
  // <A --> B --> C>
}


