#ifndef ARRAY_H
#define ARRAY_H
#include <sys/ioctl.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <random>
#include <string>

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
    winsize w;

   public:
    PrettyArray(int size) {
        ioctl(0, TIOCGWINSZ, &w);
        // startingPos = 1;
        if (size == 0) {
            unsigned short rows = 4 * (w.ws_row - 8);
            this->size = min(w.ws_col, rows) / 2;
        } else {
            this->size = size;
        }
        startingPos = (w.ws_col - this->size * 2) / 2 + 1;
        highlightColor = white;
        writeCount = 0;
        accessCount = 0;
        arr = new Item[this->size];
        this->size = this->size;
        for (int i = 0; i < this->size; i++) {
            arr[i].setData(i + 1);
            arr[i].setSize(this->size);
            arr[i].unMark();
        }
        cout << "\033[?25l";
    }
    ~PrettyArray() {
        cout << "\033[?25h";
        delete[] arr;
    }

    void printBars() {
        int delay = 10;
        int start = 2;
        std::string bars = "";
        for (int i = size; i > 0; i -= 2) {
            bars += "\033[" + to_string(start++) + ";" + to_string(startingPos) + "H";
            for (int j = 0; j < size; ++j) {
                if (arr[j] >= i + size % 2) {
                    bars += arr[j].getColor();
                    // bars += "██";
                    bars += "█▌";
                } else if (arr[j] >= i - 1 + size % 2) {
                    bars += arr[j].getColor();
                    // bars += "▄▄";
                    bars += "▄▖";
                } else
                    bars += reset + "  ";
            }
        }
        bars += "\n";
        std::cout << bars;
        usleep(delay * 1000);
    }
    void printStats(string sort, bool done = false) {
        int start = w.ws_row - (4 + done);
        cout << "\033[" << start << ";1H";
        if (done) cout << "\033[0J";
        cout << reset;
        cout << "Sort: " << sort << endl;
        cout << "Array size: " << size << endl;
        cout << "Array acessed: " << accessCount << endl;
        cout << "Array writes: " << writeCount << endl;
    }

    Item& operator[](int i) {
        printBars();
        ++accessCount;
        return arr[i];
    }

    void markItem(int i, int j = -1) {
        if (j != -1) {
            arr[j].setSelected(true);
            arr[j].setColor(highlightColor);
        }
        arr[i].setColor(highlightColor);
        arr[i].setSelected(true);
        // this->printBars();
    }

    void unmarkItem(int i, int j = -1) {
        if (j != -1) {
            arr[j].setSelected(false);
            arr[j].unMark();
        }
        arr[i].setSelected(false);
        arr[i].unMark();
        // this->printBars();
    }

    void shuffle() {
        accessCount = 0;
        writeCount = 0;
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(arr, arr + size, g);
    }
    void swap(int i, int j) {
        Item a = arr[i];
        arr[i] = arr[j];
        arr[j] = a;
        writeCount += 2;
    }
    int getSize() { return this->size; }
};

#endif
