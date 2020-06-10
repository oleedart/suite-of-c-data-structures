# CS50 Lab 3
## Oscar, CS50 Spring 2020
###### Note: This README is heavily influenced by Professor Kotz's `bag.c` README and create goes to him for much of the language present in this document. 

### Set
From CS50's webpage -
A set maintains an unordered collection of (key,item) pairs; any given key can only occur in the set once. It starts 
out empty and grows as the caller inserts new (key,item) pairs. The caller can retrieve items by asking for their key, 
but cannot remove or update pairs. Items are distinguished by their key.

### Usage

The *set* module, defined in `set.h` and implemented in `set.c`, implements a set of `const char *` keys and `void *` 
items, and exports the following functions through `set.h`:

```c
    /* Create a new (empty) set. */
    set_t *set_new(void);
    
   
    /* Insert item, identified by a key (string), into the given set.*/
    bool set_insert(set_t *set, const char *key, void *item);

    /* Return the item associated with the given key.*/
    void *set_find(set_t *set, const char *key);
    
    /* Print the whole set; provide the output file and func to print each item.*/
    void set_print(set_t *set, FILE *fp, 
                   void (*itemprint)(FILE *fp, const char *key, void *item) );
    
    /* Iterate over the set, calling a function on each item.*/
    void set_iterate(set_t *set, void *arg,
                     void (*itemfunc)(void *arg, const char *key, void *item) );
   
    /* Delete set, calling a delete function on each item.*/
    void set_delete(set_t *set, void (*itemdelete)(void *item) );
```

### Implementation

We implement this set as a linked list.
The *set* itself is represented as a `struct set` containing a pointer to the head of the list; the head pointer is NULL when the set is empty.

Each node in the list is a `struct setnode`, a type defined internally to the module.
Each setnode includes a pointer to the `void *item` and a pointer to the next setnode on the list.

To insert a new item in the set we create a new setnode to hold the `item`, and insert it at the head of the list.

To extract an item from the set, we use the key to find the item in the list.
Of course, if the list is empty, we return NULL instead.

The `set_print` method prints a little syntax around the list, and between items, but mostly calls the `itemprint` function on each item by scanning the linked list.

The `set_iterate` method calls the `itemfunc` function on each item by scanning the linked list.

The `set_delete` method calls the `itemdelete` function on each item by scanning the linked list, freeing setnodes as it proceeds.
It concludes by freeing the `struct set`.

### Assumptions

No assumptions beyond those that are clear from the spec.

*Set* allows for broad implementation and have a `void` item which allows for different variables to be used. However, 
it is challenging to test when using different variable at the same time.



### Compilation

To compile, simply `make set.o`.

To test, simply `make test`.
To get a test file of test output, run the command `make test &> testing.out`
