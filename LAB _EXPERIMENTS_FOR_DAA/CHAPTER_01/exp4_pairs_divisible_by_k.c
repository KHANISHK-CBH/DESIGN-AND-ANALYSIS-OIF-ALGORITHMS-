/*
 * Experiment 4 - Count Pairs (i, j) with nums[i]==nums[j] and (i*j) % k == 0
 * -----------------------------------------------------------------------------
 * Brute force O(n^2) check of every pair (i, j) with i < j.
 */

#include <stdio.h>

int countPairs(int nums[], int n, int k) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] == nums[j] && ((long long)i * j) % k == 0)
                count++;
        }
    }
    return count;
}

int main() {
    int nums1[] = {3, 1, 2, 2, 2, 1, 3};
    printf("Test 1 Output: %d\n", countPairs(nums1, 7, 2));

    int nums2[] = {1, 2, 3, 4};
    printf("Test 2 Output: %d\n", countPairs(nums2, 4, 1));

    return 0;
}
