/*
 * Author: Oscar Lee
 * Date: 4/25/2020
 * Purpose: This program creates a hashtable which stores key item pairs in a efficient manner
 */

#include <string.h>
#include "hashtable.h"
#include "set.h"
#include "jhash.h"
#include "memory.h"

/**************** global types ****************/
typedef struct hashtable {
    set_t **setp;
    int num_slots;

} hashtable_t;

//create a new hashtable
hashtable_t *hashtable_new(const int num_slots) {
    hashtable_t *table = (hashtable_t *) count_malloc(sizeof(hashtable_t));
    if (table != NULL) {
        if (num_slots > 0) {
            table->num_slots = num_slots;
            table->setp = count_calloc(num_slots, sizeof(struct set_t *));
            //loop through all the pointers and set their sets to NULL
            for (int i = 0; i < num_slots; i++) {
                table->setp[i] = set_new();
            }
            return table;
        }
        return NULL;
    }
    return NULL;
}

//insert into the hashtable
bool hashtable_insert(hashtable_t *ht, const char *key, void *item) {
    if (ht != NULL) {
        if (key != NULL && item != NULL) {

            //Create a key copy
            char *keycopy = (char *) count_malloc(sizeof(key));
            if (keycopy == NULL) {
                free(keycopy);
                return false;
            }
            strcpy(keycopy, key);

            //get the index to insert
            unsigned long hash = JenkinsHash(keycopy, ht->num_slots);

            //insert into the set.
            if (ht->setp[hash] != NULL) {
                set_insert(ht->setp[hash], keycopy, item);
                free(keycopy);
                return true;
            }
        }
    }
    return false;
}

//Find and return and item based on a key
void *hashtable_find(hashtable_t *ht, const char *key) {

    if (ht != NULL && key != NULL) {

        //Find the address of where this key is hashed
        unsigned long hash = JenkinsHash(key, ht->num_slots);

        //Find the key in set_find
        return set_find(ht->setp[hash], key);

    }
    return NULL;
}

//print the hashtable. Relies mostly on calling the set print function to print each set out.
void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (fp == NULL) {
        return;
    }
    if (ht != NULL) {
        for (int i = 0; i < ht->num_slots; i++) {
            if (itemprint != NULL && ht->setp[i] != NULL) {
                //call set's print function
                set_print(ht->setp[i], fp, itemprint);
            }
        }
        fputc('\n', fp);
    } else {
        fputs("(NULL)", fp);
    }
}

//iterate through the hashtable and sets. Utilizes set's iterate function to do most of the heavy lifting
void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (ht != NULL) {
        if (itemfunc != NULL) {

            //loop through pointer array
            for (int i = 0; i < ht->num_slots; i++) {

                //call set_iterate to iterate through the set
                set_iterate(ht->setp[i], arg, itemfunc);

            }
        }
    }
}

//delete the hashtable and sets. Utilizes set's delete function to do most of the heavy lifting to delete the sets
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)) {
    if (ht != NULL) {
        for (int i = 0; i < ht->num_slots; i++) {
            if (itemdelete != NULL) {
                set_delete(ht->setp[i], itemdelete);
            }

        }
        //free the pointer array and the hashtable.
        count_free(ht->setp);
        count_free(ht);
    }
}