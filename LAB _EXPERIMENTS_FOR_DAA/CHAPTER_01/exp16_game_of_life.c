/*
 * Experiment 16 - Game of Life
 * ---------------------------------
 * Computes the next generation of Conway's Game of Life for an
 * m x n board, applying all 4 rules simultaneously. Uses a
 * temporary copy of the board so that updates don't affect
 * neighbor calculations mid-pass.
 */

#include <stdio.h>

#define MAXR 20
#define MAXC 20

int countLiveNeighbors(int board[MAXR][MAXC], int m, int n, int r, int c) {
    int count = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < m && nc >= 0 && nc < n)
                count += board[nr][nc];
        }
    }
    return count;
}

void gameOfLife(int board[MAXR][MAXC], int m, int n) {
    int copy[MAXR][MAXC];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            copy[i][j] = board[i][j];

    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            int liveNeighbors = countLiveNeighbors(copy, m, n, r, c);
            if (copy[r][c] == 1) {
                // Rule 1 & 3: dies from under/over population
                if (liveNeighbors < 2 || liveNeighbors > 3)
                    board[r][c] = 0;
                // Rule 2: survives with 2 or 3 neighbors (implicit, stays 1)
            } else {
                // Rule 4: reproduction
                if (liveNeighbors == 3)
                    board[r][c] = 1;
            }
        }
    }
}

void printBoard(int board[MAXR][MAXC], int m, int n) {
    for (int i = 0; i < m; i++) {
        printf("[");
        for (int j = 0; j < n; j++) {
            printf("%d", board[i][j]);
            if (j != n - 1) printf(",");
        }
        printf("]");
        if (i != m - 1) printf(",");
    }
    printf("\n");
}

int main() {
    int board1[MAXR][MAXC] = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 1},
        {0, 0, 0}
    };
    gameOfLife(board1, 4, 3);
    printf("Test 1 Output: ");
    printBoard(board1, 4, 3);

    int board2[MAXR][MAXC] = {
        {1, 1},
        {1, 0}
    };
    gameOfLife(board2, 2, 2);
    printf("Test 2 Output: ");
    printBoard(board2, 2, 2);

    return 0;
}
