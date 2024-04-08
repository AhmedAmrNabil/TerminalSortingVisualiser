#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#include <algorithm>
#include <random>
#include <string>

#include "../colors.h"
#include "Item.h"
using namespace std;

class PrettyArray {
    Item* arr;
    int size;
    int accessCount;
    int swapCount;
    std::string defaultColor;
    std::string highlightColor;

   public:
    PrettyArray(int size = 20) {
        defaultColor = overlay2;
        highlightColor = red;
        arr = new Item[size];
        this->size = size;
        for (int i = 0; i < size; i++) {
            arr[i].setData(i + 1);
            arr[i].setColor(overlay2);
        }
    }

    void printBars() {
        std::string bars = "\e[H";
        for (int i = size; i > 0; i -= 2) {
            for (int j = 0; j < size; ++j) {
                if (size % 2 == 0) {
                    if (arr[j] >= i)
                        bars += arr[j].getColor() + "▌";
                    else if (arr[j] >= i - 1)
                        bars += arr[j].getColor() + "▖";
                    else
                        bars += reset + " ";
                } else {
                    if (arr[j] > i)
                        bars += arr[j].getColor() + "▌";
                    else if (arr[j] > i - 1)
                        bars += arr[j].getColor() + "▖";
                    else
                        bars += reset + " ";
                }
            }
            bars += "\n";
        }
        std::cout << bars;
    }
    void printStats(){
        cout << "Array acessed: " << accessCount;
    }

    Item& operator[](int i) {
        return arr[i];
    }

    void markItem(int i){
        arr[i].setColor(highlightColor);
        this->printBars();
    }

    void unmarkItem(int i){
        arr[i].setColor(defaultColor);
        this->printBars();
    }

    void shuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(arr, arr + size,g);
    }

    
};

#endif
