#ifndef VISUALISER_H
#define VISUALISER_H
#include "../Array/Array.h"

enum SORTS {
    Quick,
    Bubble,
    Merge,
    AltMerge,
    Insertion,
    Selection,
    SIZE,
};


class Visualiser {
    typedef void (Visualiser::*function)();
    PrettyArray A;
    string currentSort;
    function funcArr[SORTS::SIZE];

   public:
    Visualiser(int size = 0) : A(size) {
        currentSort = "";
        funcArr[Quick] = &Visualiser::quickSort;
        funcArr[Bubble] = &Visualiser::bubbleSort;
        funcArr[Merge] = &Visualiser::mergeSort;
        funcArr[Insertion] = &Visualiser::insertionSort;
        funcArr[AltMerge] = &Visualiser::altMergeSort;
    }

    void print() {
        A.printBars();
        A.printStats(currentSort);
    }

    void sort(SORTS s) {
        cout << "\033[J\033[2J\033[3J";
        (this->*funcArr[s])();
        A.printBars();
        A.printStats(currentSort, true);
    }

    void bubbleSort();
    void quickSort(int start, int end);
    void quickSort();
    void merge(int start, int mid, int end);
    void alternateMerge(int start, int mid, int end);
    void mergeSort(int start, int end);
    void mergeSort();
    void altMergeSort(int start,int end);
    void altMergeSort();
    void insertionSort();
    // int binarySearch(int item, int low, int high);
};

#endif