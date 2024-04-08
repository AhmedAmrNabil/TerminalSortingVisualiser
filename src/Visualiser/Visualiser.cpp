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