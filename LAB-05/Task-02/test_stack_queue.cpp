#include "MyStack.h"
#include "MyQueue.h"
#include <iostream>
using namespace std;

int main()
{
  MyStack s;
  s.push(10);
  s.push(20);
  s.push(30);
  cout << "Top of stack: " << s.top() << endl; // Should print 30
  int poppedValue;
  if (s.pop(poppedValue)) {
    cout << "Popped value: " << poppedValue << endl; // Should print 30
  }
  cout << "Top of stack after pop: " << s.top() << endl; // Should print 20

  MyQueue q;
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  q.display(cout); // Should display the queue
  cout << "Dequeue value: " << q.dequeue() << endl; // Should print 1
  q.display(cout); // Should display the queue after dequeue

  return 0;
}
