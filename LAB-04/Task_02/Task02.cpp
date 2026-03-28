// main.cpp for Task 2
#include <iostream>
using namespace std;
#include "Stack.h"
#include "MyStack.h"
#include "Queue.h"
#include "MyQueue.h"

void display(Queue *, ostream &); // Display the values in the Queue
void append(Queue * src, Queue * dst); // append src to dst
void append(Queue * src, Queue * dst, int no); // append no of values from src to dst
void reverseAppend(Queue * src, Queue * dst);// append src in dst in reverseorder
int getSize(Queue * q);
bool isEqual(Queue *, Queue * );

void insert(Queue * src, Queue * dst, int pos);
void insert(Queue * q, int v, int pos); // insert a value in the queue at the given position
void shiftRight(Queue * q, int pos);
void shiftLeft(Queue * q, int pos);
const int MAX_SIZE = 10;



int main()
{
    Queue* A = new MyQueue(MAX_SIZE);
    A->enqueue(10);
    A->enqueue(9);
    A->enqueue(2);
    A->enqueue(5);
    A->enqueue(-7);
    cout << " Queue A Values: ";
    display(A, cout);

    Queue* B = new MyQueue(MAX_SIZE);
    B->enqueue(1);
    B->enqueue(2);
    insert(B, -100, 2);
    cout << " Queue B Values after insert: ";
    display(B, cout);

    insert(A, B, 2);
    cout << " Queue B Values after insert: ";
    display(B, cout);

    shiftRight(B, 2);
    cout << " Queue B Values after shiftRight from pos 2";
    display(B, cout);

    // shiftLeft(B, 2);
    // cout << " Queue B Values after shiftLeft from pos 2: ";
    // display(B, cout);
    return 0;
}
// display: call display method of queue to print all values to the given output stream
void display(Queue *q, ostream &out) {
    q->display(out);
}

// append: make a copy of src to dequeue from without modifying original, then dequeue from copy and enqueue into dst until copy is empty
void append(Queue *src, Queue *dst) {
    MyQueue temp(*src);
    while (!temp.isEmpty()) {
        dst->enqueue(temp.dequeue());
    }
}

// append: make a copy of src to dequeue from without modifying original, then dequeue from copy and enqueue into dst only 'no' times using a counter
void append(Queue *src, Queue *dst, int no) {
    MyQueue temp(*src);
    int count = 0;
    while (!temp.isEmpty() && count < no) {
        dst->enqueue(temp.dequeue());
        count++;
    }
}

// reverseAppend: make a copy of src to dequeue from without modifying original, push every element onto a stack to reverse order, then pop from stack into dst so dst gets src in reverse
void reverseAppend(Queue *src, Queue *dst) {
    MyStack tempStack(MAX_SIZE);
    MyQueue temp(*src);
    while (!temp.isEmpty()) {
        tempStack.push(temp.dequeue());
    }
    int val;
    while (!tempStack.isEmpty()) {
        tempStack.pop(val);
        dst->enqueue(val);
    }
}

// getSize: make a copy of q to dequeue from without modifying original, then dequeue and count until copy is empty to get the size
int getSize(Queue *q) {
    MyQueue temp(*q);
    int size = 0;
    while (!temp.isEmpty()) {
        temp.dequeue();
        size++;
    }
    return size;
}

// isEqual: make copies of both queues so originals are not modified, check sizes first and return false if they differ, then dequeue from both copies and compare element by element returning false on first mismatch
bool isEqual(Queue* q1, Queue* q2) {
    MyQueue temp1(*q1);
    MyQueue temp2(*q2);
    if (getSize(q1) != getSize(q2)) return false;
    int val1, val2;
    while (!temp1.isEmpty() && !temp2.isEmpty()) {
        val1 = temp1.dequeue();
        val2 = temp2.dequeue();
        if (val1 != val2) return false;
    }
    return true;
}

// insert: make a copy of src to dequeue from and result to store final order, check if pos is out of bounds by comparing with dst size, enqueue first pos elements from dst into result, then enqueue all of src copy, then enqueue remaining dst elements, then move result back into dst
void insert(Queue *src, Queue *dst, int pos) {
    MyQueue temp(*src);
    MyQueue result(MAX_SIZE);
    int size = getSize(dst);
    if (pos < 0 || pos > size) {
        cout << "Invalid position for insert." << endl;
        return;
    }
    for (int i = 0; i < pos; ++i) {
        result.enqueue(dst->dequeue());
    }
    while (!temp.isEmpty()) {
        result.enqueue(temp.dequeue());
    }
    while (!dst->isEmpty()) {
        result.enqueue(dst->dequeue());
    }
    while (!result.isEmpty()) {
        dst->enqueue(result.dequeue());
    }
}

// insert: check if pos is out of bounds by comparing with queue size, make temp to rebuild queue 
// with v inserted, enqueue first pos elements from q into temp, then enqueue v at pos, 
// then enqueue remaining q elements, then move temp back into q
void insert(Queue *q, int v, int pos) {
    if (pos < 0 || pos > getSize(q)) {
        cout << "Invalid position for insert." << endl;
        return;
    }
    MyQueue temp(MAX_SIZE);
    for (int i = 0; i < pos; ++i) {
        temp.enqueue(q->dequeue());
    }
    temp.enqueue(v);
    while (!q->isEmpty()) {
        temp.enqueue(q->dequeue());
    }
    while (!temp.isEmpty()) {
        q->enqueue(temp.dequeue());
    }
}

// shiftRight: check if pos is out of bounds by comparing with queue size, 
// enqueue first pos elements into result unchanged, push remaining elements onto a stack so 
// the last element is on top, pop that last element and enqueue it at position pos as the wrapped element, 
// restore remaining stack elements back in order using a temp queue, then enqueue them after the 
// wrapped element, then move result back into q
void shiftRight(Queue *q, int pos) {
    int size = getSize(q);
    if (pos < 0 || pos >= size) {
        cout << "Invalid position for shiftRight." << endl;
        return;
    }
    MyQueue result(MAX_SIZE);
    for (int i = 0; i < pos; ++i) {
        result.enqueue(q->dequeue());
    }
    MyStack tempStack(MAX_SIZE);
    while (!q->isEmpty()) {
        tempStack.push(q->dequeue());
    }
    int wrapped;
    tempStack.pop(wrapped);
    result.enqueue(wrapped);
    MyQueue subTemp(MAX_SIZE);
    int val;
    while (!tempStack.isEmpty()) {
        tempStack.pop(val);
        subTemp.enqueue(val);
    }
    while (!subTemp.isEmpty()) {
        result.enqueue(subTemp.dequeue());
    }
    while (!result.isEmpty()) {
        q->enqueue(result.dequeue());
    }
}

// shiftLeft: check if pos is out of bounds by comparing with queue size, enqueue first pos elements into result unchanged, 
// dequeue the element at pos and save it as wrapped, enqueue remaining elements one step forward into result, 
// then enqueue the wrapped element at the end, then move result back into q
void shiftLeft(Queue *q, int pos) {
    int size = getSize(q);
    if (pos < 0 || pos >= size) {
        cout << "Invalid position for shiftLeft." << endl;
        return;
    }
    MyQueue result(MAX_SIZE);
    for (int i = 0; i < pos; ++i) {
        result.enqueue(q->dequeue());
    }
    int wrapped = q->dequeue();
    while (!q->isEmpty()) {
        result.enqueue(q->dequeue());
    }
    result.enqueue(wrapped);
    while (!result.isEmpty()) {
        q->enqueue(result.dequeue());
    }
}
