/*
 * Author: Oscar Lee
 * Date: 4/25/2020
 * Purpose: This program tests hashtable.c with various methods to check all of the modules functions.
 * Usage: Read input form stdin and prints output to stdout
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "readlinep.h"

void print_string_item(FILE *fp, const char *key, void *item);

void print_int_item(FILE *fp, const char *key, void *item);

void itemdelete(void *item);

void create_string_keypairs(hashtable_t *table);

void create_int_keypairs(hashtable_t *table);

static void item_count(void *arg, const char *key, void *item);

int main() {

    //Create a new 6 item hashtable
    hashtable_t *table = hashtable_new(6);
    int count = 0;

    if (table == NULL) {
        fprintf(stderr, "hashtable_new failed\n");
        return 1;
    }

    printf("Testing hashtable_insert for strings\n\n");

    //Calls a helper method to read from an input file of strings.
    create_string_keypairs(table);

    printf("Count: ");
    hashtable_iterate(table, &count, item_count);
    printf("%d\n\n", count);

    //test Nulls
    hashtable_insert(NULL, NULL, NULL);
    hashtable_insert(table, NULL, NULL);
    hashtable_insert(NULL, "caleb", "rows");

    printf("The hashtable: \n");
    hashtable_print(table, stdout, print_string_item);
    printf("\n");

    char *key_to_find = malloc(sizeof(char) * 4);
    strcpy(key_to_find, "Gus");

    char *replacement = malloc(sizeof(char) * 1024);
    strcpy(replacement, "Is on my team");

    printf("Testing an insert of a duplicate key %s (using hashtable_find).\n", key_to_find);
    printf("Item before:\n");
    printf("\t%s\n", (char *) hashtable_find(table, key_to_find));
    hashtable_insert(table, key_to_find, replacement);
    printf("Item after:\n");
    printf("\t%s\n\n", (char *) hashtable_find(table, key_to_find));
    free(key_to_find);

    printf("Reprint the hashtable:\n");
    hashtable_print(table, stdout, print_string_item);
    printf("\n");

    printf("Deleting the hashtable...\n");
    hashtable_delete(table, itemdelete);

    return 0;

}

//Possible further implementation with int's as items. NOT implemented with this example
void create_int_keypairs(hashtable_t *table) {

    void *ptr0 = malloc(sizeof(int));
    *((int *) ptr0) = 5;
    hashtable_insert(table, "oscar", ptr0);

    void *ptr1 = malloc(sizeof(int));
    *((int *) ptr1) = 7;
    hashtable_insert(table, "faith", ptr1);

    void *ptr2 = malloc(sizeof(int));
    *((int *) ptr2) = 2;
    hashtable_insert(table, "mom", ptr2);

    void *ptr3 = malloc(sizeof(int));
    *((int *) ptr3) = 6;
    hashtable_insert(table, "dad", ptr3);

    void *ptr4 = malloc(sizeof(int));
    *((int *) ptr4) = 23;
    hashtable_insert(table, "bea", ptr4);

    void *ptr5 = malloc(sizeof(int));
    *((int *) ptr5) = 435;
    hashtable_insert(table, "broskie", ptr5);

    void *ptr6 = malloc(sizeof(int));
    *((int *) ptr6) = 3;
    hashtable_insert(table, "tim", ptr6);

    void *ptr7 = malloc(sizeof(int));
    *((int *) ptr7) = 60;
    hashtable_insert(table, "oscar", ptr7);

}

//Helper method to create key and item pairs from a input file.
void create_string_keypairs(hashtable_t *table) {
    while (!feof(stdin)) {

        char *line = readlinep();
        if (line != NULL) {

            /*
             * Explanation of parsing process:
             * Here, we will take a line of input separated by a ':'.
             * We will then create pointers to the first half and second half of the split string.
             */

            //split each line by :
            char delim[] = ":";

            //Create pointers for the key and item from the file
            char *ptr1 = strtok(line, delim);
            char *ptr2 = malloc(sizeof(char) * 1024);
            strcpy(ptr2, strtok(NULL, delim));

            //Insert into table
            hashtable_insert(table, ptr1, ptr2);

            //Free those char * bc we are done with them now (Copy created inside hashtable)
            free(ptr1);


        } else {
            printf("Line is NULL\n");
        }
    }
}

//Used to count the items in the hashtable.
static void item_count(void *arg, const char *key, void *item) {

    int *num = arg;
    if (num != NULL) {
        (*num)++;
    }
}

//Print the string item.
void print_string_item(FILE *fp, const char *key, void *item) {
    char *text = item;
    if (text != NULL) {
        fprintf(fp, " %s: %s", key, text);
    } else {
        fprintf(fp, "(NULL)");
    }
}

//print an int item.
void print_int_item(FILE *fp, const char *key, void *item) {
    if (item != NULL) {
        int value = *((int *) item);
        fprintf(fp, " %s: %d", key, value);
    } else {
        fprintf(fp, "(NULL)");
    }
}

//Delete a item.
void itemdelete(void *item) {
    if (item != NULL) {
        free(item);
    }
}