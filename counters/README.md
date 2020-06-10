# CS50 Lab 3
## Oscar, CS50 Spring 2020
###### Note: This README is heavily influenced by Professor Kotz's `bag.c` README and create goes to him for much of the language present in this document. 


### Counter
From CS50's webpage -
A *counter* set is a set of counters, each distinguished by an integer key. It’s a set - each key can only occur once in
the set - and it tracks a counter for each key. It starts empty. Each time counters_add is called on a given key, the
corresponding counter is incremented. The current counter value can be retrieved by asking for the relevant key.

### Usage

The *counters* module, defined in `counters.h` and implemented in `counters.c`, implements a key of `const int`, and exports the following functions through `counters.h`:

```c
/* Create a new (empty) counter structure. */
counters_t *counters_new(void);

/* Increment the counter indicated by key.*/
int counters_add(counters_t *ctrs, const int key);

/* Return current value of counter associated with the given key.*/
int counters_get(counters_t *ctrs, const int key);

/* Set the current value of counter associated with the given key.*/
bool counters_set(counters_t *ctrs, const int key, const int count);

/* Print all counters; provide the output file.*/
void counters_print(counters_t *ctrs, FILE *fp);


/* Iterate over all counters in the set. */
void counters_iterate(counters_t *ctrs, void *arg, 
                      void (*itemfunc)(void *arg, 
                                       const int key, const int count));

/* Delete the whole counterset. */
void counters_delete(counters_t *ctrs);

```

### Implementation

We implement this counter as a linked list.
The *counters* itself is represented as a `struct counters` containing a pointer to the head of the list; the head pointer is NULL when the counter is empty.

Each node in the list is a `struct counternode`, a type defined internally to the module.
Each counternode includes a pointer to the `int key`, `int count`, and a pointer to the next counternode on the list.

To insert a new item in the counter, we give a key.

To extract an item from the counters, we take in the key and return the key's count.
Of course, if the list is empty, we return NULL instead.

The `counters_print` method prints a little syntax around the list, and between items, but mostly calls the `itemprint` function on each item by scanning the linked list.

The `counters_iterate` method calls the `itemfunc` function on each item by scanning the linked list.

The `counters_delete` method calls the `itemdelete` function on each item by scanning the linked list, freeing counternodes as it proceeds.
It concludes by freeing the `struct counters`.

### Assumptions

One assumption made is that only key's that are integers will be accepted. Any others will throw an error. 

### Compilation

To compile, simply `make counter.o`.

To test, simply `make test`.
To get a test file of test output, run the command `make test &> counterstest.out`
