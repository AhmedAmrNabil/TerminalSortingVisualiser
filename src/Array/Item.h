#ifndef ITEM_H
#define ITEM_H
#include <string>

#include "../colors.h"
class Item {
    int data;
    std::string color;

   public:
    Item(int data = 0, std::string color = reset) {
        this->color = color;
        this->data = data;
    }
    // Item(Item& item){
    //     this->color = item.color;
    //     this->data = item.data;
    // }

    // Item& operator=(Item& item){
    //     this->color = item.color;
    //     this->data = item.data;
    //     return *this;
    // }
    void setData(int data) {
        this->data = data;
    }
    void setColor(std::string color) {
        this->color = color;
    }
    int getData() { return data; }
    std::string getColor() { return this->color; }
    bool operator<(Item& item) {
        return this->data < item.data;
    }
    bool operator>(Item& item) {
        return this->data > item.data;
    }
    bool operator>=(int item) {
        return this->data >= item;
    }
    bool operator>(int item) {
        return this->data > item;
    }
};
#endif