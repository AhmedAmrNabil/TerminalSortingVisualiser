#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

void merge(int* A, int start, int mid, int end) {
    int size = end - start + 1;
    int* arr = new int[size];
    int left = start;
    int right = mid + 1;
    int current = 0;

    while (left <= mid && right <= end) {
        if (A[left] < A[right]) {
            arr[current++] = A[left++];
        } else {
            arr[current++] = A[right++];
        }
    }

    while (left <= mid) {
        arr[current++] = A[left++];
    }
    while (right <= end) {
        arr[current++] = A[right++];
    }

    for (int i = 0; i < size; i++) {
        A[start + i] = arr[i];
    }

    delete[] arr;
}

void mergeSort(int* A, int start, int end) {
    if (start >= end) return;
    int mid = (start + end) / 2;
    mergeSort(A, start, mid);
    mergeSort(A, mid + 1, end);
    merge(A, start, mid, end);
}

int main() {
    const int n = 20;
    int a[n];
	for(int i = 0; i < n; i++)a[i] = i+1;
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(a,a+n,g);
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
    mergeSort(a, 0, n - 1);
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
    return 0;
}