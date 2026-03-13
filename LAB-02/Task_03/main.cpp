#include <iostream>
#include "Stack.h"
#include "MyStack.h"

using namespace std;

void read(Stack* st , istream& in){
    cout << "Enter 10 number of enteries: ";
    int v;
    for (int i = 0 ; i < MAX_SIZE ; i++){
        in >> v; 
        st->push(v);
    }
}

bool is_Prime(int n){
    if(n <= 1){
        return false;
    }
    for (int i = 2 ; i <= n/2 ; i++){
        if (n % i == 0)
            return false;
    }
    return true;
}

bool is_PerfectSquare(int n)
{
    if (n < 0)
        return false;

    for (int i = 0; i * i <= n; i++)
    {
        if (i * i == n)
            return true;
    }

    return false;
}

bool is_Palindrome(int n)
{
    int original = n;
    int reversed = 0;

    while (n > 0)
    {
        reversed = reversed * 10 + (n % 10);
        n /= 10;
    }

    return (original == reversed);
}

void check_Prime(MyStack *s){
    MyStack temp(*s);
    while(!temp.isEmpty()){
        int val;
        temp.pop(val);
        if (is_Prime(val)){
            cout << val << " is prime" << endl;
        }else{
            cout << val << " is not prime" << endl;
        }
    }
} 

void check_isPerfectSquare(MyStack *s){
    MyStack temp(*s);
    while(!temp.isEmpty()){
        int val;
        temp.pop(val);
        if (is_PerfectSquare(val)){
            cout << val << " is perfect square" << endl;
        }else{
            cout << val << " is not perfect square "  << endl;
        }
    }
}

void check_isPalindrome(MyStack *s){
    MyStack temp(*s);
    while(!temp.isEmpty()){
        int val;
        temp.pop(val);
        if (is_Palindrome(val)){
            cout << val << " is palindrome" << endl;
        }else{
            cout << val << " is not palindrome" << endl;
        }
    }
}

bool isStackPalindrome(MyStack *s){
    MyStack rev(MAX_SIZE);
    MyStack temp(*s);
    int val;
    while(!temp.isEmpty()){
        temp.pop(val);
        rev.push(val);
    }

    int x , y;
    while (!rev.isEmpty()){
        temp.pop(x);
        rev.pop(y);

        if (x != y){
            return false;
        }
    }
    return true;
}

int main () {
    MyStack s(MAX_SIZE);
    read(&s , cin); 

    cout << "\n checking prime : " << endl;
    check_Prime(&s);

    cout << "\n checking perfect squares: " << endl;
    check_isPerfectSquare(&s);


    cout << "\n checking palindrome: " << endl;
    check_isPalindrome(&s);
    
    cout << "\nStack Palindrome Check:\n";
    if(isStackPalindrome(&s))
        cout << "Stack values form a Palindrome\n";
    else
        cout << "Stack values do NOT form a Palindrome\n";

    return 0;
}
