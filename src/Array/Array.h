#ifndef ARRAY_H
#define ARRAY_H
#include <sys/ioctl.h>

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <unistd.h>

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
    int writeCount;
    std::string defaultColor;
    std::string highlightColor;
    int startingPos;
   public:
    PrettyArray(int size) {
        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);
        startingPos = (w.ws_col - size*2) / 2 + 1;
        defaultColor = overlay0;
        highlightColor = red;
        writeCount = 0;
        accessCount = 0;
        arr = new Item[size];
        this->size = size;
        for (int i = 0; i < size; i++) {
            arr[i].setData(i + 1);
            arr[i].setColor(defaultColor);
        }
        cout << "\033[?25l";
    }
    ~PrettyArray(){
        cout << "\033[?25h";
        delete[] arr;
    }

    void printBars() {
        int delay = 20;
        int start = 2;
        std::string bars = "";
        for (int i = size; i > 0; i -= 2) {
            bars += "\033[" + to_string(start++) + ";" + to_string(startingPos) + "H";
            for (int j = 0; j < size; ++j) {
                if (arr[j] >= i + size % 2)
                    // bars += arr[j].getColor() + "▌";
                    bars += arr[j].getColor() + "█▌";
                else if (arr[j] >= i - 1 + size % 2)
                    // bars += arr[j].getColor() + "▖";
                    bars += arr[j].getColor() + "▄▖";
                else
                    bars += reset + "  ";
            }
        }
        bars += "\n";
        std::cout << bars;
        usleep(delay*1000);
        // cout << "\n" << flush;
    }
    void printStats() {
        cout << "Array acessed: " << accessCount << endl;
        cout << "Array writes: " << writeCount << endl;
    }

    Item& operator[](int i) {
        ++accessCount;
        return arr[i];
    }

    void markItem(int i,int j = -1) {
        if(j != -1)arr[j].setColor(highlightColor);
        arr[i].setColor(highlightColor);
        // this->printBars();
    }

    void unmarkItem(int i,int j = -1) {
        if(j != -1)arr[j].setColor(defaultColor);
        arr[i].setColor(defaultColor);
        // this->printBars();
    }

    void shuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(arr, arr + size, g);
    }
    void swap(int i, int j) {
        Item a = arr[i];
        arr[i] = arr[j];
        arr[j] = a;
        writeCount+=2;
    }
    int getSize() { return this->size; }
};

#endif
