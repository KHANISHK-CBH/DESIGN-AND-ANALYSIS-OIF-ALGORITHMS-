/*
 * Experiment 11 - Out of Boundary Paths
 * -----------------------------------------
 * Count the number of ways to move a ball out of an m x n grid in
 * exactly N steps, starting at cell (i, j), moving one step
 * up/down/left/right each move. Solved using bottom-up Dynamic
 * Programming with a 3D DP table dp[step][row][col].
 * Answer is taken modulo 1e9+7 as is standard for this problem.
 */

#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int findPaths(int m, int n, int N, int startI, int startJ) {
    // dp[r][c] = number of ways to be at (r,c) after "step" moves
    static long long dp[50][50];
    static long long next[50][50];

    memset(dp, 0, sizeof(dp));
    dp[startI][startJ] = 1;

    long long moveCount = 0;

    for (int step = 1; step <= N; step++) {
        memset(next, 0, sizeof(next));
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (dp[r][c] == 0) continue;
                long long ways = dp[r][c];

                // Move up
                if (r - 1 < 0) moveCount = (moveCount + ways) % MOD;
                else next[r - 1][c] = (next[r - 1][c] + ways) % MOD;

                // Move down
                if (r + 1 >= m) moveCount = (moveCount + ways) % MOD;
                else next[r + 1][c] = (next[r + 1][c] + ways) % MOD;

                // Move left
                if (c - 1 < 0) moveCount = (moveCount + ways) % MOD;
                else next[r][c - 1] = (next[r][c - 1] + ways) % MOD;

                // Move right
                if (c + 1 >= n) moveCount = (moveCount + ways) % MOD;
                else next[r][c + 1] = (next[r][c + 1] + ways) % MOD;
            }
        }
        memcpy(dp, next, sizeof(dp));
    }

    return (int)(moveCount % MOD);
}

int main() {
    printf("Test 1 Output: %d\n", findPaths(2, 2, 2, 0, 0));   // Expected 6
    printf("Test 2 Output: %d\n", findPaths(1, 3, 3, 0, 1));   // Expected 12
    return 0;
}
