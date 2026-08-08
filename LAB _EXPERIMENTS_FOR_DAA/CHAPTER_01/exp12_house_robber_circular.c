/*
 * Experiment 12 - House Robber II (Circular Street)
 * ------------------------------------------------------
 * Houses are arranged in a circle, so the first and last house are
 * adjacent. We cannot rob both. Strategy: solve the LINEAR house
 * robber problem twice -
 *   (a) excluding the last house
 *   (b) excluding the first house
 * and take the maximum of the two results. Uses O(1) space DP.
 */

#include <stdio.h>

int robLinear(int nums[], int start, int end) {
    int prev1 = 0, prev2 = 0; // prev1 = dp[i-1], prev2 = dp[i-2]
    for (int i = start; i <= end; i++) {
        int current = (nums[i] + prev2 > prev1) ? nums[i] + prev2 : prev1;
        prev2 = prev1;
        prev1 = current;
    }
    return prev1;
}

int robCircular(int nums[], int n) {
    if (n == 1) return nums[0];
    int excludeLast = robLinear(nums, 0, n - 2);
    int excludeFirst = robLinear(nums, 1, n - 1);
    return (excludeLast > excludeFirst) ? excludeLast : excludeFirst;
}

int main() {
    int nums1[] = {2, 3, 2};
    printf("Test 1 Output: %d\n", robCircular(nums1, 3));

    int nums2[] = {1, 2, 3, 1};
    printf("Test 2 Output: %d\n", robCircular(nums2, 4));

    return 0;
}
