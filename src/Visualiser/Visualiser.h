#ifndef VISUALISER_H
#define VISUALISER_H
#include "../Array/Array.h"

enum SORTS{
    Quick,
    Bubble,
    Merge,
    Insertion,
    Selection,
};

class Visualiser {
    PrettyArray A;
    string currentSort;

   public:
    Visualiser(int size = 0) : A(size) {
        currentSort = "";
    }

    void print() {
        A.printBars();
        A.printStats(currentSort);
    }

    void sort(SORTS s){
        cout << "\033[J\033[2J\033[3J";
        switch (s){
            case Quick:
                quickSort();
                break;
            case Bubble:
                bubbleSort();
                break;
            case Merge:
                mergeSort();
                break;
        }
        A.printStats(currentSort,true);
    }

    void bubbleSort();
    void quickSort(int start, int end);
    void quickSort();
    void merge(int start,int mid,int end);
    void alternateMerge(int start,int mid,int end);
    void mergeSort(int start,int end);
    void mergeSort();
};

#endif