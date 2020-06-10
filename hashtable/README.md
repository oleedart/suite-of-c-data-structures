# CS50 Lab 3
## Oscar, CS50 Spring 2020
###### Note: This README is heavily influenced by Professor Kotz's `bag.c` README and create goes to him for much of the language present in this document. 

### Hashtable
From CS50's webpage -
A hashtable is a set of (key,item) pairs. It acts just like a set, but is far more efficient for large collections.

### Usage

The *hashtable* module, defined in `hashtable.h` and implemented in `hashtable.c`, implements a set of `const char *` keys and `void *` 
items, and exports the following functions through `hashtable.h`:

```c
    /* Create a new (empty) hashtable. */
    hashtable_t *hashtable_new(const int num_slots);
    
    /* Insert item, identified by key (string), into the given hashtable. Returns true if succeeds */
    bool hashtable_insert(hashtable_t *ht, const char *key, void *item);
    
    /* Return the item associated with the given key.*/
    void *hashtable_find(hashtable_t *ht, const char *key);

    /* Print the whole table; provide the output file and func to print each item.*/
    void hashtable_print(hashtable_t *ht, FILE *fp, 
                         void (*itemprint)(FILE *fp, const char *key, void *item));
    
    /* Iterate over all items in the table; in undefined order.*/
    void hashtable_iterate(hashtable_t *ht, void *arg,
                           void (*itemfunc)(void *arg, const char *key, void *item) );
    
    /* Delete hashtable, calling a delete function on each item.*/
    void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) );
    

```

### Implementation

We implement this hashtable as an array of sets
The *hashtable* itself is represented as a `struct hashtable` containing a pointer array of sets.

The pointer array points to sets, with a defined number of sets created based on user input.

To insert a new item in the hashtable, we find the key's hashcode and insert the `key` and `item` into its respective set.

To extract an item from the hashtable, we use the key to find it's hashcode and pull it from a set.
Of course, if the set is empty, we return NULL instead.

The `hashtable_print` method prints a little syntax around the sets, and between items, but mostly calls the `itemprint` function on each item by scanning the sets. Calls the print function on set aswell.

The `hashtable_iterate` method calls the `itemfunc` function on each item by scanning and calling the sets.

The `hashtable_delete` method calls the `itemdelete` function on each item by scanning and calling delete on the sets. It frees sets as it proceeds.
It concludes by freeing the `struct hashtable`.

### Assumptions

No assumptions beyond those that are clear from the spec.

As with set *hashtable* allows for broad implementation and have a `void` item which allows for different variables to be used. However, 
it is challenging to test when using different variable at the same time.



### Compilation

To compile, simply `make hashtable.o`.

To test, simply `make test`.
To get a test file of test output, run the command `make test &> testing.out`
