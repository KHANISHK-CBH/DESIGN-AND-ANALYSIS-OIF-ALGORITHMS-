/*
 * Experiment 15 - Positions of Large Groups
 * ----------------------------------------------
 * Scans a string in a single pass, identifying consecutive groups
 * of the same character. Any group of length >= 3 is reported as
 * a [start, end] interval, in increasing order of start index.
 */

#include <stdio.h>
#include <string.h>

void findLargeGroups(char *s) {
    int n = strlen(s);
    int i = 0;
    int found = 0;

    printf("Output: [");
    while (i < n) {
        int j = i;
        while (j < n && s[j] == s[i])
            j++;
        // Group is s[i..j-1]
        if (j - i >= 3) {
            if (found) printf(", ");
            printf("[%d,%d]", i, j - 1);
            found = 1;
        }
        i = j;
    }
    printf("]\n");
}

int main() {
    findLargeGroups("abbxxxxzzy"); // Expected [[3,6]]
    findLargeGroups("abc");        // Expected []
    return 0;
}
