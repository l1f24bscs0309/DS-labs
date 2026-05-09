
#include <iostream>
using namespace std;
#include "Queue.h"
#include "ArrayQueue.h"

// copyQueue: base case = src is empty
// case size=1: dequeue, enqueue to copy
// case size=N: dequeue front, enqueue to copy, recurse on rest
void copyQueue(ArrayQueue<int> src, ArrayQueue<int> &copy)
{
    if (src.isEmpty())
        return;
    int v = src.dequeue();
    copy.enqueue(v);
    copyQueue(src, copy);
}

// display: base case = queue is empty
// case size=1: dequeue and print
// case size=N: dequeue front, print, recurse
void display(ArrayQueue<int> as)
{
    if (as.isEmpty())
        return;
    int v = as.dequeue();
    cout << v << " ";
    display(as);
}

// getSize: base case = empty, return 0
// case size=1: dequeue, return 1
// case size=N: dequeue, return 1 + getSize(rest)
int getSize(ArrayQueue<int> as)
{
    if (as.isEmpty())
        return 0;
    as.dequeue();
    return 1 + getSize(as);
}

// max: base case = 1 element, dequeue and return
// case size=N: dequeue front, get max of rest, return bigger
int max(ArrayQueue<int> as)
{
    int v = as.dequeue();
    if (as.isEmpty())
        return v;
    int restMax = max(as);
    return (v > restMax) ? v : restMax;
}

// Helper: count occurrences of target in queue (recursive)
int countOccurrences(ArrayQueue<int> as, int target)
{
    if (as.isEmpty())
        return 0;
    int v = as.dequeue();
    int rest = countOccurrences(as, target);
    return (v == target) ? rest + 1 : rest;
}

// Helper: check if value exists in queue (recursive)
bool existsInQueue(ArrayQueue<int> as, int val)
{
    if (as.isEmpty())
        return false;
    int v = as.dequeue();
    if (v == val)
        return true;
    return existsInQueue(as, val);
}

// Helper: build frequency queue recursively
// For each unique element, enqueue: value then its count
void buildFrequency(ArrayQueue<int> src, ArrayQueue<int> original, ArrayQueue<int> &seen, ArrayQueue<int> &result)
{
    if (src.isEmpty())
        return;
    int v = src.dequeue();
    if (!existsInQueue(seen, v))
    {
        seen.enqueue(v);
        int freq = countOccurrences(original, v);
        result.enqueue(v);
        result.enqueue(freq);
    }
    buildFrequency(src, original, seen, result);
}

// frequency: returns a queue where pairs of (value, count) are stored
ArrayQueue<int> frequency(ArrayQueue<int> adt)
{
    ArrayQueue<int> result(10);
    ArrayQueue<int> seen(10);
    ArrayQueue<int> original(10);
    copyQueue(adt, original);
    buildFrequency(adt, original, seen, result);
    return result;
}

int main()
{
    ArrayQueue<int> q(10);
    q.enqueue(1);
    q.enqueue(3);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(1);
    q.enqueue(3);

    cout << "Display: ";
    display(q);
    cout << endl;

    cout << "Size: " << getSize(q) << endl;
    cout << "Max: " << max(q) << endl;

    ArrayQueue<int> copy(10);
    copyQueue(q, copy);
    cout << "Copy display: ";
    display(copy);
    cout << endl;

    cout << "Frequency (value then count pairs): " << endl;
    ArrayQueue<int> freq = frequency(q);
    display(freq);
    cout << endl;

    return 0;
}
