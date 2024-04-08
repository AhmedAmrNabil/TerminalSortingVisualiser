#include "Visualiser.h"

void Visualiser::bubbleSort() {
    A.shuffle();
    currentSort = "Bubble";
    int size = A.getSize();
    for (int i = 0; i < size; i++) {
        A.markItem(0);
        for (int j = 0; j < size - 1 - i; j++) {
            A.markItem(j + 1);
            if (A[j] > A[j + 1]) {
                A.swap(j, j + 1);
            }
            print();
            A.unmarkItem(j);
        }
        A.unmarkItem(size - 1 - i);
    }
    print();
}

void Visualiser::quickSort() {
    currentSort = "QuickSort";
    A.shuffle();
    quickSort(0, A.getSize() - 1);
}

void Visualiser::quickSort(int start, int end) {
    if (start >= end) return;
    Item pivot = A[end];
    int pivotIndex = start;
    A.markItem(end);
    for (int i = start; i < end; i++) {
        A.markItem(i);
        if (A[i] < pivot) {
            A.markItem(pivotIndex);
            print();
            A.swap(i, pivotIndex);
            print();
            A.unmarkItem(pivotIndex);
            pivotIndex++;
        }
        print();
        A.unmarkItem(i);
    }
    A.swap(end, pivotIndex);
    A.unmarkItem(end);
    A.markItem(pivotIndex);
    print();
    A.unmarkItem(pivotIndex);
    quickSort(start, pivotIndex - 1);
    quickSort(pivotIndex + 1, end);
    print();
}