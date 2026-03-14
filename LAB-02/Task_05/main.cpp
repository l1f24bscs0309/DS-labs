#include <iostream>
using namespace std;


template <typename T, size_t N>
int binarySearch(T (&arr)[N] , T key){
    int low = 0 , high = N-1 ;
    while(low <= high){
        int mid = (low+high) / 2;
        if(arr[mid] == key){
            return mid;
        }else if (arr[mid] < key){
            low = mid + 1;
        }else {
            high = mid - 1;
        }
    }
    return -1;
}

template <typename T>
void printSearchResult(int index, T key) {
    if (index != -1)
        cout << "Found " << key << " at index " << index << endl;
    else
        cout << key << " not found" << endl;
}

int main () {
    // Test with an integer array (sorted) of size 5
    int intArray[5] = {11, 12, 22, 25, 64};
    int intKey = 22;
    int intIndex = binarySearch(intArray, intKey);
    printSearchResult(intIndex, intKey);

    // Test with a float array (sorted) of size 4
    float floatArray[4] = {0.57, 1.62, 2.71, 3.14};
    float floatKey = 2.71;
    int floatIndex = binarySearch(floatArray, floatKey);
    printSearchResult(floatIndex, floatKey);

    // Test with a string array (sorted) of size 4
    string stringArray[4] = {"apple", "banana", "grape", "orange"};
    string stringKey = "grape";
    int stringIndex = binarySearch(stringArray, stringKey);
    printSearchResult(stringIndex, stringKey);

    return 0;
}
