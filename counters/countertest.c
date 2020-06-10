/*
 * Author: Oscar Lee
 * Date: 4/25/2020
 * Purpose: This program tests counters.c with various methods to check all of the modules functions.
 * Usage: Read input form stdin and prints output to stdout
 */

#include <stdio.h>
#include "readlinep.h"
#include "counters.h"

static void keycount(void *arg, const int key, const int count);

static void itemcount(void *arg, const int key, const int count);

int main() {

    counters_t *cptr;
    int num_keys = 0;
    int num_items = 0;

    printf("This is the test output for various tests of counters.c\n\n");

    //create a new counter
    cptr = counters_new();
    if (cptr == NULL) {
        fprintf(stderr, "counters_new failed\n");
        return 1;
    }

    //Adding data from stdin and assigning it to a key, adding it to the counters.
    printf("Adding data to keys:\n\n");
    while (!feof(stdin)) {
        int key = 0;
        fscanf(stdin, "%d", &key);
        counters_add(cptr, key);
    }

    printf("Number of keys: ");
    counters_iterate(cptr, &num_keys, keycount);
    printf("%d\n", num_keys);

    printf("Number of items: ");
    counters_iterate(cptr, &num_items, itemcount);
    printf("%d\n\n", num_items);

    // test with null counter, null item
    counters_add(NULL, 0);

    printf("The counters:\n");
    counters_print(cptr, stdout);
    printf("\n");

    printf("Getting count of key 1: ");
    printf("%d\n", counters_get(cptr, 1));

    printf("Getting count of key 2: ");
    printf("%d\n", counters_get(cptr, 2));

    printf("Getting count of key 8: ");
    printf("%d\n\n", counters_get(cptr, 8));

    printf("Testing counters_set for key 1\n");
    if (counters_set(cptr, 1, 40) == 1) {
        printf("Set succeeded, key %d is now %d\n\n", 1, counters_get(cptr, 1));
    }

    printf("Reprinting the counters\n");
    counters_print(cptr, stdout);
    printf("\n");

    printf("deleting the counters...\n");
    counters_delete(cptr);

    return 0;
}

//Used to count the number of unique keys
static void keycount(void *arg, const int key, const int count) {

    int *num_keys = arg;
    if (num_keys != NULL) {
        (*num_keys)++;
    }

}

//Used to count the number of certain keys.
static void itemcount(void *arg, const int key, const int count) {

    int *num_items = arg;
    if (num_items != NULL) {
        (*num_items) += count;
    }

}