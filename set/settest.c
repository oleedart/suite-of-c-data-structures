/*
 * Author: Oscar Lee
 * Date: 4/25/2020
 * Purpose: This program tests set.c with various methods to check all of the modules functions.
 * Usage: Read input form stdin and prints output to stdout
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "set.h"
#include "readlinep.h"

void print_string_item(FILE *fp, const char *key, void *item);
void print_int_item(FILE *fp, const char *key, void *item);
void itemdelete(void* item);
void create_string_keypairs(set_t *set);
static void item_count (void *arg, const char *key ,void *item);

int main() {

    printf("This is the test for set.c\n\n");

    //create a new set
    set_t *set = set_new();
    int count = 0;

    if(set == NULL) {
        fprintf(stderr, "set_new failed\n");
        return 1;
    }

    printf("Testing set_insert\n\n");
    create_string_keypairs(set);

    printf("Count: ");
    set_iterate(set, &count, item_count);
    printf("%d\n\n", count);

    //test Nulls
    set_insert(NULL, NULL, NULL);
    set_insert(set, NULL, NULL);
    set_insert(NULL, "caleb", "rows");

    printf("The set: \n");
    set_print(set, stdout, print_string_item);
    printf("\n");

    char *key_to_find = malloc(sizeof(char) * 4);
    strcpy(key_to_find, "Gus");

    char *replacement = malloc(sizeof(char) * 1024);
    strcpy(replacement, "Is on my team");

    printf("Testing an insert of a duplicate key %s (using set_find).\n", key_to_find);
    printf("Item before:\n");
    printf("\t%s\n", (char *) set_find(set, key_to_find));
    set_insert(set, key_to_find, replacement);
    printf("Item after:\n");
    printf("\t%s\n\n", (char *) set_find(set, key_to_find));
    free(key_to_find);

    printf("Reprint the set:\n");
    set_print(set, stdout, print_string_item);
    printf("\n");

    printf("Deleting the set...\n");
    set_delete(set, itemdelete);

    return 0;
}

//Inserts a string key and string item based off of a file of input.
void create_string_keypairs(set_t *set) {
    while (!feof(stdin)) {

        char *line = readlinep();
        if (line != NULL) {

            //split each line by :
            char delim[] = ":";

            //Create pointers for the key and item from the file
            char *ptr1 = strtok(line, delim);
            char *ptr2 = malloc(sizeof(char) * 1024);
            strcpy(ptr2, strtok(NULL, delim));

            //Insert into set
            set_insert(set, ptr1, ptr2);

            //Free those char * bc we are done with them now (Copy created inside set)
            free(ptr1);


        } else {
            printf("Line is NULL\n");
        }

    }
}

//Used to count the items in the set
static void item_count (void *arg, const char *key ,void *item) {

    int *num = arg;
    if (num != NULL) {
        (*num)++;
    }
}

//delete the item passed in as a param
void itemdelete(void* item)
{
    if (item != NULL) {
        free(item);
    }
}

//print a string option
void print_string_item(FILE *fp, const char *key, void *item) {
    //char *formater = strcat(key, (char *) ": ");

    char *text = item;
    if (text == NULL) {
        fprintf(fp, "(null)");
    }
    else {
        fprintf(fp, " %s: %s", key, text);
    }
}

//print a int option, if given.
void print_int_item(FILE *fp, const char *key, void *item) {
    if(item != NULL) {
        int value = *((int*)item);
        fprintf(fp, " %s: %d", key, value);
    } else {
        fprintf(fp, "(NULL)");
    }

}