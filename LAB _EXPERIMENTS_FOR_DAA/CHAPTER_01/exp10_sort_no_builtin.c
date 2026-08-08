/*
 * Experiment 10 - Sort an Array in O(n log n) Without Built-in
 * Sort Functions, With Smallest Possible Space Complexity
 * -----------------------------------------------------------------
 * Heap Sort is used here: it achieves O(n log n) time with only
 * O(1) auxiliary space (in-place), which beats Merge Sort's O(n)
 * extra space requirement.
 */

#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Maintains the max-heap property for subtree rooted at index i
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements one by one from the heap
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
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
    int nums[] = {5, 2, 3, 1, 4, -7, 0};
    int n = sizeof(nums) / sizeof(nums[0]);

    printf("Before Sorting: ");
    printArray(nums, n);

    heapSort(nums, n);

    printf("After Sorting:  ");
    printArray(nums, n);

    return 0;
}
