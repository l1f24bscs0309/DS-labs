// main.cpp for task 1

#include <iostream>
using namespace std;
#include <iostream>
using namespace std;
#include "Stack.h"
#include "MyStack.h"
#include "Queue.h"
#include "MyQueue.h"

void read(Queue *q, istream &in); // read from user or file until queue is full
void display(Queue *q, ostream &out); // Display the values in the Queue
void append(Queue * src, Queue * dst); // append src to dst
void append(Queue * src, Queue * dst, int no); // append no of values from
void reverseAppend(Queue * src, Queue * dst);// append src in dst in reverse
int getSize(Queue * q);
void stats(Queue * q, int & sum, float & average);
bool isEqual(Queue *q1, Queue *q2);
const int MAX_SIZE = 5;

/*
 the assignment asks us to implement the functions in main.cpp and test them. The functions are defined above and we will implement them below. The main function will create queues, read values into them, display them, and test the append and reverse append functions, as well as the stats and isEqual functions.
 
 first i wrote all the functions in main.cpp and then i will implement them one by one. 
 
 after read the queue status is A: 1-> 2-> 3-> 4-> 5
 after append A to B, B should be 1-> 2-> 3-> 4-> 5
 after append A to C with no = 2, C should be 9-> 7-> 5-> 1-> 2
 after reverse append C to D, D should be 2-> 1-> 5-> 7-> 9
 after stats on A, sum should be 15 and average should be 3.0
 after append A to M, M should be 1-> 2-> 3-> 4-> 5
 after append N to M, M should be 1-> 2-> 3-> 4-> 5 (N is empty so it should not change M)

 the function i reused are :
    - append(Queue * src, Queue * dst)
    - getSize(Queue * q)
    - copy constructor of MyQueue
    - display(Queue *q, ostream &out)
    - isEmpty() and isFull() functions of Queue class
    - enqueue and dequeue functions of MyQueue class

learning from this task was to understand how to manipulate queues and stacks, how to implement functions that operate on these data structures, and how to test them effectively. I also learned about the importance of using copy constructors to avoid 
modifying the original data when performing operations like append and reverse append. Additionally, I gained experience in calculating statistics from a queue and comparing two queues for equality.

*/


int main(){

    Queue* A = new MyQueue(MAX_SIZE);
    int n = 0;

    read(A, cin);
    cout << " Queue A Values: ";
    display(A, cout);

    Queue* B = new MyQueue(MAX_SIZE);
    append(A, B);
    cout << " Queue B Values: ";
    display(B, cout);

    Queue* C = new MyQueue(MAX_SIZE);
    C->enqueue(9);
    C->enqueue (7);
    C->enqueue(5);
    append(A, C, 2);
    cout << "Queue C Values after append of 2 values from A: ";
    display(C, cout);

    Queue * D = new MyQueue(MAX_SIZE);
    reverseAppend(C, D);
    cout << "Queue D Values after reverse append from V: ";
    display(D, cout);

    int mx = 0;
    float ag = 0.0;
    stats(A, mx, ag);

    cout << "Queue A Values: ";
    display(A, cout);

    cout << "Average is " << ag << " maximum is " << mx << endl;

    Queue* M = new MyQueue(MAX_SIZE);
    Queue* N = new MyQueue(MAX_SIZE);
    Queue* P = new MyQueue(MAX_SIZE);

    append(A, M);
    append(N, M);
    append(N, P);
    P->enqueue(111);
    if(!isEqual(A, M)){
        cout << "Not Equal:\n";
    }else{
        cout << "Equal:\n";
    }

    if(!isEqual(A, P)){
        cout << "Not Equal:\n";
    }else{
        cout << "Equal:\n";
    }
    return 0;
}

void read(Queue *q, istream &in) {
    cout << "Enter values to add to queue: ";
    int value;
    while(!q->isFull()){
        in >> value;
        q->enqueue(value);
    }
}

void display(Queue *q, ostream &out) {
    q->display(out);
}

void append(Queue *src, Queue *dst) {
    MyQueue temp(*src);
    while(!temp.isEmpty()){
        dst->enqueue(temp.dequeue());
    }
}

void append(Queue *src, Queue *dst, int no) {
    MyQueue temp(*src);
    int count = 0;
    while(!temp.isEmpty() && count < no){
        dst->enqueue(temp.dequeue());
        count++;
    }
}

void reverseAppend(Queue *src, Queue *dst) {
    MyStack tempStack(MAX_SIZE);
    MyQueue temp(*src);
    while(!temp.isEmpty()){
        tempStack.push(temp.dequeue());
    }
    int val;
    while(!tempStack.isEmpty()){
        tempStack.pop(val);
        dst->enqueue(val);
    }
}

int getSize(Queue *q) {
    MyQueue temp(*q);
    int size = 0;
    while(!temp.isEmpty()){
        temp.dequeue();
        size++;
    }
    return size;
}

void stats(Queue * q, int & sum, float & average){
    MyQueue temp(*q);
    sum = 0;
    int count = 0;
    while(!temp.isEmpty()){
        sum += temp.dequeue();
        count++;
    }
    average = (float)sum / count;
}

bool isEqual(Queue* q1, Queue* q2){
    MyQueue temp1(*q1);
    MyQueue temp2(*q2);

    if(getSize(q1) != getSize(q2)) return false;

    int val1, val2;
    while(!temp1.isEmpty() && !temp2.isEmpty()){
        val1 = temp1.dequeue();
        val2 = temp2.dequeue();
        if(val1 != val2) return false;
    }
    return temp1.isEmpty() && temp2.isEmpty();
}

