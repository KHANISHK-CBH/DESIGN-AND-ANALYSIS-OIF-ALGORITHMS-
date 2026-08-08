/*
 * Experiment 2 - Count of Elements Existing in the Other Array
 * ---------------------------------------------------------------
 * Given nums1 (size n) and nums2 (size m):
 *  answer1 = count of indices i such that nums1[i] exists in nums2
 *  answer2 = count of indices i such that nums2[i] exists in nums1
 * Uses boolean presence arrays (hash-set style using a small array)
 * since constraints are small integers, for O(n+m) time.
 */

#include <stdio.h>

#define RANGE 2001   // supports values from -1000 to 1000 (offset by 1000)
#define OFFSET 1000

void countExistence(int nums1[], int n, int nums2[], int m,
                     int *answer1, int *answer2) {
    int present1[RANGE] = {0};
    int present2[RANGE] = {0};

    for (int i = 0; i < n; i++)
        present1[nums1[i] + OFFSET] = 1;
    for (int i = 0; i < m; i++)
        present2[nums2[i] + OFFSET] = 1;

    *answer1 = 0;
    *answer2 = 0;

    for (int i = 0; i < n; i++)
        if (present2[nums1[i] + OFFSET])
            (*answer1)++;

    for (int i = 0; i < m; i++)
        if (present1[nums2[i] + OFFSET])
            (*answer2)++;
}

int main() {
    int nums1_a[] = {2, 3, 2};
    int nums2_a[] = {1, 2};
    int a1, a2;
    countExistence(nums1_a, 3, nums2_a, 2, &a1, &a2);
    printf("Test 1 Output: [%d,%d]\n", a1, a2);

    int nums1_b[] = {4, 3, 2, 3, 1};
    int nums2_b[] = {2, 2, 5, 2, 3, 6};
    countExistence(nums1_b, 5, nums2_b, 6, &a1, &a2);
    printf("Test 2 Output: [%d,%d]\n", a1, a2);

    return 0;
}
