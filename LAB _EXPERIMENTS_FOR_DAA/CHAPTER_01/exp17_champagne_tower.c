/*
 * Experiment 17 - Champagne Tower
 * ------------------------------------
 * Simulates champagne overflow through a pyramid of glasses using
 * Dynamic Programming. dp[r][c] tracks how many cups of liquid
 * have flowed into glass (r, c) in total (can exceed 1.0 = full).
 * Overflow above 1.0 splits equally to the two glasses below.
 */

#include <stdio.h>

#define ROWS 100

double champagneTower(int poured, int queryRow, int queryGlass) {
    static double dp[ROWS][ROWS];
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < ROWS; j++)
            dp[i][j] = 0.0;

    dp[0][0] = (double)poured;

    for (int r = 0; r < queryRow; r++) {
        for (int c = 0; c <= r; c++) {
            if (dp[r][c] > 1.0) {
                double overflow = (dp[r][c] - 1.0) / 2.0;
                dp[r + 1][c] += overflow;
                dp[r + 1][c + 1] += overflow;
            }
        }
    }

    double result = dp[queryRow][queryGlass];
    if (result > 1.0) result = 1.0;
    if (result < 0.0) result = 0.0;
    return result;
}

int main() {
    printf("Test 1 Output: %.5f\n", champagneTower(1, 1, 1)); // Expected 0.00000
    printf("Test 2 Output: %.5f\n", champagneTower(2, 1, 1)); // Expected 0.50000
    return 0;
}
