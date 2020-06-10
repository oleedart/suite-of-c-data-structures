/*
 * Author: Oscar Lee
 * Date: 4/25/2020
 * Purpose: This program creates a set which stores key item pairs
 */

#include <string.h>
#include "set.h"
#include "memory.h"

//local type
typedef struct setnode {
    const char *key;
    void *item;
    struct setnode *next;
} setnode_t;

//Global type
typedef struct set {
    struct setnode *head;
} set_t;

static setnode_t *setnode_new(const char *key, void *item);

//create a new set
set_t *set_new(void) {
    set_t *set = (set_t *) count_malloc(sizeof(set_t));
    if(set == NULL) {
        return NULL;
    } else {
        set->head = NULL;
        return set;
    }
}

//Create a new node for the set
static setnode_t *setnode_new(const char *key, void *item) {
    setnode_t *setnode = (setnode_t *) count_malloc(sizeof(setnode_t));
    if(setnode == NULL) {
        return NULL;
    } else {
        //assign values to the node
        setnode->key = key;
        setnode->item = item;
        setnode->next = NULL;
        return setnode;
    }
}

bool set_insert(set_t *set, const char *key, void *item) {
    //check if any parameter is equal to null
    if(set != NULL && key != NULL && item != NULL) {
        //create a copy of key so that the user can do something else with their key on their end.
        char *keycopy = (char *) count_malloc(sizeof(key));

        if(keycopy == NULL) {
            free(keycopy);
            return false;
        }
        strcpy(keycopy, key);

        setnode_t *setnode = setnode_new(keycopy, item);
        if(setnode != NULL && keycopy != NULL) {
            if (set->head != NULL) {
                //check if key exists
                for (setnode_t *node = set->head; node != NULL; node = node->next) {

                    if (strcmp(node->key, keycopy) == 0) {

                        //replace
                        void *holder = node->item;
                        node->item = item;
                        count_free(holder);
                        count_free((void *) keycopy);

                        //Free the setnode
                        count_free(setnode);
                        return true;
                    }

                    //if it is the at the end, and not found, add the key
                    if (node->next == NULL) {
                        setnode->next = set->head;
                        set->head = setnode;
                        return true;
                    }
                }
            } else {
                set->head = setnode;
                return true;
            }
        } else {
            //clear setnode and keycopy
            free(setnode);
            free(keycopy);
            return false;
        }
    }
    return false;
}

//Find a item, given a key
void *set_find(set_t *set, const char *key) {

    //check if set and key are not null
    if(set != NULL && key != NULL) {
        for (setnode_t *node = set->head; node != NULL; node = node->next) {
            if(strcmp(node->key, key) == 0) {
                return node->item;
            }
        }
    }
    return NULL;

}

//print the entire set using a user defined print function
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item) ) {
    if(fp != NULL) {
        if(set != NULL) {
            fputc('{', fp);
            for(setnode_t *node = set->head; node != NULL; node = node->next) {
                if(itemprint != NULL) {
                    (*itemprint)(fp, node->key, node->item);
                    fputc(',', fp);
                }
            }
            fputs("}\n", fp);
        } else {
            fputs("(null)", fp);
        }
    }
}

//Iterate through using a user defined function
void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item) ) {
    if(set != NULL) {
        if(itemfunc != NULL) {
            for(setnode_t *node = set->head; node != NULL; node = node->next) {
                (*itemfunc)(arg, node->key, node->item);
            }
        }
    }
}

//Delete and free
void set_delete(set_t *set, void (*itemdelete)(void *item) ) {
    if(set != NULL) {
        for(setnode_t *node = set->head; node != NULL;) {
            if(itemdelete != NULL) {
                //Free key and item
                (*itemdelete)((void *)node->key);
                (*itemdelete)(node->item);
            }

            //free node
            setnode_t *next = node->next;
            count_free(node);
            node = next;

        }
        //free the set
        count_free(set);
    }
}