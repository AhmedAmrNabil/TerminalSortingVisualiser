#ifndef VISUALISER_H
#define VISUALISER_H
#include "../Array/Array.h"

class Visualiser {
    PrettyArray A;
    string currentSort;

   public:
    Visualiser(int size = 30) : A(size) {
        currentSort = "";
    }

    void print() {
        A.printBars();
        cout << "\033[0m";
        cout << "\nSort: " << currentSort << endl;
        A.printStats();
    }

    void bubbleSort();

};

#endif