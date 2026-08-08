/*
 * Experiment 13 - Climbing Stairs
 * ----------------------------------
 * Number of distinct ways to climb n steps, taking either 1 or 2
 * steps at a time. This follows the Fibonacci recurrence:
 *     ways(n) = ways(n-1) + ways(n-2)
 * Solved bottom-up with O(1) space.
 */

#include <stdio.h>

int climbStairs(int n) {
    if (n <= 2) return n;

    int prev2 = 1, prev1 = 2;
    for (int i = 3; i <= n; i++) {
        int current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    return prev1;
}

int main() {
    printf("Test 1 Output: %d\n", climbStairs(4)); // Expected 5
    printf("Test 2 Output: %d\n", climbStairs(3)); // Expected 3
    return 0;
}
