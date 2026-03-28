#include "Order.h"    // ← must come before Queue and MyQueue
#include "Queue.h"
#include "MyQueue.h"
#include "MyStack.h"
#include <iostream>
using namespace std;

void read(Queue<Order> *q, istream &in);
void stimulate(Queue<Order> *q, ostream &out);

int main() {
    const int MAX_ORDERS = 5;
    MyQueue<Order> orderQueue(MAX_ORDERS);

    // hardcode the menu orders from the table
    orderQueue.enqueue(Order("Burger", 200, 20));
    orderQueue.enqueue(Order("Sandwich", 250, 30));
    orderQueue.enqueue(Order("French Fries", 100, 10));
    orderQueue.enqueue(Order("Fried Chickens", 400, 40));
    orderQueue.enqueue(Order("Pizza", 350, 40));

    cout << "Orders placed in sequence:\n";
    orderQueue.display(cout);

    cout << "\nProcessing orders...\n\n";
    stimulate(&orderQueue, cout);

    return 0;
}
void read(Queue<Order> *q, istream &in) {
    cout << "What item would you like to order? ";
    string item;
    cin >> item;
    cout << "How much does it cost? ";
    int price;
    cin >> price;
    cout << "How long will it take to prepare? ";
    int time_taken;
    cin >> time_taken;

    if (q->isFull()) {
        cout << "Queue is full, cannot add more orders.\n";
        return;
    }
    Order new_order(item, price, time_taken);
    q->enqueue(new_order);
}

void stimulate(Queue<Order> *q, ostream &out) {
    if (q->isEmpty()) {
        out << "No orders to process.\n";
        return;
    }

    int total_income = 0;
    int orderNum = 1;

    out << "Processing orders in sequence...\n\n";
    out << "No.\tItem\t\tPrice\tTime Taken\tStatus\n";
    out << "---\t----\t\t-----\t----------\t------\n";

    while (!q->isEmpty()) {
        Order current_order = q->dequeue();   // dequeue = served in order
        out << orderNum++ << ".\t"
            << current_order.item << "\t\t"
            << current_order.price << "\t"
            << current_order.time_taken << " mins\t\t"
            << "Served ✓\n";
        total_income += current_order.price;
    }

    out << "\nAll orders processed in order.\n";
    out << "Total Income: " << total_income << " PKR\n";
}
