# Design and Analysis of Algorithms — Lab Report

**Note on numbering:** The source problem set did not carry explicit experiment numbers (e.g. 1.1, 2.1). Experiments below are numbered **1 to 17** sequentially in the order the problems appeared.

---

# Experiment 1 – First Palindromic String

## File Name
`exp1_palindrome.c`

## Aim
To write a C program that finds the first palindromic string in a given array of strings.

## Objective
To understand string traversal and the two-pointer technique for palindrome checking, and apply it while scanning an array in order.

## Theory
A string is a palindrome if it reads identically forward and backward. The two-pointer technique checks characters from both ends moving inward, which avoids the overhead of reversing the string. Scanning the array left to right and returning on the first match guarantees the *first* palindromic string is reported, matching the problem's ordering requirement.

## Algorithm
1. For each string `words[i]` in the array, from index 0 onward:
   a. Set `left = 0`, `right = length-1`.
   b. While `left < right`: if `s[left] != s[right]`, not a palindrome — break.
   c. Otherwise increment `left`, decrement `right`.
   d. If the loop completes without mismatch, `words[i]` is palindromic — return it.
2. If no string is palindromic after scanning the full array, return `""`.

## Pseudocode
```
function isPalindrome(s):
    left = 0, right = length(s) - 1
    while left < right:
        if s[left] != s[right]: return false
        left++, right--
    return true

function firstPalindrome(words[], n):
    for i in 0..n-1:
        if isPalindrome(words[i]): return words[i]
    return ""
```

## C Program
```c
/*
 * Experiment 1 - First Palindromic String in an Array
 * ----------------------------------------------------
 * Reads an array of strings and prints the first string that
 * reads the same forward and backward. Prints "" if none exists.
 */

#include <stdio.h>
#include <string.h>

// Returns 1 if the string is a palindrome, else 0
int isPalindrome(char *s) {
    int left = 0;
    int right = strlen(s) - 1;
    while (left < right) {
        if (s[left] != s[right])
            return 0;
        left++;
        right--;
    }
    return 1;
}

// Returns pointer to first palindromic string, or NULL if none found
char *firstPalindrome(char *words[], int n) {
    for (int i = 0; i < n; i++) {
        if (isPalindrome(words[i]))
            return words[i];
    }
    return NULL;
}

int main() {
    char *words1[] = {"abc", "car", "ada", "racecar", "cool"};
    int n1 = 5;

    char *words2[] = {"notapalindrome", "racecar"};
    int n2 = 2;

    char *result1 = firstPalindrome(words1, n1);
    printf("Test 1 Output: %s\n", result1 ? result1 : "\"\"");

    char *result2 = firstPalindrome(words2, n2);
    printf("Test 2 Output: %s\n", result2 ? result2 : "\"\"");

    return 0;
}
```

## Sample Input
```
words1 = ["abc","car","ada","racecar","cool"]
words2 = ["notapalindrome","racecar"]
```

## Sample Output
```
Test 1 Output: ada
Test 2 Output: racecar
```

## Dry Run / Manual Calculation
For `words1`: "abc" → a≠c, fail. "car" → c≠r, fail. "ada" → a==a, d is middle, passes → return "ada" immediately (index 2), even though "racecar" at index 3 is also palindromic.

## Explanation
The program never checks strings after finding the first palindrome, matching the requirement to return only the *first* one. Each palindrome check itself runs in O(length of string) using constant extra space.

## Time Complexity
O(n × k), where n = number of strings and k = average string length (each string is checked in the worst case).

## Space Complexity
O(1) auxiliary space (excluding input storage) — only pointers/indices are used.

## Result
The program correctly identified "ada" and "racecar" as the first palindromic strings for the two test cases.

## Conclusion
The two-pointer technique efficiently detects palindromes without extra memory, and early-return scanning ensures correctness for "first occurrence" style problems.

## Viva Questions and Answers
1. **Q: What is a palindrome?**
   A: A string that reads the same forwards and backwards, e.g. "racecar".
2. **Q: Why use two pointers instead of reversing the string?**
   A: Reversing needs O(n) extra space; two pointers check in-place with O(1) space.
3. **Q: What is the time complexity of checking one string of length k?**
   A: O(k), since at most k/2 comparisons are made.
4. **Q: What does the function return if no palindrome exists?**
   A: An empty string `""`.
5. **Q: Why does the loop stop as soon as the first palindrome is found?**
   A: Because the problem asks only for the first palindromic string, not all of them — stopping early avoids unnecessary work.

---

# Experiment 2 – Count of Elements Existing in the Other Array

## File Name
`exp2_array_intersection_count.c`

## Aim
To count, for two integer arrays, how many elements of each array also appear in the other array.

## Objective
To apply hashing/presence-array techniques to convert an O(n×m) brute-force membership check into O(n+m).

## Theory
Checking "does this value exist in the other array" naively for every element costs O(m) per lookup with linear search, giving O(n×m) overall. By first marking which values are present in each array using a boolean presence array (a simplified hash set for a small known value range), each membership check becomes O(1), reducing total time to O(n+m).

## Algorithm
1. Create boolean arrays `present1` and `present2` sized to cover the value range.
2. Mark `present1[v] = true` for every `v` in `nums1`; similarly for `present2` from `nums2`.
3. `answer1` = count of `nums1[i]` where `present2[nums1[i]]` is true.
4. `answer2` = count of `nums2[i]` where `present1[nums2[i]]` is true.
5. Return `[answer1, answer2]`.

## Pseudocode
```
function countExistence(nums1, n, nums2, m):
    mark present1[] from nums1
    mark present2[] from nums2
    answer1 = count of nums1[i] where present2[nums1[i]] true
    answer2 = count of nums2[i] where present1[nums2[i]] true
    return [answer1, answer2]
```

## C Program
```c
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
```

## Sample Input
```
nums1 = [2,3,2], nums2 = [1,2]
nums1 = [4,3,2,3,1], nums2 = [2,2,5,2,3,6]
```

## Sample Output
```
Test 1 Output: [2,1]
Test 2 Output: [3,4]
```

## Dry Run / Manual Calculation
For Test 2: `present2` has {2,5,3,6}. Checking nums1=[4,3,2,3,1]: 4∉, 3∈, 2∈, 3∈, 1∉ → answer1 = 3.
`present1` has {4,3,2,1}. Checking nums2=[2,2,5,2,3,6]: 2∈,2∈,5∉,2∈,3∈,6∉ → answer2 = 4.

## Explanation
Presence arrays act as a direct-address hash table since the value range is small and known, giving constant-time lookups instead of scanning the other array repeatedly.

## Time Complexity
O(n + m) — one pass to build presence arrays, one pass to count matches.

## Space Complexity
O(R) where R is the value range covered by the presence arrays (constant for a fixed range, e.g. O(2001) here).

## Result
The program correctly computed [2,1] and [3,4] for the two given test cases.

## Conclusion
Presence/hash arrays convert repeated membership tests from linear to constant time, a key optimization pattern in DAA.

## Viva Questions and Answers
1. **Q: Why not use nested loops directly?**
   A: Nested loops give O(n×m) time; presence arrays reduce this to O(n+m).
2. **Q: What is the OFFSET used for in the code?**
   A: To handle negative numbers, since array indices cannot be negative — it shifts the value range to start at 0.
3. **Q: What data structure would you use if the value range were very large (e.g., up to 10^9)?**
   A: A hash set/hash map instead of a fixed-size array, since a direct-address array would be impractical.
4. **Q: Is order preserved in the output?**
   A: No, we only count matches; order of elements doesn't affect the final counts.
5. **Q: What happens if nums1 and nums2 share no elements?**
   A: Both answer1 and answer2 would be 0.

---

# Experiment 3 – Sum of Squares of Distinct Counts of All Subarrays

## File Name
`exp3_sum_squares_distinct_subarrays.c`

## Aim
To compute the sum of squares of the distinct-value count of every possible subarray of a given array.

## Objective
To practice subarray enumeration and incremental frequency tracking using a sliding-window-like expansion.

## Theory
There are O(n²) subarrays in an array of size n. For each starting index `i`, as the ending index `j` expands from `i` to `n-1`, a frequency table can track how many distinct elements are currently in the window `[i, j]` incrementally (O(1) amortized per step), instead of recomputing distinct counts from scratch for every subarray (which would cost O(n) per subarray).

## Algorithm
1. For each start index `i` from 0 to n-1:
   a. Reset frequency table and distinct counter.
   b. For each end index `j` from `i` to n-1:
      - If `nums[j]` was unseen in this window (`freq[nums[j]] == 0`), increment `distinct`.
      - Increment `freq[nums[j]]`.
      - Add `distinct²` to the running total.
2. Return total.

## Pseudocode
```
function sumOfSquares(nums, n):
    total = 0
    for i in 0..n-1:
        reset freq[]
        distinct = 0
        for j in i..n-1:
            if freq[nums[j]] == 0: distinct++
            freq[nums[j]]++
            total += distinct * distinct
    return total
```

## C Program
```c
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
```

## Sample Input
```
nums = [1,2,1]
nums = [1,1]
```

## Sample Output
```
Test 1 Output: 15
Test 2 Output: 3
```

## Dry Run / Manual Calculation
For [1,2,1]: subarrays and distinct counts — [1]:1, [2]:1, [1]:1, [1,2]:2, [2,1]:2, [1,2,1]:2.
Sum of squares = 1+1+1+4+4+4 = 15. ✔ Matches program output.

## Explanation
The reset of the frequency array for each new start index keeps the logic simple (brute-force O(n²) subarrays), while the inner loop tracks distinct count incrementally rather than recomputing it, saving an inner O(n) pass.

## Time Complexity
O(n² ) for the subarray enumeration (frequency-array reset dominates at O(n × MAXVAL) in this implementation; for pure algorithmic complexity relative to n with a hash map instead, O(n²)).

## Space Complexity
O(MAXVAL) for the frequency array — effectively O(1) relative to n if the value range is fixed and bounded.

## Result
The program correctly output 15 and 3 for the two test cases, matching the manual calculation.

## Conclusion
Incremental frequency tracking avoids recomputation and is a common DAA pattern for subarray/substring aggregate problems.

## Viva Questions and Answers
1. **Q: How many subarrays does an array of size n have?**
   A: n(n+1)/2.
2. **Q: Why is the frequency array reset for every new `i`?**
   A: Because each new starting index begins a fresh window with no elements counted yet.
3. **Q: Could this problem be solved faster than O(n²)?**
   A: Not asymptotically better in general, since there are O(n²) subarrays to account for, though contribution-based techniques can optimize per-subarray work.
4. **Q: What does "distinct count" mean for a subarray?**
   A: The number of unique values present in that particular subarray.
5. **Q: Why use `long long` for the total?**
   A: Because squared distinct counts summed over O(n²) subarrays can overflow a 32-bit `int` for larger inputs.

---

# Experiment 4 – Count Pairs (i, j) with nums[i]==nums[j] and (i×j) divisible by k

## File Name
`exp4_pairs_divisible_by_k.c`

## Aim
To count index pairs (i, j) with i<j where the values at those indices are equal and the product of indices is divisible by k.

## Objective
To practice brute-force pair enumeration with a compound condition check.

## Theory
This problem requires checking every pair of indices, since the divisibility condition depends on the *indices themselves* (not just values), which rules out simple value-frequency grouping alone without extra bookkeeping. A direct O(n²) double loop is the straightforward and correct approach for lab-level input sizes.

## Algorithm
1. For each `i` from 0 to n-1:
   a. For each `j` from i+1 to n-1:
      - If `nums[i]==nums[j]` and `(i*j) % k == 0`, increment count.
2. Return count.

## Pseudocode
```
function countPairs(nums, n, k):
    count = 0
    for i in 0..n-1:
        for j in i+1..n-1:
            if nums[i]==nums[j] and (i*j) % k == 0:
                count++
    return count
```

## C Program
```c
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
```

## Sample Input
```
nums = [3,1,2,2,2,1,3], k = 2
nums = [1,2,3,4], k = 1
```

## Sample Output
```
Test 1 Output: 4
Test 2 Output: 0
```

## Dry Run / Manual Calculation
Valid pairs found: (0,6): nums equal (3,3), 0×6=0 divisible by 2. (2,3): (2,2), 2×3=6 divisible by 2. (2,4): (2,2), 2×4=8 divisible by 2. (3,4): (2,2), 3×4=12 divisible by 2. Total = 4. ✔

## Explanation
Since `k` divides `i*j`, and index 0 makes any product 0 (divisible by any k), such pairs are automatically included — this is handled naturally by the modulo check without special-casing.

## Time Complexity
O(n²) — every pair of indices is examined once.

## Space Complexity
O(1) auxiliary space.

## Result
The program correctly returned 4 and 0 for the given test cases.

## Conclusion
Brute-force pair enumeration remains the clearest and most reliable approach when the condition depends on both values and index arithmetic together.

## Viva Questions and Answers
1. **Q: Why can't we group by value alone and skip index checks?**
   A: Because divisibility of i*j by k depends on the indices, not the values, so index information cannot be discarded.
2. **Q: What is the time complexity of this brute-force approach?**
   A: O(n²).
3. **Q: Why does i=0 always satisfy divisibility?**
   A: Because i*j = 0 when i=0, and 0 is divisible by any non-zero k.
4. **Q: Why is `(long long)` used in the modulo computation?**
   A: To avoid potential integer overflow when multiplying large indices, though not strictly needed for small n it's a safe practice.
5. **Q: Could a hashmap of value→indices speed this up?**
   A: Partially — it reduces candidate pairs to only equal-value groups, but the index-divisibility check must still be done per pair within each group.

---

# Experiment 5 – Find Maximum Element (Least Time Complexity)

## File Name
`exp5_max_element_linear.c`

## Aim
To find the maximum element of an array using the least possible time complexity.

## Objective
To demonstrate that a single linear pass is both necessary and sufficient to find the maximum of an unsorted array.

## Theory
Since every element could potentially be the maximum, an algorithm must examine each element at least once — this gives a lower bound of Ω(n). A single linear scan comparing a running maximum against each element achieves exactly O(n), matching this lower bound, making it optimal.

## Algorithm
1. Set `maxVal = arr[0]`.
2. For each subsequent element, if it is greater than `maxVal`, update `maxVal`.
3. Return `maxVal` after the scan completes.

## Pseudocode
```
function findMax(arr, n):
    maxVal = arr[0]
    for i in 1..n-1:
        if arr[i] > maxVal: maxVal = arr[i]
    return maxVal
```

## C Program
```c
/*
 * Experiment 5 - Find Maximum Element (Least Time Complexity)
 * ----------------------------------------------------------------
 * A single linear scan (O(n)) is the least possible time complexity
 * for finding the maximum of an unsorted array, since every element
 * must be inspected at least once.
 */

#include <stdio.h>

int findMax(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }
    return maxVal;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    printf("Test 1 Output: %d\n", findMax(arr1, 5));

    int arr2[] = {7, 7, 7, 7, 7};
    printf("Test 2 Output: %d\n", findMax(arr2, 5));

    int arr3[] = {-10, 2, 3, -4, 5};
    printf("Test 3 Output: %d\n", findMax(arr3, 5));

    return 0;
}
```

## Sample Input
```
{1,2,3,4,5}
{7,7,7,7,7}
{-10,2,3,-4,5}
```

## Sample Output
```
Test 1 Output: 5
Test 2 Output: 7
Test 3 Output: 5
```

## Dry Run / Manual Calculation
For {-10,2,3,-4,5}: maxVal starts at -10 → 2>-10 update to 2 → 3>2 update to 3 → -4 not > 3 → 5>3 update to 5. Final: 5. ✔

## Explanation
No comparison-based algorithm can find the maximum in fewer than n-1 comparisons, so this linear approach is asymptotically optimal.

## Time Complexity
O(n).

## Space Complexity
O(1).

## Result
The program correctly output 5, 7, and 5 for the three test cases.

## Conclusion
A simple linear scan is provably the fastest general approach for maximum-finding in an unsorted array.

## Viva Questions and Answers
1. **Q: Why is O(n) considered optimal here?**
   A: Because every element must be examined at least once to guarantee correctness, so no algorithm can do better than O(n).
2. **Q: How many comparisons does this algorithm perform?**
   A: Exactly n-1 comparisons.
3. **Q: Would sorting the array first be faster for finding the max?**
   A: No — sorting takes O(n log n), which is slower than the O(n) linear scan.
4. **Q: What if all elements are equal?**
   A: The maxVal remains that same value throughout — correct output as shown in Test 2.
5. **Q: Does this algorithm work with negative numbers?**
   A: Yes, comparisons work identically regardless of sign, as shown in Test 3.

---

# Experiment 6 – Sort a List Then Find the Maximum

## File Name
`exp6_sort_then_max.c`

## Aim
To sort a list using an efficient sorting algorithm and then determine the maximum element from the sorted list.

## Objective
To understand Merge Sort's divide-and-conquer approach and how a sorted array simplifies extracting the maximum (last element).

## Theory
Merge Sort recursively divides the array into halves, sorts each half, and merges them back in sorted order, achieving O(n log n) time. Once sorted in ascending order, the maximum element is trivially the last element of the array — an O(1) lookup after sorting.

## Algorithm
1. If the list is empty, report accordingly.
2. Recursively divide the array into two halves until sub-arrays of size 1 remain.
3. Merge sorted halves back together in ascending order.
4. Return the last element of the fully sorted array as the maximum.

## Pseudocode
```
function mergeSort(arr, l, r):
    if l < r:
        m = (l+r)/2
        mergeSort(arr, l, m)
        mergeSort(arr, m+1, r)
        merge(arr, l, m, r)

function sortAndFindMax(arr, n):
    if n == 0: return "empty"
    mergeSort(arr, 0, n-1)
    return arr[n-1]
```

## C Program
```c
/*
 * Experiment 6 - Sort a List Then Find the Maximum Element
 * ---------------------------------------------------------------
 * Sorts the array using an efficient O(n log n) algorithm (Merge
 * Sort) and then reports the last element (maximum) of the sorted
 * array. Handles the empty-list edge case explicitly.
 */

#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Returns 1 and sets *maxVal if list is non-empty, else returns 0
int sortAndFindMax(int arr[], int n, int *maxVal) {
    if (n == 0)
        return 0; // empty list

    mergeSort(arr, 0, n - 1);
    *maxVal = arr[n - 1];
    return 1;
}

void testCase(int arr[], int n) {
    int maxVal;
    if (sortAndFindMax(arr, n, &maxVal))
        printf("Output: %d\n", maxVal);
    else
        printf("Output: List is empty. No maximum exists.\n");
}

int main() {
    int *arr1 = NULL; // represents an empty list, size 0
    printf("Test 1 (Empty List): ");
    testCase(arr1, 0);

    int arr2[] = {5};
    printf("Test 2 (Single Element): ");
    testCase(arr2, 1);

    int arr3[] = {3, 3, 3, 3, 3};
    printf("Test 3 (All Same): ");
    testCase(arr3, 5);

    return 0;
}
```

## Sample Input
```
[]
[5]
[3,3,3,3,3]
```

## Sample Output
```
Test 1 (Empty List): Output: List is empty. No maximum exists.
Test 2 (Single Element): Output: 5
Test 3 (All Same): Output: 3
```

## Dry Run / Manual Calculation
For [3,3,3,3,3]: Merge Sort splits into halves of equal values, merges back unchanged (already sorted), last element = 3.

## Explanation
The empty-list case is checked explicitly before invoking `mergeSort`, avoiding out-of-bounds access. All other cases run the standard divide-and-conquer merge sort before reading off the last element.

## Time Complexity
O(n log n) for the sort; O(1) for reading the maximum afterward → overall O(n log n).

## Space Complexity
O(n) auxiliary space for the temporary `L` and `R` arrays used during merging.

## Result
The program correctly handled the empty list, single element, and all-equal-elements cases.

## Conclusion
Sorting before finding the maximum is less efficient than a direct linear scan (Experiment 5), but is useful when the sorted order is needed for other purposes too.

## Viva Questions and Answers
1. **Q: Why is Merge Sort O(n log n)?**
   A: It divides the array in log n levels, and merging at each level costs O(n) total, giving O(n log n).
2. **Q: Is Merge Sort in-place?**
   A: No, it requires O(n) auxiliary space for merging.
3. **Q: Why check `n == 0` before sorting?**
   A: To avoid invalid array accesses (arr[-1] or arr[n-1] on an empty array).
4. **Q: Is sort-then-max efficient compared to a direct linear scan?**
   A: No — O(n log n) is slower than the O(n) linear scan approach for just finding the maximum.
5. **Q: Is Merge Sort stable?**
   A: Yes, equal elements retain their relative order during merging.


---

# Experiment 7 – Unique Elements from a List

## File Name
`exp7_unique_elements.c`

## Aim
To create a new list containing only the unique (first-occurrence) elements from an input list.

## Objective
To practice building a result list while checking for prior occurrence, and to analyze the space complexity of the approach.

## Theory
An element is included in the output only the first time it is seen. This requires, for each new element, checking whether it already exists in the result built so far. A simple linear "seen so far" search against the growing result array achieves this without extra data structures, at the cost of higher time complexity compared to a hash-based approach.

## Algorithm
1. Initialize an empty `result` array.
2. For each element in the input array:
   a. If it is not already present in `result`, append it.
3. Return `result`.

## Pseudocode
```
function getUnique(arr, n):
    result = []
    for x in arr:
        if x not in result:
            append x to result
    return result
```

## C Program
```c
/*
 * Experiment 7 - Extract Unique Elements from a List
 * ----------------------------------------------------
 * Builds a new list containing only the first occurrence of each
 * element (preserving input order) using a simple "seen so far"
 * linear search. Space complexity is analyzed in the report.
 */

#include <stdio.h>

int isSeen(int result[], int size, int val) {
    for (int i = 0; i < size; i++)
        if (result[i] == val)
            return 1;
    return 0;
}

int getUnique(int arr[], int n, int result[]) {
    int size = 0;
    for (int i = 0; i < n; i++) {
        if (!isSeen(result, size, arr[i])) {
            result[size++] = arr[i];
        }
    }
    return size;
}

void printArray(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i != n - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    int arr1[] = {3, 7, 3, 5, 2, 5, 9, 2};
    int result1[8];
    int size1 = getUnique(arr1, 8, result1);
    printf("Test 1 Output: ");
    printArray(result1, size1);

    int arr2[] = {-1, 2, -1, 3, 2, -2};
    int result2[6];
    int size2 = getUnique(arr2, 6, result2);
    printf("Test 2 Output: ");
    printArray(result2, size2);

    int arr3[] = {1000000, 999999, 1000000};
    int result3[3];
    int size3 = getUnique(arr3, 3, result3);
    printf("Test 3 Output: ");
    printArray(result3, size3);

    return 0;
}
```

## Sample Input
```
[3, 7, 3, 5, 2, 5, 9, 2]
[-1, 2, -1, 3, 2, -2]
[1000000, 999999, 1000000]
```

## Sample Output
```
Test 1 Output: [3, 7, 5, 2, 9]
Test 2 Output: [-1, 2, 3, -2]
Test 3 Output: [1000000, 999999]
```

## Dry Run / Manual Calculation
For [3,7,3,5,2,5,9,2]: 3 new→add, 7 new→add, 3 seen→skip, 5 new→add, 2 new→add, 5 seen→skip, 9 new→add, 2 seen→skip. Result = [3,7,5,2,9]. ✔

## Explanation
Because `isSeen` performs a linear search of the result array for every input element, the overall approach is quadratic in the worst case, but requires no extra hashing data structure — a trade-off between simplicity and speed.

## Time Complexity
O(n²) in the worst case (n elements, each checked against a growing result list of up to n elements).
*(Space complexity discussion below — this can be improved to O(n) time using a hash set.)*

## Space Complexity
O(n) — the result array itself stores up to n elements in the worst case (all unique); no other significant extra space is used.

## Result
The program correctly extracted [3,7,5,2,9], [-1,2,3,-2], and [1000000,999999] for the three test cases.

## Conclusion
This approach clearly demonstrates the time-space trade-off: using no auxiliary hash structure keeps space at O(n) but raises time to O(n²); using a hash set would bring time down to O(n) at the cost of extra hash-table space.

## Viva Questions and Answers
1. **Q: What is the space complexity of this algorithm?**
   A: O(n), for storing the output list of unique elements.
2. **Q: What is the time complexity, and why?**
   A: O(n²) in the worst case, because each new element is linearly searched against the growing result list.
3. **Q: How could this be optimized to O(n) time?**
   A: By using a hash set to check "seen" status in O(1) instead of a linear scan.
4. **Q: Does the order of elements in the output matter here?**
   A: The output preserves the order of first occurrence, though the problem statement notes order may vary depending on implementation.
5. **Q: Does this algorithm handle negative numbers correctly?**
   A: Yes, as shown by Test 2 with negative values.

---

# Experiment 8 – Bubble Sort

## File Name
`exp8_bubble_sort.c`

## Aim
To sort an array of integers using the Bubble Sort technique and analyze its time complexity.

## Objective
To understand the repeated adjacent-swap mechanism of Bubble Sort and its best/worst case behavior.

## Theory
Bubble Sort repeatedly steps through the array, compares adjacent elements, and swaps them if they are in the wrong order. After each full pass, the largest unsorted element "bubbles up" to its correct position at the end. An optional `swapped` flag allows early termination if the array becomes sorted before all passes complete, improving the best-case performance.

## Algorithm
1. For each pass `i` from 0 to n-2:
   a. For each `j` from 0 to n-i-2:
      - If `arr[j] > arr[j+1]`, swap them; set `swapped = true`.
   b. If no swap occurred in this pass, the array is sorted — break early.
2. Return the sorted array.

## Pseudocode
```
function bubbleSort(arr, n):
    for i in 0..n-2:
        swapped = false
        for j in 0..n-i-2:
            if arr[j] > arr[j+1]:
                swap(arr[j], arr[j+1])
                swapped = true
        if not swapped: break
```

## C Program
```c
/*
 * Experiment 8 - Bubble Sort
 * ---------------------------
 * Repeatedly swaps adjacent out-of-order elements until the array
 * is sorted in ascending order. Includes an early-exit flag for the
 * best-case optimization.
 */

#include <stdio.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break; // already sorted, exit early
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Before Sorting: ");
    printArray(arr, n);

    bubbleSort(arr, n);

    printf("After Sorting:  ");
    printArray(arr, n);

    return 0;
}
```

## Sample Input
```
{64, 34, 25, 12, 22, 11, 90}
```

## Sample Output
```
Before Sorting: 64 34 25 12 22 11 90
After Sorting:  11 12 22 25 34 64 90
```

## Dry Run / Manual Calculation
Pass 1: 64,34→swap; 64,25→swap; 64,12→swap; 64,22→swap; 64,11→swap; 64,90→no swap. Array: 34 25 12 22 11 64 90.
Subsequent passes continue bubbling smaller values left until fully sorted: 11 12 22 25 34 64 90.

## Explanation
Each pass guarantees the next-largest unsorted element reaches its correct final position, so after n-1 passes at most, the array is fully sorted.

## Time Complexity
Worst/Average case: O(n²). Best case (already sorted, with early exit): O(n).

## Space Complexity
O(1) — sorting is done in place.

## Result
The array {64,34,25,12,22,11,90} was correctly sorted to {11,12,22,25,34,64,90}.

## Conclusion
Bubble Sort is simple to implement but inefficient for large datasets due to its O(n²) average complexity; it is mainly used for educational purposes or very small inputs.

## Viva Questions and Answers
1. **Q: What is the worst-case time complexity of Bubble Sort?**
   A: O(n²).
2. **Q: What is the best-case time complexity, and how is it achieved?**
   A: O(n), achieved with the `swapped` flag when the array is already sorted.
3. **Q: Is Bubble Sort stable?**
   A: Yes, equal elements are never swapped past each other.
4. **Q: Is Bubble Sort an in-place sorting algorithm?**
   A: Yes, it requires only O(1) extra space.
5. **Q: Why does the largest element "bubble" to the end after the first pass?**
   A: Because it is compared against and swapped past every smaller element it encounters during that pass.

---

# Experiment 9 – Binary Search

## File Name
`exp9_binary_search.c`

## Aim
To check whether a given number exists in a sorted array using Binary Search and analyze its time complexity.

## Objective
To understand the divide-and-conquer principle applied to searching, and why a sorted array is a prerequisite.

## Theory
Binary Search requires the array to be sorted. It repeatedly compares the target with the middle element of the current search range: if equal, found; if the target is smaller, search the left half; if larger, search the right half. This halves the search space each step, giving logarithmic time complexity.

**Important note:** The given test-case array `{3,4,6,-9,10,8,9,30}` is **not sorted**, but Binary Search mandates sorted input. This program sorts the array first (using Bubble Sort) and then performs Binary Search, so the reported position corresponds to the index within the **sorted** array, not the original unsorted order.

## Algorithm
1. Sort the array (prerequisite for Binary Search).
2. Set `low = 0`, `high = n-1`.
3. While `low <= high`:
   a. `mid = (low+high)/2`.
   b. If `arr[mid] == key`, return `mid`.
   c. Else if `arr[mid] < key`, set `low = mid+1`.
   d. Else set `high = mid-1`.
4. If not found, return -1.

## Pseudocode
```
function binarySearch(arr, n, key):
    low = 0, high = n-1
    while low <= high:
        mid = (low+high)/2
        if arr[mid] == key: return mid
        elif arr[mid] < key: low = mid+1
        else: high = mid-1
    return -1
```

## C Program
```c
/*
 * Experiment 9 - Binary Search on a Sorted Array
 * -------------------------------------------------
 * NOTE: Binary search requires a SORTED array. The given test-case
 * array is first sorted, then searched for the key. The position
 * printed corresponds to the index within the sorted array.
 */

#include <stdio.h>

int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

void bubbleSort(int arr[], int n) { // small helper to ensure sorted input
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
}

void runTest(int key) {
    int arr[] = {3, 4, 6, -9, 10, 8, 9, 30};
    int n = 8;
    bubbleSort(arr, n);

    int pos = binarySearch(arr, n, key);
    if (pos != -1)
        printf("Element %d is found at position %d\n", key, pos);
    else
        printf("Element %d is not found\n", key);
}

int main() {
    runTest(10);
    runTest(100);
    return 0;
}
```

## Sample Input
```
X = {3,4,6,-9,10,8,9,30}, KEY = 10
X = {3,4,6,-9,10,8,9,30}, KEY = 100
```

## Sample Output
```
Element 10 is found at position 6
Element 100 is not found
```
*(Position 6 refers to the 0-indexed position within the sorted array `{-9,3,4,6,8,9,10,30}`. This differs from the position stated against the unsorted input in the original problem text, since Binary Search is only valid on sorted data.)*

## Dry Run / Manual Calculation
Sorted array: {-9,3,4,6,8,9,10,30} (indices 0–7).
Search for 10: low=0,high=7,mid=3→arr[3]=6<10→low=4. mid=5→arr[5]=9<10→low=6. mid=6→arr[6]=10==10→found at index 6. ✔

## Explanation
The helper `bubbleSort` guarantees the precondition of Binary Search is satisfied before searching, keeping the demonstration self-contained and correct.

## Time Complexity
O(log n) for the search itself; O(n²) for the sorting step if unsorted input is provided (dominates overall); O(log n) if the input is already sorted.

## Space Complexity
O(1) — iterative binary search uses constant extra space.

## Result
The program correctly located 10 at index 6 in the sorted array and correctly reported that 100 does not exist.

## Conclusion
Binary Search is highly efficient (O(log n)) but strictly requires sorted data; sorting overhead must be accounted for when the input isn't already sorted.

## Viva Questions and Answers
1. **Q: What is the precondition for Binary Search to work correctly?**
   A: The array must be sorted.
2. **Q: What is the time complexity of Binary Search?**
   A: O(log n).
3. **Q: Why does Binary Search halve the search space each step?**
   A: Comparing against the middle element eliminates one entire half of the remaining range each iteration.
4. **Q: What happens if the array is not sorted?**
   A: Binary Search may give incorrect or inconsistent results, since its correctness depends on sorted ordering.
5. **Q: What is the space complexity of the iterative Binary Search?**
   A: O(1), since only a few index variables are used.

---

# Experiment 10 – Sort an Array in O(n log n) Without Built-in Functions, With Smallest Space Complexity

## File Name
`exp10_sort_no_builtin.c`

## Aim
To sort an integer array in ascending order in O(n log n) time without using built-in sort functions, using the smallest possible auxiliary space.

## Objective
To understand Heap Sort as an in-place O(n log n) sorting algorithm, and why it is preferable to Merge Sort when minimizing space is the priority.

## Theory
Heap Sort first builds a max-heap from the array, then repeatedly swaps the root (maximum) with the last unsorted element and re-heapifies the reduced heap. Because heap operations work directly on the array in place, Heap Sort achieves O(n log n) time with only O(1) auxiliary space — unlike Merge Sort, which needs O(n) extra space for merging.

## Algorithm
1. Build a max-heap from the input array (heapify from the last non-leaf node upward).
2. Repeat until the heap is empty:
   a. Swap the root (max element) with the last element of the heap.
   b. Reduce heap size by 1.
   c. Heapify the root to restore the max-heap property.
3. The array is now sorted in ascending order.

## Pseudocode
```
function heapify(arr, n, i):
    largest = i, left = 2i+1, right = 2i+2
    if left<n and arr[left]>arr[largest]: largest=left
    if right<n and arr[right]>arr[largest]: largest=right
    if largest != i:
        swap(arr[i], arr[largest])
        heapify(arr, n, largest)

function heapSort(arr, n):
    for i in n/2-1 downto 0: heapify(arr, n, i)
    for i in n-1 downto 1:
        swap(arr[0], arr[i])
        heapify(arr, i, 0)
```

## C Program
```c
/*
 * Experiment 10 - Sort an Array in O(n log n) Without Built-in
 * Sort Functions, With Smallest Possible Space Complexity
 * -----------------------------------------------------------------
 * Heap Sort is used here: it achieves O(n log n) time with only
 * O(1) auxiliary space (in-place), which beats Merge Sort's O(n)
 * extra space requirement.
 */

#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Maintains the max-heap property for subtree rooted at index i
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements one by one from the heap
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i != n - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    int nums[] = {5, 2, 3, 1, 4, -7, 0};
    int n = sizeof(nums) / sizeof(nums[0]);

    printf("Before Sorting: ");
    printArray(nums, n);

    heapSort(nums, n);

    printf("After Sorting:  ");
    printArray(nums, n);

    return 0;
}
```

## Sample Input
```
[5, 2, 3, 1, 4, -7, 0]
```

## Sample Output
```
Before Sorting: [5, 2, 3, 1, 4, -7, 0]
After Sorting:  [-7, 0, 1, 2, 3, 4, 5]
```

## Dry Run / Manual Calculation
Building the max-heap from [5,2,3,1,4,-7,0] rearranges it to [5,4,3,1,2,-7,0]. Repeated root-extraction and re-heapify then place elements in ascending order at the end of the array, yielding [-7,0,1,2,3,4,5].

## Explanation
Heap Sort avoids the O(n) extra memory that Merge Sort needs because all operations happen within the same array — only a constant number of temporary variables are used for swaps.

## Time Complexity
O(n log n) — building the heap takes O(n), and n extractions each costing O(log n) give O(n log n) overall.

## Space Complexity
O(1) auxiliary space (in-place sorting), better than Merge Sort's O(n).

## Result
The array was correctly sorted to [-7, 0, 1, 2, 3, 4, 5].

## Conclusion
Heap Sort is the preferred choice when both O(n log n) time and minimal (O(1)) auxiliary space are required simultaneously.

## Viva Questions and Answers
1. **Q: Why is Heap Sort chosen over Merge Sort for this problem?**
   A: Heap Sort is in-place (O(1) space) while Merge Sort needs O(n) extra space; both are O(n log n) in time.
2. **Q: What is a max-heap?**
   A: A complete binary tree where every parent node is greater than or equal to its children.
3. **Q: What is the time complexity of building a heap from an unsorted array?**
   A: O(n), using the bottom-up heapify approach.
4. **Q: Is Heap Sort a stable sorting algorithm?**
   A: No, Heap Sort is not stable — equal elements may not retain their original relative order.
5. **Q: Why do we swap the root with the last element during extraction?**
   A: To move the current maximum to its correct sorted position at the end while keeping the remaining elements as a valid heap structure to be re-heapified.


---

# Experiment 11 – Out of Boundary Paths (Ball in Grid)

## File Name
`exp11_ball_out_of_grid.c`

## Aim
To find the number of ways to move a ball out of an m×n grid boundary in exactly N steps, starting from a given cell.

## Objective
To apply Dynamic Programming to a state-space counting problem involving grid movement over discrete time steps.

## Theory
At each step, the ball can move up, down, left, or right. If a move takes it outside the grid, that counts as one valid "out of boundary" path. Because the number of ways to be at each cell depends only on the previous step's counts, this is solved with DP where `dp[step][row][col]` represents the number of ways to reach `(row,col)` after `step` moves. Moves that exit the grid boundary contribute directly to the answer.

## Algorithm
1. Initialize `dp[start_row][start_col] = 1` (the ball starts there with 1 way).
2. For each step from 1 to N:
   a. For every cell with a non-zero count, distribute that count to its 4 neighbors.
   b. If a neighbor is outside the grid, add the count to `moveCount` (paths that just exited).
   c. Otherwise, add the count to the neighboring cell's next-step total.
3. After N steps, return `moveCount % (10^9+7)`.

## Pseudocode
```
function findPaths(m, n, N, i, j):
    dp[i][j] = 1
    moveCount = 0
    for step in 1..N:
        next = new grid of zeros
        for each cell (r,c) with dp[r][c] > 0:
            for each of 4 directions:
                if out of bounds: moveCount += dp[r][c]
                else: next[neighbor] += dp[r][c]
        dp = next
    return moveCount mod (1e9+7)
```

## C Program
```c
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
```

## Sample Input
```
m=2, n=2, N=2, i=0, j=0
m=1, n=3, N=3, i=0, j=1
```

## Sample Output
```
Test 1 Output: 6
Test 2 Output: 12
```

## Dry Run / Manual Calculation
For m=2,n=2,N=2,start=(0,0): Step 1 → ball can move to (1,0), (0,1), or exit up/left (2 exits). Step 2 → from surviving positions, more exits occur. Summing all paths that exit within exactly 2 steps gives 6, matching the DP result.

## Explanation
Because moves at each step only depend on the counts from the *previous* step, the 2D DP table is refreshed each iteration ("next"), which is a standard technique to avoid overwriting values mid-update.

## Time Complexity
O(N × m × n) — N steps, each processing every one of the m×n cells with O(1) work per cell (4 directions).

## Space Complexity
O(m × n) for the two DP grids (current and next step), independent of N.

## Result
The program correctly computed 6 and 12 for the given test cases, matching expected outputs.

## Conclusion
This problem demonstrates DP over an evolving 2D state space across discrete time steps — a pattern common to many grid/graph counting problems.

## Viva Questions and Answers
1. **Q: Why is a modulo (1e9+7) used?**
   A: Because the number of paths can grow exponentially large, modulo arithmetic keeps values within standard integer bounds.
2. **Q: Why use two separate grids (dp and next) instead of updating dp in place?**
   A: Updating in place would use partially-updated (step k) values while still computing step k, corrupting the calculation; a fresh "next" grid keeps steps properly separated.
3. **Q: What does it mean for the ball to be "out of boundary"?**
   A: The ball has moved to a position outside the row/column range of the grid, i.e., it has left the grid.
4. **Q: What is the time complexity of this DP solution?**
   A: O(N × m × n).
5. **Q: Could this be solved with recursion and memoization instead?**
   A: Yes, top-down memoized recursion with state (step, row, col) is an equivalent alternative to this bottom-up approach.

---

# Experiment 12 – House Robber II (Circular Street)

## File Name
`exp12_house_robber_circular.c`

## Aim
To determine the maximum amount of money that can be robbed from houses arranged in a circle without robbing two adjacent houses.

## Objective
To extend the classic linear House Robber DP to a circular arrangement by decomposing it into two linear sub-problems.

## Theory
In a circle, house 0 and house n-1 are adjacent, so they cannot both be robbed. This constraint is handled by solving the standard linear House Robber problem twice: once excluding the last house (allowing the first), and once excluding the first house (allowing the last) — then taking the maximum of the two results, which correctly accounts for the circular adjacency.

## Algorithm
1. If there is only 1 house, return its value directly (no adjacency conflict possible).
2. Compute `robLinear` over houses[0 .. n-2] (excludes last house).
3. Compute `robLinear` over houses[1 .. n-1] (excludes first house).
4. Return the maximum of the two.

`robLinear` itself uses O(1)-space DP: `dp[i] = max(dp[i-1], dp[i-2] + nums[i])`.

## Pseudocode
```
function robLinear(nums, start, end):
    prev1 = 0, prev2 = 0
    for i in start..end:
        current = max(nums[i] + prev2, prev1)
        prev2 = prev1, prev1 = current
    return prev1

function robCircular(nums, n):
    if n == 1: return nums[0]
    return max(robLinear(nums, 0, n-2), robLinear(nums, 1, n-1))
```

## C Program
```c
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
```

## Sample Input
```
nums = [2,3,2]
nums = [1,2,3,1]
```

## Sample Output
```
Test 1 Output: 3
Test 2 Output: 4
```

## Dry Run / Manual Calculation
For [2,3,2]: excludeLast → rob [2,3] → best = 3. excludeFirst → rob [3,2] → best = 3. Max = 3. ✔
For [1,2,3,1]: excludeLast → rob [1,2,3] → best = 4 (1+3). excludeFirst → rob [2,3,1] → best = 3. Max = 4. ✔

## Explanation
By splitting the circular problem into two overlapping linear ranges that together cover every valid non-adjacent selection (never picking both endpoints), the maximum of the two sub-solutions gives the correct global answer.

## Time Complexity
O(n) — two linear passes, each O(n).

## Space Complexity
O(1) — only a constant number of variables are tracked per pass.

## Result
The program correctly computed 3 and 4 for the given circular test cases.

## Conclusion
Decomposing a circular constraint into two linear DP sub-problems is a reusable technique for "circular array" variants of classic DP problems.

## Viva Questions and Answers
1. **Q: Why can't we directly apply the linear House Robber DP to a circular arrangement?**
   A: Because in a circle, the first and last houses are adjacent, which the linear DP doesn't account for.
2. **Q: How is the circular constraint handled here?**
   A: By solving two linear sub-problems — one excluding the first house, one excluding the last — and taking the maximum.
3. **Q: What is the time complexity of the overall circular solution?**
   A: O(n), since two O(n) linear passes are performed.
4. **Q: What is the base case when n == 1?**
   A: Return nums[0] directly, since there's no adjacency conflict with only one house.
5. **Q: What recurrence does `robLinear` use?**
   A: dp[i] = max(dp[i-1], dp[i-2] + nums[i]).

---

# Experiment 13 – Climbing Stairs

## File Name
`exp13_climbing_stairs.c`

## Aim
To find the number of distinct ways to climb n stairs, taking either 1 or 2 steps at a time.

## Objective
To recognize and apply the Fibonacci recurrence pattern in a Dynamic Programming context.

## Theory
To reach step n, the last move was either a 1-step from step n-1, or a 2-step from step n-2. So the total ways to reach step n is the sum of ways to reach step n-1 and step n-2 — identical to the Fibonacci recurrence. This can be computed bottom-up with only two variables tracking the previous two results.

## Algorithm
1. If n ≤ 2, return n directly (base cases: 1 way for n=1, 2 ways for n=2).
2. Otherwise, iteratively compute `current = prev1 + prev2` from i=3 to n, shifting `prev1`/`prev2` forward each time.
3. Return the final `prev1`.

## Pseudocode
```
function climbStairs(n):
    if n <= 2: return n
    prev2 = 1, prev1 = 2
    for i in 3..n:
        current = prev1 + prev2
        prev2 = prev1, prev1 = current
    return prev1
```

## C Program
```c
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
```

## Sample Input
```
n = 4
n = 3
```

## Sample Output
```
Test 1 Output: 5
Test 2 Output: 3
```

## Dry Run / Manual Calculation
n=4: prev2=1(n=1), prev1=2(n=2). i=3: current=2+1=3(n=3). prev2=2, prev1=3. i=4: current=3+2=5(n=4). Result: 5. ✔

## Explanation
This is the Fibonacci sequence shifted by one index; using only two rolling variables avoids the O(n) space of a full DP array.

## Time Complexity
O(n).

## Space Complexity
O(1).

## Result
The program correctly returned 5 and 3 ways for n=4 and n=3 respectively.

## Conclusion
Recognizing recurrence patterns like Fibonacci allows converting what looks like a combinatorial/recursive problem into an efficient O(n) time, O(1) space iterative solution.

## Viva Questions and Answers
1. **Q: Why does this problem follow the Fibonacci recurrence?**
   A: Because the last step taken to reach stair n is either 1 step from n-1 or 2 steps from n-2, so ways(n) = ways(n-1) + ways(n-2).
2. **Q: What are the base cases and why?**
   A: ways(1)=1 and ways(2)=2, since there's only one way to climb 1 stair and two ways (1+1 or 2) to climb 2 stairs.
3. **Q: Why is only O(1) space needed instead of a full array?**
   A: Because each new value only depends on the previous two values, which can be tracked with two rolling variables.
4. **Q: What is the time complexity of the iterative solution?**
   A: O(n).
5. **Q: Could this be solved recursively without memoization? What's the downside?**
   A: Yes, but naive recursion recomputes overlapping subproblems, giving exponential O(2^n) time — much worse than the O(n) iterative DP.

---

# Experiment 14 – Unique Paths

## File Name
`exp14_unique_paths.c`

## Aim
To count the number of unique paths a robot can take from the top-left to the bottom-right corner of an m×n grid, moving only right or down.

## Objective
To apply 2D Dynamic Programming to a grid path-counting problem.

## Theory
The number of ways to reach any cell (i,j) equals the sum of ways to reach the cell above it (i-1,j) and the cell to its left (i,j-1), since those are the only two cells from which (i,j) can be reached. Cells in the first row or first column have exactly one way to be reached (a straight line of moves), forming the base case.

## Algorithm
1. Set `dp[0][j] = 1` for all j (first row) and `dp[i][0] = 1` for all i (first column).
2. For each other cell (i,j): `dp[i][j] = dp[i-1][j] + dp[i][j-1]`.
3. Return `dp[m-1][n-1]`.

## Pseudocode
```
function uniquePaths(m, n):
    for i in 0..m-1:
        for j in 0..n-1:
            if i==0 or j==0: dp[i][j] = 1
            else: dp[i][j] = dp[i-1][j] + dp[i][j-1]
    return dp[m-1][n-1]
```

## C Program
```c
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
```

## Sample Input
```
m=7, n=3
m=3, n=2
```

## Sample Output
```
Test 1 Output: 28
Test 2 Output: 3
```

## Dry Run / Manual Calculation
For m=3,n=2: dp[0][*]=1,1; dp[*][0]=1,1,1. dp[1][1]=dp[0][1]+dp[1][0]=1+1=2. dp[2][1]=dp[1][1]+dp[2][0]=2+1=3. Result: 3. ✔

## Explanation
This is mathematically equivalent to choosing (m-1) "down" moves among (m-1)+(n-1) total moves, i.e. C(m+n-2, m-1), which the DP table computes without needing factorials directly.

## Time Complexity
O(m × n) — every cell of the grid is computed once.

## Space Complexity
O(m × n) for the DP table (can be reduced to O(n) using a 1D rolling array).

## Result
The program correctly computed 28 and 3 unique paths for the given grid dimensions.

## Conclusion
Grid-based path counting is a classic 2D DP pattern, directly connected to combinatorics (binomial coefficients).

## Viva Questions and Answers
1. **Q: Why does the first row and first column have exactly 1 path each?**
   A: Because reaching any cell in the first row/column requires moving only in a single direction (right-only or down-only) with no choice involved.
2. **Q: What recurrence relation is used?**
   A: dp[i][j] = dp[i-1][j] + dp[i][j-1].
3. **Q: Is there a closed-form mathematical formula for this problem?**
   A: Yes, C(m+n-2, m-1), the binomial coefficient counting arrangements of down/right moves.
4. **Q: Can the space complexity be reduced?**
   A: Yes, to O(n) using a single 1D array updated row by row, since each row only depends on the previous row.
5. **Q: What is the time complexity of the DP solution?**
   A: O(m × n).


---

# Experiment 15 – Positions of Large Groups

## File Name
`exp15_large_groups.c`

## Aim
To find all intervals of consecutive repeated-character groups (of length ≥ 3) in a given string.

## Objective
To practice single-pass string scanning to identify and report contiguous groups.

## Theory
A "group" is a maximal run of the same character. By scanning the string once and tracking where each run starts and ends, any run of length ≥ 3 ("large group") can be reported as a `[start, end]` interval. Since we scan left to right, intervals are naturally produced in increasing order of start index.

## Algorithm
1. Set `i = 0`.
2. While `i < n`:
   a. Set `j = i`; advance `j` while `s[j] == s[i]`.
   b. The group spans `[i, j-1]`. If its length (`j-i`) ≥ 3, record the interval.
   c. Set `i = j` to continue from the next group.
3. Return all recorded intervals.

## Pseudocode
```
function findLargeGroups(s):
    i = 0
    result = []
    while i < length(s):
        j = i
        while j < length(s) and s[j] == s[i]: j++
        if j - i >= 3: result.append([i, j-1])
        i = j
    return result
```

## C Program
```c
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
```

## Sample Input
```
s = "abbxxxxzzy"
s = "abc"
```

## Sample Output
```
Output: [[3,6]]
Output: []
```

## Dry Run / Manual Calculation
For "abbxxxxzzy": groups are "a"[0,0], "bb"[1,2], "xxxx"[3,6], "zz"[7,8], "y"[9,9]. Only "xxxx" has length ≥3 → [[3,6]]. ✔

## Explanation
Because each character is visited exactly once across the outer and inner while loops combined (the inner loop's total iterations across the whole run equal n), the algorithm remains linear despite the nested loop structure.

## Time Complexity
O(n) — each character is examined exactly once overall.

## Space Complexity
O(1) extra space (excluding the space needed to store the output intervals).

## Result
The program correctly identified [[3,6]] and [] for the two test strings.

## Conclusion
Single-pass group detection is an efficient and simple technique for identifying consecutive runs in strings, applicable to run-length encoding and similar problems.

## Viva Questions and Answers
1. **Q: What defines a "large group" in this problem?**
   A: A maximal run of the same character with length 3 or more.
2. **Q: Why is the overall time complexity O(n) despite the nested while loops?**
   A: Because the inner loop's pointer `j` never resets backward — across the whole string, `j` advances at most n times in total.
3. **Q: How are group intervals represented?**
   A: As [start, end] pairs of 0-indexed positions, inclusive on both ends.
4. **Q: Are the resulting intervals guaranteed to be sorted by start index?**
   A: Yes, since the string is scanned left to right in order.
5. **Q: What happens if the string has no large groups?**
   A: An empty result list is returned, as shown in Test 2 ("abc").

---

# Experiment 16 – Game of Life

## File Name
`exp16_game_of_life.c`

## Aim
To compute the next generation of Conway's Game of Life for a given m×n board.

## Objective
To apply neighbor-counting logic and simultaneous state updates using a snapshot/copy technique.

## Theory
Each cell's next state depends on its 8 neighbors' *current* (not yet updated) states. To apply all updates "simultaneously" as the rules require, the program reads neighbor counts from an unmodified copy of the board while writing results into the original board, preventing already-updated cells from affecting other cells' calculations in the same generation.

## Algorithm
1. Copy the current board into a temporary array.
2. For each cell (r,c):
   a. Count live neighbors using the copy.
   b. If cell is live: dies if neighbors < 2 or > 3; otherwise stays alive.
   c. If cell is dead: becomes alive if exactly 3 live neighbors.
3. Update the original board with the new states.

## Pseudocode
```
function gameOfLife(board, m, n):
    copy = duplicate(board)
    for r in 0..m-1:
        for c in 0..n-1:
            liveNeighbors = countLiveNeighbors(copy, r, c)
            if copy[r][c] == 1:
                if liveNeighbors < 2 or liveNeighbors > 3: board[r][c] = 0
            else:
                if liveNeighbors == 3: board[r][c] = 1
```

## C Program
```c
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
```

## Sample Input
```
board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
board = [[1,1],[1,0]]
```

## Sample Output
```
Test 1 Output: [0,0,0],[1,0,1],[0,1,1],[0,1,0]
Test 2 Output: [1,1],[1,1]
```

## Dry Run / Manual Calculation
For board2 [[1,1],[1,0]]: cell(0,0)=1 has neighbors (0,1)=1,(1,0)=1,(1,1)=0 → 2 live neighbors → survives (stays 1). cell(1,1)=0 has neighbors (0,0)=1,(0,1)=1,(1,0)=1 → 3 live neighbors → becomes alive. Result: [[1,1],[1,1]]. ✔

## Explanation
Using an unmodified `copy` for neighbor lookups ensures the "simultaneous" update rule is honored — without it, cells updated early in the scan would corrupt neighbor counts for cells processed later in the same pass.

## Time Complexity
O(m × n) — each cell's 8 neighbors are checked once, a constant-time operation per cell.

## Space Complexity
O(m × n) for the temporary copy of the board.

## Result
The program correctly computed the next generation for both test boards.

## Conclusion
Simultaneous cellular automaton updates require decoupling "read" state from "write" state, typically via a snapshot copy — a pattern broadly useful in simulation problems.

## Viva Questions and Answers
1. **Q: Why is a copy of the board needed instead of updating in place?**
   A: Because updating in place would let already-changed cells influence neighbor counts for cells processed later in the same generation, violating the "simultaneous update" rule.
2. **Q: How many neighbors does an interior cell have?**
   A: 8 (all cells horizontally, vertically, and diagonally adjacent).
3. **Q: What are the four rules of Conway's Game of Life?**
   A: Under-population (die if <2 live neighbors), survival (live if 2-3 live neighbors), over-population (die if >3), and reproduction (dead cell becomes alive with exactly 3 live neighbors).
4. **Q: What is the time complexity of computing one generation?**
   A: O(m × n), since each of the m×n cells does O(1) neighbor-counting work.
5. **Q: Who devised the Game of Life?**
   A: The British mathematician John Horton Conway, in 1970.

---

# Experiment 17 – Champagne Tower

## File Name
`exp17_champagne_tower.c`

## Aim
To determine how full a specific glass is in a pyramid of champagne glasses after pouring a given number of cups into the top.

## Objective
To model liquid overflow propagation through a triangular grid using Dynamic Programming.

## Theory
Each glass can hold at most 1 cup. Any amount poured beyond 1 cup overflows equally to the two glasses directly below it (left and right). By tracking the *total* amount that has flowed into each glass (which may exceed 1), and propagating the excess (`amount - 1`) split in half to the next row, we can compute the fill level of any glass. The final displayed fill level is capped between 0 and 1.

## Algorithm
1. Set `dp[0][0] = poured` (all champagne starts at the top glass).
2. For each row `r` from 0 to queryRow-1:
   a. For each glass `c` in that row, if `dp[r][c] > 1`, compute overflow `(dp[r][c]-1)/2`.
   b. Add that overflow to `dp[r+1][c]` and `dp[r+1][c+1]`.
3. Return `dp[queryRow][queryGlass]`, clamped to the range [0, 1].

## Pseudocode
```
function champagneTower(poured, queryRow, queryGlass):
    dp[0][0] = poured
    for r in 0..queryRow-1:
        for c in 0..r:
            if dp[r][c] > 1:
                overflow = (dp[r][c]-1)/2
                dp[r+1][c] += overflow
                dp[r+1][c+1] += overflow
    return clamp(dp[queryRow][queryGlass], 0, 1)
```

## C Program
```c
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
```

## Sample Input
```
poured=1, query_row=1, query_glass=1
poured=2, query_row=1, query_glass=1
```

## Sample Output
```
Test 1 Output: 0.00000
Test 2 Output: 0.50000
```

## Dry Run / Manual Calculation
For poured=2: dp[0][0]=2. Overflow = (2-1)/2 = 0.5. dp[1][0] += 0.5, dp[1][1] += 0.5. Query (1,1) = 0.5. ✔

## Explanation
Tracking the *total inflow* (which can exceed 1) rather than clamping at every step simplifies the propagation logic; clamping is only applied at the very end when reporting the queried glass's fill level.

## Time Complexity
O(queryRow²) — proportional to the number of glasses processed up to the queried row (triangular number).

## Space Complexity
O(ROWS²) for the DP table as implemented (can be reduced to O(queryRow²) or even O(queryRow) with a 1D rolling array).

## Result
The program correctly computed fill levels of 0.00000 and 0.50000 for the two test cases.

## Conclusion
Modeling "excess propagation" with unclamped running totals, then clamping only at output time, is a clean way to simulate overflow-based physical systems with DP.

## Viva Questions and Answers
1. **Q: Why can dp[r][c] exceed 1.0 during computation even though a glass can only hold 1 cup?**
   A: dp[r][c] tracks the *total inflow* into that glass, not its physical capacity; only the excess above 1.0 overflows, but the running total is kept unclamped for correct downstream calculations, and clamped only when reporting the final answer.
2. **Q: How is overflow distributed to the row below?**
   A: Equally split — half the excess goes to the glass directly below-left, half to below-right.
2. **Q: What is the time complexity of this DP approach?**
   A: O(queryRow²), proportional to the triangular number of glasses processed.
4. **Q: What does clamping the final result achieve?**
   A: It ensures the reported fill level correctly reflects a real glass, which can be at most completely full (1.0) or empty (0.0).
5. **Q: Why is a 2D DP table a natural fit for this pyramid structure?**
   A: Because the pyramid itself is naturally indexed by row and position-within-row, matching a 2D triangular array directly.

---

# Master File – all_app.c

## Purpose
Compiles and runs all 17 experiment programs sequentially, printing the experiment number/name before each run, and a SUCCESS/FAILED status after each. Execution continues even if one experiment fails, and a final summary is printed.

## C Program
```c
/*
 * all_app.c - Master Runner for DAA Lab
 * ===========================================
 * Compiles and runs every experiment .c file in this folder, one
 * after another, printing the experiment number/name before each
 * run and a SUCCESS/FAILED status after it. Execution continues
 * even if one experiment fails to compile or crashes. A final
 * summary is printed at the end.
 *
 * Compile:  gcc -o all_app all_app.c
 * Run:      ./all_app
 *
 * NOTE: This runner uses system() calls to invoke gcc and each
 * compiled binary. All experiment .c files must be present in the
 * same directory as all_app.c / all_app.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *id;       // Experiment number, e.g. "1"
    const char *name;     // Experiment name
    const char *source;   // Source .c filename (without extension)
} Experiment;

Experiment experiments[] = {
    {"1",  "First Palindromic String",                 "exp1_palindrome"},
    {"2",  "Count of Elements Existing in Other Array", "exp2_array_intersection_count"},
    {"3",  "Sum of Squares of Distinct Counts",         "exp3_sum_squares_distinct_subarrays"},
    {"4",  "Count Pairs Divisible by K",                "exp4_pairs_divisible_by_k"},
    {"5",  "Find Maximum Element (Linear Scan)",        "exp5_max_element_linear"},
    {"6",  "Sort Then Find Maximum",                    "exp6_sort_then_max"},
    {"7",  "Unique Elements from a List",                "exp7_unique_elements"},
    {"8",  "Bubble Sort",                                "exp8_bubble_sort"},
    {"9",  "Binary Search",                              "exp9_binary_search"},
    {"10", "Sort Without Built-ins (Heap Sort)",         "exp10_sort_no_builtin"},
    {"11", "Out of Boundary Paths (Ball in Grid)",       "exp11_ball_out_of_grid"},
    {"12", "House Robber II (Circular)",                 "exp12_house_robber_circular"},
    {"13", "Climbing Stairs",                             "exp13_climbing_stairs"},
    {"14", "Unique Paths",                                "exp14_unique_paths"},
    {"15", "Positions of Large Groups",                  "exp15_large_groups"},
    {"16", "Game of Life",                                "exp16_game_of_life"},
    {"17", "Champagne Tower",                             "exp17_champagne_tower"}
};

int main() {
    // Line-buffer stdout so our printf() headers interleave correctly
    // with the output of each child process launched via system().
    setvbuf(stdout, NULL, _IOLBF, 0);

    int total = sizeof(experiments) / sizeof(experiments[0]);
    int successCount = 0, failCount = 0;

    for (int i = 0; i < total; i++) {
        char compileCmd[256];
        char runCmd[256];

        printf("===================================\n");
        printf("RUNNING EXPERIMENT %s - %s\n", experiments[i].id, experiments[i].name);
        printf("===================================\n");
        fflush(stdout);

        // Build and execute compile command: gcc -o exp<id> exp<id>.c
        snprintf(compileCmd, sizeof(compileCmd),
                 "gcc -o %s %s.c 2>/dev/null",
                 experiments[i].source, experiments[i].source);

        int compileStatus = system(compileCmd);

        if (compileStatus != 0) {
            printf("STATUS : FAILED (compilation error)\n\n");
            fflush(stdout);
            failCount++;
            continue;
        }

        // Build and execute run command: ./exp<id>
        snprintf(runCmd, sizeof(runCmd), "./%s", experiments[i].source);
        fflush(stdout);
        int runStatus = system(runCmd);

        if (runStatus == 0) {
            printf("STATUS : SUCCESS\n\n");
            successCount++;
        } else {
            printf("STATUS : FAILED (runtime error)\n\n");
            failCount++;
        }
        fflush(stdout);
    }

    printf("===================================\n");
    printf("ALL EXPERIMENTS COMPLETED\n");
    printf("===================================\n");
    printf("Total Experiments : %d\n", total);
    printf("Successful         : %d\n", successCount);
    printf("Failed             : %d\n", failCount);

    return 0;
}
```

## Verified Actual Output (abridged)
```
===================================
RUNNING EXPERIMENT 1 - First Palindromic String
===================================
Test 1 Output: ada
Test 2 Output: racecar
STATUS : SUCCESS

===================================
RUNNING EXPERIMENT 2 - Count of Elements Existing in Other Array
===================================
Test 1 Output: [2,1]
Test 2 Output: [3,4]
STATUS : SUCCESS

... (experiments 3-16 follow the same pattern) ...

===================================
RUNNING EXPERIMENT 17 - Champagne Tower
===================================
Test 1 Output: 0.00000
Test 2 Output: 0.50000
STATUS : SUCCESS

===================================
ALL EXPERIMENTS COMPLETED
===================================
Total Experiments : 17
Successful         : 17
Failed             : 0
```
All 17 experiments compiled and ran successfully with 0 failures, confirmed by actual execution.

---

# Folder Structure

```
DAA_LAB/
├── exp1_palindrome.c
├── exp2_array_intersection_count.c
├── exp3_sum_squares_distinct_subarrays.c
├── exp4_pairs_divisible_by_k.c
├── exp5_max_element_linear.c
├── exp6_sort_then_max.c
├── exp7_unique_elements.c
├── exp8_bubble_sort.c
├── exp9_binary_search.c
├── exp10_sort_no_builtin.c
├── exp11_ball_out_of_grid.c
├── exp12_house_robber_circular.c
├── exp13_climbing_stairs.c
├── exp14_unique_paths.c
├── exp15_large_groups.c
├── exp16_game_of_life.c
├── exp17_champagne_tower.c
└── all_app.c
```

# GCC Compile Commands (Individual Experiments)

```bash
gcc -o exp1_palindrome exp1_palindrome.c
gcc -o exp2_array_intersection_count exp2_array_intersection_count.c
gcc -o exp3_sum_squares_distinct_subarrays exp3_sum_squares_distinct_subarrays.c
gcc -o exp4_pairs_divisible_by_k exp4_pairs_divisible_by_k.c
gcc -o exp5_max_element_linear exp5_max_element_linear.c
gcc -o exp6_sort_then_max exp6_sort_then_max.c
gcc -o exp7_unique_elements exp7_unique_elements.c
gcc -o exp8_bubble_sort exp8_bubble_sort.c
gcc -o exp9_binary_search exp9_binary_search.c
gcc -o exp10_sort_no_builtin exp10_sort_no_builtin.c
gcc -o exp11_ball_out_of_grid exp11_ball_out_of_grid.c
gcc -o exp12_house_robber_circular exp12_house_robber_circular.c
gcc -o exp13_climbing_stairs exp13_climbing_stairs.c
gcc -o exp14_unique_paths exp14_unique_paths.c
gcc -o exp15_large_groups exp15_large_groups.c
gcc -o exp16_game_of_life exp16_game_of_life.c
gcc -o exp17_champagne_tower exp17_champagne_tower.c
```

Run any individual experiment with, e.g.: `./exp1_palindrome`

# Compile and Run the Master File

```bash
gcc -o all_app all_app.c
./all_app
```

# Experiment Summary Table

| Experiment No | Experiment Name | File Name |
| --- | --- | --- |
| 1 | First Palindromic String | exp1_palindrome.c |
| 2 | Count of Elements Existing in Other Array | exp2_array_intersection_count.c |
| 3 | Sum of Squares of Distinct Counts | exp3_sum_squares_distinct_subarrays.c |
| 4 | Count Pairs Divisible by K | exp4_pairs_divisible_by_k.c |
| 5 | Find Maximum Element (Linear Scan) | exp5_max_element_linear.c |
| 6 | Sort Then Find Maximum | exp6_sort_then_max.c |
| 7 | Unique Elements from a List | exp7_unique_elements.c |
| 8 | Bubble Sort | exp8_bubble_sort.c |
| 9 | Binary Search | exp9_binary_search.c |
| 10 | Sort Without Built-ins (Heap Sort) | exp10_sort_no_builtin.c |
| 11 | Out of Boundary Paths (Ball in Grid) | exp11_ball_out_of_grid.c |
| 12 | House Robber II (Circular) | exp12_house_robber_circular.c |
| 13 | Climbing Stairs | exp13_climbing_stairs.c |
| 14 | Unique Paths | exp14_unique_paths.c |
| 15 | Positions of Large Groups | exp15_large_groups.c |
| 16 | Game of Life | exp16_game_of_life.c |
| 17 | Champagne Tower | exp17_champagne_tower.c |

