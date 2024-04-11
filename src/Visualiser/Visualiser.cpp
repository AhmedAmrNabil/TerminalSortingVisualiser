#include "Visualiser.h"

void Visualiser::bubbleSort() {
    currentSort = "Bubble";
    A.shuffle();
    bool swapped = false;
    int size = A.getSize();
    for (int i = 0; i < size; i++) {
        A.markItem(0);
        swapped = false;
        for (int j = 0; j < size - 1 - i; j++) {
            A.markItem(j + 1);
            if (A[j] > A[j + 1]) {
                A.swap(j, j + 1);
                swapped = true;
            }
            print();
            A.unmarkItem(j);
        }
        A.unmarkItem(size - 1 - i);
        if (!swapped) break;
    }
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
}

void Visualiser::merge(int start, int mid, int end) {
    int firstSize = mid - start + 1;
    int secondSize = end - mid;
    Item* tmp1 = new Item[firstSize];
    Item* tmp2 = new Item[secondSize];

    for (int i = 0; i < firstSize; ++i)
        tmp1[i] = A[start + i];
    for (int i = 0; i < secondSize; ++i)
        tmp2[i] = A[mid + 1 + i];

    int left = 0;
    int right = 0;
    int current = start;

    while (left < firstSize && right < secondSize) {
        A.markItem(start + left, mid + 1 + right);
        print();
        if (tmp1[left] < tmp2[right]) {
            A[current++] = tmp1[left++];
            A.unmarkItem(start + left - 1);
        } else {
            A[current++] = tmp2[right++];
            A.unmarkItem(mid + right);
        }
    }
    while (left < firstSize) {
        A.markItem(start + left);
        A[current++] = tmp1[left++];
        print();
        A.unmarkItem(start + left - 1);
    }
    while (right < secondSize) {
        A.markItem(mid + 1 + right);
        A[current++] = tmp2[right++];
        print();
        A.unmarkItem(mid + right);
    }
    delete[] tmp1;
    delete[] tmp2;
}

void Visualiser::alternateMerge(int start, int mid, int end) {
    int size = end - start + 1;
    Item* arr = new Item[size];
    int left = start;
    int right = mid + 1;
    int current = 0;

    while (left <= mid && right <= end) {
        A.markItem(left, right);
        print();
        if (A[left] < A[right]) {
            A.unmarkItem(left);
            arr[current++] = A[left++];
        } else {
            A.unmarkItem(right);
            arr[current++] = A[right++];
        }
    }

    while (left <= mid) {
        A.markItem(left);
        print();
        A.unmarkItem(left);
        arr[current++] = A[left++];
    }
    while (right <= end) {
        A.markItem(right);
        print();
        A.unmarkItem(right);
        arr[current++] = A[right++];
    }

    for (int i = 0; i < size; i++) {
        A[start + i] = arr[i];
        A.markItem(start + i);
        print();
        A.unmarkItem(start + i);
    }

    delete[] arr;
}

void Visualiser::mergeSort(int start, int end) {
    if (start >= end) return;
    int mid = (start + end) / 2;
    mergeSort(start, mid);
    mergeSort(mid + 1, end);
    merge(start, mid, end);
}

void Visualiser::mergeSort() {
    currentSort = "MergeSort";
    A.shuffle();
    mergeSort(0, A.getSize() - 1);
}

void Visualiser::altMergeSort(int start, int end) {
    if (start >= end) return;
    int mid = (start + end) / 2;
    altMergeSort(start, mid);
    altMergeSort(mid + 1, end);
    alternateMerge(start, mid, end);
}

void Visualiser::altMergeSort() {
    currentSort = "Alt MergeSort";
    A.shuffle();
    altMergeSort(0, A.getSize() - 1);
}

// int Visualiser::binarySearch(int item,
//                              int low, int high) {
//     if (high <= low)
//         return (item > A[low].getData()) ? (low + 1) : low;

//     int mid = (low + high) / 2;
//     if (A[mid].getData() == item) return mid + 1;
//     if (A[mid].getData() < item) return binarySearch(item, mid + 1, high);
//     return binarySearch(item, low, mid - 1);
// }

void Visualiser::insertionSort() {
    A.shuffle();
    currentSort = "InsertionSort";
    int j;
    Item key;
    for (int i = 1; i < A.getSize(); i++) {
        key = A[i];
        j = i - 1;

        while (key < A[j] && j >= 0) {
            A.markItem(j, j + 1);
            print();
            A.unmarkItem(j, j + 1);
            A[j + 1] = A[j];
            --j;
        }
        A[j + 1] = key;
    }
}

void Visualiser::heapify(int i, int n) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    A.markItem(largest);

    if (left < n && A[largest] < A[left]) {
        A.markItem(left);
        print();
        A.unmarkItem(largest);
        largest = left;
    }

    if (right < n && A[largest] < A[right]) {
        A.markItem(right);
        print();
        A.unmarkItem(largest);
        largest = right;
    }

    if (largest != i) {
        A.markItem(i);
        print();
        A.swap(largest, i);
        print();
        A.unmarkItem(largest, i);
        heapify(largest, n - 1);
    } else
        A.unmarkItem(largest);

}

void Visualiser::heapSort() {
    A.shuffle();
    currentSort = "Heap Sort";

    //building max heap
    for (int i = A.getSize() / 2 - 1; i >= 0; --i) {
        heapify(i, A.getSize());
    }

    for (int i = A.getSize() - 1; i >= 0; --i) {
        A.markItem(0, i);
        print();
        A.swap(0, i);
        print();
        A.unmarkItem(0, i);
        heapify(0, i);
    }
}
