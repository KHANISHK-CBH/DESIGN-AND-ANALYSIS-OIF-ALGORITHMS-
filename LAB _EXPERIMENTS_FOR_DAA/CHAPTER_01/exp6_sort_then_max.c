/*
 * Experiment 6 - Sort a List Then Find the Maximum Element
 * ---------------------------------------------------------------
 * Sorts the array using an efficient O(n log n) algorithm (Merge
 * Sort) and then reports the last element (maximum) of the sorted
 * array. Handles the empty-list edge case explicitly.
 */

#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Returns 1 and sets *maxVal if list is non-empty, else returns 0
int sortAndFindMax(int arr[], int n, int *maxVal) {
    if (n == 0)
        return 0; // empty list

    mergeSort(arr, 0, n - 1);
    *maxVal = arr[n - 1];
    return 1;
}

void testCase(int arr[], int n) {
    int maxVal;
    if (sortAndFindMax(arr, n, &maxVal))
        printf("Output: %d\n", maxVal);
    else
        printf("Output: List is empty. No maximum exists.\n");
}

int main() {
    int *arr1 = NULL; // represents an empty list, size 0
    printf("Test 1 (Empty List): ");
    testCase(arr1, 0);

    int arr2[] = {5};
    printf("Test 2 (Single Element): ");
    testCase(arr2, 1);

    int arr3[] = {3, 3, 3, 3, 3};
    printf("Test 3 (All Same): ");
    testCase(arr3, 5);

    return 0;
}
