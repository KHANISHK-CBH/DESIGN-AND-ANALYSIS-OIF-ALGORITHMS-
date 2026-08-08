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
