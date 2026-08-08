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
