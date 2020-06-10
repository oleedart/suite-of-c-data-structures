/* 
 * bagtest.c - test program for CS50 bag module
 *
 * usage: read user names from stdin

 * CS50, January 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bag.h"
#include "readlinep.h"

void nameprint(FILE *fp, void *item);
void namedelete(void* item);
static void itemcount(void *arg, void *item);

/* **************************************** */
int main() 
{
  bag_t *bag;
  int namecount = 0;

  // create a bag
  bag = bag_new();
  if (bag == NULL) {
    fprintf(stderr, "bag_new failed\n");
    return 1;
  }

  printf("testing bag_insert:\n");
  // read names and ages from stdin
  while (!feof(stdin)) {
    char *name = readlinep();
    if (name != NULL) {
      bag_insert(bag, name);
    }
  }

  printf("Count: ");
  bag_iterate(bag, &namecount, itemcount);
  printf("%d\n", namecount);  

  // test with null bag, null item
  bag_insert(NULL, NULL);
  bag_insert(bag, NULL);

  printf("The bag:\n");
  bag_print(bag, stdout, nameprint);
  printf("\n");

  printf("delete the bag...\n");
  bag_delete(bag, namedelete);

  return 0;
}


/* count the non-null items in the bag.
 * note here we don't care what kind of item is in bag.
 */
static void itemcount(void *arg, void *item)
{
  int *nitems = arg;

  if (nitems != NULL && item != NULL)
    (*nitems)++;
}

// print a name 
void nameprint(FILE *fp, void *item)
{
  char *name = item; 
  if (name == NULL) {
    fprintf(fp, "(null)");
  }
  else {
    fprintf(fp, "\"%s\"", name); 
  }
}

// delete a name 
void namedelete(void* item)
{
  if (item != NULL) {
    free(item);   
  }
}


