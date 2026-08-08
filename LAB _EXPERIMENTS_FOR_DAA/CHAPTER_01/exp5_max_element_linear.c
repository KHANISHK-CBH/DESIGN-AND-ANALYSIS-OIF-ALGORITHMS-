/*
 * Experiment 5 - Find Maximum Element (Least Time Complexity)
 * ----------------------------------------------------------------
 * A single linear scan (O(n)) is the least possible time complexity
 * for finding the maximum of an unsorted array, since every element
 * must be inspected at least once.
 */

#include <stdio.h>

int findMax(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }
    return maxVal;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    printf("Test 1 Output: %d\n", findMax(arr1, 5));

    int arr2[] = {7, 7, 7, 7, 7};
    printf("Test 2 Output: %d\n", findMax(arr2, 5));

    int arr3[] = {-10, 2, 3, -4, 5};
    printf("Test 3 Output: %d\n", findMax(arr3, 5));

    return 0;
}
