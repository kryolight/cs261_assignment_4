# Assignment 5

The goal of this assignment is to work with priority queues.  A secondary goal is to start diving into data structures at a lower level than we have been, implementing some of the essential operations of the priority queue from scratch.

You are provided here with a dynamic array implementation (`dynarray.h` and `dynarray.c`) and the template for an implementation of a priority queue (`pq.h` and `pq.c`).  You should use the dynamic array implementation to implement a minimizing binary heap underlying the priority queue.

## Functions to implement

You must fill out the functions below in the priority queue implementation in `pq.c`.  When you are implementing these functions **you should not break the encapsulation of the dynamic array.**  That is, you should not access the internal details of the dynamic array but should instead use the functions comprising the dynamic array's public interface.

  * `void pq_insert(struct pq* pq, void* item, int priority)`

    This function inserts a given piece of data (`item`) into the priority queue with the specified priority (`priority`).  Importantly, **lower values of `priority` correspond to items with higher priority relative to other items.**  For example, an item with `priority` 0 should be returned from the priority queue before an item with `priority` 5.

    Implementing this function entails finding the correct location in the heap array in which to insert the new element, inserting it there, and then making sure the minimizing heap property (that every element's value is less than the values of its children) is maintained.

    To implement this function, you will be introduced to the new concept of a `void` pointer (`void*`).  This is simply a generic pointer that can point to a memory address of any type.  The dynamic array implementation stores `void` pointers.  We will use these to hold pointers to an auxiliary structure (`struct pq_elem`) representing a single element in the priority queue, including its priority value and its associated data.

  * `void* pq_first(struct pq* pq)`

    This function simply returns the data represented by the highest-priority element in the priority queue.  To do this, you will have to figure out the location in the heap array corresponding to the highest-priority element in the priority queue and return the data represented by that element (i.e. the `item` field of the `struct pq_elem` stored at that location in the priority queue).

  * `void* pq_remove_first(struct pq* pq)`

    This function removes the highest-priority element from the priority queue and returns the data it represents.  To implement this, you will have to find the same element in the heap array you found when implementing `pq_first()`.  Here, however, you will also have to find the appropriate element to replace that element in the heap array, perform the replacement, and ensure that the minimizing heap property (that every element's value is less than the values of its children) is maintained.

## Example sequence of calls

Suppose the user made this sequence of insertions into an empty `struct pq` called `pq`:
```
pq_insert(pq, "sixteen", 16);
pq_insert(pq, "eight", 8);
pq_insert(pq, "twenty", 20);
pq_insert(pq, "four", 4);
pq_insert(pq, "twelve", 16);
```

Then suppose they ran this loop:
```
while (!pq_isempty(pq)) {
  printf("%s\n", pq_remove_first(pq));
}
```

The following should be the output of that loop:
```
four
eight
twelve
sixteen
twenty
```

## Test program

A program to test your priority queue is available in `test_pq.c`.  You can compile this using the provided `Makefile` and then run it like so:
```
make
./test_pq
```
The program will run a series of insertions and a series of removals.  After each operation, it will check to make sure the priority queue has the appropriate structure (in particular that the first element is what's expected).

## Grading criteria

Your assignment will be graded by compiling it on `flip.engr.oregonstate.edu` using the provided `Makefile`, so make sure you have tested your work under those conditions.  If you currently don't have access to `flip`, you should be able to create an ENGR account at https://teach.engr.oregonstate.edu/ (follow the link that says "Create a new account").

Some other requirements:
  * You may not change the function signatures (i.e. `void foo(int k)`).
  * You may not add or remove files.

The assignment is worth 100 points total.

  * 40 points: `pq_insert()`
  * 20 points: `pq_first()`
  * 40 points: `pq_remove_first()`
