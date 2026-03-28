#include <string>
#include <iostream>
using namespace std;

class Order {

    public:
        Order() : item(""), price(0), time_taken(0), currentTime(0) {}
        Order(string item, int price, int time_taken) : item(item), price(price), time_taken(time_taken) {}
        friend ostream& operator<<(ostream& out, const Order& o) {
            out << o.item << " (Price: " << o.price << ", Time: " << o.time_taken << " mins)";
            return out;
        }
        string item;
        int price;
        int time_taken;
        int currentTime;
};
