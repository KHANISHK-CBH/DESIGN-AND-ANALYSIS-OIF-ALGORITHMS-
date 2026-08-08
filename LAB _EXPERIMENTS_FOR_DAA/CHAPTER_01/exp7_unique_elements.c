/*
 * Experiment 7 - Extract Unique Elements from a List
 * ----------------------------------------------------
 * Builds a new list containing only the first occurrence of each
 * element (preserving input order) using a simple "seen so far"
 * linear search. Space complexity is analyzed in the report.
 */

#include <stdio.h>

int isSeen(int result[], int size, int val) {
    for (int i = 0; i < size; i++)
        if (result[i] == val)
            return 1;
    return 0;
}

int getUnique(int arr[], int n, int result[]) {
    int size = 0;
    for (int i = 0; i < n; i++) {
        if (!isSeen(result, size, arr[i])) {
            result[size++] = arr[i];
        }
    }
    return size;
}

void printArray(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i != n - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    int arr1[] = {3, 7, 3, 5, 2, 5, 9, 2};
    int result1[8];
    int size1 = getUnique(arr1, 8, result1);
    printf("Test 1 Output: ");
    printArray(result1, size1);

    int arr2[] = {-1, 2, -1, 3, 2, -2};
    int result2[6];
    int size2 = getUnique(arr2, 6, result2);
    printf("Test 2 Output: ");
    printArray(result2, size2);

    int arr3[] = {1000000, 999999, 1000000};
    int result3[3];
    int size3 = getUnique(arr3, 3, result3);
    printf("Test 3 Output: ");
    printArray(result3, size3);

    return 0;
}
