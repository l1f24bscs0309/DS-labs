#include <iostream>
using namespace std;
#include "Stack.h"
#include "MyStack.h"

void read(Stack *, istream &, int);
void display(Stack *, ostream &);
void copy(Stack * src, Stack * dst);
void insert(Stack * src, Stack * dst, int pos);
void shiftUp(Stack * s, int pos);
void shiftDown(Stack * s, int pos);
void stats(Stack * s, int & max, float & average);

int main()
{
    Stack * A = new MyStack(MAX_SIZE);
    int n = 0;
    cout << "please select a number between 1 and " << MAX_SIZE << ": ";
    cin >> n;
    read(A, cin, n);
    cout << "Stack A Values: ";
    display(A, cout);

    Stack * B = new MyStack(MAX_SIZE);
    copy(A, B);
    cout << "Stack B Values: ";
    display(B, cout);

    Stack * C = new MyStack(MAX_SIZE);
    C->push(9);
    C->push(7);
    C->push(5);
    insert(A, C, 2);
    cout << "Stack C Values: ";
    display(C, cout);

    shiftUp(C, 2);
    cout << "Stack C Values: ";
    display(C, cout);

    shiftDown(C, 2);
    cout << "Stack C Values: ";
    display(C, cout);

    int mx = 0;
    float ag = 0.0;
    stats(C, mx, ag);
    cout << "Stack C Values: ";
    display(C, cout);
    cout << "Average is " << ag << " maximum is " << mx << endl;

    delete A;
    delete B;
    delete C;
    return 0;
}

void read(Stack * s, istream & in, int n)
{
    for (int i = 0; i < n; i++)
    {
        int v;
        cout << "Enter value " << i + 1 << ": ";
        in >> v;
        s->push(v);
    }
}

void display(Stack * s, ostream & out)
{
    int i = 0, v;
    while (s->get(i, v))
    {
        out << v << " ";
        i++;
    }
    out << endl;
}

void copy(Stack * src, Stack * dst)
{
    int i = 0, v;
    while (src->get(i, v))
    {
        dst->push(v);
        i++;
    }
}

void insert(Stack * src, Stack * dst, int pos)
{
    int dstSize = 0;
    int temp[MAX_SIZE];
    while (dst->get(dstSize, temp[dstSize])) dstSize++;

    int dummy;
    while (!dst->isEmpty()) dst->pop(dummy);

    for (int i = 0; i < pos && i < dstSize; i++)
        dst->push(temp[i]);

    int i = 0, v;
    while (src->get(i, v))
    {
        dst->push(v);
        i++;
    }

    for (int i = pos; i < dstSize; i++)
        dst->push(temp[i]);
}

void shiftUp(Stack * s, int pos)
{
    int size = 0, v;
    while (s->get(size, v)) size++;

    s->push(0); // grow by one

    for (int j = size; j > pos; j--)
    {
        int val;
        s->get(j - 1, val);
        s->insert(j, val);
    }
    s->insert(pos, 0); // clear the gap
}

void shiftDown(Stack * s, int pos)
{
    int size = 0, v;
    while (s->get(size, v)) size++;

    for (int j = pos; j < size - 1; j++)
    {
        int val;
        s->get(j + 1, val);
        s->insert(j, val);
    }

    int dummy;
    s->pop(dummy); // shrink by one
}

void stats(Stack * s, int & max, float & average)
{
    int i = 0, v, count = 0;
    long sum = 0;
    max = 0;
    while (s->get(i, v))
    {
        if (v > max) max = v;
        sum += v;
        count++;
        i++;
    }
    average = count > 0 ? (float)sum / count : 0.0f;
}
