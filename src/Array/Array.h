#ifndef ARRAY_H
#define ARRAY_H
#include <sys/ioctl.h>

#include <algorithm>
#include <iostream>
#include <random>
#include <string>

#include "../colors.h"
#include "Item.h"

// int main (void)
// {
//     struct winsize w;
//     ioctl(0, TIOCGWINSZ, &w);

//     printf ("lines %d\n", w.ws_row);
//     printf ("columns %d\n", w.ws_col);
//     return 0;
// }
using namespace std;

class PrettyArray {
    Item* arr;
    int size;
    int accessCount;
    int swapCount;
    std::string defaultColor;
    std::string highlightColor;

   public:
    PrettyArray(int size) {
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
        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);
        int startingPos = (w.ws_col - size) / 2;
        int start = 1;
        std::string bars = "";
        for (int i = size; i > 0; i -= 2) {
            bars += "\e[" + to_string(start++) + ";" + to_string(startingPos) + "H";
            for (int j = 0; j < size; ++j) {
                if (arr[j] >= i + size % 2)
                    bars += arr[j].getColor() + "▌";
                else if (arr[j] >= i - 1 + size % 2)
                    bars += arr[j].getColor() + "▖";
                else
                    bars += reset + " ";
            }
        }
        std::cout << bars;
    }
    void printStats() {
        cout << "Array acessed: " << accessCount;
    }

    Item& operator[](int i) {
        return arr[i];
    }

    void markItem(int i) {
        arr[i].setColor(highlightColor);
        this->printBars();
    }

    void unmarkItem(int i) {
        arr[i].setColor(defaultColor);
        this->printBars();
    }

    void shuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(arr, arr + size, g);
    }
};

#endif
