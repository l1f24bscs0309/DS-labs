#include <iostream>
using namespace std;
#include "AbstractArray.h"
#include "MyArray.h"

#define MAX_SIZE 10

void read(AbstractArray * aa, istream & in, int n)
{
    for (int i = 0; i < n; i++)
    {
        int v;
        cout << "Enter value " << i + 1 << ": ";
        in >> v;
        aa->add(v);
    }
}

void display(AbstractArray * aa, ostream & out)
{
    int i = 0;
    int v;
    while (aa->get(i, v))
    {
        out << v << " ";
        i++;
    }
    out << endl;
}

void copy(AbstractArray * src, AbstractArray * dst)
{
    int i = 0;
    int v;
    while (src->get(i, v))
    {
        dst->add(v);
        i++;
    }
}

void insert(AbstractArray * src, AbstractArray * dst, int pos)
{
    int i = 0;
    int v;
    while (src->get(i, v))
    {
        dst->insert(pos + i, v);
        i++;
    }
}

void shiftLeft(AbstractArray * aa, int pos){
    int i = pos;
    int next;
    while (aa->get(i + 1, next))
    {
        aa->insert(i, next);
        i++;
    }
}

void shiftRight(AbstractArray * aa, int pos){
    int i = 0;
    int size = 0;
    int v;
    while (aa->get(i, v)) { size++; i++; }

    for (int j = size - 1; j > pos; j--)
    {
        int val;
        aa->get(j - 1, val);
        aa->insert(j, val);
    }
}

void stats(AbstractArray * aa, int & max, float & average)
{
    int i = 0, v, count = 0;
    long sum = 0;
    max = 0;
    while (aa->get(i, v))
    {
        if (v > max) max = v;
        sum += v;
        count++;
        i++;
    }
    average = (float)sum / count;
}

int main()
{
    AbstractArray * A = new MyArray(MAX_SIZE);

    int n = 0;
    cout << "please select a number between 1 and " << MAX_SIZE << ": ";
    cin >> n;

    read(A, cin, n);

    cout << "Array A Values: ";
    display(A, cout);

    AbstractArray * B = new MyArray(MAX_SIZE);

    copy(A, B);

    cout << "Array B Values: ";
    display(B, cout);

    AbstractArray * C = new MyArray(MAX_SIZE);

    C->add(9);
    C->add(7);
    C->add(5);

    insert(A, C, 2);

    cout << "Array C Values: ";
    display(C, cout);

    shiftLeft(C, 2);
    cout << "Array C Values: ";
    
    display(C, cout);

    shiftRight(C, 2);
    cout << "Array C Values: ";

    display(C, cout);

    int mx = 0;
    float ag = 0.0;
    stats(C, mx, ag);
    cout << "Array C Values: ";
    display(C, cout);
    cout << "Average is " << ag << " maximum is " << mx << endl;
    return 0;
}
