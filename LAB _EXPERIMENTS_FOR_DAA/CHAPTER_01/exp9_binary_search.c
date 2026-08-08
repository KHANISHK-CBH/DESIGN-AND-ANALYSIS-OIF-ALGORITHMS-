/*
 * Experiment 9 - Binary Search on a Sorted Array
 * -------------------------------------------------
 * NOTE: Binary search requires a SORTED array. The given test-case
 * array is first sorted, then searched for the key. The position
 * printed corresponds to the index within the sorted array.
 */

#include <stdio.h>

int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

void bubbleSort(int arr[], int n) { // small helper to ensure sorted input
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
}

void runTest(int key) {
    int arr[] = {3, 4, 6, -9, 10, 8, 9, 30};
    int n = 8;
    bubbleSort(arr, n);

    int pos = binarySearch(arr, n, key);
    if (pos != -1)
        printf("Element %d is found at position %d\n", key, pos);
    else
        printf("Element %d is not found\n", key);
}

int main() {
    runTest(10);
    runTest(100);
    return 0;
}
