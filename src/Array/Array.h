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

struct RGB {
    int r, g, b;
};

inline string& operator+=(string& s, RGB rgb) {
    s += "\033[38;2;" + to_string(rgb.r) + ";" + to_string(rgb.g) + ";" + to_string(rgb.b) + "m";
    return s;
}
inline float hue2rgb(float p, float q, float t) {
    if (t < 0)
        t += 1;
    if (t > 1)
        t -= 1;
    if (t < 1. / 6)
        return p + (q - p) * 6 * t;
    if (t < 1. / 2)
        return q;
    if (t < 2. / 3)
        return p + (q - p) * (2. / 3 - t) * 6;

    return p;
}
inline RGB hsl2rgb(float h, float s, float l) {
    RGB result;

    if (0 == s) {
        result.r = result.g = result.b = l;  // achromatic
    } else {
        float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;
        result.r = hue2rgb(p, q, h + 1. / 3) * 255;
        result.g = hue2rgb(p, q, h) * 255;
        result.b = hue2rgb(p, q, h - 1. / 3) * 255;
    }

    return result;
}

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
            unsigned short rows = 4 * (w.ws_row - 7);
            this->size = min(w.ws_col, rows) / 2;
        }else{
            this->size = size;
        }
        startingPos = (w.ws_col - this->size * 2) / 2 + 1;
        defaultColor = overlay0;
        highlightColor = text;
        writeCount = 0;
        accessCount = 0;
        arr = new Item[this->size];
        this->size = this->size;
        for (int i = 0; i < this->size; i++) {
            arr[i].setData(i + 1);
            arr[i].setColor(defaultColor);
        }
        cout << "\033[?25l";
    }
    ~PrettyArray() {
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
                if (arr[j] >= i + size % 2) {
                    if (arr[j].getColor() == highlightColor)
                        bars += "\033[38;2;255;255;255m";
                    else
                        bars += hsl2rgb(arr[j].getData() / double(size), 0.8, 0.6);
                    // bars += "█▌";
                    bars += "██";
                } else if (arr[j] >= i - 1 + size % 2) {
                    if (arr[j].getColor() == highlightColor)
                        bars += "\033[38;2;255;255;255m";
                    else
                        bars += hsl2rgb(arr[j].getData() / double(size), 0.8, 0.6);
                    // bars += "▄▖";
                    bars += "▄▄";
                } else
                    bars += reset + "  ";
            }
        }
        bars += "\n";
        std::cout << bars;
        usleep(delay * 1000);
    }
    void printStats(string sort,bool done = false) {
        int start = w.ws_row - (4 + done);
        cout << "\033[" << start << ";1H";
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
        if (j != -1) arr[j].setColor(highlightColor);
        arr[i].setColor(highlightColor);
        // this->printBars();
    }

    void unmarkItem(int i, int j = -1) {
        if (j != -1) arr[j].setColor(defaultColor);
        arr[i].setColor(defaultColor);
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
