/*
 * Experiment 3 - Sum of Squares of Distinct Counts of All Subarrays
 * --------------------------------------------------------------------
 * For every subarray nums[i..j], compute the number of distinct
 * values in it, square that count, and sum over all subarrays.
 * Brute force approach: O(n^2) subarrays, O(1) amortized update of
 * distinct count using a frequency array as the window expands.
 */

#include <stdio.h>

#define MAXVAL 100001

long long sumOfSquares(int nums[], int n) {
    long long total = 0;
    int freq[MAXVAL];

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < MAXVAL; k++) freq[k] = 0; // reset for each start
        int distinct = 0;
        for (int j = i; j < n; j++) {
            if (freq[nums[j]] == 0)
                distinct++;
            freq[nums[j]]++;
            total += (long long)distinct * distinct;
        }
    }
    return total;
}

int main() {
    int nums1[] = {1, 2, 1};
    printf("Test 1 Output: %lld\n", sumOfSquares(nums1, 3));

    int nums2[] = {1, 1};
    printf("Test 2 Output: %lld\n", sumOfSquares(nums2, 2));

    return 0;
}
