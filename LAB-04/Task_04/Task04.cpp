#include "Queue.h"
#include "MyQueue.h"
#include "MyStack.h"
#include <iostream>
using namespace std;

void reverseFirstKElements(Queue* q , int k);

/*
 * first lets make a queue of size 10
 * moving 5 elemnts into it
 * after calling the reverseFirstKElements we get the first 3 elements reversed and the rest in the same order
*/

int main (){
    Queue* q = new MyQueue(10);
    q->enqueue(10);
    q->enqueue(20);
    q->enqueue(30);
    q->enqueue(40);
    q->enqueue(50);
    cout << "Original Queue: ";
    q->display(cout);
    int k = 3;
    reverseFirstKElements(q, k);
    cout << "Queue after reversing first " << k << " elements: ";
    q->display(cout);

    Queue* q2= new MyQueue(10);
    q2->enqueue(15);
    q2->enqueue(0);
    q2->enqueue(-3);
    q2->enqueue(99);
    cout << "Original Queue 2: ";
    q2->display(cout);
    k = 4;
    reverseFirstKElements(q2, k);
    cout << "Queue 2 after reversing first " << k << " elements: ";
    q2->display(cout);
     return 0;
}


int getSize(Queue* q){
    MyQueue temp(*q);
    int size = 0;
    while(!temp.isEmpty()){
        temp.dequeue();
        size++;
    }
    return size;
}

/* first we get the size of queue using the getsize function
now we create the stack and and dequeue the first k elemetns from the queue and push them on to the stack
now we pop the elements from the stack and enqueue them back to the queue, this will reverse the order of the first k elements
finally we need to move the remaining size-k elements from the front of the queue to the back 
of the queue to maintain their order after the reversed elements
*/

void reverseFirstKElements(Queue* q , int k){
    int size = getSize(q);
    MyStack st(size);
    for (int i = 0 ; i < k ; i++){
        st.push(q->dequeue());
    }
    int v;
    while(!st.isEmpty()){
        st.pop(v);
        q->enqueue(v);
    }
    for (int i = 0 ; i < size - k ; i++){
        q->enqueue(q->dequeue());
    }
}
