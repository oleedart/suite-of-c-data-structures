/*
 * Author: Oscar Lee
 * Date: 4/25/2020
 * Purpose: This program counts the number of times a integer key is inserted.
 */

#include "counters.h"
#include "memory.h"

//Local type
typedef struct counternode {
    int key;
    int count;
    struct counternode *next;
} counternode_t;

//Global type
typedef struct counters {
    struct counternode *head;
} counters_t;

//Not visible outside this file
static counternode_t *counternode_new(int key, int count);

//create a new counter
counters_t *counters_new(void) {
    counters_t *ctrs = (counters_t *) count_malloc(sizeof(counters_t));

    //check if we were able to assign memory
    if (ctrs == NULL) {
        return NULL;
    } else {
        ctrs->head = NULL;
        return ctrs;
    }
}

//add a counter
int counters_add(counters_t *ctrs, const int key) {

    //check if ctrs is not null and key is greater than 1
    if (ctrs != NULL && key >= 0) {
        counternode_t *new = counternode_new(key, 1);
        if (new != NULL) {
            if (ctrs->head == NULL) {
                //If this is the very first item in the list, set the head of the list to the new item and exit.
                ctrs->head = new;
                return ctrs->head->count;
            } else {

                bool found = false;

                for (counternode_t *node = ctrs->head; node != NULL; node = node->next) {
                    if (node->key == key) {
                        node->count++;
                        count_free(new);
                        found = true;
                        return node->count;
                    }
                }

                if (!found) {
                    for (counternode_t *node = ctrs->head; node != NULL; node = node->next) {

                        new->next = ctrs->head;
                        ctrs->head = new;
                        return node->count;
                    }
                }
            }
        }
    }
    return 0;

}

/**************** counternode_new ****************/
/* Allocate and initialize a counternode */
// the 'static' modifier means this function is not visible
// outside this file
static counternode_t *counternode_new(const int key, int count) {

    //create a new node
    counternode_t *node = (counternode_t *) count_malloc(sizeof(counternode_t));
    if (node != NULL) {
        //Assign this node values
        node->key = key;
        node->count = count;
        node->next = NULL;
        return node;
    }
    return NULL;

}

//get a counter and return the number of occurrences of that key
int counters_get(counters_t *ctrs, const int key) {

    if (ctrs != NULL && key >= 0) {
        for (counternode_t *node = ctrs->head; node != NULL; node = node->next) {
            if (node->key == key) {
                return node->count;
            }
        }
    }
    return 0;

}

//set the number of key occurrences to be a certain count
bool counters_set(counters_t *ctrs, const int key, const int count) {

    if (ctrs != NULL && key >= 0 && count >= 0) {

        bool found = false;

        //Loop through nodes and if we find the key
        for (counternode_t *node = ctrs->head; node != NULL; node = node->next) {
            if (node->key == key) {
                node->count = count;
                found = true;
                return true;
            }
        }
        if (!found) {
            //Go to end of linked list and add with count
            counternode_t *new = counternode_new(key, count);
            if (new != NULL) {
                for (counternode_t *node = ctrs->head; node != NULL; node = node->next) {
                    if (node->next == NULL) {
                        new->next = ctrs->head;
                        ctrs->head = new;
                        return true;
                    }
                }
            }

        }
    }

    return false;
}

//Print the entire linked list of counter nodes
void counters_print(counters_t *ctrs, FILE *fp) {
    if (fp != NULL) {
        if (ctrs != NULL) {
            fputc('{', fp);
            //Loop through each node
            for (counternode_t *node = ctrs->head; node != NULL; node = node->next) {
                fprintf(fp, "%d", node->key);
                fputc(':', fp);
                fprintf(fp, "%d", node->count);

                //selectively add comma
                if (node->next != NULL) {
                    fputc(',', fp);
                }
            }
            fputs("}\n", fp);
        } else {
            fputs("(null)", fp);
        }
    }
}

//Iterate through the linked list, and return argument, key, and count.
void counters_iterate(counters_t *ctrs, void *arg, void (*itemfunc)(void *arg, const int key, const int count)) {
    if (ctrs != NULL && itemfunc != NULL) {
        for (counternode_t *node = ctrs->head; node != NULL; node = node->next) {
            (*itemfunc)(arg, node->key, node->count);
        }
    }
}

//Delete and free the memory of the nodes. Frees the counter itself.
void counters_delete(counters_t *ctrs) {
    if (ctrs != NULL) {
        for (counternode_t *node = ctrs->head; node != NULL;) {
            counternode_t *next = node->next;
            count_free(node);
            node = next;
        }
        count_free(ctrs);
    }
}