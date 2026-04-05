#include "Node.h"
#include <iostream>
using namespace std;

Node* copy(Node* head){
   if (head == nullptr) return nullptr;

   Node* newHead = new Node(head->data);
   Node* copyCurrent = newHead;
   Node* original = head->next;

   while(original != nullptr){
       copyCurrent->next = new Node(original->data);
       copyCurrent = copyCurrent->next;
       original = original->next;
   }
   return newHead;
}

void freeMemory(Node* head){
    while(head != nullptr){
        Node* temp = head->next;
        delete head;
        head = temp;
    }
}

void insert(Node*& head, const int value , const int pos){
   Node* newNode = new Node(value); 
   if(pos == 0){
       newNode->next = head;
       head = newNode;
       return;
   }

   Node* temp = head;
   Node* prev = head;
   int counter = 0;

   while(temp != nullptr && counter < pos){
       prev = temp;
       temp = temp->next;
       counter++;
   }
   prev->next = newNode;
   newNode->next = temp;
}

int remove(Node*& head , const int &pos){
    Node* temp = head;

    if(pos == 0){
        int val = head->data;
        head = head->next;
        delete temp;
        return val;
    }

    Node* prev = head;
    int counter = 0;
    while(temp != nullptr && counter < pos){
       prev = temp;
       temp = temp->next;
       counter++;
    }
    
    if (temp == nullptr) return -1;

    prev->next = temp->next;
    int val = temp->data;
    delete temp;
    return val;
}

void display(Node* head) {
    if (head == nullptr) {
        cout << "List is empty" << endl;
        return;
    }

    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next != nullptr) cout << " -> ";
        temp = temp->next;
    }
    cout << endl;
}

int main (){
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);

    cout << "Original List: ";
    display(head);

    Node* copiedList = copy(head);
    cout << "Copied List: ";
    display(copiedList);

    insert(head, 0, 0); // Insert at the beginning
    insert(head, 4, 3); // Insert at the end
    insert(head, 5, 2); // Insert in the middle

    cout << "List after insertions: ";
    display(head);

    cout << "Removed value at position 0: " << remove(head, 0) << endl; // Remove from the beginning
    cout << "Removed value at position 2: " << remove(head, 2) << endl; // Remove from the middle
    cout << "Removed value at position 3: " << remove(head, 3) << endl; // Remove from the end

    cout << "List after removals: ";
    display(head);

    freeMemory(head);
    freeMemory(copiedList);
    
    return 0;
}
