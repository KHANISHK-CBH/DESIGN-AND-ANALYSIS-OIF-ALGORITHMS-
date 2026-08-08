/*
 * Experiment 14 - Unique Paths
 * --------------------------------
 * A robot at the top-left of an m x n grid can only move right or
 * down. Count the number of unique paths to the bottom-right
 * corner using bottom-up Dynamic Programming.
 */

#include <stdio.h>

int uniquePaths(int m, int n) {
    int dp[100][100];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 1; // only one way along top row / left column
            else
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[m - 1][n - 1];
}

int main() {
    printf("Test 1 Output: %d\n", uniquePaths(7, 3)); // Expected 28
    printf("Test 2 Output: %d\n", uniquePaths(3, 2)); // Expected 3
    return 0;
}
