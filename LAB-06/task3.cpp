#include <iostream>
using namespace std;
#include "AbstractStack.h"
#include "ArrayStack.h"


// copyStack: base case = src is empty
// case size=1: pop 1 element, push to copy
// case size=N: pop top, recurse on rest, push back (to maintain order, push after recursion)
void copyStack(ArrayStack<int> src, ArrayStack<int> &copy)
{
    if (src.isEmpty())
        return;
    int v = 0;
    src.pop(v);
    copyStack(src, copy);
    copy.push(v);
}

// display: base case = stack is empty
// case size=1: pop and print
// case size=N: pop top, print it, recurse
void display(ArrayStack<int> as)
{
    if (as.isEmpty())
        return;
    int v = 0;
    as.pop(v);
    cout << v << " ";
    display(as);
}

// getSize: base case = stack is empty, return 0
// case size=1: pop, return 1
// case size=N: pop, return 1 + getSize(rest)
int getSize(ArrayStack<int> as)
{
    if (as.isEmpty())
        return 0;
    int v = 0;
    as.pop(v);
    return 1 + getSize(as);
}

// max: base case = stack has 1 element, pop and return it
// case size=N: pop top, get max of rest, compare and return bigger
int max(ArrayStack<int> as)
{
    int v = 0;
    as.pop(v);
    if (as.isEmpty())
        return v;
    int restMax = max(as);
    return (v > restMax) ? v : restMax;
}

// Helper: count how many times 'target' appears in stack (recursive)
int countOccurrences(ArrayStack<int> as, int target)
{
    if (as.isEmpty())
        return 0;
    int v = 0;
    as.pop(v);
    int rest = countOccurrences(as, target);
    return (v == target) ? rest + 1 : rest;
}

// Helper: check if value already exists in result stack (recursive)
bool existsInStack(ArrayStack<int> as, int val)
{
    if (as.isEmpty())
        return false;
    int v = 0;
    as.pop(v);
    if (v == val)
        return true;
    return existsInStack(as, val);
}

// Helper: build frequency stack recursively
// For each unique element in src, push its count into result
void buildFrequency(ArrayStack<int> src, ArrayStack<int> original, ArrayStack<int> &seen, ArrayStack<int> &result)
{
    if (src.isEmpty())
        return;
    int v = 0;
    src.pop(v);
    if (!existsInStack(seen, v))
    {
        seen.push(v);
        int freq = countOccurrences(original, v);
        result.push(freq);
        result.push(v);
    }
    buildFrequency(src, original, seen, result);
}

// frequency: returns a stack where each value is followed by its count
// Format in stack (bottom to top): val1, count1, val2, count2, ...
ArrayStack<int> frequency(ArrayStack<int> adt)
{
    ArrayStack<int> result(10);
    ArrayStack<int> seen(10);
    ArrayStack<int> original(10);
    copyStack(adt, original);
    buildFrequency(adt, original, seen, result);
    return result;
}

int main()
{
    ArrayStack<int> s(10);
    s.push(1);
    s.push(3);
    s.push(2);
    s.push(3);
    s.push(1);
    s.push(3);

    cout << "Display: ";
    display(s);
    cout << endl;

    cout << "Size: " << getSize(s) << endl;
    cout << "Max: " << max(s) << endl;

    ArrayStack<int> copy(10);
    copyStack(s, copy);
    cout << "Copy display: ";
    display(copy);
    cout << endl;

    cout << "Frequency (value then count pairs, top to bottom):" << endl;
    ArrayStack<int> freq = frequency(s);
    display(freq);
    cout << endl;

    return 0;
}
