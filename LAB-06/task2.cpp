
#include <iostream>
using namespace std;

// ---- BASE CASE ANALYSIS (before each function) ----

// func: base case = n <= 0 (nothing to print)
// case n=1: print 1, stop
// case n=N: print N, call func(N-1)
void func(int n)
{
    if (n <= 0)
        return;
    cout << n << endl;
    func(n - 1);
}

// sum: base case = n <= 0, return 0
// case n=1: return 1
// case n=N: return N + sum(N-1)
int sum(int n = 10)
{
    if (n <= 0)
        return 0;
    return n + sum(n - 1);
}

// max: base case = size == 1, return a[0]
// case size=1: return a[0]
// case size=N: compare a[N-1] with max(a, N-1), return bigger one
int max(int a[], int size)
{
    if (size == 1)
        return a[0];
    int prevMax = max(a, size - 1);
    if (a[size - 1] > prevMax)
        return a[size - 1];
    return prevMax;
}

// countDigits: base case = n == 0, return 0
// case n=single digit: return 1
// case n=N digits: return 1 + countDigits(n/10)
int countDigits(int n)
{
    if (n == 0)
        return 0;
    return 1 + countDigits(n / 10);
}

// displayDigits: base case = n == 0, stop
// case n=single digit: print n%10
// case n=N: go deeper first (so digits print in same order as iterative = last digit first)
void displayDigits(int n)
{
    if (n == 0)
        return;
    cout << n % 10 << " ";
    displayDigits(n / 10);
}

// binarySearch: base case = low > high, return -1 (not found)
// case: a[mid]==v, return mid
// case: v > a[mid], search right half
// case: v < a[mid], search left half
int binarySearch(int a[], int low, int high, int v)
{
    if (low > high)
        return -1;
    int mid = (low + high) / 2;
    if (a[mid] == v)
        return mid;
    if (v > a[mid])
        return binarySearch(a, mid + 1, high, v);
    return binarySearch(a, low, mid - 1, v);
}

int main()
{
    cout << "=== func(5) ===" << endl;
    func(5);

    cout << "\n=== sum(10) ===" << endl;
    cout << "Sum = " << sum(10) << endl;

    cout << "\n=== max ===" << endl;
    int arr[] = {3, 1, 7, 2, 9, 4};
    int size = 6;
    cout << "Max = " << max(arr, size) << endl;

    cout << "\n=== countDigits(12345) ===" << endl;
    cout << "Digits = " << countDigits(12345) << endl;

    cout << "\n=== displayDigits(12345) ===" << endl;
    displayDigits(12345);
    cout << endl;

    cout << "\n=== binarySearch ===" << endl;
    int sorted[] = {1, 3, 5, 7, 9, 11, 13};
    int idx = binarySearch(sorted, 0, 6, 7);
    cout << "Index of 7 = " << idx << endl;
    idx = binarySearch(sorted, 0, 6, 6);
    cout << "Index of 6 = " << idx << endl;

    return 0;
}
