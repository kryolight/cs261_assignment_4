/*
 * This file contains the implementation of a priority queue.
 *
 * You must complete the implementations of these functions:
 *   pq_insert()
 *   pq_first()
 *   pq_remove_first()
 */

#include <stdlib.h>
#include <assert.h>

#include "dynarray.h"
#include "pq.h"

// This is the initial capacity that will be allocated for the heap.
#define INITIAL_HEAP_CAPACITY 16

/*
 * This is the definition of the structure we will use to represent the
 * priority queue.  It contains only a dynamic array, which will be used to
 * store the heap underlying the priority queue.
 */
struct pq {
  struct dynarray* heap;
};


/*
 * This is an auxiliary structure that we'll use to represent a single element
 * in the priority queue.  It contains two fields:
 *
 *   priority - the priority value assigned to the item
 *   item - the pointer to the data item represented by this element
 *
 * Both of these will come directly from the corresponding values passed to
 * pq_insert().
 */
struct pq_elem {
  int priority;
  void* item;
};


/*
 * This function allocates and initializes a new priority queue.
 *
 * You should not modify this function.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  assert(pq);
  pq->heap = dynarray_create(INITIAL_HEAP_CAPACITY);
  return pq;
}


/*
 * This function frees the memory associated with a priority queue.
 *
 * You should not modify this function.
 */
void pq_free(struct pq* pq) {
  assert(pq);
  while (!pq_isempty(pq)) {
    pq_remove_first(pq);
  }
  dynarray_free(pq->heap);
  free(pq);
}

/*
 * This function returns 1 if the given priority queue is empty or 0
 * otherwise.
 *
 * You should not modify this function.
 */
int pq_isempty(struct pq* pq) {
  assert(pq);
  return dynarray_size(pq->heap) == 0;
}


/*
 * This function inserts a new item with a specified priority into a priority
 * queue.
 *
 * You should complete the implementation of this function.  The first part
 * is done for, where a new element is created to be placed into the dynamic
 * array underlying the priority queue.
 */
void pq_insert(struct pq* pq, void* item, int priority) {
  assert(pq);
  /* FIXME: Complete this function */
  /*
   * Restore the heap so that it has the property that every node's priority
   * value is less than the priority values of its children.  This can be
   * done by "percolating" the newly added element up in the heap array.  To
   * perform the percolation, you will have to compare the priority values of
   * the struct pq_elems in the heap array (i.e. by comparing the
   * elem->priority values).
   */
  struct pq_elem *new_pq_elem = malloc(sizeof(struct pq_elem));
  assert(new_pq_elem);
  new_pq_elem->priority = priority;
  new_pq_elem->item = item;

  dynarray_insert(pq->heap, -1, new_pq_elem);

  int size = dynarray_size(pq->heap);
  int index = size - 1;
  int parent_index = (index - 1) / 2;

  while(index != 0)
  {
    if(((struct pq_elem *)dynarray_get(pq->heap, index))->priority < ((struct pq_elem *)dynarray_get(pq->heap, parent_index))->priority)
    {
      struct pq_elem *parent_temp = dynarray_get(pq->heap, parent_index);
      struct pq_elem *index_temp = dynarray_get(pq->heap, index);
      dynarray_set(pq->heap, parent_index, index_temp);
      dynarray_set(pq->heap, index, parent_temp);
    }
    index = (index - 1) / 2;
    parent_index = (index - 1) / 2;
  }
}


/*
 * This function returns the first (highest-priority) item from a priority
 * queue without removing it.
 *
 * You should complete the implementation of this function.
 */
void* pq_first(struct pq* pq) {
  assert(pq);
  assert(dynarray_size(pq->heap) > 0);
  /* FIXME: Complete this function */
  return(((struct pq_elem *)dynarray_get(pq->heap, 0))->item);
}


/*
 * This function removes the first (highest-priority) element from a priority
 * queue and returns its value.
 *
 * You should complete this function.
 */
void* pq_remove_first(struct pq* pq) {
  assert(pq);
  assert(dynarray_size(pq->heap) > 0);

  /* FIXME: Complete this function */
  /*
   * Determine what index in the heap array corresponds to the highest-priority
   * element (i.e. the one with the lowest priority value), and store the
   * value there in first_elem.
   */
  void* retval = ((struct pq_elem *)dynarray_get(pq->heap, 0))->item;
  /*
   * Replace the highest-priority element with the appropriate one from within
   * the heap array.  Remove that replacement element from the array after
   * copying its value to the location of the old highest-priority element..
   */
  free(dynarray_get(pq->heap, 0));
  struct pq_elem *last_pq_elem = dynarray_get(pq->heap, -1);
  dynarray_set(pq->heap, 0, last_pq_elem);
  dynarray_remove(pq->heap, -1);
  /*
   * Restore the heap so that it has the property that every node's priority
   * value is less than the priority values of its children.  This can be
   * done by "percolating" the element that replaced the highest-priority
   * element down in the heap array.  To perform the percolation, you will
   * have to compare the priority values of the struct pq_elems in the heap
   * array (i.e. by comparing the elem->priority values).  It may be helpful
   * to write a helper function to accomplish this percolation down.
   */
  int index = 0;
  int left_child = 0;
  int right_child = 0;
  int size = dynarray_size(pq->heap);
  int min_child = 0;
  int min_child_priority = 0;
  int index_priority = 0;
  int done = 0;
  struct pq_elem *temp;
  if(dynarray_size(pq->heap) != 0)
  {
    left_child = index * 2 + 1;
    right_child = index * 2 + 2;
    while(!(left_child >= size && right_child >= size) && done == 0)
    {
      if (left_child >= size)
      {
        min_child = right_child;
      } 
      else if (right_child >= size)
      {
        min_child = left_child;
      }
      else if (((struct pq_elem *)dynarray_get(pq->heap, left_child))->priority < ((struct pq_elem *)dynarray_get(pq->heap, right_child))->priority)
      {
        min_child = left_child;
      }
      else
      {
        min_child = right_child;
      }
      index_priority = ((struct pq_elem *)dynarray_get(pq->heap, index))->priority;
      min_child_priority = ((struct pq_elem *)dynarray_get(pq->heap, min_child))->priority;
      if(min_child_priority < index_priority)
      {
        temp = dynarray_get(pq->heap, index);
        dynarray_set(pq->heap, index, dynarray_get(pq->heap, min_child));
        dynarray_set(pq->heap, min_child, temp);
      } else {
        done = 1;
      }
      index = min_child;
      left_child = index * 2 + 1;
      right_child = index * 2 +2;
    }
  }
  /*
   * Return the extracted item, if the element taken out of the priority
   * queue is not NULL.
   */
  return retval;
}
